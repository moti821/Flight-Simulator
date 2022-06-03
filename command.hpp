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
    virtual int next_line();
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
    // VarCommand(){}
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
};


class WhileCommand : public Command
{
public:
    virtual void do_command(int);
    void create_vec_line(int);
    virtual int next_line();
    virtual ~WhileCommand(){}
private:
    std::vector<int> vec_lines_to_while;
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