#pragma once

#include <db/db_manager.h>
#include <grpcpp/grpcpp.h>

#include <kafka/telegram_notification_producer.hpp>
#include <user-service/alert-grpc-service.hpp>
#include <user-service/auth-grpc-service.hpp>
#include <user-service/notif-client-grpc-service.hpp>

class UserGrpcServer {
 public:
  UserGrpcServer(const std::string& grpc_uri, const int& grpc_port,
                 std::shared_ptr<DbManager> db,
                 std::shared_ptr<TelegramNotificationProducer>
                     telegram_notification_producer)
      : auth_service_(db),
        notif_service_(db),
        alert_service_(db, telegram_notification_producer) {
    std::string addr = grpc_uri + ":" + std::to_string(grpc_port);
    builder_.AddListeningPort(addr, grpc::InsecureServerCredentials());

    builder_.RegisterService(&auth_service_);
    builder_.RegisterService(&notif_service_);
    builder_.RegisterService(&alert_service_);

    server_ = std::unique_ptr(builder_.BuildAndStart());
  }

  /// @brief дождаться окончания работы gRPC сервера (пока не случиться ошибка,
  /// либо не прервут работу)
  void wait() { server_->Wait(); }

  /// @brief завершить работу сервера
  void shutdown() { server_->Shutdown(); }

  ~UserGrpcServer() { shutdown(); }

 private:
  grpc::ServerBuilder builder_;
  std::unique_ptr<grpc::Server> server_;
  AuthGrpcService auth_service_;
  NotifClientGrpcService notif_service_;
  AlertGrpcService alert_service_;
};