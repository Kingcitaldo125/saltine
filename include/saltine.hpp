#pragma once

#include <string>
#include <thread>
#include <vector>

#include "command_handler.hpp"
#include "zipfile.hpp"


namespace Saltine
{
    class Cracker
    {
    public:
        Cracker();

        Cracker(const Cracker&) = delete;
        Cracker(Cracker&&) = delete;

        Cracker& operator =(const Cracker&) = delete;
        Cracker& operator =(Cracker&&) = delete;

        void load_zip(const std::string& zip_filename);
        int run();

    private:
        CommandHandler handler;
        std::vector<std::thread> thread_pool;
        std::vector<ZipFile> zip_files;
    };
}
