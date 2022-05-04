#pragma once

class Parser
{
public:

    Parser(){}

    void pars();

private:
    std::unordered_map<std::string,Command*> commands;
    // void create_h_map();

    //void runner(Command* command);
};