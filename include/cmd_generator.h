// include/cmd_generator.h
#pragma once
#include "config_data.h"

class CmdGenerator : public ConfigData {
public:

    CmdGenerator();
    ~CmdGenerator();
    int BuildCommand();
    int CompileAllSrcFiles();
    int CreateSLB();

    void PopNotification();
};