#pragma once
#include "Persona.h"
#include <list>

using std::list;

class Vida
{
private:
    Persona *Adan = nullptr;
    Persona *Eva = nullptr;
    int EdadMax = 100;

    list<Persona *> Personas;
    list<Persona*> Mujeres;
    list<Persona*> Hombres;
public:
    Vida();
    Vida(Persona *Adan, Persona *Eva);
    void Iniciar();
};