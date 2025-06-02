// src/main.cpp
#include "json_parser.h"
#include "cmd_generator.h"

// 程序执行的具体步骤
int running_program(CmdGenerator* data) {
    int success; JsonParser parser;

    // 第一阶段：加载配置文件========================
    success = parser.LoadConfigFile("./sllg_config.json", data);
    // 检查
    if(success != 0) return success;


// 第二阶段：构建命令并编译目标文件========================
    success = data->BuildCommand();
    // 检查
    if(success != 0) return success;


// 第三阶段：创建静态链接库========================
    success = data->CreateSLB();
    // 检查
    if(success != 0) return success;


// 结束========================
    // 完成通知
    data->PopNotification();

    return 0;
}

// 主函数
int main() {

    // 创建实例
    CmdGenerator* data = new CmdGenerator();

    // 运行程序
    int success = running_program(data);
    // 检查
    if(success != 0) return success;

    // 资源清理
    delete data; data = nullptr;

    return 0;
}
