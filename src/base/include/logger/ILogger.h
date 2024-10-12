#pragma once

#include <boost/shared_ptr.hpp>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void logInfo(const char* msg) = 0;
    virtual void logWarning(const char* msg) = 0;
    virtual void logError(const char* msg) = 0;
};

using ILoggerPtr = boost::shared_ptr<ILogger>;