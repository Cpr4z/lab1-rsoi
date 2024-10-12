#pragma once

#include "../include/request_response_support/IResponseFactory.h"

class BeastResponseFactory : public IResponseFactory
{
public:
    virtual IResponsePtr CreateResponse() const override;

    virtual ~BeastResponseFactory() = default;
};