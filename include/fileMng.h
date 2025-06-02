// include/fileMng.h
#pragma once
#include "kits/strings.h"
#include "kits/streams.h"
#include "kits/filesystems.h"
#include <vector>

using PathArray = std::vector<fs::path>;

class FileMng {
public:
    static int ExecuteCommand(const string& command);
    static void CollectSourceFiles(const fs::path& directory, PathArray& source_files);
    static string GenerateObjectName(const fs::path& source_path, const fs::path& base_path, const string& module_name);

    
};