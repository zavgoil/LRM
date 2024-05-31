#include <QDebug>
#include <app-backend/app-backend.hpp>
#include <thread>

AppBackend::AppBackend(int argc, char* argv[]) {
  config_.read(argc, argv);
  auth_service_ = std::make_unique<user_service::AuthService::Stub>(
      grpc::CreateChannel(config_.rpc_map.user_service.uri + ":" +
                              std::to_string(config_.rpc_map.user_service.port),
                          grpc::InsecureChannelCredentials()));
}

void AppBackend::signIn(const QString& username, const QString& password) {
  grpc::ClientContext context{};
  user_service::SignInRequest request{};
  user_service::SignInResponse responce{};

  request.set_login(username.toStdString());
  request.set_password(password.toStdString());

  if (auth_service_ == nullptr)
    throw std::logic_error("Auth service not inited");
  auto status = auth_service_->SignIn(&context, request, &responce);

  if (!status.ok()) {
    qDebug() << "Error " << status.error_code() << ":"
             << status.error_message();
  } else {
    qDebug() << "Success. Token - " << responce.token();
  }
}

void AppBackend::signUp(const QString& username, const QString& password) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  grpc::ClientContext context{};
  user_service::SignUpRequest request{};
  user_service::SignUpResponse responce{};

  request.set_login(username.toStdString());
  request.set_password(password.toStdString());

  if (auth_service_ == nullptr)
    throw std::logic_error("Auth service not inited");
  auto status = auth_service_->SignUp(&context, request, &responce);

  if (!status.ok()) {
    qDebug() << "Error " << status.error_code() << ":"
             << status.error_message();
  } else {
    qDebug() << "Success. Token - " << responce.token();
  }
}