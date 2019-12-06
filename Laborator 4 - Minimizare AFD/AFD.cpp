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
		afd.m_stari.emplace_back(str);
		--numar;
	}
	in >> numar;
	while (numar)
	{
		char chr;
		in >> chr;
		afd.m_sigma.emplace_back(chr);
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
		afd.m_delta.emplace_back(stareSimbolStare);
		--numar;
	}
	in >> afd.m_stareInitiala;
	in >> numar;
	while (numar)
	{
		std::string str;
		in >> str;
		afd.m_finale.emplace_back(str);
		--numar;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const AFD& afd)
{
	out << "  " << (char)235 << " ";
	for (const auto& simbol : afd.m_sigma)
	{
		out << "| " << simbol << "  ";
	}
	for (const auto& stareLinie : afd.m_stari)
	{
		out << "\n----";
		for (const auto& simbol : afd.m_sigma)
		{
			out << "|----";
		}
		out << '\n';
		if (stareLinie == afd.m_stareInitiala)
		{
			out << "->" << stareLinie;
		}
		else
		{
			bool ok = false;
			for (const auto& stareFinala : afd.m_finale)
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
		for (const auto& simbol : afd.m_sigma)
		{
			bool ok = false;
			for (const auto& stareSimbolStare : afd.m_delta)
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

uint8_t AFD::Verificare(std::string cuvant)
{
	std::string stare = m_stareInitiala;
	for (const auto& simbol : cuvant)
	{
		bool gasit = false;
		for (const auto& stareSimbolStare : m_delta)
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
	for (const auto& stareFinala : m_finale)
	{
		if (stareFinala == stare)
		{
			return 0;
		}
	}
	return 1;
}

std::vector<std::string> AFD::GetStari() const
{
	return m_stari;
}

std::vector<char> AFD::GetSigma() const
{
	return m_sigma;
}

std::vector<AFD::StareSimbolStare> AFD::GetDelta() const
{
	return m_delta;
}

std::string AFD::GetStareInitiala() const
{
	return m_stareInitiala;
}

std::vector<std::string> AFD::GetFinale() const
{
	return m_finale;
}

void AFD::SetStari(const std::vector<std::string>& stari)
{
	m_stari = stari;
}

void AFD::SetSigma(const std::vector<char>& sigma)
{
	m_sigma = sigma;
}

void AFD::SetDelta(const std::vector<StareSimbolStare>& delta)
{
	m_delta = delta;
}

void AFD::SetStareInitiala(const std::string& stareInitiala)
{
	m_stareInitiala = stareInitiala;
}

void AFD::SetFinale(const std::vector<std::string>& finale)
{
	m_finale = finale;
}

bool AFD::isFinal(const std::string& posibilFinal) const
{
	for (const auto& stareFinala : m_finale)
	{
		if (posibilFinal == stareFinala)
		{
			return true;
		}
	}
	return false;
}
