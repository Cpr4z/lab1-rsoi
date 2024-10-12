#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

using tcp = net::ip::tcp;
using error_code = boost::system::error_code;