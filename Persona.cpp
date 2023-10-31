#include "Persona.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

int generarNumeroAleatorio(int rangoMinimo, int rangoMaximo) {
    // Obtener la semilla basada en el tiempo actual
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    // Crear el generador de números pseudoaleatorios con la semilla
    std::mt19937 generador(seed);
    
    // Crear la distribución uniforme dentro del rango especificado
    std::uniform_int_distribution<int> distribucion(rangoMinimo, rangoMaximo);
    
    // Generar y devolver el número aleatorio
    return distribucion(generador);
}

Persona::Persona()
{
    this->Edad = 0;
    this->Nombre = "sin nombre";
    this->Genero = MUJER;
    this->Padre = nullptr;
    this->Madre = nullptr;
}

Persona::Persona(Persona *Padre, Persona *Madre, string Nombre, GENERO Genero)
{
    this->Padre = Padre;
    if(Padre != nullptr) this->Padre->AgregarHijo(this);
    this->Madre = Madre;
    if(Madre != nullptr) this->Madre->AgregarHijo(this);
    this->Nombre = Nombre;
    this->Genero = Genero;
    this->Edad = 0;
    int code = 0;
    for (auto &it : Nombre) {
        code += it;
    }
    this->Fertil = (generarNumeroAleatorio(0, code) >= (code / 2));
}

void Persona::AgregarHijo(Persona *Hijo)
{
    if(Hijo != nullptr){
        Hijos.push_back(Hijo);
    }
}

bool Persona::HasHermanos()
{
    bool has;
    if(HasPadre()){
        has = (Padre->GetHijos().size() > 1);
    }else{
        has = false;
    }

    if(HasMadre()){
        has = (Madre->GetHijos().size() > 1);
    }else{
        has = false;
    }
    return has;
}

void Persona::removeReferences()
{
    if(HasPadre()){
        auto hijos = Padre->GetHijos();
        auto it = std::find(hijos.begin(), hijos.end(), this);

        hijos.erase(it);
    }

    if(HasMadre()){
        auto hijos = Madre->GetHijos();
        auto it = std::find(hijos.begin(), hijos.end(), this);

        hijos.erase(it);
    }

    if(HasHijos()){
        if(GetGenero() == HOMBRE)
            for(auto &it: Hijos){
                it->SetPadre(nullptr);
            }
        else
            for(auto &it: Hijos){
                it->SetMadre(nullptr);
            }
    }
}

bool Persona::CanSnupSnup(Persona *persona)
{
    if (!IsFertil())
        return false;

    if(persona != nullptr){
        if (!persona->IsFertil())
            return false;
        if(this->GetGenero() != persona->GetGenero()){
            if(this->GetEdad() > generarNumeroAleatorio(9, 14)){
                if(persona->GetEdad() > generarNumeroAleatorio(9, 14)){
                    if(this->GetGenero() == HOMBRE){
                        if(persona->GetHijos().size() < 5){
                            return true;
                        }
                    }else{
                        if(this->GetHijos().size() < 5){
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Persona::IsFertil()
{
    return Fertil;
}

vector<Persona *> Persona::GetHermanos()
{
    vector<Persona *> hermanos;

    if(HasHermanos()){
        if(HasPadre()){
            for(auto &it: GetPadre()->GetHijos()){
                if(it != this){
                    hermanos.push_back(it);
                }
            }
        }

        if(HasMadre()){
            for(auto &it: GetMadre()->GetHijos()){
                if(std::find(hermanos.begin(), hermanos.end(), it) == hermanos.end()){
                    if(it != this){
                        hermanos.push_back(it);
                    }
                }
            }
        }
    }

    return hermanos;
}
