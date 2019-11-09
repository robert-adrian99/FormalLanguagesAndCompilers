#include "AFN.h"
#include <cstdint>

std::istream& operator>>(std::istream& in, AFN& afn)
{
	uint16_t numar;
	in >> numar;
	while (numar)
	{
		std::string str;
		in >> str;
		afn.stari.emplace_back(str);
		--numar;
	}
	in >> numar;
	while (numar)
	{
		char chr;
		in >> chr;
		afn.sigma.emplace_back(chr);
		--numar;
	}
	in >> numar;
	while (numar)
	{
		std::string str1, str2;
		char chr;
		in >> str1;
		in >> chr;
		in >> str2;
		AFN::StareSimbol stareSimbol = std::make_pair(str1, chr);
		AFN::StareSimbolStare stareSimbolStare = std::make_pair(stareSimbol, str2);
		afn.delta.emplace_back(stareSimbolStare);
		--numar;
	}
	in >> afn.stareInitiala;
	in >> numar;
	while (numar)
	{
		std::string str;
		in >> str;
		afn.finale.emplace_back(str);
		--numar;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const AFN& afn)
{
	//out << "\nStarile automatului sunt: ";
	//for (const auto& stare : afn.stari)
	//{
	//	out << stare << " ";
	//}
	//out << "\n\nAlfabetul de intrare este: ";
	//for (const auto& simbol : afn.sigma)
	//{
	//	out << simbol << " ";
	//}
	//out << "\n\nFunctia de tranzitie este:\n";
	//for (const auto& stareSimbolStare : afn.delta)
	//{
	//	const auto& stareSimbol = stareSimbolStare.first;
	//	out << (char)235 << "(" << stareSimbol.first << ", " << stareSimbol.second << ") = " << stareSimbolStare.second << '\n';
	//}
	//out << "\nStarea initiala este: " << afn.stareInitiala << '\n';
	//out << "\nStarile finale sunt: ";
	//for (const auto& stare : afn.finale)
	//{
	//	out << stare << " ";
	//}
	//out << "\n\n";
	out << "  " << (char)235 << " ";
	for (const auto& simbol : afn.sigma)
	{
		out << "| " << simbol << "  ";
	}
	for (const auto& stareLinie : afn.stari)
	{
		out << "\n----";
		for (const auto& simbol : afn.sigma)
		{
			out << "|----";
		}
		out << '\n';
		if (stareLinie == afn.stareInitiala)
		{
			out << "->" << stareLinie;
		}
		else
		{
			bool ok = false;
			for (const auto& stareFinala : afn.finale)
			{
				if (stareLinie == stareFinala)
				{
					out << "F " << stareLinie;
					ok = true;
					break;
				}
			}
			if (ok == false)
			{
				out << "  " << stareLinie;
			}
		}
		for (const auto& simbol : afn.sigma)
		{
			bool ok = false;
			for (const auto& stareSimbolStare : afn.delta)
			{
				if (std::make_pair(stareLinie, simbol) == stareSimbolStare.first)
				{
					out << "| " << stareSimbolStare.second << " ";
					ok = true;
					break;
				}
			}
			if (ok == false)
			{
				out << "| -- ";
			}
		}
	}
	out << "\n\n";
	return out;
}

uint8_t AFN::verificDelta(std::string  cuvant, std::string stare)
{
	if (cuvant == "")
	{
		for(const auto& stareFinala : finale)
		{ 
			if (stare == stareFinala)
			{
				return 0;
			}
		}
		return 1;
	}
	bool ok = false;
	for (auto tranzitie : delta)
	{
 		if (std::make_pair(stare, cuvant[cuvant.length() - 1]) == tranzitie.first)
		{
			std::string aux = cuvant;
			aux.erase(aux.end()-1);
			uint8_t verif = verificDelta(aux, tranzitie.second);
			if (verif == 0)
			{
				return 0;
			}
			if (verif == 1)
			{
				ok = true;
			}
		}
	}
	if (ok == true)
	{
		return 1;
	}
	return 2;
}

std::string AFN::reverse(std::string cuvant)
{
	std::string cuvantNou = "";
	for (int index = cuvant.length() - 1; index >= 0; --index)
	{
		cuvantNou += cuvant[index];
	}
	return cuvantNou;
}

uint8_t AFN::verificare(std::string cuvant)
{
	return verificDelta(reverse(cuvant), stareInitiala);
}