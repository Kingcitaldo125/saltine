#include <fstream>
#include <sstream>
#include <vector>

#include "zipfile.hpp"
#include "command_handler.hpp"

#define ZIP_MAGIC_NUM "504b 0304"
#define ZIP_MAGIC_NUM_EMPTY "504b 0506"
#define ZIP_MAGIC_NUM_SPANNED "504b 0708"

#define OUTFILE_NAME "out.txt"

using namespace Saltine;

static CommandHandler cmd_handler;


ZipFile::ZipFile(const std::string& fname)
{
    has_headers = false;

    std::stringstream ss;
    ss << std::string("xxd -l64 ");
    ss << fname;
    ss << (" >>" OUTFILE_NAME);

    cmd_handler.run_command(">" OUTFILE_NAME);
    cmd_handler.run_command(ss.str());

    std::ifstream iff(OUTFILE_NAME, std::ios::in);

    if (iff.is_open() == false)
    {
        cmd_handler.run_command("rm " OUTFILE_NAME);
        return;
    }

    std::string file_bytes_str("");

    while(iff >> file_bytes_str) {}

    cmd_handler.run_command("rm " OUTFILE_NAME);

    const bool b1 = file_bytes_str.find(ZIP_MAGIC_NUM);
    const bool b2 = file_bytes_str.find(ZIP_MAGIC_NUM_EMPTY);
    const bool b3 = file_bytes_str.find(ZIP_MAGIC_NUM_SPANNED);

    has_headers = b1 || b2 || b3;
    filename = fname;
}
