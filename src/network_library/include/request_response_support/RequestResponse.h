#pragma once

#include <map>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "../../base/include/exceptions/server_exceptions.h"

using headers_t = std::map<std::string, std::string>;

namespace network
{
    enum method_t : size_t
    {
        GET,
        POST,
        DELETE,
        PUT,
        PATCH,
        UNDEFINED
    };

    enum http_code_t
    {
        CODE_200 = 200, // OK
        CODE_201 = 201, // Created
        CODE_204 = 204, // No content
        CODE_400 = 400, // bad request
        CODE_401 = 401, // unauthorized
        CODE_403 = 403, // forbidden
        CODE_404 = 404, // not found
        CODE_503 = 503  // internal server error
    };
}

class IRequest;
using IRequestPtr = boost::shared_ptr<IRequest>;

class IRequest
{
public:
    virtual ~IRequest() = default;

    virtual std::string GetBody() const = 0;
    virtual std::string GetTarget() const = 0;
    virtual headers_t GetHeaders() const = 0;
    virtual network::method_t GetMethod() const = 0;

    virtual void SetBody(const std::string &body) = 0;
    virtual void SetHeaders(const headers_t &headers) = 0;
    virtual void SetTarget(const std::string &target) = 0;
    virtual void SetMethod(const network::method_t &method) = 0;

    // TODO make copy ctor
    void copy(const IRequestPtr &another_req)
    {
        SetBody(another_req->GetBody());
        SetTarget(another_req->GetTarget());
        SetHeaders(another_req->GetHeaders());
        SetMethod(another_req->GetMethod());
    }
};

class IResponse;
using IResponsePtr = boost::shared_ptr<IResponse>;

class IResponse
{
public:
    virtual ~IResponse() = default;

    virtual std::string GetBody() const = 0;
    virtual void SetBody(const std::string& body) = 0;

    virtual headers_t GetHeaders() const = 0;
    virtual void SetHeaders(const headers_t& headers) = 0;

    virtual network::http_code_t GetStatus() const = 0;
    virtual void SetStatus(network::http_code_t status) = 0;

    void Copy(const IResponsePtr& response)
    {
        SetBody(response->GetBody());
        SetHeaders(response->GetHeaders());
        SetStatus(response->GetStatus());
    }
};

