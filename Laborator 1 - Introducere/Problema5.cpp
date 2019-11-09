/*5. Scrieți un subprogram care să citească n cuvinte de la tastatură și care să le sorteze în ordine
crescătoare*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void readWords(std::vector<std::string>& vecStr)
{
	uint16_t n;
	std::cout << "Please enter the number of words:";
	std::cin >> n;
	while (n)
	{
		std::string str;
		std::cout << "Enter a word:";
		std::cin >> str;
		vecStr.push_back(str);
		--n;
	}
}
int main()
{
	std::vector<std::string> vectorString;
	readWords(vectorString);
	std::sort(vectorString.begin(), vectorString.end());
	for (int index = 0; index < vectorString.size(); index++)
	{
		std::cout << vectorString[index] << " ";
	}
	std::cout << std::endl;
	return 0;
}