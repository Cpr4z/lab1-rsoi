#pragma once

#include <unordered_map>

#include "../include/network/net_asio.h"
#include "../include/request_response_support/RequestResponse.h"

class BeastReq : public IRequest
{
public:
    BeastReq() = default;
    BeastReq(const http::request<http::string_body>& req);
    virtual std::string GetBody() const override;
    virtual std::string GetTarget() const override;
    virtual headers_t GetHeaders() const override;
    virtual network::method_t GetMethod() const override;

    virtual void SetBody(const std::string& body) override;
    virtual void SetHeaders(const headers_t& headers) override;
    virtual void SetTarget(const std::string& target) override;
    virtual void SetMethod(const network::method_t& method) override;

private:
    http::request<http::string_body> m_request;
    bool m_isFromReq = false;
    const std::unordered_map<std::string, network::method_t> m_methodsFrom {
            {"GET", network::GET}, {"POST", network::POST}, {"DELETE", network::DELETE},{"PUT", network::PUT}, {"PATCH", network::PATCH}
    };
    std::string m_body;
    headers_t m_headers;
    std::string m_target;
    network::method_t m_method;
};

http::request<http::string_body> MakeBeastReq(const IRequestPtr& req);