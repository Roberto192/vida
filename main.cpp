#include <iostream>
#include "Vida.h"

int main(){

    Vida nuevaVida(new Persona(nullptr, nullptr, "Adan", HOMBRE), new Persona(nullptr, nullptr, "Eva", MUJER));
    
    nuevaVida.Iniciar();
    return 0;
}