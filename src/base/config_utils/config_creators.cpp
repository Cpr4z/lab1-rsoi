#include "include/config/config_creators.h"

#include "yaml_config.h"
#include <boost/smart_ptr/make_shared.hpp>

IConfigPtr createYAMLConfig(const std::string& filename)
{
    return boost::make_shared<YamlCppConfig>(filename);
}