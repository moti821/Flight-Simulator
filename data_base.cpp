# include <iostream>
#include "data_base.hpp"

DataBase* DataBase::instance = 0;
std::unordered_map<std::string, double> DataBase::symbol_table;

DataBase* DataBase::get_instance()
{
    if(instance == 0)
    {
        DataBase* instance = new DataBase;
    };
    return instance;
}
DataBase::DataBase(){}

