#pragma once

#include <cstdlib>

#include <iostream>

//#define DO_LOG


namespace Saltine
{
    class CommandHandler
    {
    public:
        static int run_command(const char* cmd);
        static int run_command(const std::string& cmd);
    };

    int CommandHandler::run_command(const char* cmd)
    {
        #ifdef DO_LOG
        std::cout << "Running command : " << cmd << std::endl;
        #endif

        return system(cmd);
    }

    int CommandHandler::run_command(const std::string& cmd)
    {
        return run_command(cmd.c_str());
    }
}
