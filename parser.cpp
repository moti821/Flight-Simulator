#include "parser.hpp"


Parser::Parser(){
    commands["openDataServer"] = new Openservercommand;
    commands["connect"] = new Connectcommand;

}



void Parser::pars()
{

    Lexer *lex = new Lexer;
    lex->opneInstructionsFile("file_text.txt");
    std::vector<std::vector<std::string>> data = lex->getAllLines();
    
    for(int i=0 ; i<data.size() ; i++){
        std::vector<std::string> line = data[i];   //lex->getLine(i);
        Command* next_command = commands[line[0]];
        runner(next_command);
        
        if(line[0] == "while"){
            //while_loop();
        }
    }
};


void Parser::runner(Command* command)
{
    std::cout << command << std::endl;
    command->do_command();
}

