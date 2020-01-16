#include "AnalizatorLexical.h"
#include <iostream>
#include <fstream>

void AnalizatorLexical::Analizeaza(const std::string& numeFisier)
{
	char caracter;
	std::string buffer;
	std::fstream fisier(numeFisier);

	if (!fisier.is_open())
	{
		std::cout << "error while opening the file\n";
		return;
	}

	bool singleLineComment = false;
	bool multiLineComment = false;
	while (fisier >> std::noskipws >> caracter)
	{
		if (singleLineComment || multiLineComment)
		{
			if (singleLineComment && caracter == '\n')
			{
				singleLineComment = false;
			}

			if (multiLineComment && caracter == '*')
			{
				fisier >> caracter;
				if (caracter == EOF)
				{
					break;
				}

				if (caracter == '/')
				{
					multiLineComment = false;
				}
			}
			continue;
		}

		if (caracter == '/')
		{
			std::string comment(1, caracter);
			fisier >> caracter;
			if (caracter == EOF)
			{
				AfiseazaUnitatiLexicale(comment);
				break;
			}

			if (caracter == '*')
			{
				multiLineComment = true;
				comment += caracter;
			}
			else if (caracter == '/')
			{
				singleLineComment = true;
				comment += caracter;
			}
			if (multiLineComment || singleLineComment)
			{
				AfiseazaUnitatiLexicale(comment);
				continue;
			}
		}

		if (IsSpatiu(std::string(1, caracter)))
		{
			if (!buffer.empty())
			{
				AfiseazaUnitatiLexicale(buffer);
				buffer = "";
			}
			continue;
		}

		if (IsOperator(std::string(1, caracter)))
		{
			if (!buffer.empty() && !IsOperator(buffer))
			{
				AfiseazaUnitatiLexicale(buffer);
				buffer = "";
			}
		}

		if (IsSeparator(std::string(1, caracter)))
		{
			if (!buffer.empty())
			{
				AfiseazaUnitatiLexicale(buffer);
				buffer = "";
			}
			if (IsSeparator(std::string(1, caracter)))
			{
				AfiseazaUnitatiLexicale(std::string(1, caracter));
				continue;
			}
		}
		buffer += caracter;
	}
	fisier.close();
}

bool AnalizatorLexical::IsIdentificator(const std::string& string)
{
	if (isdigit(string[0]))
	{
		return false;
	}
	for (int index = 0; index < string.length(); ++index)
	{
		if (!isalpha(string[index]) && !isdigit(string[index]) && string[index] != '_')
		{
			return false;
		}
	}
	return true;
}

bool AnalizatorLexical::IsNumar(const std::string& string)
{
	for (int index = 0; index < string.length(); ++index)
	{
		if (!isdigit(string[index]))
		{
			return false;
		}
	}
	return true;
}

bool AnalizatorLexical::IsValoareBooleana(const std::string& string)
{
	return string == "true" || string == "false";
}

bool AnalizatorLexical::IsString(const std::string& string)
{
	return string[0] == '"' && string[string.length() - 1] == '"';
}

bool AnalizatorLexical::IsComentariu(const std::string& string)
{
	return string == "/*" || string == "//";
}

bool AnalizatorLexical::IsCuvantCheie(const std::string& string)
{
	for (const auto& cuvantCheie : cuvinteCheie)
	{
		if (cuvantCheie == string)
		{
			return true;
		}
	}
	return false;
}

bool AnalizatorLexical::IsInstructiune(const std::string& string)
{
	for (const auto& instructiune : instructiuni)
	{
		if (instructiune == string)
		{
			return true;
		}
	}
	return false;
}

bool AnalizatorLexical::IsOperator(const std::string& string)
{
	for (const auto& operatorIndex : operatori)
	{
		if (operatorIndex == string)
		{
			return true;
		}
	}
	return false;
}

bool AnalizatorLexical::IsSeparator(const std::string& string)
{
	for (const auto& separator : separatori)
	{
		if (separator == string)
		{
			return true;
		}
	}
	return false;
}

bool AnalizatorLexical::IsSpatiu(const std::string& string)
{
	return string == " " || string == "\n" || string == "\t";
}

void AnalizatorLexical::AfiseazaUnitatiLexicale(const std::string& token)
{
	if (IsOperator(token))
	{
		std::cout << "< operator      - " << token << " >" << std::endl;
	}
	else if (IsSeparator(token))
	{
		std::cout << "< separator     - " << token << " >" << std::endl;
	}
	else if (IsCuvantCheie(token))
	{
		std::cout << "< cuvant cheie  - " << token << " >" << std::endl;
	}
	else if (IsInstructiune(token))
	{
		std::cout << "< instructiune  - " << token << " >" << std::endl;
	}
	else if (IsNumar(token))
	{
		std::cout << "< numar         - " << token << " >" << std::endl;
	}
	else if (IsString(token))
	{
		std::cout << "< string        - " << token << " >" << std::endl;
	}
	else if (IsValoareBooleana(token))
	{
		std::cout << "< bool          - " << token << " >" << std::endl;
	}
	else if (IsIdentificator(token))
	{
		std::cout << "< identificator - " << token << " >" << std::endl;
	}
	else if (IsComentariu(token))
	{
		std::cout << "< comentariu    - " << token << " >" << std::endl;
	}
}

