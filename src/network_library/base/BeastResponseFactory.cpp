#include "BeastResponseFactory.h"
#include <boost/smart_ptr/make_shared.hpp>
#include "Response.h"

IResponsePtr BeastResponseFactory::CreateResponse() const
{
    return boost::make_shared<BeastResp>();
}