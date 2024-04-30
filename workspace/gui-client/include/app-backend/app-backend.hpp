#pragma once

#include <grpcpp/grpcpp.h>
#include <proto/user-service.grpc.pb.h>

#include <QObject>
#include <QQmlEngine>

class AppBackend : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
 public:
  Q_INVOKABLE void signIn(const QString& username, const QString& password);
  Q_INVOKABLE void signUp(const QString& username, const QString& password);

 private:
  user_service::SignIn::Stub sign_in_service_{grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials())};
  user_service::SignUp::Stub sign_up_service_{grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials())};
  ;
};