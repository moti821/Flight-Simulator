#pragma once
#include <vector>
#include <string>

class Command
{
public:
    virtual void do_command(const std::vector<std::string> &line) = 0;
    virtual ~Command() = default;
};

class OpenServerCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
};

class ConnectCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
};

class VarCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);

private:
};

class AssignmentCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
private:
    std::string find_word_convert_to_value(const std::string &str_line);
};

class WhileCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
private:
    bool expression(double value, const std::string &operat, double condition);

private:
};

class PrintCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
};

class SleepCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
};