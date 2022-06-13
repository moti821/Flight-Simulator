#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"


int main()
{
    Lexer::get_instance()->opneInstructionsFile("file_text1.txt");

    Parser* pars = new Parser();
    pars->parse();

    delete pars;
}