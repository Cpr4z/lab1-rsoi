#pragma once

#include "../include/network/net_asio.h"
#include "../include/request_response_support/RequestResponse.h"

class BeastResp : public IResponse
{
public:
    BeastResp() = default;
    BeastResp(const http::response<http::string_body>& resp);
    std::string GetBody() const override;
    void SetBody(const std::string& body) override;

    headers_t GetHeaders() const override;
    void SetHeaders(const headers_t& headers) override;

    network::http_code_t GetStatus() const override;
    void SetStatus(network::http_code_t status) override;

private:
    std::string m_body;
    headers_t m_headers;
    network::http_code_t m_status = network::CODE_200;

    http::response<http::string_body> m_resp;

    bool m_isFromResp = false;
};

http::response<http::string_body> MakeBeastResp(const IResponsePtr& resp);