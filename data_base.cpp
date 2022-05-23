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


// void DataBase::create_H_map()
// {
//     symbol_table["/instrumentation/airspeed-indicator/indicated-speed-kt"] = 0;
//     symbol_table["/sim/time/warp"] = 0;
//     symbol_table["/controls/switches/magnetos"] = 0;
//     symbol_table["/instrumentation/heading-indicator/offset-deg"] = 21.992;
//     symbol_table["/instrumentation/altimeter/indicated-altitude-ft"] = 0;
//     symbol_table["/instrumentation/altimeter/pressure-alt-ft"] = 0;
//     symbol_table["/instrumentation/attitude-indicator/indicated-pitch-deg"] = 0;
//     symbol_table["/instrumentation/attitude-indicator/indicated-roll-deg"] = 0;
//     symbol_table["/instrumentation/attitude-indicator/internal-pitch-deg"] = 0;
//     symbol_table["/instrumentation/attitude-indicator/internal-roll-deg"] = 0;
//     symbol_table["/instrumentation/encoder/indicated-altitude-ft"] = 0;
//     symbol_table["/instrumentation/encoder/pressure-alt-ft"] = 0;
//     symbol_table["/instrumentation/gps/indicated-altitude-ft"] = 0;
//     symbol_table["/instrumentation/gps/indicated-ground-speed-kt"] = 0;
//     symbol_table["/instrumentation/gps/indicated-vertical-speed"] = 0;
//     symbol_table["/instrumentation/heading-indicator/indicated-heading-deg"] = 22.33;
//     symbol_table["/instrumentation/magnetic-compass/indicated-heading-deg"] = 0;
//     symbol_table["/instrumentation/slip-skid-ball/indicated-slip-skid"] = 0;
//     symbol_table["/instrumentation/turn-indicator/indicated-turn-rate"] = 0;
//     symbol_table["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = 0;
//     symbol_table["/controls/flight/aileron"] = 0;
//     symbol_table["/controls/flight/elevator"] = 0;
//     symbol_table["/controls/flight/rudder"] = 0;
//     symbol_table["/controls/flight/flaps"] = 0;
//     symbol_table["/controls/engines/engine/throttle"] = 0;
//     symbol_table["/controls/engines/current-engine/throttle"] = 0;
//     symbol_table["/controls/switches/master-avionics"] = 0; 
//     symbol_table["/controls/switches/starter"] = 0;
//     symbol_table["/engines/active-engine/auto-start"] = 0;
//     symbol_table["/controls/flight/speedbrake"] = 0; 
//     symbol_table["/sim/model/c172p/brake-parking"] = 0;
//     symbol_table["/controls/engines/engine/primer"] = 0;
//     symbol_table["/controls/engines/current-engine/mixture"] = 0;
//     symbol_table["/controls/switches/master-bat"] = 0; 
//     symbol_table["/controls/switches/master-alt"] = 0;
//     symbol_table["/engines/engine/rpm"] = 0;
// }