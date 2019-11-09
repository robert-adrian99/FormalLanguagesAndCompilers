#include "AFD.h"
#include <cstdint>

std::istream& operator>>(std::istream& in, AFD& afd)
{
	uint16_t numar;
	in >> numar;
	while (numar)
	{
		std::string str;
		in >> str;
		afd.stari.emplace_back(str);
		--numar;
	}
	in >> numar;
	while (numar)
	{
		char chr;
		in >> chr;
		afd.sigma.emplace_back(chr);
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
		AFD::StareSimbol stareSimbol = std::make_pair(str1, chr);
		AFD::StareSimbolStare stareSimbolStare = std::make_pair(stareSimbol, str2);
		afd.delta.emplace_back(stareSimbolStare);
		--numar;
	}
	in >> afd.stareInitiala;
	in >> numar;
	while (numar)
	{
		std::string str;
		in >> str;
		afd.finale.emplace_back(str);
		--numar;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const AFD& afd)
{
	//out << "\nStarile automatului sunt: ";
	//for (const auto& stare : afd.stari)
	//{
	//	out << stare << " ";
	//}
	//out << "\n\nAlfabetul de intrare este: ";
	//for (const auto& simbol : afd.sigma)
	//{
	//	out << simbol << " ";
	//}
	//out << "\n\nFunctia de tranzitie este:\n";
	//for (const auto& stareSimbolStare : afd.delta)
	//{
	//	const auto& stareSimbol = stareSimbolStare.first;
	//	out << (char)235 << "(" << stareSimbol.first << ", " << stareSimbol.second << ") = " << stareSimbolStare.second << '\n';
	//}
	//out << "\nStarea initiala este: " << afd.stareInitiala << '\n';
	//out << "\nStarile finale sunt: ";
	//for (const auto& stare : afd.finale)
	//{
	//	out << stare << " ";
	//}
	//out << "\n\n";
	out << "  " << (char)235 << " ";
	for (const auto& simbol : afd.sigma)
	{
		out << "| " << simbol << "  ";
	}
	for(const auto& stareLinie : afd.stari)
	{
		out << "\n----";
		for (const auto& simbol : afd.sigma)
		{
			out << "|----";
		}
		out << '\n';
		if (stareLinie == afd.stareInitiala)
		{
			out << "->" << stareLinie;
		}
		else
		{
			bool ok = false;
			for (const auto& stareFinala : afd.finale)
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
		for (const auto& simbol : afd.sigma)
		{
			bool ok = false;
			for (const auto& stareSimbolStare : afd.delta)
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

uint8_t AFD::verificare(std::string cuvant)
{
	std::string stare = stareInitiala;
	for (const auto& simbol : cuvant)
	{
		bool gasit = false;
		for (const auto& stareSimbolStare : delta)
		{
			if (std::make_pair(stare, simbol) == stareSimbolStare.first)
			{
				stare = stareSimbolStare.second;
				gasit = true;
				break;
			}
		}
		if (gasit == false)
		{
			return 2;
		}
	}
	for (const auto& stareFinala : finale)
	{
		if (stareFinala == stare)
		{
			return 0;
		}
	}
	return 1;
}