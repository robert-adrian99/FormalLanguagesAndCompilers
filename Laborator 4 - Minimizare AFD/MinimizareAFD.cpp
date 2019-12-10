#include "MinimizareAFD.h"
#include <fstream>

MinimizareAFD::MinimizareAFD()
{
	std::string cuvant;
	std::ifstream inAFD("AFD_Input.txt");
	inAFD >> m_afdInitial;
	inAFD.close();
	std::cout << "\nAFD-ul initial:\n";
	std::cout << m_afdInitial;
}

void MinimizareAFD::EliminareStariInaccesibile()
{
	std::vector<std::string> stari;
	for (const auto& stare : m_afdInitial.GetStari())
	{
		if (stare == m_afdInitial.GetStareInitiala())
		{
			stari.emplace_back(stare);
		}
		else
		{
			for (const auto& tranzitie : m_afdInitial.GetDelta())
			{
				if (stare == tranzitie.second)
				{
					stari.emplace_back(stare);
					break;
				}
			}
		}
	}
	m_afdMinimizat.SetStari(stari);
}

void MinimizareAFD::CreareMatriceEchivalenta()
{
	size_t numar_ = 0;
	for (const auto& stare : m_afdMinimizat.GetStari())
	{
		std::vector<std::string> vectorAuxiliar;
		for (size_t index = 0; index < numar_; index++)
		{
			vectorAuxiliar.emplace_back("_");
		}
		numar_++;
		vectorAuxiliar.emplace_back(stare);
		m_matriceEchivalenta.emplace_back(vectorAuxiliar);
	}
}

void MinimizareAFD::MarcareFinalNefinal()
{
	const auto& stariMinimizat = m_afdMinimizat.GetStari();
	for (size_t linie = 0; linie < stariMinimizat.size(); linie++)
	{
		const auto& stare = stariMinimizat[linie];
		for (size_t coloana = 0; coloana < linie; coloana++)
		{
			const auto& perecheStare = stariMinimizat[coloana];
			if (perecheStare != stare &&
				((m_afdInitial.isFinal(perecheStare) && !m_afdInitial.isFinal(stare)) || 
				(!m_afdInitial.isFinal(perecheStare) && m_afdInitial.isFinal(stare))))
			{
				m_matriceEchivalenta[linie][coloana] = "x";
			}
		}
	}
}

void MinimizareAFD::AfisareMatriceEchivalenta()
{
	for (const auto& linieMatrice : m_matriceEchivalenta)
	{
		for (const auto& element : linieMatrice)
		{
			std::cout << element << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void MinimizareAFD::IteratiiMarcareMatrice()
{
	const auto& stariMinimizat = m_afdMinimizat.GetStari();
	int iteratie = 1;
	bool ok = false;
	do
	{
		auto matriceAuxiliara = m_matriceEchivalenta;
		ok = false;
		for (size_t linie = 1; linie < m_matriceEchivalenta.size(); linie++)
		{
			for (size_t coloana = 0; coloana < linie; coloana++)
			{
				if (m_matriceEchivalenta[linie][coloana] == "_")
				{
					std::string stareIntermediara1 = "", stareIntermediara2 = "";
					for (const auto& simbol : m_afdInitial.GetSigma())
					{
						for (const auto& tranzitie : m_afdInitial.GetDelta())
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
								if (m_matriceEchivalenta[indice1][indice2] != "_")
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
		std::cout << "Iteratia " << iteratie++ << ":\n";
		AfisareMatriceEchivalenta();
		m_matriceEchivalenta = matriceAuxiliara;
	} while (ok == true);
}

std::string MinimizareAFD::CautareStareEchivalenta(std::string stare)
{
	for (const auto& stareEchivalenta : m_stariEchivalente)
	{
		for (const auto& stareEchiv : stareEchivalenta)
		{
			if (stareEchiv == stare)
			{
				return stareEchivalenta.front();
			}
		}
	}
	return "";
}

void MinimizareAFD::DetectareStariEchivalente()
{
	const auto& stariMinimizat = m_afdMinimizat.GetStari();
	for (size_t coloana = 0; coloana < m_matriceEchivalenta.size(); coloana++)
	{
		std::vector<std::string> vectorIntermediar;
		vectorIntermediar.push_back(stariMinimizat[coloana]);
		if (CautareStareEchivalenta(stariMinimizat[coloana]) == "")
		{
			for (size_t linie = coloana + 1; linie < m_matriceEchivalenta.size(); linie++)
			{
				if (m_matriceEchivalenta[linie][coloana] == "_")
				{
					vectorIntermediar.push_back(stariMinimizat[linie]);
				}
			}
			m_stariEchivalente.push_back(vectorIntermediar);
		}
	}
	std::cout << "Starile echivalente sunt:\n";
	for (const auto& stareEchivalenta : m_stariEchivalente)
	{
		for (const auto& stare : stareEchivalenta)
		{
			std::cout << stare << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void MinimizareAFD::EliminareStariEchivalenteAndDetectareFinale()
{
	std::vector<std::string> stariMinimizat;
	std::vector<std::string> stariFinale;
	for (const auto& stareEchivalenta : m_stariEchivalente)
	{
		stariMinimizat.push_back(stareEchivalenta.front());
		for (const auto& stare : stareEchivalenta)
		{
			if (m_afdInitial.isFinal(stare))
			{
				stariFinale.push_back(stare);
			}
		}
	}
	m_afdMinimizat.SetStari(stariMinimizat);
	m_afdMinimizat.SetFinale(stariFinale);
}

AFD::StareSimbolStare MinimizareAFD::CreareTranzitie(std::string starePlecare, char simbol, std::string stareSosire)
{
	AFD::StareSimbol stareSimbol = std::make_pair(starePlecare, simbol);
	return std::make_pair(stareSimbol, stareSosire);
}

void MinimizareAFD::RefacDelta()
{
	std::vector<AFD::StareSimbolStare> delta;
	for (const auto& tranzitie : m_afdInitial.GetDelta())
	{
		delta.push_back(std::make_pair(std::make_pair(CautareStareEchivalenta(tranzitie.first.first), tranzitie.first.second), CautareStareEchivalenta(tranzitie.second)));
	}
	m_afdMinimizat.SetDelta(delta);
}

void MinimizareAFD::AlgoritmMinimizare2()
{
	m_afdMinimizat.SetSigma(m_afdInitial.GetSigma());
	m_afdMinimizat.SetStareInitiala(m_afdInitial.GetStareInitiala());
	EliminareStariInaccesibile();
	CreareMatriceEchivalenta();
	MarcareFinalNefinal();
	AfisareMatriceEchivalenta();
	IteratiiMarcareMatrice();
	DetectareStariEchivalente();
	EliminareStariEchivalenteAndDetectareFinale();
	RefacDelta();
}

std::ostream& operator<<(std::ostream& out, MinimizareAFD minimAFD)
{
	out << "AFD-ul minimizat este:\n";
	out << minimAFD.m_afdMinimizat;
	return out;
}