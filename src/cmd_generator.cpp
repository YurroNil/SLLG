// src/cmd_generator.cpp
#include "cmd_generator.h"
#include "fileMng.h"

CmdGenerator::CmdGenerator() {}
CmdGenerator::~CmdGenerator() {}

// 第二阶段：编译源文件
int CmdGenerator::CompileAllSrcFiles() {
try {
    // 编译每个源文件
    for (const auto& source_path : SourceFiles) {
        // 生成目标文件名
        string object_name = FileMng::GenerateObjectName(
            source_path, 
            fs::path(SourceDirs[0]).parent_path(), 
            LibraryName
        );
        
        // 构建目标文件路径
        fs::path object_path = fs::path(OutputDir) / object_name;
        ObjectFiles.push_back(object_path.string());
        
        // 确保目标目录存在
        fs::create_directories(object_path.parent_path());
        
        // 构建编译命令
        CompileCommand = cmdPrefix + 
            " \"" + source_path.string() + "\"" +
            IncludeFlags +
            " -o \"" + object_path.string() + "\"" +
            LibSuffixStr;
        
        // 执行编译命令
        if (FileMng::ExecuteCommand(CompileCommand)) {
            std::cerr << "\033[1;31m编译失败: " << source_path << "\033[0m" << std::endl;
        }
    }

} catch (const std::exception& e) {
    std::cerr << "\033[1;31m错误: " << e.what() << "\033[0m" << std::endl;
    return EXIT_FAILURE;
}

    return 0;
}

int CmdGenerator::BuildCommand() {
    int success;
try {
    std::cout << "\n\033[1;35m" << string(60, '=') << "\033[0m";
    std::cout << "\n\033[1;35m阶段 1: 编译源文件\033[0m\n";
    
    // 构建包含路径参数
    for (const auto& path : IncludePaths) {
        IncludeFlags += " -I\"" + path + "\"";
    }
    
    // 构建库后缀参数
    for (const auto& lib : LibSuffix) {
        LibSuffixStr += " " + lib;
    }
    // 构建并执行编译源文件的命令
    success = CompileAllSrcFiles();

} catch (const std::exception& e) {
    std::cerr << "\033[1;31m错误: " << e.what() << "\033[0m" << std::endl;
    return EXIT_FAILURE;
}
    return 0;
}

// 第三阶段：创建静态库
int CmdGenerator::CreateSLB() {
    int success;
try{
    std::cout << "\n\033[1;35m" << string(60, '=') << "\033[0m";
    std::cout << "\n\033[1;35m阶段 2: 创建静态库\033[0m\n";
    
    // 构建静态库路径
    LibraryPath = fs::path(OutputDir) / ("lib" + LibraryName + ".a");
    
    // 构建打包命令
    ArchiveCommand = "ar.exe rcs \"" + LibraryPath.string() + "\"";
    for (const auto& obj : ObjectFiles) {
        ArchiveCommand += " \"" + obj + "\"";
    }
    
    // 执行打包命令
    if (FileMng::ExecuteCommand(ArchiveCommand)) {
        std::cerr << "\033[1;31m静态库创建失败\033[0m" << std::endl;
    }

} catch (const std::exception& e) {
    std::cerr << "\033[1;31m错误: " << e.what() << "\033[0m" << std::endl;
    return EXIT_FAILURE;
}
    return 0;
}

// 任务处理完成通知
void CmdGenerator::PopNotification() {
    std::cout << "\n\033[1;35m" << string(60, '=')
        << "\033[0m" << "\n\033[1;32m静态库创建成功!\033[0m"
        << "\n  库路径: " << LibraryPath
        << "\n  包含目标文件: " << ObjectFiles.size() << " 个"
    << std::endl;
}