# pragma once
#include <unordered_map>


class DataBase
{
public:
    static DataBase* get_instance();
    void insert_value(std::string var, double value);
    double get_value(std::string var);

private:
    static DataBase* instance;
    DataBase();
    
    static std::unordered_map<std::string, double> symbol_table;
};
