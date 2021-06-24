#include "conector.h"

conector::conector()
{
    currentState = 0;
}

void conector::set_state(bool state)
{

    currentState = state;
}

bool conector::get_state()
{
    return currentState;
}
