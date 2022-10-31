#include <iostream>
#include "parser.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Enter the path of instruction file" << std::endl;
        return 0;
    }

    Parser *pars = new Parser();
    pars->parse(argv[1]);
    delete pars;
    return 0;
}