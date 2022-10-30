#pragma once
#include <unordered_map>

class DataBase
{
public:
    static DataBase *get_instance();
    void set_value(const std::string &var, double value);
    double get_value(const std::string &var);

private:
    static DataBase *instance;
    DataBase();
    static std::unordered_map<std::string, double> symbol_table;
};
