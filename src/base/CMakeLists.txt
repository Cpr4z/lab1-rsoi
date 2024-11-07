project(base)

add_library(${PROJECT_NAME} STATIC)

target_sources( ${PROJECT_NAME} PRIVATE
        include/exceptions/base_exception.h
        include/exceptions/database_exceptions.h
        include/exceptions/logic_exceptions.h
        include/exceptions/server_exceptions.h
        include/config/IConfig.h
        include/config/config_creators.h
        include/config/base_constants.h
        include/logger/ILogger.h
        include/logger/LoggerFactory.h

        config_utils/yaml_config.h
        config_utils/yaml_config.cpp
        config_utils/config_creators.cpp

        logger/Logger.h
        logger/Logger.cpp
        logger/LoggerFactory.cpp
)

#find_package(nlohmann_json 3.2.0 REQUIRED)
#
#include_directories(${nlohmann_json_INCLUDE_DIRS})
#find_package(yaml-cpp REQUIRED)

target_compile_options(base PRIVATE -fPIC)

find_package(PkgConfig REQUIRED)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp)

include_directories(${YAMLCPP_INCLUDE_DIRS})
link_directories(${YAMLCPP_LIBRARY_DIRS})
#target_link_libraries(your_target_name PRIVATE yaml-cpp)


target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/config_utils
        ${CMAKE_CURRENT_SOURCE_DIR}/logger
        ${CMAKE_CURRENT_SOURCE_DIR}/include/config
        ${CMAKE_CURRENT_SOURCE_DIR}/include/exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/include/logger
#        ${nlohmann_json_INCLUDE_DIRS})
)

target_link_libraries( ${PROJECT_NAME} PUBLIC
        ${YAMLCPP_LIBRARIES}
#        yaml-cpp
#        nlohmann_json::nlohmann_json
        Boost::boost
        spdlog::spdlog
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)