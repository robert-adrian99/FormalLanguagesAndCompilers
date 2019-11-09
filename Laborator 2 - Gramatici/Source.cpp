#include <iostream>
#include "Gramatica.h"

void afisareVerificare(int val)
{
	std::cout << std::endl;
	switch (val)
	{
	case 0:
		std::cout << "Gramatica este corecta!";
		break;
	case 1:
		std::cout << "VN intersectat cu VT nu este vid!";
		break;
	case 2:
		std::cout << "S nu apartine lui VN!";
		break;
	case 3:
		std::cout << "Membrul stang al unei productii nu contine nici un terminal!";
		break;
	case 4:
		std::cout << "Nu exista nici o productie al carei membru stang sa contina doar S!";
		break;
	case 5:
		std::cout << "Cel putin o productie contine si alte elemente in afara de cele din VN si VT!";
		break;
	default:
		std::cout << "A aparut o eroare!";
		break;
	}
	std::cout << std::endl;
}

int main()
{
	Gramatica gram;
	gram.citire();
	std::cout << std::endl;
	std::cout << "Gramatica este:" << std::endl;
	gram.afisare();
	int val = gram.verificare();
	afisareVerificare(val);
	if (val == 0)
	{
		int optiune;
		unsigned int nr;
		std::cout << std::endl << "Introduceti 0 pt a afisa doar cuvantul generat si 1 pt a afisa si pasii intermediari!" << std::endl;
		std::cout << "Optiunea: ";
		std::cin >> optiune;
		std::cout << "Introduceti numarul de cuvinte care sa fie generate!" << std::endl;
		std::cout << "Numarul de cuvinte:";
		std::cin >> nr;
		int index = 1;
		while (nr > 0)
		{
			std::cout << index << ". ";
			gram.generare(optiune);
			std::cout << std::endl;
			--nr;
			++index;
		}
	}
	return 0;
}