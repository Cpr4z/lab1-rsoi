#pragma once

#include <boost/shared_ptr.hpp>

#include "../config/IConfig.h"
#include "ILogger.h"

class LoggerFactory {
public:
    LoggerFactory() = delete;
    LoggerFactory(const LoggerFactory&) = delete;
    LoggerFactory& operator=(const LoggerFactory&) = delete;

    static ILoggerPtr createLogger();
    static void initLogger(const IConfigPtr& config);
};