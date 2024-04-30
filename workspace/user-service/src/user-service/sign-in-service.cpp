#include <user-service/sign-in-service.hpp>

SignInService::SignInService(DbManager& db) : db_(db) {}

::grpc::Status SignInService::SignIn(
    ::grpc::ServerContext* context,
    const ::user_service::SignInRequest* request,
    ::user_service::SignInResponse* response) {
  std::string token = "";
  try {
    token = db_.getUuid(request->login(), request->password());
  } catch (UserNotFound const& e) {
    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "User not found");
  } catch (WrongPassword const& e) {
    return ::grpc::Status(::grpc::StatusCode::UNAUTHENTICATED,
                          "Wrong password");
  } catch (std::runtime_error const& e) {
    return ::grpc::Status(::grpc::StatusCode::INTERNAL, e.what());
  } catch (...) {
    return ::grpc::Status(::grpc::StatusCode::INTERNAL, "");
  }
  response->set_token(token);
  return ::grpc::Status(::grpc::StatusCode::OK, "");
}