#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "server.hpp"
#include "lexer.hpp"
// #include "parser.hpp"
// #include "shunting_yard.cpp"


class Command
{
public:
    virtual void do_command(int) = 0;
};


class OpenServerCommand : public Command
{
public:
    virtual void do_command(int);
};


class ConnectCommand : public Command
{
public:
    virtual void do_command(int);
};


class VarCommand : public Command
{
public:
    VarCommand(){}
    virtual void do_command(int);
    // std::unordered_map<std::string, std::string>& get_H_map();
    static std::unordered_map<std::string, std::string> variable;
private:
};


class EqualCommand : public Command
{
public:
    virtual void do_command(int);
};


class WhileCommand : public Command
{
public:
    virtual void do_command(int);
    void create_vec_line(int);
    int next_line();
private:
    std::vector<int> while_lines;
};


class PrintCommand : public Command
{
public:
    virtual void do_command(int);
};


class SleepCommand : public Command
{
public:
    virtual void do_command(int);
};