#pragma once

class Command
{
public:
    virtual void do_command() = 0;

};

class Openservercommand : public Command
{
public:
    virtual void do_command();
};

class Connectcommand : public Command
{
public:
    virtual void do_command();
};