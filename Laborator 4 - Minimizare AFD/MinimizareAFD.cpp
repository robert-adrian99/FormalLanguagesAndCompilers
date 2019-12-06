#include "MinimizareAFD.h"
#include <fstream>

MinimizareAFD::MinimizareAFD()
{
	std::string cuvant;
	std::ifstream inAFD("AFD_Input.txt");
	inAFD >> afdInitial;
	inAFD.close();
	std::cout << afdInitial;
}

void MinimizareAFD::AlgoritmMinimizare2()
{
	std::vector<std::string> stari;
	for (const auto& stare : afdInitial.GetStari())
	{
		if (stare == afdInitial.GetStareInitiala())
		{
			stari.emplace_back(stare);
		}
		else 
		{
			for (const auto& tranzitie : afdInitial.GetDelta())
			{
				if (stare == tranzitie.second)
				{
					stari.emplace_back(stare);
					break;
				}
			}
		}
	}
	afdMinimizat.SetStari(stari);
	size_t numar_ = 0;
	for (const auto& stare : afdMinimizat.GetStari())
	{
		std::vector<std::string> vectorAuxiliar;
		for (size_t index = 0; index < numar_; index++)
		{
			vectorAuxiliar.emplace_back("_");
		}
		numar_++;
		vectorAuxiliar.emplace_back(stare);
		matriceEchivalenta.emplace_back(vectorAuxiliar);
	}
	const auto& stariMinimizat = afdMinimizat.GetStari();
	for (size_t linie = 0; linie < stari.size(); linie++)
	{
		const auto& stare = stariMinimizat[linie];
		for (size_t coloana = 0; coloana < linie; coloana++)
		{
			const auto& perecheStare = stariMinimizat[coloana];
			if (perecheStare != stare &&
			((afdInitial.isFinal(perecheStare) && !afdInitial.isFinal(stare)) 
			|| (!afdInitial.isFinal(perecheStare) && afdInitial.isFinal(stare))))
			{
				matriceEchivalenta[linie][coloana] = "x";
			}
		}
	}
	for (const auto& linieMatrice : matriceEchivalenta)
	{
		for (const auto& element : linieMatrice)
		{
			std::cout << element << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	int iteratie = 1;
	bool ok = false;
	do
	{
		auto matriceAuxiliara = matriceEchivalenta;
		ok = false;
		for (size_t linie = 0; linie < matriceEchivalenta.size(); linie++)
		{
			for (size_t coloana = 0; coloana < linie; coloana++)
			{
				if (matriceEchivalenta[linie][coloana] == "_")
				{
					std::string stareIntermediara1 = "", stareIntermediara2 = "";
					for (const auto& simbol : afdInitial.GetSigma())
					{
						for (const auto& tranzitie : afdInitial.GetDelta())
						{
							if (tranzitie.first.first == stariMinimizat[linie] && tranzitie.first.second == simbol)
							{
								stareIntermediara1 = tranzitie.second;
							}
							if (tranzitie.first.first == stariMinimizat[coloana] && tranzitie.first.second == simbol)
							{
								stareIntermediara2 = tranzitie.second;
							}
						}
						if (stareIntermediara1 != "" && stareIntermediara2 != "")
						{
							size_t indice1 = -1, indice2 = -1;
							for (size_t index = 0; index < stariMinimizat.size(); index++)
							{
								if (stareIntermediara1 == stariMinimizat[index])
								{
									indice1 = index;
								}
								if (stareIntermediara2 == stariMinimizat[index])
								{
									indice2 = index;
								}
							}
							if (indice1 == indice2)
							{
								break;
							}
							else
							{
								if (indice1 < indice2)
								{
									std::swap(indice1, indice2);
								}
								if (matriceEchivalenta[indice1][indice2] != "_")
								{
									matriceAuxiliara[linie][coloana] = "x";
									ok = true;
								}
							}
						}
					}
				}
			}
		}
		std::cout << "Iteratia " << iteratie++ <<":\n";
		for (const auto& linieMatrice : matriceEchivalenta)
		{
			for (const auto& element : linieMatrice)
			{
				std::cout << element << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		matriceEchivalenta = matriceAuxiliara;
	} while (ok == true);

}
