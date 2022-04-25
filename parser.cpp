#include "parser.hpp"
#include "lexer.hpp"




void Parser::pars()
{
    Lexer lex;
    lex.opneInstructionsFile("file_text.txt");
    std::vector<std::vector<std::string>> data = lex.getAllLines();
    for(int i=0 ; i<data.size() ; i++){
        std::vector<std::string> line = lex.getLine(i);
    }

};

int main()
{
    Parser par;

    par.pars();

}

