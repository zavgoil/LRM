#pragma once

#include <grpcpp/grpcpp.h>
#include <proto/user-service.grpc.pb.h>

#include <QObject>
#include <QQmlEngine>
#include <config/config.hpp>
#include <memory>

class AppBackend : public QObject {
  Q_OBJECT

 public:
  AppBackend(int argc, char* argv[]);

  Q_INVOKABLE void signIn(const QString& username, const QString& password);
  Q_INVOKABLE void signUp(const QString& username, const QString& password);

 private:
  Config config_;
  std::unique_ptr<user_service::AuthService::Stub> auth_service_{nullptr};
};