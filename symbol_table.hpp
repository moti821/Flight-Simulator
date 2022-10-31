#pragma once
#include <unordered_map>

class SymbolTable
{
public:
    static SymbolTable *get_instance();
    void set_var(const std::string &name, const std::string &path);
    void set_data(const std::string &path, double value);
    void set_value(const std::string &var, double value);
    double get_value(const std::string &var);

private:
    static SymbolTable *instance;
    SymbolTable();
    std::unordered_map<std::string, double> symbol_table;
    std::unordered_map<std::string, std::string> variable;
    std::unordered_map<std::string, std::string> paths;
};
