#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Command
{
public:
    virtual void do_command(const std::vector<std::string> &line) = 0;
    virtual ~Command() {}
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
    static std::unordered_map<std::string, std::string> variable;

private:
};

class EqualCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
    std::string find_word_convert_to_value(std::string str_line);
};

class WhileCommand : public Command
{
public:
    void do_command(const std::vector<std::string> &line);
    bool expression(double value, std::string operat, double condition);

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