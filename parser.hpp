#pragma once
#include <unordered_map>
#include "command.hpp"

class Parser
{
public:
    Parser();
    ~Parser();
    
    void create_hash();
    void parse();
    Command* get_command(std::string name_command);
    static std::vector<int> vec_lines_to_while;

private:
    void create_vec_line(int);
    static std::unordered_map <std::string, Command *> commands;
};