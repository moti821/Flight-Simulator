#pragma once
#include <unordered_map>
#include "command.hpp"

class Parser
{
public:
    Parser();
    ~Parser()
    {
    delete commands["openDataServer"];
    delete commands["connect"];
    delete commands["var"];
    delete commands["equal"];
    delete commands["while"];
    delete commands["print"];
    delete commands["sleep"];

    }

    void creat_hash();
    Command* parse(std::vector<std::string>&);
    std::string delete_space(std::string);
    std::string find_word_convert_to_value(std::string str_line);

private:
    static std::unordered_map <std::string, Command *> commands;
};