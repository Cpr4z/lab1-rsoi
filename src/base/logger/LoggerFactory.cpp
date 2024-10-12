#include "include/logger/LoggerFactory.h"

#include "Logger.h"

ILoggerPtr LoggerFactory::createLogger() {
    return SpdLogger::Instance();
}

void LoggerFactory::initLogger(const IConfigPtr& config) {
    SpdLogger::initLogger(config);
}


