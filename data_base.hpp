# pragma once
#include <unordered_map>
#include <vector>

class DataBase
{
public:
    static DataBase* get_instance();
    static std::unordered_map<std::string, double> symbol_table;

private:
    static DataBase* instance;
    DataBase();
};
