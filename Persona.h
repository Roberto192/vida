#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

enum GENERO{
    HOMBRE, MUJER
};

class Persona
{
private:
    Persona *Padre = nullptr;
    Persona *Madre = nullptr;
    vector<Persona *> Hijos;
    string Nombre;
    GENERO Genero;
    int Edad;
    bool Fertil;
public:
    Persona();
    Persona(Persona *Padre, Persona *Madre, string Nombre, GENERO Genero);
    void AgregarHijo(Persona *Hijo);

    bool HasPadre(){return Padre != nullptr;};
    bool HasMadre(){return Madre != nullptr;};
    bool HasHijos(){return !Hijos.empty();};
    bool HasHermanos();
    bool CanSnupSnup(Persona *persona);
    bool IsFertil();

    void removeReferences();
    void SetPadre(Persona *Padre){this->Padre = Padre;};
    void SetMadre(Persona *Madre){this->Madre = Madre;};
    void SetNombre(string Nombre){this->Nombre = Nombre;};
    void SetEdad(int Edad){this->Edad = Edad;};
    void SetFertil(bool fertil) { this->Fertil = fertil; };
    
    Persona* GetPadre(){return this->Padre;};
    Persona* GetMadre(){return this->Madre;};
    string GetNombre(){return this->Nombre;};
    int GetEdad(){return this->Edad;};
    GENERO GetGenero(){return this->Genero;};
    vector<Persona *>& GetHijos(){return this->Hijos;};
    vector<Persona *> GetHermanos();
};
