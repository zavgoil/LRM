#pragma once

#include <grpcpp/grpcpp.h>
#include <proto/user-service.grpc.pb.h>

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <config/config.hpp>
#include <functional>
#include <memory>
#include <thread>

#include "app-backend/contact-list-model.hpp"

class AppBackend : public QObject {
  Q_OBJECT

 public:
  AppBackend(int argc, char* argv[], ContactListModel* contact_list_model);
  ~AppBackend() {
    if (worker_.joinable()) worker_.join();
  }

  Q_INVOKABLE void signIn(const QString& username, const QString& password);
  Q_INVOKABLE void signUp(const QString& username, const QString& password);

  Q_INVOKABLE void getContacts();
  Q_INVOKABLE void setContacts();

  // std::vector<Contact> getContacts();
  // void setContacts(std::vector<Contact> contacts);

 signals:
  void openLoadingPopup();
  void closeLoadingPopup();
  void showError(QString error_message);

  void signUpDone();
  void signInDone();

 private:
  Config config_;
  std::string token_;
  std::thread worker_;

  ContactListModel* contact_list_model_;

  std::unique_ptr<user_service::AuthService::Stub> auth_service_{nullptr};
  std::unique_ptr<user_service::NotificationClientService::Stub>
      notif_client_service_{nullptr};
};
