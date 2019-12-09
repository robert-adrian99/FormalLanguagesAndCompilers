#pragma once
#include "AFD.h"

class MinimizareAFD
{
public:
	MinimizareAFD();
	void AlgoritmMinimizare2();
	friend std::ostream& operator<<(std::ostream& out, MinimizareAFD minimAFD);

private:
	void EliminareStariInaccesibile();
	void CreareMatriceEchivalenta();
	void MarcareFinalNefinal();
	void AfisareMatriceEchivalenta();
	void IteratiiMarcareMatrice();
	std::string CautareStareEchivalenta(std::string stare);
	void DetectareStariEchivalente();
	void EliminareStariEchivalenteAndDetectareFinale();
	AFD::StareSimbolStare CreareTranzitie(std::string starePlecare, char simbol, std::string stareSosir);
	void RefacDelta();

private:
	std::vector<std::vector<std::string>> m_matriceEchivalenta;
	std::vector<std::vector<std::string>> m_stariEchivalente;
	AFD m_afdInitial;
	AFD m_afdMinimizat;
};

