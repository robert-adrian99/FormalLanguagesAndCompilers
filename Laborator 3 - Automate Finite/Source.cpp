#include <fstream>
#include "AFD.h"
#include "AFN.h"

void alegeAFD()
{
	std::cout << "Ati ales AFD\n\n";
	AFD afd;
	std::string cuvant;
	std::ifstream inAFD("AFD_Input.txt");
	inAFD >> afd;
	inAFD.close();
	std::cout << afd;
	char optiune;
	do
	{
		std::cout << "Introduceti un cuvant din " << (char)228 << "* pentru a verifica daca este acceptat sau nu de AFD: ";
		std::cin >> cuvant;
		std::cout << std::endl;
		uint8_t verific = afd.verificare(cuvant);
		switch (verific)
		{
		case 0:
			std::cout << "Cuvantul este acceptat!\n";
			break;
		case 1:
			std::cout << "Cuvantul nu este acceptat!\n";
			break;
		case 2:
			std::cout << "Blocaj!\n";
			break;
		default:
			break;
		}
		std::cout << "\nDoriti sa mai verificati un cuvant? y/n ";
		std::cin >> optiune;
		std::cout << std::endl;
	} while (optiune == 'y' ? true : false);
}

void alegeAFN()
{
	std::cout << "Ati ales AFN\n\n";
	AFN afn;
	std::string cuvant;
	std::ifstream inAFN("AFN_Input.txt");
	inAFN >> afn;
	inAFN.close();
	std::cout << afn;
	char optiune;
	do
	{
		std::cout << "Introduceti un cuvant din " << (char)228 << "* pentru a verifica daca este acceptat sau nu de AFN: ";
		std::cin >> cuvant;
		std::cout << std::endl;
		uint8_t verific = afn.verificare(cuvant);
		switch (verific)
		{
		case 0:
			std::cout << "Cuvantul este acceptat!\n";
			break;
		case 1:
			std::cout << "Cuvantul nu este acceptat!\n";
			break;
		case 2:
			std::cout << "Blocaj!\n";
			break;
		default:
			break;
		}
		std::cout << "\nDoriti sa mai verificati un cuvant? y/n ";
		std::cin >> optiune;
		std::cout << std::endl;
	} while (optiune == 'y' ? true : false);
}

int main()
{
	uint16_t optiune;
	do
	{
		std::cout << "Alegeti 1 pentru AFD, 2 pentru AFN sau 9 pentru a parasi programul:";
		std::cin >> optiune;
		std::cout << std::endl;
		switch (optiune)
		{
		case 1:
			alegeAFD();
			break;
		case 2:
			alegeAFN();
			break;
		case 9:
			break;
		default:
			break;
		}
	} while (optiune != 9);
	return 0;
}