#pragma once

#include <proto/user-service.grpc.pb.h>

#include <project-util/format/json.hpp>
#include <project-util/format/json_macro.hpp>
#include <string>
#include <vector>

struct NotificationClients : public JsonFormat<NotificationClients> {
  std::vector<std::string> internal;
  std::vector<std::string> email;

  size_t getCount() { return internal.size() + email.size(); }

  NotificationClients() = default;
  NotificationClients(::user_service::NotificationClients proto_message) {
    for (auto i : proto_message.internal()) internal.push_back(i);
    for (auto i : proto_message.email()) email.push_back(i);
  }
  ::user_service::NotificationClients* to_proto() const {
    auto proto_message = new ::user_service::NotificationClients();

    for (auto i : internal) proto_message->add_internal(i);
    for (auto i : email) proto_message->add_email(i);

    return proto_message;
  }
};
DEFINE_JSON(NotificationClients, internal, email)