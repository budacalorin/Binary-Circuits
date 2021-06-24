#ifndef CONECTOR_H
#define CONECTOR_H

class conector
{
    public:
        bool currentState;
        bool alive=0;

        void set_state(bool state);
        bool get_state();
        conector();
};

#endif // CONECTOR_H
