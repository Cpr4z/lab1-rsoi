#include "client_server_connection.h"

#include "../../base/include/config/base_constants.h"
#include "../../base/include/exceptions/server_exceptions.h"
#include "../../base/include/logger/LoggerFactory.h"

#include <boost/thread.hpp>
#include <chrono>
#include <iostream>
#include <boost/smart_ptr/make_shared.hpp>


ClientServerConnection::ClientServerConnection(net::io_context &context,
                                               const IClientServerSessionCreatorPtr &creator,
                                               const IConfigPtr &config) :
                                               m_sessionCreator(creator), m_acceptor(context),
                                               m_context(context), m_config(config)
{
    m_clientSockets = connectClientSockets(m_config);
    connectServerSocket(config);
}

void ClientServerConnection::Run() {

}

void ClientServerConnection::fail(const error_code &ec, const std::string &desc)
{
    std::ostringstream oss;
    oss << "error code: " << ec.message() << " description: " << desc;
    LoggerFactory::createLogger()->logError(oss.str().c_str());

    throw ServerException(oss.str());
}

void ClientServerConnection::connectServerSocket(const IConfigPtr &config)
{
    error_code ec;

    int port = config->GetIntField({AppLiterals::Server, AppLiterals::Port});

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

std::vector<boost::shared_ptr<tcp::socket>> ClientServerConnection::connectClientSockets(const IConfigPtr &config) {
    std::vector<boost::shared_ptr<tcp::socket>> client_sockets;
    std::vector<std::string> clients = config->GetStringArray({AppLiterals::Clients});

    for (auto client : clients)
    {
        std::ostringstream oss;
        oss << "Connecting to " << client << "...";
        LoggerFactory::createLogger()->logInfo(oss.str().c_str());

        std::string host = config->GetStringField({client, AppLiterals::ClientHost});
        int port = config->GetIntField({client, AppLiterals::ClientPort});
        tcp::endpoint ep(net::ip::address::from_string(host), port);

        boost::shared_ptr<tcp::socket> client_sock = boost::make_shared<tcp::socket>(m_context);
        client_sock->connect(ep);

        client_sockets.push_back(client_sock);
        LoggerFactory::createLogger()->logInfo("Connected");
    }

    return client_sockets;
}

void ClientServerConnection::acceptNew() {
    clearExpiredConnections();

    m_acceptor.async_accept(
            [this](error_code ec, tcp::socket sock)
            {
                if (ec)
                {
                    fail(ec, "accept");
                    return;
                }
                LoggerFactory::createLogger()->logInfo("start new session");
                auto session = m_sessionCreator->CreateSession();
                auto fut = session->Run(std::move(sock), m_clientSockets);
                m_coroutineSessions.push_back(coroutine_cssession_t(session, std::move(fut)));

                acceptNew();
            });
}

void ClientServerConnection::clearExpiredConnections() {
    using namespace std::chrono_literals;

    for (size_t i = 0; i < m_coroutineSessions.size(); i++)
    {
        m_coroutineSessionEraseMutex.lock();
        if (m_coroutineSessions[i].second.wait_for(0s) == std::future_status::ready)
        {
            LoggerFactory::createLogger()->logInfo("erase session");
            m_coroutineSessions.erase(m_coroutineSessions.begin() + i);
        }
        m_coroutineSessionEraseMutex.unlock();
    }
}
