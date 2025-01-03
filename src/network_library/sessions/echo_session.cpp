#include "echo_session.h"

#include <time.h>

#include <iostream>
#include <memory>

#include "../coroutines/read_awaiter.h"
#include "../coroutines/write_awaiter.h"
#include "../coroutines/future.h"

/*#include "read_awaiter.h"
#include "std_future.hpp"
#include "write_awaiter.h"*/

#define BUF_LEN 1024

std::future<void> EchoSession::Run(tcp::socket sock)
{
    char buf[BUF_LEN];

    while (true)
    {
        size_t bytes_read = co_await AsyncRead(sock, net::buffer(buf));
        std::cout << "Server get message: " << buf << std::endl;
        co_await AsyncWrite(sock, {buf, bytes_read});
        std::cout << "Server has sent message" << std::endl;
    }
}