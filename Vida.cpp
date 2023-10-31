#include "Vida.h"
#include <iostream>
#include <random>
#include <string>
#include <chrono>

class GeneradorNombres
{
private:
	std::string subfijoHombre;
	std::string subfijoMujer;
	int longitudNombre;

	char generarVocalAleatoria()
	{
		std::random_device rd;
		std::mt19937 generador(rd());
		std::uniform_int_distribution<int> distribucion(0, 4);
		int indice = distribucion(generador);
		std::string vocales = "aeiou";
		return vocales[indice];
	}

	char generarConsonanteAleatoria()
	{
		std::random_device rd;
		std::mt19937 generador(rd());
		std::uniform_int_distribution<int> distribucion(0, 19);
		int indice = distribucion(generador);
		std::string consonantes = "bcdfghjklmnpqrstvwxyz";
		return consonantes[indice];
	}

public:
	GeneradorNombres(const std::string& subfijoH, const std::string& subfijoM, int longitud)
	{
		subfijoHombre = subfijoH;
		subfijoMujer = subfijoM;
		longitudNombre = longitud;
	}

	std::string generarNombreAleatorio(GENERO genero)
	{
		std::random_device rd;
		std::mt19937 generador(rd());
		std::uniform_int_distribution<int> distribucion(2, longitudNombre);
		int longitud = distribucion(generador);
		std::string nombre;

		char ultimoCaracter = '\0';
		char penultimoCaracter = '\0';

		if (genero == HOMBRE)
		{
			longitud -= subfijoHombre.length();
		}
		else
		{
			longitud -= subfijoMujer.length();
		}

		for (int i = 0; i < longitud; i++)
		{
			char caracter;
			if (i == 0)
			{
				// Primer caracter: vocal aleatoria
				caracter = generarVocalAleatoria();
			}
			else if (i == 1)
			{
				// Segundo caracter: consonante después de vocal
				caracter = generarConsonanteAleatoria();
			}
			else
			{
				// Caracteres siguientes
				if (ultimoCaracter == 't' || penultimoCaracter == 'n')
				{
					// Regla para 't' o 'n'
					caracter = (i % 2 == 0) ? generarVocalAleatoria() : generarConsonanteAleatoria();
				}
				else if (ultimoCaracter >= 'a' && ultimoCaracter <= 'z')
				{
					// Regla para consonante no dicha en las primeras reglas
					if ((i - 1) - (ultimoCaracter - 'a') <= 3)
					{
						caracter = (i % 2 == 0) ? generarVocalAleatoria() : generarConsonanteAleatoria();
					}
					else
					{
						caracter = (i % 2 == 0) ? generarVocalAleatoria() : generarConsonanteAleatoria();
					}
				}
				else
				{
					// En caso de no cumplir ninguna regla anterior, se genera aleatoriamente
					caracter = (i % 2 == 0) ? generarVocalAleatoria() : generarConsonanteAleatoria();
				}
			}

			nombre += caracter;
			penultimoCaracter = ultimoCaracter;
			ultimoCaracter = caracter;
		}

		if (genero == HOMBRE)
		{
			nombre += subfijoHombre;
		}
		else
		{
			nombre += subfijoMujer;
		}

		return nombre;
	}

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

};

Vida::Vida()
{
	Adan = nullptr;
	Eva = nullptr;
}

Vida::Vida(Persona* Adan, Persona* Eva)
{
	if(Adan != nullptr && Eva != nullptr)
	{
		this->Adan = Adan;
		this->Eva = Eva;
		this->Adan->SetFertil(true);
		this->Eva->SetFertil(true);
		if (this->Adan != this->Eva)
		{
			Personas.push_back(Adan);
			Personas.push_back(Eva);

			Mujeres.push_back(Eva);
			Hombres.push_back(Adan);
		}
	}
}

void Vida::Iniciar()
{
	while (!Personas.empty())
	{
		std::cout << "Inicio" << std::endl;

		for (auto& it : Hombres) {

			if (it->IsFertil())
				for (auto& et : Mujeres) {
					if (it->CanSnupSnup(et)) {
						GENERO gen;
						string nombre;
						Persona* bebe;
						if (GeneradorNombres("on", "an",0).generarNumeroAleatorio(0, 100) > 50)
						{
							gen = MUJER;
						}
						else
						{
							gen = HOMBRE;
						}
						nombre = GeneradorNombres("on", "an", 15).generarNombreAleatorio(gen);

						if (it->GetGenero() == HOMBRE)
						{
							bebe = new Persona(it, et, nombre, gen);
							Hombres.push_back(bebe);
						}
						else
						{
							bebe = new Persona(et, it, nombre, gen);
							Mujeres.push_back(bebe);
						}

						Personas.push_back(bebe);
						//----------------------
						std::cout << "New beby: " << bebe->GetNombre() << " from: " << it->GetNombre() << " & " << et->GetNombre() << std::endl;
						//----------------------
					}
				}
		}

		auto it = Personas.begin();
		while (it != Personas.end())
		{
			std::cout << "---------------------------------------------\n";
			std::cout << "Nombre: " << (*it)->GetNombre() << std::endl;
			std::cout << "Edad: " << (*it)->GetEdad() << std::endl;
			std::cout << "Genero: " << (*it)->GetGenero() << std::endl;
			std::cout << "Fertil: " << (*it)->IsFertil() << std::endl;
			std::cout << "Hijos: {";
			for (auto& et : (*it)->GetHijos()) {
				std::cout << et->GetNombre() << ", ";
			}
			std::cout << "}" << std::endl;
			if ((*it)->HasPadre())
				std::cout << "Padre: " << (*it)->GetPadre()->GetNombre() << std::endl;
			if ((*it)->HasMadre())
				std::cout << "Madre: " << (*it)->GetMadre()->GetNombre() << std::endl;
			std::cout << "---------------------------------------------\n";

			(*it)->SetEdad((*it)->GetEdad() + 1);
			if ((*it)->GetEdad() > EdadMax)
			{
				(*it)->removeReferences();
				//--------------------------
				std::cout << "Death: " << (*it)->GetNombre() << std::endl;
				//--------------------------
				it = Personas.erase(it); // Eliminar elemento y actualizar el iterador
			}
			else
			{
				++it; // Avanzar al siguiente elemento
			}
		}

		std::cout << "Fin" << std::endl;
	}
	std::cout << "Life has perished :c" << std::endl;
}
