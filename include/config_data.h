// include/config_data.h
#pragma once

#include "kits/strings.h"
#include <vector>
#include "kits/filesystems.h"
#include "nlohmann/json.hpp"

// 别名
using PathArray = std::vector<fs::path>;
using StringArray = std::vector<string>;
using json = nlohmann::json;

// 结构体
struct ConfigData {

    // strings
    string LibraryName;
    string cmdPrefix;
    string OutputDir;
    string IncludeFlags;
    string LibSuffixStr;
    string CompileCommand;
    string ArchiveCommand;


    // string arrays
    StringArray IncludePaths;
    StringArray SourceDirs;
    StringArray LibSuffix;
    StringArray ObjectFiles;

    // 杂项
    fs::path LibraryPath;
    PathArray SourceFiles;
    json Config;
    string ConfigPath;
};
