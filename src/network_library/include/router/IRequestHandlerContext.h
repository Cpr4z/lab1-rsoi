#pragma once

#include "../request_response_support/RequestResponse.h"

class IRequestHandlerContext
{
public:
    virtual ~IRequestHandlerContext() = default;
    virtual IRequestPtr GetCurrentRequest() = 0;
    virtual IResponsePtr GetCurrentResponse() = 0;
};

using IRequestHandlerContextPtr = boost::shared_ptr<IRequestHandlerContext>;