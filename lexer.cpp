#include <fstream>
#include "lexer.hpp"

Lexer::Lexer()
{

};

void Lexer::opneInstructionsFile(std::string file_path)
{
    std::string line;
    std::fstream fs;
    fs.open(file_path, std::fstream::in);
    while(std::getline(fs,line)){
        
        std::vector<std::string> vec_line;
        vec_line.push_back(line);
        all_lines.push_back(vec_line);
        
        if (line == "-1"){
            break;
        }
    };
    fs.close();
        std::cout << all_lines[2][0] << std::endl;
    return;
};

int main()
{
    Lexer s;
    s.opneInstructionsFile("file_text.txt");
    //Lexer::opneInstructionsFile("/home/file_text")
    return 0;
};