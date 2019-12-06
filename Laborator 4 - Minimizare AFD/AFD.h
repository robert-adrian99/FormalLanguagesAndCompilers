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
	uint8_t Verificare(std::string cuvant);
	std::vector<std::string> GetStari() const;
	std::vector<char> GetSigma() const;
	std::vector<StareSimbolStare> GetDelta() const;
	std::string GetStareInitiala() const;
	std::vector<std::string> GetFinale() const;
	void SetStari(const std::vector<std::string>& stari);
	void SetSigma(const std::vector<char>& sigma);
	void SetDelta(const std::vector<StareSimbolStare>& delta);
	void SetStareInitiala(const std::string& stareInitiala);
	void SetFinale(const std::vector<std::string>& finale);
	bool isFinal(const std::string& posibilFinal) const;

private:
	std::vector<std::string> m_stari;
	std::vector<char> m_sigma;
	std::vector<StareSimbolStare> m_delta;
	std::string m_stareInitiala;
	std::vector<std::string> m_finale;
};

