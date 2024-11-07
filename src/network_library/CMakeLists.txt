project(NetworkLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED
        router/RequestHandlerContext.h
        router/router.cpp
        base/Request.h
        base/Response.h
        base/Request.cpp
        base/IResposeFactory.cpp
        base/BeastResponseFactory.h
        base/BeastResponseFactory.cpp
        base/Response.cpp
        coroutines/write_awaiter.cpp
        net.cpp
        router/RequestHandlerContext.cpp)

target_sources( ${PROJECT_NAME} PUBLIC
        coroutines/future.h
        coroutines/future.cpp
        coroutines/http_read_awaiter.h
        coroutines/http_read_awaiter.cpp
        coroutines/http_write_awaiter.h
        coroutines/http_write_awaiter.cpp
        coroutines/read_awaiter.h
        coroutines/read_awaiter.cpp

        connections/client_server_connection.cpp
        connections/client_server_connection.h
        connections/server_connection.cpp
        connections/server_connection.h

        sessions/echo_session.h
        sessions/echo_session.cpp
        sessions/http_session.h
        sessions/http_session.cpp
        sessions/http_client_server_session.h
        sessions/http_client_server_session.cpp

        include/network/IClientServerSession.h
        include/network/IConnection.h
        include/network/IServerSession.h
        include/network/net.h
        include/network/net_asio.h

        include/request_handler/IClientServerRequestHandler.h
        include/request_handler/IServerRequestHandler.h

        include/request_response_support/IResponseFactory.h
        include/request_response_support/RequestResponse.h

        include/router/IClientServerRoute.h
        include/router/IRequestHandlerContext.h
        include/router/router.h
)

#find_package(nlohmann_json 3.2.0 REQUIRED)
#find_package(yaml-cpp REQUIRED)

#include_directories(/opt/homebrew/Cellar/yaml-cpp/0.8.0/include)
#link_directories(/opt/homebrew/Cellar/yaml-cpp/0.8.0/lib)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(YAMLCPP REQUIRED yaml-cpp)
#
#include_directories(${YAMLCPP_INCLUDE_DIRS})
#link_directories(${YAMLCPP_LIBRARY_DIRS})

#include_directories(${nlohmann_json_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/base
    ${CMAKE_CURRENT_SOURCE_DIR}/connections
    ${CMAKE_CURRENT_SOURCE_DIR}/coroutines
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/router
    ${CMAKE_CURRENT_SOURCE_DIR}/sessions
)

target_include_directories( ${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${LIBPQ_INCLUDE_DIRS}
        ${LIBPQXX_INCLUDE_DIRS}
#        ${nlohmann_json_INCLUDE_DIRS}
        /opt/homebrew/Cellar/libpqxx/7.9.2/include
        /opt/homebrew/Cellar/yaml-cpp/0.8.0/include
)

target_link_libraries( ${PROJECT_NAME} PRIVATE
        base
        Boost::boost
#        /opt/homebrew/Cellar/yaml-cpp/0.8.0/lib/libyaml-cpp.dylib
#        ${YAMLCPP_LIBRARIES}
#        nlohmann_json::nlohmann_json
        ${LIBPQ_LIBRARIES}
        ${LIBPQXX_LIBRARIES}
)
