#ifndef __NOTIFICATION_CLIENT_JSON_HPP__
#define __NOTIFICATION_CLIENT_JSON_HPP__

#include <proto/user-service.grpc.pb.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void to_json(json& j, const ::user_service::NotificationClient& p);
void from_json(const json& j, ::user_service::NotificationClient& p);
void to_json(json& clients_json, const ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>& clients);
void from_json(const json& json, ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>& clients);

#endif
