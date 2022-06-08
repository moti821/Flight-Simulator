#pragma once
#include <vector>
#include <string>
#include <unordered_map>


class Command
{
public:
    virtual void do_command(int num_line) = 0;
    virtual ~Command(){}
};


class OpenServerCommand : public Command
{
public:
    virtual void do_command(int num_line);
    virtual ~OpenServerCommand(){}
};


class ConnectCommand : public Command
{
public:
    virtual void do_command(int num_line);
    virtual ~ConnectCommand(){}
};


class VarCommand : public Command
{
public:
    virtual void do_command(int num_line);
    virtual ~VarCommand(){}
    static std::unordered_map <std::string, std::string> variable;
private:
};


class EqualCommand : public Command
{
public:
    virtual void do_command(int num_line);
    virtual ~EqualCommand(){}
    std::string find_word_convert_to_value(std::string str_line);
};


class WhileCommand : public Command
{
public:
    virtual void do_command(int num_line);
    virtual ~WhileCommand(){}
private:
};


class PrintCommand : public Command
{
public:
    virtual void do_command(int num_line);
    virtual ~PrintCommand(){}
};


class SleepCommand : public Command
{
public:
    virtual void do_command(int num_line);
    virtual ~SleepCommand(){}
};