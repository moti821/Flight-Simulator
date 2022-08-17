#include <iostream>
#include "parser.hpp"


int main(int argc, char** argv)
{
    Parser pars{}; 
    pars.parse(argv[1]);
}