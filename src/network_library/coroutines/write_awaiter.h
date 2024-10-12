#pragma once

#include <coroutine>

#include "../include/network/net_asio.h"

struct WriteAwaiter
{
    bool await_ready();

    void await_suspend(std::coroutine_handle<> h);

    void await_resume();

    tcp::socket &socket_;
    net::const_buffer buffer_ = net::const_buffer();

    std::error_code ec_ = std::error_code();
};

WriteAwaiter AsyncWrite(tcp::socket &socket, net::const_buffer buffer);