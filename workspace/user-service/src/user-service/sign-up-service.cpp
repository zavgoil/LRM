#include <user-service/sign-up-service.hpp>

SignUpService::SignUpService(DbManager& db) : db_(db) {}

::grpc::Status SignUpService::SignUp(
    ::grpc::ServerContext* context,
    const ::user_service::SignUpRequest* request,
    ::user_service::SignUpResponse* response) {
  std::string token = "";
  try {
    token = db_.addUser(request->login(), request->password());
  } catch (LoginAlreadyExists const& e) {
    return ::grpc::Status(::grpc::StatusCode::ALREADY_EXISTS,
                          "Login already exists");
  } catch (TokenAlreadyExists const& e) {
    return ::grpc::Status(::grpc::StatusCode::INTERNAL, "Token already exists");
  } catch (std::runtime_error const& e) {
    return ::grpc::Status(::grpc::StatusCode::INTERNAL, e.what());
  } catch (...) {
    return ::grpc::Status(::grpc::StatusCode::INTERNAL, "");
  }

  response->set_token(token);
  return ::grpc::Status(::grpc::StatusCode::OK, "");
}