set( CMAKE_CXX_STANDARD 20 )

if ( UNIX )
#    set( CMAKE_CXX_FLAGS "-pedantic -Werror -Wall -Wextra -Wdiv-by-zero -fPIC" )
#    set( CMAKE_CXX_FLAGS_RELEASE "-O3 -finline-functions -DNDEBUG" )
#    set( CMAKE_CXX_FLAGS_DEBUG "-g -fno-inline -DDEBUG" )
#    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-warnings-as-errors=*;-checks=-*,modernize-use-override")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4250")
endif ()

enable_testing()