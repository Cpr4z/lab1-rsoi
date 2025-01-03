#include "write_awaiter.h"

//#include <boost/bind.hpp>

WriteAwaiter AsyncWrite(tcp::socket &socket, net::const_buffer buffer)
{
    return WriteAwaiter{socket, buffer};
}

bool WriteAwaiter::await_ready()
{
    return false;
}

void WriteAwaiter::await_suspend(std::coroutine_handle<> h)
{
    net::async_write(socket_, buffer_,
                             [this, h](auto ec, size_t) mutable
                             {
                                 ec_ = ec;
                                 h.resume();
                             });
}

void WriteAwaiter::await_resume()
{
    if (ec_)
    {
        throw std::system_error(ec_);
    }
}
