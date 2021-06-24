#ifndef SCENA_JOC
#define SCENA_JOC

#include <cstring>
#include "ceas.h"
#include "andGate.h"
#include "orGate.h"
#include "xorGate.h"
#include "conector.h"
#include "DLatch.h"
#include "line.h"
#include "notGate.h"
#include "source.h"

using namespace std;

class scena_joc
{
    public:
        long long timp_precedent;
        int numarConectoare;
        conector connectors[100];
        int numarAnd;
        andGate andGates[30];
        int numarOr;
        orGate orGates[30];
        int numarXor;
        xorGate xorGates[30];
        int numarDLatches;
        DLatch DLatches[20];
        int numarClocks;
        int numarLines;
        line lines[100];
        sf::RectangleShape buttons[100];
        ceas ceasuri[30];
        int numarNot;
        notGate notGates[30];
        sf::Text markers[100];
        int numarMarkers;
        int modJoc;
        bool playgorund;
        sf::RectangleShape piese[100];
        int numarPiese;
        int piesaSelectata;
        sf::RectangleShape ghost;
        bool setLine=0;
        source sources[30];
        int numarSurse;
        bool saving=0;
        string preset_name;


        void draw();
        void draw_and_gates();
        void draw_or_gates();
        void draw_xor_gates();
        void draw_lines();
        void draw_buttons();
        void draw_clocks();
        void draw_not_gates();
        void draw_markers();
        void draw_piese();
        void draw_surse();

        void add_and_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color);
        void add_or_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color);
        void add_xor_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color);
        void add_clock(sf::Vector2f Size, sf::Vector2f position, sf::Color color, int timpTrue, int timpFalse);
        void add_not_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color);
        void add_marker(sf::Vector2f position, string text, int characterSize, sf::Color color, sf::FloatRect rect);
        void add_piesa(string text);
        void add_line(sf::Vector2f position);
        void add_source(sf::Vector2f Size, sf::Vector2f position,sf::Color color);
        void connect(int indice,bool apply);

        void update_events();
        void saving_screen();
        void update_buttons();
        void update_surse();
        long long update_timp();
        void update_clocks(long long timpTrecut);
        void verificare_final();

        void update();
        void logic(long long timpTrecut);

        void reset(string preset);
        void reset_porti();
        void setup_playgorund();
        void setup_special(string preset);


        void add(int piesa,sf::Vector2f position,sf::Vector2f Size);
        void erase(sf::Vector2f position);
        void delete_connector(int indice,int indice_linie);


        void fix_marker (sf::Text &text, sf::FloatRect rect);
        void fix(int indiceLinie,int indiceConector);

        template <typename T>
        void debug(T poarta,string nume);

        void save(string name);
};


#endif
