#include <notification-client/notification-client-json.hpp>
#include "util/log.hpp"

void to_json(json& j, const ::user_service::NotificationClient& p) {
    j = json{
        {"type", p.type()},
        {"data", p.data()}
    };
}

void from_json(const json& j, ::user_service::NotificationClient& p) {
    p.set_type(j.at("type"));
    p.set_data(j.at("data"));
}

void to_json(json& clients_json, const ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>& clients) {
    for(auto&client : clients)
    {
        json client_json;
        to_json(client_json, client);
        clients_json.emplace_back(client_json);
    }
}

void from_json(const json& json, ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>& clients) {
    for(auto&j: json)
    {
        ::user_service::NotificationClient client;
        from_json(j, client);
        clients.Add(std::move(client));
    }
}
