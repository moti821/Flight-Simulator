#include <unordered_map>
#include "parser.hpp"
// #include "lexer.hpp"
// #include "command.hpp"

Parser::Parser(){

}

void Parser::create_h_map()
{
    
    commands["openDataServer"] = new Openservercommand;
    commands["connect"] = new Connectcommand;
    
};

void Parser::pars()
{

    create_h_map();
    Lexer *lex = new Lexer;
    lex->opneInstructionsFile("file_text.txt");
    std::vector<std::vector<std::string>> data = lex->getAllLines();
    for(int i=0 ; i<2 ; i++){
        std::vector<std::string> line = data[i];   //lex->getLine(i);
        //std::string command = line[0];
        //Command* command = commands.find(line[0])->second;
        //std::string command = line[0];
        // std::cout << commands.find(command)->second << std::endl;

        runner(commands[line[0]]);


        // if(line[0] == "openDataServer"){
        //     Openservercommand *openservercommand = new Openservercommand;
        //     openservercommand->do_command();
        // }
        // if(line[0] == "connect"){
        //     Connectcommand *connectcommand = new Connectcommand;
        //     connectcommand->do_command();
        // }

        // else{
        //     std::cout<< "dd" <<std::endl;
        // }
        // if(line[0] == "while"){
        //     while(){
                
        //     }
        // }
    }
    //std::cout << commands << std::endl;
};


void Parser::runner(Command* command)
{
    std::cout << command << std::endl;
    command->do_command();
}

int main()
{
    Parser par;

    par.pars();

}

