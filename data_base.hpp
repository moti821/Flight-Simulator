# pragma once
#include <unordered_map>

class DataBase
{
public:
    static DataBase* get_instance();
    static std::unordered_map<std::string, double> symbol_table;
    void create_H_map();
    
private:
    static DataBase* instance;
    DataBase();
};
