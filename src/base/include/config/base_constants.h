#pragma once

#include <string>

namespace AppLiterals {
    const std::string LogFile = "LogFile";

    const std::string Server = "Server";
    const std::string Port = "Port";
    const std::string Clients = "Clients";
    const std::string ClientHost = "Host";
    const std::string ClientPort = "Port";

    const std::string DbHost = "DB_HOST";
    const std::string DbName = "DB_NAME";
    const std::string DbPort = "DB_PORT";
    const std::string DbUser = "DB_USER";
    const std::string DbUserPassword = "DB_USER_PASSWORD";

    const std::string UsedCriterions = "UsedCriterions";

    const std::string Auth = "Auth";
    const std::string JWTTokenLifeTime = "JWTTokenLifeTime";
    const std::string JWTAlgorithm = "JWTAlgorithm";
    const std::string JWTSecrete = "JWTSecrete";

//    template<size_t size>
//    [[nodiscard]] constexpr auto to_string_array(const std::string_view& sv)
//    {
//        std::array<char, size + 1> arr;
//        for (int i = 0; i <size; ++i) {
//            arr[i] = sv[i];
//        }
//        arr[size + 1] = '\0';
//        return arr;
//    }
}