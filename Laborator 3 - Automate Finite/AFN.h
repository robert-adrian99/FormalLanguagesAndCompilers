#pragma once
#include <vector>
#include <string>
#include <iostream>

class AFN
{
private:
	using StareSimbol = std::pair<std::string, char>;
	using StareSimbolStare = std::pair<StareSimbol, std::string>;

public:
	friend std::istream& operator>>(std::istream& in, AFN& afn);
	friend std::ostream& operator<<(std::ostream& out, const AFN& afn);

private:
	uint8_t VerificDelta(std::string cuvant, std::string stare);
	std::string Reverse(std::string cuvant);

public:
	uint8_t Verificare(std::string cuvant);

private:
	std::vector<std::string> m_stari;
	std::vector<char> m_sigma;
	std::vector<StareSimbolStare> m_delta;
	std::string m_stareInitiala;
	std::vector<std::string> m_finale;
};