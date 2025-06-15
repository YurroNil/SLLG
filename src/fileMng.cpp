// src/fileMng.cpp
#include "fileMng.h"

// 执行系统命令并返回结果
int FileMng::ExecuteCommand(const string& command) {
    std::cout << "\n\033[1;34m执行命令: \033[0m" << command << std::endl;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "\033[1;31m命令执行失败 (代码: " << result << ")\033[0m" << std::endl;
    }
    return result;
}

// 递归收集所有源文件
void FileMng::CollectSourceFiles(const fs::path& directory, PathArray& source_files) {
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() &&
            // 收集cpp和c后缀的源文件
            (entry.path().extension() == ".cpp" or
            entry.path().extension() == ".c"))
        {
            source_files.push_back(entry.path()); 
        }
    }
}

// 生成目标文件名（处理嵌套目录）
string FileMng::GenerateObjectName(const fs::path& source_path, const fs::path& base_path, const string& module_name) {
    // 获取相对路径
    fs::path relative_path = fs::relative(source_path, base_path);
    
    // 移除扩展名
    string object_name = relative_path.stem().string();
    
    // 处理父目录
    if (relative_path.has_parent_path()) {
        fs::path parent_path = relative_path.parent_path();
        if (!parent_path.empty() && parent_path != ".") {
            // 将路径分隔符替换为下划线
            string parent_str = parent_path.string();
            std::replace(parent_str.begin(), parent_str.end(), '\\', '_');
            std::replace(parent_str.begin(), parent_str.end(), '/', '_');
            object_name = parent_str + "_" + object_name;
        }
    }
    
    // 添加模块名前缀
    return module_name + "_" + object_name + ".o";
}