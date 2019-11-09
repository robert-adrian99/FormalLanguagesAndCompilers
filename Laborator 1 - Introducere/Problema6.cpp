/*6. Să se rețină într-un vector de cuvinte și să se afișeze unul sub altul toate prefixele proprii ale
unui cuvant citit de la tastatură (prefixele unui cuvânt sunt compuse din minim un caracter și
maxim toate caracterele, citite de la stânga la dreapta. Prefix propriu este un prefix, care este
diferit de cuvântul dat). Exemplu: toate prefixele proprii ale cuvântului ANANAS sunt: A, AN, ANA, ANAN, ANANA*/
#include <iostream>
#include <string>
#include <vector>

void readWord(std::string& word)
{
	std::cout << "Please enter a word:";
	std::cin >> word;
}

void properPrefixes(std::vector<std::string>& vectorPrefixes, std::string word)
{
	std::string prefix = "";
	for (auto letter : word)
	{
		prefix += letter;
		vectorPrefixes.push_back(prefix);
	}
	vectorPrefixes.pop_back();
}

int main()
{
	std::string word;
	readWord(word);
	std::vector<std::string> vectorPrefixes;
	properPrefixes(vectorPrefixes, word);
	for (size_t index = 0; index < vectorPrefixes.size(); index++)
		std::cout << index + 1 << ". " << vectorPrefixes[index] << std::endl;
	std::cout << std::endl;
	return 0;
}