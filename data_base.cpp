#include <mutex>
#include "data_base.hpp"

DataBase* DataBase::instance = 0;
std::unordered_map<std::string, double> DataBase::symbol_table;
std::mutex my_lock;

DataBase* DataBase::get_instance()
{
    if(instance == 0)
    {
        DataBase* instance = new DataBase;
    };
    return instance;
}

DataBase::DataBase(){}


void DataBase::insert_value(std::string var, double value)
{
    my_lock.lock();
    symbol_table[var] = value;
    my_lock.unlock();
}

double DataBase::get_value(std::string var)
{
    my_lock.lock();
    double value =  symbol_table[var];
    my_lock.unlock();
    return value;
}