#include <iostream>

#include "saltine.hpp"


int main(int argc, char** argv)
{
    Saltine::Cracker cracker;

    cracker.load_zip("/home/parelt/projects/saltine/test.zip");

    std::cout << cracker.run() << std::endl;

    return 0;
}
