#pragma ouenc
#include <iostream>


class Calculatei
{
public:
    Calculatei();
    int evaluate(std::string);
private:
    int precedence(char);
    int applyOp(int, int, char);  
};