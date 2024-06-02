#pragma once

#include <map>
#include <string>
struct Contact{
    enum class Type { NONE, INTERNAL, EMAIL, TELEGRAM };
    const inline static std::map<Type, std::string> TypeToString = {
        {Type::INTERNAL, "Внутреннее приложение"},
        {Type::EMAIL, "Email"},
        {Type::TELEGRAM, "Телеграм"},
        };

    Type type;
    std::string data;
};
