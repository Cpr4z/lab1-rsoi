#pragma once

#include "../../base/include/config/IConfig.h"
#include "../include/network/IServerSession.h"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

#include "../include/network/IConnection.h"

using coroutine_session_t = std::pair<boost::shared_ptr<IServerSession>, std::future<void>>;

class ServerConnection :
        public IConnection,
        std::enable_shared_from_this<ServerConnection>
{
public:
    ServerConnection(net::io_context& context, const IServerSessionCreatorPtr& creator, const IConfigPtr& config);

    virtual ~ServerConnection() = default;

    virtual void Run() override;

protected:
    void fail(const error_code& ec, const std::string& desc);

private:
    void acceptNew();
    void cleanExpiredConnections();

    std::vector<coroutine_session_t> m_coroutineSessions;
    std::mutex m_coroutineSessionEraseMutex;
    boost::shared_ptr<IServerSessionCreator> m_creator;
    tcp::acceptor m_acceptor;
    net::io_context& m_context;
    boost::shared_ptr<IConfig> m_config;
};

