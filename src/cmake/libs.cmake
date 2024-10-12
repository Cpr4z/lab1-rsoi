#add_library(libpqxx INTERFACE IMPORTED)
#
#set_target_properties(libpqxx PROPERTIES IMPORTED_GLOBAL TRUE)
#target_include_directories(libpqxx SYSTEM INTERFACE "/usr/include" "/usr/include/postgresql")
#if (${LIBPQXX_LINK_STATIC})
#    target_link_libraries(libpqxx INTERFACE "/usr/lib/x86_64-linux-gnu/libpq.a")
#else()
#    target_link_libraries(libpqxx INTERFACE "/usr/lib/x86_64-linux-gnu/libpq.so")
#endif ()
#
#add_library(libpqxx::pqxx ALIAS libpqxx)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

link_directories(${LIBPQ_LIBRARY_DIRS} ${LIBPQXX_LIBRARY_DIRS})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS filesystem unit_test_framework date_time REQUIRED)
#find_package(yaml-cpp REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)
#find_package(nlohmann_json 3.2.0 REQUIRED)
#find_package(jsoncpp REQUIRED)

#include_directories(${JSONCPP_INCLUDE_DIRS})
