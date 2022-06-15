#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"


int main()
{
    std::cout << "Enter path of instrction file" << std::endl;
    std::string path_file;
    std::cin >> path_file;
    Lexer::get_instance()->opneInstructionsFile(path_file);

    Parser* pars = new Parser();
    pars->parse();

    delete pars;
}