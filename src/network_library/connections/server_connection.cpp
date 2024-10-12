#include "server_connection.h"

#include "../../base/include/config/base_constants.h"
#include "../../base/include/exceptions/server_exceptions.h"
#include "../../base/include/logger/LoggerFactory.h"

#include <boost/thread.hpp>
#include <chrono>
#include <iostream>

#include "../include/network/IServerSession.h"
#include "../coroutines/future.h"


ServerConnection::ServerConnection(net::io_context& context, const IServerSessionCreatorPtr& creator,
                                   const IConfigPtr& config) :
                                   m_creator(creator), m_acceptor(context), m_context(context), m_config(config)
{
    error_code ec;
    if (m_config)
    {
        int port = m_config->GetIntField({AppLiterals::Server, AppLiterals::Port});
        tcp::endpoint ep(net::ip::address_v4(), port);
        m_acceptor.open(ep.protocol(), ec);

        if (ec)
        {
            fail(ec, "open acceptor");
            return;
        }

        m_acceptor.set_option(net::socket_base::reuse_address(true), ec);

        if (ec)
        {
            fail(ec, "set option");
            return;
        }

        m_acceptor.bind(ep, ec);

        if (ec)
        {
            fail(ec, "bind");
            return;
        }

        m_acceptor.listen(net::socket_base::max_listen_connections, ec);

        if (ec)
        {
            fail(ec, "listen");
            return;
        }
    }
}

void ServerConnection::Run()
{
    acceptNew();
    m_context.run();
}

void ServerConnection::acceptNew()
{
    cleanExpiredConnections();

    m_acceptor.async_accept(
            [this](error_code ec, tcp::socket sock)
            {
                if (ec)
                {
                    fail(ec, "accept");
                    return;
                }
                LoggerFactory::createLogger()->logInfo("start new session");
                auto session = m_creator->CreateSession();
                auto fut = session->Run(std::move(sock));
                m_coroutineSessions.push_back(coroutine_session_t(session, std::move(fut)));

                acceptNew();
            });
}

void ServerConnection::cleanExpiredConnections()
{
    using namespace std::chrono_literals;

    for (size_t i = 0; i < m_coroutineSessions.size(); i++)
    {
        m_coroutineSessionEraseMutex.lock();
        if (m_coroutineSessions[i].second.wait_for(0s) == std::future_status::ready)
        {
            m_coroutineSessions.erase(m_coroutineSessions.begin() + i);
            LoggerFactory::createLogger()->logInfo("erase session");
        }
        m_coroutineSessionEraseMutex.unlock();
    }
}

void ServerConnection::fail(const error_code &ec, const std::string &desc)
{
    std::ostringstream oss;
    oss << "error code: " << ec.message() << " description: " << desc;
    LoggerFactory::createLogger()->logError(oss.str().c_str());

    throw ServerException(oss.str());
}
