#pragma  once

#include <boost/shared_ptr.hpp>

#include "include/logger/ILogger.h"
#include "include/config/IConfig.h"


class SpdLogger : public ILogger {
public:
    static boost::shared_ptr<SpdLogger> Instance();
    static void initLogger(const IConfigPtr& config);
    // turf off warning about double virtual
    virtual void logInfo(const char* msg) override;
    virtual void logWarning(const char* msg) override;
    virtual void logError(const char* msg) override;

    //TODO make private ctor
//private:
//    SpdLogger();
};

using SpdLoggerPtr = boost::shared_ptr<SpdLogger>;