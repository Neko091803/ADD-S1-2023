#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>
using namespace std;

class Move
{
public:
    Move();
    string getName();
    void setName(string name);
    string moveName;
};

#endif