#pragma once
#include <vector>
#include <string>
#include <unordered_map>

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
    virtual void do_command(std::vector<std::string>&);
private:
    std::unordered_map<std::string, std::string> variable;
};


class WhileCommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>&);
};