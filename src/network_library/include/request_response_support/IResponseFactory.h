#pragma once

#include "RequestResponse.h"

class IResponseFactory
{
public:
    virtual ~IResponseFactory() = 0;

    virtual IResponsePtr CreateResponse() const = 0;
    virtual IResponsePtr CreateResponse(network::http_code_t, const std::string &body, const headers_t &headers) const;
};

using IResponseFactoryPtr = boost::shared_ptr<IResponseFactory>;
