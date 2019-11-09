#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>

class Gramatica
{
public:
	Gramatica();
	void citire();
	void afisare();
	int verificare();
	void generare(bool optiune);

private:
	void productiiAplicabile(const std::string& cuvantGenerat, std::vector<int>& prodAplicabile);

private:
	std::vector<char> VN;
	std::vector<char> VT;
	char S;
	std::vector<std::string> prodStanga;
	std::vector<std::string> prodDreapta;
};

