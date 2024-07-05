#pragma once

namespace Saltine
{
    struct ZipFile
    {
        ZipFile(const std::string& fname);
        std::string filename;
        bool has_headers;
    };
}
