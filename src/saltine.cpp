#include <csignal>

#include <iostream>

#include "saltine.hpp"

#define DO_LOG

using namespace Saltine;


static bool failsafe_trigger = false;


static void s_handler(int sig)
{
    failsafe_trigger = true;
}

static int crack(CommandHandler& handler, const std::string& zipfilename)
{
    const std::string unzip_command = "unzip -P ";
    const std::string unzip_dir("./uzdir");

    const auto cleanup = [&handler, &unzip_dir]()
    {
        handler.run_command("rm -rf " + unzip_dir);
    };

    handler.run_command("mkdir " + unzip_dir);

    while(1)
    {
        if (failsafe_trigger == true)
        {
            cleanup();
            break;
        }

        const std::string gen_password("test");
        const std::string f_command = unzip_command + gen_password + ' ' + "-d " + unzip_dir + ' ' + zipfilename;

        const int res = handler.run_command(f_command);

        if (res == 0)
        {
            std::cout << "Found password for file '" << zipfilename << "': " << gen_password << "\n";
            cleanup();
            return res;
        }

        cleanup();
        break;
    }

    return -1;
}


Cracker::Cracker()
{
    signal(SIGTERM, s_handler);
    signal(SIGKILL, s_handler);
}

int Cracker::run()
{
    for(const auto& file : zip_files)
    {
        thread_pool.push_back(std::thread(crack, std::ref(handler), std::cref(file.filename)));
    }

    for(auto& th : thread_pool)
    {
        //failsafe_trigger = true;
        th.join();
    }

    return 0;
}

void Cracker::load_zip(const std::string& zip_filename)
{
    ZipFile zp (zip_filename);

    if (zp.has_headers == false)
    {
        #ifdef DO_LOG
            std::cout << "Zipfile '" << zip_filename << "' does not have headers.'\n";
        #endif

        return;
    }

    zip_files.emplace_back(zp);

#ifdef DO_LOG
    std::cout << "Loaded zipfile '" << zip_filename << "'\n";
#endif
}
