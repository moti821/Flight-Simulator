#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <chrono>
#include "server.hpp"
#include "lexer.hpp"
#include "data_base.hpp"


class Command
{
public:
    virtual void do_command(int) = 0;
    virtual ~Command(){}
};


class OpenServerCommand : public Command
{
public:
    virtual void do_command(int);
    virtual ~OpenServerCommand(){}
};


class ConnectCommand : public Command
{
public:
    virtual void do_command(int);
    virtual ~ConnectCommand(){}
};


class VarCommand : public Command
{
public:
    virtual void do_command(int);
    virtual ~VarCommand(){}
    static std::unordered_map <std::string, std::string> variable;
private:
};


class EqualCommand : public Command
{
public:
    virtual void do_command(int);
    virtual ~EqualCommand(){}
    std::string find_word_convert_to_value(std::string str_line);
};


class WhileCommand : public Command
{
public:
    virtual void do_command(int);
    virtual ~WhileCommand(){}
private:
};


class PrintCommand : public Command
{
public:
    virtual void do_command(int);
    virtual ~PrintCommand(){}
};


class SleepCommand : public Command
{
public:
    virtual void do_command(int);
    virtual ~SleepCommand(){}
};