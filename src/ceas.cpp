#include "ceas.h"
#include <iostream>
#include "init.h"
ceas::ceas()
{
    //ctor
}

void ceas::update(long long timpTrecut)
{
    if (outputConnector!=NULL)
    {
        timpRamas -= timpTrecut;
        if (timpRamas <= 0)
        {
            if (semn == true)
            {
                semn = false;
                timpRamas = timpFalse;
            }
            else
            {
                semn = true;
                timpRamas = timpTrue;
            }
            outputConnector->set_state(semn);
        }
    }

    if (semn==true)
    {
        if (timpTrue!=timpRamas)
            bara.setRotation((float)-timpRamas/((float)timpTrue/360));
        else
            bara.setRotation(0);
        bara.setFillColor(pornitC);
    }
    if (semn==false)
    {

        if (timpTrue!=timpRamas)
            bara.setRotation((float)-timpRamas/((float)timpFalse/360));
        else
            bara.setRotation(0);
        bara.setFillColor(opritC);
    }
}

void ceas::reset()
{
    shape.setTexture(&clockT);
    active=0;
    outputConnector=NULL;
    lineOutput.set_connector(0);
    semn=0;
}
