#include "Logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include "boost/smart_ptr/make_shared.hpp"

#include "include/config/base_constants.h"

boost::shared_ptr <SpdLogger> SpdLogger::Instance() {
    return boost::make_shared<SpdLogger>();
}

void SpdLogger::initLogger(const IConfigPtr &config) {
    std::string filePath = config->GetStringField({AppLiterals::LogFile});
    if (filePath != "stdout")
    {
        auto logger = spdlog::basic_logger_mt("file_logger", filePath, true);
        spdlog::set_default_logger(logger);
    }
}

void SpdLogger::logInfo(const char* msg) {
    spdlog::info(msg);
}

void SpdLogger::logWarning(const char* msg) {
    spdlog::warn(msg);
}

void SpdLogger::logError(const char* msg) {
    spdlog::error(msg);
}
