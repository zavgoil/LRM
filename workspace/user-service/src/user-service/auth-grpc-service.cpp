#include <user-service/auth-grpc-service.hpp>

AuthGrpcService::AuthGrpcService(DbManager& db) : db_(db) {}

::grpc::Status AuthGrpcService::SignUp(
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

::grpc::Status AuthGrpcService::SignIn(
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