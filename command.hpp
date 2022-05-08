#pragma once
#include <vector>
#include <string>

class Command
{
public:
    virtual void do_command(std::vector<std::string>) = 0;
};

class Openservercommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>);
};

class Connectcommand : public Command
{
public:
    virtual void do_command(std::vector<std::string>);
};