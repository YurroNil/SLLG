// include/json_parser.h
#pragma once
#include "config_data.h"
#include "kits/streams.h"
#include "nlohmann/json.hpp"


class JsonParser {
public:
    int LoadConfigFile(const string& path, ConfigData* data);
    int OpenFile(const string& path, json& config);

};