#include <iostream>
#include "parser.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        Parser pars{};
        pars.parse(argv[1]);
    }
    else
        std::cout << "Enter the path of instruction file" << std::endl;
}