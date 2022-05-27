#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"
#include "server.hpp"
#include "client.hpp"
#include "command.hpp"
#include "data_base.hpp"



int main()
{
    Lexer *lex = Lexer::get_instance();
    lex->opneInstructionsFile("file_text1.txt");
    std::vector<std::vector<std::string>> data = lex->getAllLines();

    Parser pars;
    for (int i = 0; i < data.size(); i++)
    {
        std::vector<std::string> line = data[i];
        Command* command = pars.parse(line);
        command->do_command(i);
        if(line[0] == "while"){
            i = DataBase::get_instance()->s;
        }
    }
}