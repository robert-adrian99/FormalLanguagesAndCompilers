/*7. Se dă un vector de cuvinte v și un subșir de caractere s1. Să se rețină într-un alt vector, toate
cuvintele din v, care conțin subșirul s1.*/
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> readWords(std::string& s1)
{
	uint16_t n;
	std::vector<std::string> vecStr;
	std::cout << "Please enter the number of words:";
	std::cin >> n;
	while (n)
	{
		std::string str;
		std::cout << "Enter a word:";
		std::cin >> str;
		vecStr.push_back(str);
		n--;
	}
	std::cout << "Please enter the substring:";
	std::cin >> s1;
	return vecStr;
}

std::vector<std::string> chooseString(const std::vector<std::string>& vecStr1, const std::string& s1)
{
	std::vector<std::string> vecStr2;
	for (int index = 0; index < vecStr1.size(); index++)
	{
		if (auto p = vecStr1[index].find(s1))
			if (p <= vecStr1[index].size())
				vecStr2.push_back(vecStr1[index]);
	}
	return vecStr2;
}

int main()
{
	std::string s1;
	std::vector<std::string> vectorString1 = readWords(s1);
	std::vector<std::string> vectorString2 = chooseString(vectorString1, s1);
	std::cout << "The second vector that contains the words with " << s1 << ":" << std::endl;
	for (int index = 0; index < vectorString2.size(); index++)
	{
		std::cout << vectorString2[index] << " ";
	}
	std::cout << std::endl;
	return 0;
}