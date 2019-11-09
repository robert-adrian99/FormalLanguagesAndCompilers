#pragma once
#include <vector>
#include <string>
#include <iostream>

class AFD
{
private:
	using StareSimbol = std::pair<std::string, char>;
	using StareSimbolStare = std::pair<StareSimbol, std::string>;

public:
	friend std::istream& operator>>(std::istream& in, AFD& afd);
	friend std::ostream& operator<<(std::ostream& out, const AFD& afd);

public:
	uint8_t verificare(std::string cuvant);

private:
	std::vector<std::string> stari;
	std::vector<char> sigma;
	std::vector<StareSimbolStare> delta;
	std::string stareInitiala;
	std::vector<std::string> finale;
};

