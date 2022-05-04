#include <unordered_map>
#include "parser.hpp"
#include "lexer.hpp"
#include "command.hpp"


// void Parser::create_h_map()
// {
//     commands["opendataserver"] = new Openservercommand;
//     commands["connect"] = new Connectcommand;
    
// };


void Parser::pars()
{
    // create_h_map();
    Lexer *lex = new Lexer;
    lex->opneInstructionsFile("file_text.txt");
    std::vector<std::vector<std::string>> data = lex->getAllLines();
    for(int i=0 ; i<data.size() ; i++){
        std::vector<std::string> line = data[i];   //lex->getLine(i);
        //runner(commands[line[0]]);


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
    std::cout << commands << std::endl;
};


// void Parser::runner(Command* command)
// {
//     command->do_command();
// }

int main()
{
    Parser par;

    par.pars();

}

