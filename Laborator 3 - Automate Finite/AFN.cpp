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
		afn.m_stari.emplace_back(str);
		--numar;
	}
	in >> numar;
	while (numar)
	{
		char chr;
		in >> chr;
		afn.m_sigma.emplace_back(chr);
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
		afn.m_delta.emplace_back(stareSimbolStare);
		--numar;
	}
	in >> afn.m_stareInitiala;
	in >> numar;
	while (numar)
	{
		std::string str;
		in >> str;
		afn.m_finale.emplace_back(str);
		--numar;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const AFN& afn)
{
	out << "  " << (char)235 << " ";
	for (const auto& simbol : afn.m_sigma)
	{
		out << "| " << simbol << "  ";
	}
	for (const auto& tranzitie : afn.m_delta)
	{
		out << "\n----";
		for (const auto& simbol : afn.m_sigma)
		{
			out << "|----";
		}
		out << '\n';
		bool ok = false;
		if (tranzitie.first.first == afn.m_stareInitiala)
		{
			out << "->";
			ok = true;
		}
		for (const auto& stareFinala : afn.m_finale)
		{
			if (tranzitie.first.first == stareFinala)
			{
				out << "F ";
				ok = true;
				break;
			}
		}
		out << (ok == false ? " " : "") << tranzitie.first.first << (ok == false ? " " : "");
		ok = false;
		for (const auto& simbol : afn.m_sigma)
		{
			if (tranzitie.first.second == simbol)
			{
				out << "| " << tranzitie.second << " ";
				ok = true;
			}
			else
			{
				out << "| -- ";
			}
		}
	}
	out << "\n\n";
	return out;
}

uint8_t AFN::VerificDelta(std::string  cuvant, std::string stare)
{
	if (cuvant == "")
	{
		for(const auto& stareFinala : m_finale)
		{ 
			if (stare == stareFinala)
			{
				return 0;
			}
		}
		return 1;
	}
	bool ok = false;
	for (auto tranzitie : m_delta)
	{
 		if (std::make_pair(stare, cuvant[cuvant.length() - 1]) == tranzitie.first)
		{
			std::string aux = cuvant;
			aux.erase(aux.end()-1);
			uint8_t verif = VerificDelta(aux, tranzitie.second);
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

std::string AFN::Reverse(std::string cuvant)
{
	std::string cuvantNou = "";
	for (int index = cuvant.length() - 1; index >= 0; --index)
	{
		cuvantNou += cuvant[index];
	}
	return cuvantNou;
}

uint8_t AFN::Verificare(std::string cuvant)
{
	return VerificDelta(Reverse(cuvant), m_stareInitiala);
}