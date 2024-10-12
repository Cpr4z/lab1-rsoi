#pragma once

#include "base_exception.h"

PROJECT_EXCEPTION(ServerException, BaseException, "Server Error")
PROJECT_EXCEPTION(JsonParserException, ServerException, "Json parser Error")
PROJECT_EXCEPTION(ConfigReaderException, ServerException, "Config read Error")