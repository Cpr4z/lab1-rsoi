#include "Request.h"

#define REQ_VERSION 11

http::request<http::string_body> MakeBeastReq(const IRequestPtr& req)
{
    std::unordered_map<network::method_t, http::verb> methods_to = {
            {network::GET,    http::verb::get},
            {network::POST,   http::verb::post},
            {network::DELETE, http::verb::delete_},
            {network::PUT,    http::verb::put},
            {network::PATCH,  http::verb::patch}
    };

    http::verb verb = http::verb::unknown;
    if (methods_to.contains(req->GetMethod()))
    {
        verb = methods_to[req->GetMethod()];
    }

    http::request<http::string_body> res(verb, req->GetTarget(), REQ_VERSION);

    for(auto header: req->GetHeaders())
    {
        res.set(header.first, header.second);
    }

    res.body() = req->GetBody();

    res.prepare_payload();

    return res;
}


BeastReq::BeastReq(const http::request <http::string_body> &req) : m_request(req), m_isFromReq(true) {

}

std::string BeastReq::GetBody() const
{
    if (m_isFromReq)
        return m_request.body();

    return m_body;
}

std::string BeastReq::GetTarget() const
{
    if (!m_isFromReq)
        return m_target;
    std::string res(m_request.target());
    return res;
}

headers_t BeastReq::GetHeaders() const
{
    if (!m_isFromReq)
        return m_headers;

    headers_t res;

    for (auto const &field : m_request)
        res[std::string(field.name_string())] = std::string(field.value());

    return res;
}

network::method_t BeastReq::GetMethod() const
{
    if (!m_isFromReq)
        return m_method;

    std::string method(m_request.method_string());

    auto it = m_methodsFrom.find(method);
    if (it != m_methodsFrom.end())
        return it->second;

    return network::UNDEFINED;
}

void BeastReq::SetBody(const std::string &body)
{
    m_body = body;
}

void BeastReq::SetHeaders(const headers_t &headers)
{
    m_headers = headers;
}

void BeastReq::SetMethod(const network::method_t &method)
{
    m_method = method;
}

void BeastReq::SetTarget(const std::string &target)
{
    m_target = target;
}
