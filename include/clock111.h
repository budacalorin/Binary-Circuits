#ifndef CLOCK_H
#define CLOCK_H

#include "conector.h"

class clock
{
public:
    float speedRatio;
    int timpRamas;
    bool semn;
    int timpTrue;
    int timpFlase;
    conector *outputConnector;

    clock();

};

#endif // CLOCK_H
