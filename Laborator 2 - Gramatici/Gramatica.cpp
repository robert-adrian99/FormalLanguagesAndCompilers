#include "Gramatica.h"


Gramatica::Gramatica()
{
	srand((unsigned)time(0));
}

void Gramatica::citire()
{
	std::ifstream input("FileInput.txt");
	char caracter;
	int nrProd;
	input >> caracter;
	while (caracter != '0')
	{
		VN.push_back(caracter);
		input >> caracter;
	}
	input >> caracter;
	while (caracter != '0')
	{
		VT.push_back(caracter);
		input >> caracter;
	}
	input >> S;
	input >> nrProd;
	std::string str;
	while (nrProd)
	{
		input >> str;
		prodStanga.push_back(str);
		input >> str;
		prodDreapta.push_back(str);
		--nrProd;
	}
}

void Gramatica::afisare()
{
	std::cout << "VN = { ";
	for (auto chr : VN)
	{
		std::cout << chr << ", ";
	}
	std::cout << "}" << std::endl;
	std::cout << "VT = { ";
	for (auto chr : VT)
	{
		std::cout << chr << ", ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Simbolul de start = " << S << std::endl;
	for (size_t index = 0; index < prodDreapta.size(); index++)
	{
		std::cout << prodStanga[index] << " -> " << prodDreapta[index] << std::endl;
	}
}

int Gramatica::verificare()
{
	// APARTENENTA LUI S LA VN SI INTERSECTIA LUI VN CU VT VIDA
	// verific apartenenta lui S la VN
	bool verificStart = false;
	for (auto chr : VN)
	{
		if (chr == S)
		{
			// S apartine lui VN
			verificStart = true;
		}
		//verific ca intersectia lui VN cu VT sa fie vida
		for (auto chr2 : VT)
		{
			if (chr == chr2)
			{
				// am gasit ca intersectia VN cu VT nu este vida
				return 1;
			}
		}
	}
	if (verificStart == false)
	{
		// S nu apartine lui VN
		return 2;
	}

	// MEMBRUL STANG AL PRODUCTIEI
	// resetez verificStart pt verificare daca exista o productie doar cu S in stanga
	verificStart = false;
	for (auto str : prodStanga)
	{
		std::string strStart = "";
		strStart += S;
		if (str == strStart)
		{
			// am gasit ca productia are doar S in stanga
			verificStart = true;
		}
		// verific daca exista cel putin un neterminal in productie
		bool verificNeterminal = false;
		for (auto chr : str)
		{
			// verific ca elementul din productie sa fie din VN sau VT
			bool verificElement = false;
			for (auto chr1 : VN)
			{
				if (chr == chr1)
				{
					// am gasit ca elementul din stanga din productie este din VN
					verificElement = true;
					// am gasit ca exista cel putin un neterminal in stanga intr-o productie
					verificNeterminal = true;
				}
			}
			if (verificElement == false)
			{
				// elementul nu este in VN => verific daca este in VT
				for (auto chr1 : VT)
				{
					if (chr == chr1)
					{
						// am gasit ca elementul este in VT
						verificElement = true;
					}
				}
			}
			if (verificElement == false)
			{
				// elementul din stanga din productie nu este nici in VN, nici in VT
				return 5;
			}
		}
		if (verificNeterminal == false)
		{
			// membrul stang al productiei nu contine nici un neterminal
			return 3;
		}
	}
	if (verificStart == false)
	{
		// nu exista nici o productie care sa aiba doar S in stanga
		return 4;
	}

	// MEMBRUL DREPT AL PRODUCTIEI
	for (auto str : prodDreapta)
	{
		for (auto chr : str)
		{
			// verific ca elementul din productie sa fie din VN sau VT
			bool verificElement = false;
			for (auto chr1 : VN)
			{
				if (chr == chr1)
				{
					// am gasit ca elementul este din VN
					verificElement = true;
				}
			}
			if (verificElement == false)
			{
				// elementul nu este in VN => verific daca este in VT
				for (auto chr1 : VT)
				{
					if (chr == chr1)
					{
						// am gasit ca elementul este din VT
						verificElement = true;
					}
				}
			}
			if (verificElement == false)
			{
				// elementul din dreapta din productie nu este nici in VN, nici in VT
				return 5;
			}
		}
	}
	// toate conditiile sunt indeplinite => gramatica este corecta
	return 0;
}

void Gramatica::productiiAplicabile(const std::string& cuvantGenerat, std::vector<int>& prodAplicabile)
{
	prodAplicabile.clear();
	for (size_t index = 0; index < prodStanga.size(); index++)
	{
		if (cuvantGenerat.find(prodStanga[index]) != std::string::npos)
		{
			prodAplicabile.push_back(index);
		}
	}
}

void Gramatica::generare(bool optiune)
{
	std::string cuvantGenerat = "";
	cuvantGenerat += S;
	std::vector<int> prodAplicabile;
	productiiAplicabile(cuvantGenerat, prodAplicabile);
	while (prodAplicabile.size())
	{
		int aplica = rand() % prodAplicabile.size();
		auto x = cuvantGenerat.find(prodStanga[prodAplicabile[aplica]]);
		std::string temporar = "";
		temporar.assign(cuvantGenerat.begin() + x + prodStanga[prodAplicabile[aplica]].length(), cuvantGenerat.end());
		if (optiune == true)
		{
			std::cout << cuvantGenerat << " => ";
		}
		cuvantGenerat.replace(cuvantGenerat.begin() + x, cuvantGenerat.end(), prodDreapta[prodAplicabile[aplica]]);
		cuvantGenerat.append(temporar);
		productiiAplicabile(cuvantGenerat, prodAplicabile);
	}
	std::cout << cuvantGenerat << std::endl;
}