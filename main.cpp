#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"
#include "server.hpp"
#include "client.hpp"
#include "command.hpp"
#include "data_base.hpp"



int main()
{
    Lexer *lex = new Lexer;
    lex->opneInstructionsFile("file_text.txt");
    std::vector<std::vector<std::string>> data = lex->getAllLines();
    // DataBase::get_instance()->create_H_map();

    Parser pars;
    for (int i = 0; i < data.size(); i++)
    {
        std::vector<std::string> line = data[i];
        Command* command = pars.parse(line);
        command->do_command(line);
        if(line[0] == "while")
        {
            //
        }

    }
}