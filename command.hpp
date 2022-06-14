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
    void do_command(int num_line);
    ~OpenServerCommand(){}
};


class ConnectCommand : public Command
{
public:
    void do_command(int num_line);
    ~ConnectCommand(){}
};


class VarCommand : public Command
{
public:
    void do_command(int num_line);
    ~VarCommand(){}
    static std::unordered_map <std::string, std::string> variable;
private:
};


class EqualCommand : public Command
{
public:
    void do_command(int num_line);
    ~EqualCommand(){}
    std::string find_word_convert_to_value(std::string str_line);
};


class WhileCommand : public Command
{
public:
    void do_command(int num_line);
    ~WhileCommand(){}
private:
};


class PrintCommand : public Command
{
public:
    void do_command(int num_line);
    ~PrintCommand(){}
};


class SleepCommand : public Command
{
public:
    void do_command(int num_line);
    ~SleepCommand(){}
};