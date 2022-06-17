#include "helper.h"

std::string Helper::GetEnvironmentVariable(const std::string& key, const std::string& defaultValue) {
    char* val = getenv(key.c_str());
    return val == NULL ? defaultValue : std::string(val);
}