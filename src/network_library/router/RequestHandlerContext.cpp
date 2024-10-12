#include "RequestHandlerContext.h"

#include "../base/Request.h"
#include "../base/Response.h"

RequestsHandlerContext::RequestsHandlerContext()
{
    m_request = boost::make_shared<BeastReq>();
    m_response = boost::make_shared<BeastResp>();
}

IRequestPtr RequestsHandlerContext::GetCurrentRequest() {
    return m_request;
}

IResponsePtr RequestsHandlerContext::GetCurrentResponse() {
    return m_response;
}
