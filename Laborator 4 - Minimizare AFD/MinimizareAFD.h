#pragma once
#include "AFD.h"

class MinimizareAFD
{
public:
	MinimizareAFD();
	void AlgoritmMinimizare2();

private:
	std::vector<std::vector<std::string>> matriceEchivalenta;
	AFD afdInitial;
	AFD afdMinimizat;
};

