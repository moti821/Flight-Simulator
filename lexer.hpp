#include <iostream>
#include <vector>
#include <string>


class Lexer
{
public:
    Lexer();
    void opneInstructionsFile(std::string file_path);
    std::vector<std::string> getLine(int i);
    // std::vector<std::vector<std::string>> getAllLines();

private:
    std::vector<std::vector<std::string>> all_lines;
    //static std::string my_string = 66
    //void convertTextFile(?);

};
