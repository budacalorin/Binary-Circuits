#include "../include/scena_meniu.h"
#include <cstring>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "fstream"
#include "../include/init.h"

using namespace std;
void scena_meniu::adaugare_optiune(const char *s)
{
    strcpy(optiuni[++numar_optiuni], s);
}

void scena_meniu::input_tastatura()
{
    sf::Mouse mouse;
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                up = 1;
                down = 0;
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                up = 0;
                down = 1;
            }
            if (event.key.code == sf::Keyboard::Enter)
            {
                enter = 1;
            }
            if (event.key.code == sf::Keyboard::Escape)
            {
                scena_curenta = 1;
            }
            if (event.key.code == sf::Keyboard::Delete&&scena_curenta==3)
            {
                ifstream fin ("saves/saves.txt");
                ofstream fout ("saves/backup.txt");
                char txt[300];
                while (fin.peek()!=EOF)
                {
                    fin.getline(txt,300);
                    fout << txt<<"\n";
                }
                fin.close();
                fout.close();

                fin.open("saves/backup.txt");
                fout.open("saves/saves.txt");
                bool ok=1;
                bool gasit=0;
                while (fin.peek()!=EOF)
                {
                    fin.getline(txt,300);
                    if (txt[0]=='N'&&txt[1]==':')
                    {
                        char c[300];
                        strcpy(c,txt+2);
                        if (ok==0)
                        {
                            gasit=1;
                        }
                        if (strcmp(c,optiuni[optiune_curenta])==0)
                        {
                            ok=0;
                        }
                        else
                        {
                            ok=1;
                        }
                    }
                    if (ok==1||gasit==1)
                    {
                        fout<<txt<<"\n";
                    }
                }
                fin.close();
                fout.close();
                //optiune_curenta--;
                scena_curenta=-1;
            }
        }

        if (event.type==sf::Event::MouseButtonReleased)
        {
            for (int i=1; i<=numar_optiuni; i++)
            {
                if (text[i].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y))
                        ||((text[i].getGlobalBounds().top<=mouse.getPosition(window).y&&mouse.getPosition(window).y<=text[i].getGlobalBounds().top+text[i].getGlobalBounds().height)&&
                           (text[i].getGlobalBounds().left-100<=mouse.getPosition(window).x&&mouse.getPosition(window).x<=text[i].getGlobalBounds().left+text[i].getGlobalBounds().width+100)))
                {
                    actiune();
                }
            }
        }
        if (event.type==sf::Event::MouseMoved)
        {
            for (int i=1; i<=numar_optiuni; i++)
            {
                if (text[i].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y))
                        ||((text[i].getGlobalBounds().top<=mouse.getPosition(window).y&&mouse.getPosition(window).y<=text[i].getGlobalBounds().top+text[i].getGlobalBounds().height)&&
                           (text[i].getGlobalBounds().left-100<=mouse.getPosition(window).x&&mouse.getPosition(window).x<=text[i].getGlobalBounds().left+text[i].getGlobalBounds().width+100)))
                {
                    optiune_curenta=i;
                }
            }
        }
        if (event.type == sf::Event::Closed)
        {
            gameOn = 0;
        }
    }
}

void scena_meniu::deplasare()
{
    if (up == 1)
    {
        optiune_curenta--;
        if(optiune_curenta == 0)
        {
            optiune_curenta = 1;
        }
        up = 0;
    }
    if (down == 1)
    {
        optiune_curenta++;
        if (optiune_curenta == numar_optiuni + 1)
        {
            optiune_curenta = numar_optiuni;
        }
        down = 0;
    }
    if (enter == 1)
    {
        actiune();
        enter = 0;
    }
    while (optiune_curenta>numar_optiuni)
        optiune_curenta--;
    while (optiune_curenta<1)
        optiune_curenta++;

}

void scena_meniu::draw()
{
    window.clear();
    window.draw(background);
    afisare_optiuni();
    window.display();
}

void scena_meniu::afisare_optiuni()
{
    for (int i=1; i<=numar_optiuni; i++)
    {
        if (optiune_curenta == i)
        {
            text[i].setFillColor(sf::Color(150,150,150));
            //text[i].setStyle(sf::Text::Underlined);
        }
        else
        {
            text[i].setFillColor(sf::Color::Black);
            //text[i].setStyle(sf::Text::Regular);
        }
        window.draw(text[i]);
    }
}

void scena_meniu::update()
{
    input_tastatura();
    deplasare();
    draw();
}

void scena_meniu::actiune()
{
    if (strstr(optiuni[optiune_curenta], "Play"))
    {
        scena_curenta = -1;
    }
    if (strstr(optiuni[optiune_curenta], "Exit"))
    {
        gameOn = 0;
    }
    if (strstr(optiuni[optiune_curenta], "Playground"))
    {
        modJoc=1;
        scena_curenta = 0;
    }
    if (strstr(optiuni[optiune_curenta], "Back"))
    {
        scena_curenta = 1;
    }
    ifstream fin("saves/saves.txt");
    char text[100];
    while (fin.peek()!=EOF)
    {
        fin.getline(text,100);
        ifstream fin("saves/saves.txt");
        if (text[0]=='N'&&text[1]==':')
        {
            strcpy(text,text+2);
            if (strcmp(optiuni[optiune_curenta],text)==0)
            {
                scena_curenta=0;
                break;
            }
        }
    }
    fin.close();

    //cout << modJoc<<endl;

}

void scena_meniu::generare_text()
{
    int x_optiuni = 200;
    int size=750/numar_optiuni;
    if (size>60)
        size=60;
    //cout << size <<endl;
    int y_optiuni = height - numar_optiuni * (size+0)-size/4;

    for (int i = 1; i <= numar_optiuni; i++)
    {
        string s;
        int aux=i;
        while (aux!=0)
        {
            s=char(aux%10+'0') +s;
            aux/=10;
        }
        s+=". ";
        s+=optiuni[i];
        // cout << s <<endl;
        text[i].setString(s.data());
        text[i].setCharacterSize (size);
        text[i].setPosition(sf::Vector2f(x_optiuni, y_optiuni));
        y_optiuni += size+0;
        text[i].setFillColor(sf::Color::Black);
        text[i].setFont (font);
        text[i].setOutlineColor(sf::Color::Black);
        text[i].setOutlineThickness(1);
    }
}
