#include <mutex>
#include <iostream>
#include "symbol_table.hpp"
#include "client.hpp"


SymbolTable *SymbolTable::instance = 0;
std::mutex my_lock;


SymbolTable *SymbolTable::get_instance()
{
    if (instance == 0)
    {
        instance = new SymbolTable;
    };
    return instance;
}

SymbolTable::SymbolTable() {}

void SymbolTable::set_var(const std::string &name, const std::string &path)
{
    my_lock.lock();
    try
    {
        variable[path] = name;
        paths[name] = path;
        symbol_table[name] = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    my_lock.unlock();
    
}

void SymbolTable::set_data(const std::string &path, double value)
{
    std::string var = variable[path];
    if(var != " ")
    {
        my_lock.lock();
        try
        {
            symbol_table[var] = value;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        my_lock.unlock();
    }
}

void SymbolTable::set_value(const std::string &var, double value)
{
    std::string path = paths[var];
    if (path == "")
    {
        my_lock.lock();
        try
        {
            symbol_table[var] = value;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        my_lock.unlock();
    }
    else
    {        
        Client::getInstance()->send(path, value);
    }
}

double SymbolTable::get_value(const std::string &var)
{
    my_lock.lock();
    double value;
    try
    {
        value = symbol_table[var];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    my_lock.unlock();
    return value;
}