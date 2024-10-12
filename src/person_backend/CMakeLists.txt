project(person_backend)

add_executable(${PROJECT_NAME}
        unit_tests/PersonFacadeTest.h
        unit_tests/PersonsRepositoryMock.h
        unit_tests/PersonFacadeTest.cpp
        unit_tests/main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_sources( ${PROJECT_NAME} PRIVATE
        main.cpp

        data_transfer_object/PersonDTO.h
        data_transfer_object/PersonDTO.cpp
        data_transfer_object/PersonPatchDTO.h
        data_transfer_object/PersonPostDTO.cpp
        data_transfer_object/PersonPostDTO.h

        utils/PersonsGateway.h
        utils/PersonsGateway.cpp
        utils/PersonsServerHandler.h
        utils/PersonServerHandler.cpp

        person_facade/person_facade.h
        person_facade/person_facade.cpp

        database_manager/IPersonsRepository.h
        database_manager/PostgresPersonsRepository.h
        database_manager/PostgresPersonsRepository.cpp
        database_manager/PersonsDA.h
        database_manager/PersonsDA.cpp
)

add_library(backend_person
        main.cpp

        data_transfer_object/PersonDTO.h
        data_transfer_object/PersonDTO.cpp
        data_transfer_object/PersonPatchDTO.h
        data_transfer_object/PersonPostDTO.cpp
        data_transfer_object/PersonPostDTO.h

        utils/PersonsGateway.h
        utils/PersonsGateway.cpp
        utils/PersonsServerHandler.h
        utils/PersonServerHandler.cpp

        person_facade/person_facade.h
        person_facade/person_facade.cpp

        database_manager/IPersonsRepository.h
        database_manager/PostgresPersonsRepository.h
        database_manager/PostgresPersonsRepository.cpp
        database_manager/PersonsDA.h
        database_manager/PersonsDA.cpp
)

set(BOOST_ROOT "/usr/local/include/boost")
set(BOOST_INCLUDE_DIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARY_DIR "${BOOST_ROOT}/lib")

find_package(Boost REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

find_package(nlohmann_json 3.11.3 REQUIRED)

include_directories("/opt/homebrew/Cellar/nlohmann-json/3.11.3/include")

find_path(NLOHMANN_JSON_INCLUDE_DIR nlohmann/json.hpp PATHS /opt/homebrew/Cellar/nlohmann-json/3.11.3/include)

if(NLOHMANN_JSON_INCLUDE_DIR)
    include_directories(${NLOHMANN_JSON_INCLUDE_DIR})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/data_transfer_object
        ${CMAKE_CURRENT_SOURCE_DIR}/database_manager
        ${CMAKE_CURRENT_SOURCE_DIR}/person_facade
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        ${LIBPQ_INCLUDE_DIRS}
        ${LIBPQXX_INCLUDE_DIRS}
        /opt/homebrew/Cellar/libpqxx/7.9.2/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    NetworkLib
    Boost::boost
    nlohmann_json::nlohmann_json
    ${LIBPQ_LIBRARIES}
    ${LIBPQXX_LIBRARIES})
