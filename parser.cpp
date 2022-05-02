#include "parser.hpp"
#include "lexer.hpp"
#include "command.hpp"




void Parser::pars()
{
    Lexer *lex = new Lexer;
    lex->opneInstructionsFile("file_text.txt");
    std::vector<std::vector<std::string>> data = lex->getAllLines();
    for(int i=0 ; i<data.size() ; i++){
        std::vector<std::string> line = lex->getLine(i);
        // std::string comm = line[0];
        
        // runner(new comm);

        if(line[0] == "openDataServer"){
            Openservercommand *openservercommand = new Openservercommand;
            openservercommand->do_command();
        }
        if(line[0] == "connect"){
            Connectcommand *connectcommand = new Connectcommand;
            connectcommand->do_command();
        }

        else{
            std::cout<< "dd" <<std::endl;
        }
        // if(line[0] == "while"){
        //     while(){
                
        //     }
        // }
    }

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

