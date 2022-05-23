# pragma once
#include <unordered_map>
#include <vector>

class DataBase
{
public:
    static DataBase* get_instance();
    static std::unordered_map<std::string, double> symbol_table;
    // static std::unordered_map<std::string, std::string> path_to_name;
    // static std::vector<std::pair<std::string, int>> name_to_number;
    // void create_H_map();
    
private:
    static DataBase* instance;
    DataBase();
};
