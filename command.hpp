#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "server.hpp"


class Command
{
public:
    virtual void do_command(std::vector<std::string>&) = 0;
};


class OpenServerCommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>&);
};


class ConnectCommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>&);
};


class VarCommand : public Command
{
public:
    VarCommand(){}
    virtual void do_command(std::vector<std::string>&);
    // std::unordered_map<std::string, std::string>& get_H_map();
    static std::unordered_map<std::string, std::string> variable;
private:
};


class EqualCommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>&);
};


class WhileCommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>&);
};


class PrintCommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>&);
};


class SleepCommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>&);
};