#pragma once

#include <string>
#include <stdlib.h>

class Helper final {
public:
    static std::string GetEnvironmentVariable(const std::string& key, const std::string& defaultValue);
};