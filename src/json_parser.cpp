// src/json_parser.cpp
#include "json_parser.h"
#include "fileMng.h"

// 流入数据
int JsonParser::OpenFile(const string& path, json& config) {
    // 读取配置文件
    std::ifstream config_file(path);
    if (!config_file.is_open()) {
        std::cerr << "\033[1;31m错误: 无法打开 sllg_config.json 文件\033[0m" << std::endl;
        return EXIT_FAILURE;
    }

    config_file >> config;
    return 0;
}

// 第一阶段：加载配置文件
int JsonParser::LoadConfigFile(const string& path, ConfigData* data) {
    data->ConfigPath = path; int success;
try {
    std::cout << "\n\033[1;35m" << string(60, '=') << "\033[0m";
    std::cout << "\n\033[1;35m静态链接库生成器(SLLG) - 启动\033[0m\n";

    success = OpenFile(path, data->Config);
    if(success != 0) return success;

    // 解析配置
    data->LibraryName = data->Config["library_name"];
    data->IncludePaths = data->Config["paths"]["include"];
    data->SourceDirs = data->Config["paths"]["source_code"];
    data->cmdPrefix = data->Config["arguments"]["cmd_prefix"];
    data->LibSuffix = data->Config["arguments"]["lib_suffix"];
    data->OutputDir = data->Config["arguments"]["output"];

    // 确保输出目录存在
    fs::create_directories(data->OutputDir);

    // 收集所有源文件
    std::vector<fs::path> source_files;
    for (const auto& dir : data->SourceDirs) {
        if (fs::exists(dir) && fs::is_directory(dir)) {
            FileMng::CollectSourceFiles(dir, data->SourceFiles);
        }
    }

    std::cout << "\n\033[1;32m配置加载成功!\033[0m"
        << "\n  库名称: " << data->LibraryName
        << "\n  源文件数: " << data->SourceFiles.size()
        << "\n  输出目录: " << data->OutputDir
    << std::endl;

} catch (const std::exception& e) {
    std::cerr << "\033[1;31m错误: " << e.what() << "\033[0m" << std::endl;
    return EXIT_FAILURE;
}

    return 0;
}
