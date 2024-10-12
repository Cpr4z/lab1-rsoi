#pragma once

#include "../include/network/IConnection.h"
#include "../../base/include/config/IConfig.h"

#include "../include/network/IClientServerSession.h"
#include "../include/network/net_asio.h"
#include <boost/shared_array.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

using coroutine_cssession_t = std::pair<boost::shared_ptr<IClientServerSession>, std::future<void>>;

class ClientServerConnection :
        public IConnection,
        public boost::enable_shared_from_this<ClientServerConnection>
{
public:
    ClientServerConnection(net::io_context& context, const IClientServerSessionCreatorPtr& creator, const IConfigPtr& config);

    virtual void Run() override;

protected:
    void fail(const error_code& ec, const std::string& desc);

private:
    void connectServerSocket(const IConfigPtr& config);
    std::vector<boost::shared_ptr<tcp::socket>> connectClientSockets(const IConfigPtr& config);
    void acceptNew();
    void clearExpiredConnections();

private:
    std::vector<coroutine_cssession_t> m_coroutineSessions;
    std::mutex m_coroutineSessionEraseMutex;
    std::vector<boost::shared_ptr<tcp::socket>> m_clientSockets;
    boost::shared_ptr<IClientServerSessionCreator> m_sessionCreator;
    tcp::acceptor m_acceptor;
    net::io_context &m_context;
    boost::shared_ptr<IConfig> m_config;

};