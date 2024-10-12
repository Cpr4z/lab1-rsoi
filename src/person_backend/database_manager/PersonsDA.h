#pragma once

#include "IPersonsRepository.h"
#include "../../base/include/config/IConfig.h"

const std::string PersonBD = "DB_PERSONS";

IPersonsRepositoryPtr createPersonsRepository(const IConfigPtr& config, const std::string& connectionSection);