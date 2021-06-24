#include "xorGate.h"
#include "init.h"
#include <iostream>
using namespace std;
xorGate::xorGate()
{
    input1 = NULL;
    input2 = NULL;
    output = NULL;
    //shape.setOutlineThickness(2);
    //shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(100, 100, 100));
}

bool xorGate::run()
{
    if (input1!=NULL&&input2!=NULL&&output!=NULL)
    {
        output->set_state((input1->get_state()!=input2->get_state()));
        return input1->get_state()!=input2->get_state();
    }
    if (input1!=NULL&&output!=NULL)
    {
        output->set_state(input1->get_state());
        return input1->get_state();
    }
    if (input2!=NULL&&output!=NULL)
    {
        output->set_state(input2->get_state());
        return input2->get_state();
    }
    return 0;

}

void xorGate::reset()
{
    active=0;
    indiceInput1=indiceInput2=0;
    input1=input2=NULL;
    output=NULL;
    lineInput1.set_connector(0);
    lineInput2.set_connector(0);
    lineOutput.set_connector(0);
    shape.setTexture(&xorT);
}
