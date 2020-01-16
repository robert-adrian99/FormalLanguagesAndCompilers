#pragma once
#include <string>
#include <array>

class AnalizatorLexical
{
public:
	void Analizeaza(const std::string& numeFisier);

private:
	bool IsIdentificator(const std::string& string);
	bool IsNumar(const std::string& string);
	bool IsValoareBooleana(const std::string& string);
	bool IsString(const std::string& string);
	bool IsComentariu(const std::string& string);
	bool IsCuvantCheie(const std::string& string);
	bool IsInstructiune(const std::string& string);
	bool IsOperator(const std::string& string);
	bool IsSeparator(const std::string& string);
	bool IsSpatiu(const std::string& str);
	void AfiseazaUnitatiLexicale(const std::string& token);

private:
	const std::array<std::string, 8> cuvinteCheie{ "void", "int", "float", "auto", "double", "do", "switch", "return" };
	const std::array<std::string, 16> operatori{ "<", ">", "<=", ">=", "*", "+", "-", "/", "=", "-=", "*=", "+=", "/=", "++", "--", "==" };
	const std::array<std::string, 8> separatori{ "{", "}", ",", "(", ")", ";" , "[", "]" };
	const std::array<std::string, 3> instructiuni{ "for", "while", "if" };
};

