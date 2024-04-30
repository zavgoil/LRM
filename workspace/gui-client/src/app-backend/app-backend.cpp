#include <QDebug>
#include <app-backend.hpp>

void AppBackend::signIn(const QString& username, const QString& password) {
  grpc::ClientContext context{};
  user_service::SignInRequest request{};
  user_service::SignInResponse responce{};

  request.set_login(username.toStdString());
  request.set_password(password.toStdString());

  auto status = sign_in_service_.SignIn(&context, request, &responce);

  if (!status.ok()) {
    qDebug() << "Error " << status.error_code() << ":"
             << status.error_message();
  } else {
    qDebug() << "Success. Token - " << responce.token();
  }
}

void AppBackend::signUp(const QString& username, const QString& password) {
  grpc::ClientContext context{};
  user_service::SignUpRequest request{};
  user_service::SignUpResponse responce{};

  request.set_login(username.toStdString());
  request.set_password(password.toStdString());

  auto status = sign_up_service_.SignUp(&context, request, &responce);

  if (!status.ok()) {
    qDebug() << "Error " << status.error_code() << ":"
             << status.error_message();
  } else {
    qDebug() << "Success. Token - " << responce.token();
  }
}