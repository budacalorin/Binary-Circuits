#ifndef DLATCH_H
#define DLATCH_H
#include "ceas.h"
#include "conector.h"

class DLatch
{
    public:
        bool currentState;
        conector *clockConnector;
        conector *inputConnector;


        DLatch();
        bool run(ceas clock, conector *connector);
};

#endif // DLATCH_H
