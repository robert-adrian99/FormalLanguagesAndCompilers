/*1. Să se determine de câte ori apare un anumit caracter într-un șir de caractere dat.*/
#include <iostream>
#include <string>

int numberChar(std::string str, char chr)
{
	int number = 0;
	for (int i = 0; i < str.length(); i++)
		if (str[i] == chr)
			number++;
	return number;
}

int main()
{
	std::string str;
	char chr;
	std::cout << "Please enter the string:";
	getline(std::cin, str);
	std::cout << "Please enter the character:";
	std::cin >> chr;
	std::cout << "The character " << chr << " appears " << numberChar(str, chr) << " time(s) in " << str << "." << std::endl;
	return 0;
}