#pragma once
#include <vector>
#include <string>
#include <unordered_map>
// #include<thread>
class Command
{
public:
    std::unordered_map<std::string, std::string> variable;
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