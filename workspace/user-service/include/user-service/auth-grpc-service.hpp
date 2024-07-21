#pragma once

#include <db/db_manager.h>
#include <proto/user-service.grpc.pb.h>

#include <memory>

/// @brief gRPC сервис для регистрации и авторизации пользователей
class AuthGrpcService : public user_service::AuthService::Service {
 public:
  AuthGrpcService(std::shared_ptr<DbManager> db);

  /// @brief Регистрация пользователя
  /// @param context gGRPC контекст
  /// @param request запрос
  /// @param response ответ
  /// @return статус
  ::grpc::Status SignUp(::grpc::ServerContext* context,
                        const ::user_service::SignUpRequest* request,
                        ::user_service::SignUpResponse* response) override;
  
  /// @brief Авторизация пользователя
  /// @param context gGRPC контекст
  /// @param request запрос
  /// @param response ответ
  /// @return статус
  ::grpc::Status SignIn(::grpc::ServerContext* context,
                        const ::user_service::SignInRequest* request,
                        ::user_service::SignInResponse* response) override;

 private:
  std::shared_ptr<DbManager> db_;
};