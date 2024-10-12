#include "../include/request_response_support/IResponseFactory.h"

IResponsePtr IResponseFactory::CreateResponse(network::http_code_t code, const std::string &body,
                                             const headers_t &headers) const
{
    IResponsePtr resp = this->CreateResponse();

    resp->SetStatus(code);
    resp->SetBody(body);
    resp->SetHeaders(headers);

    return resp;
}

IResponseFactory::~IResponseFactory() = default;