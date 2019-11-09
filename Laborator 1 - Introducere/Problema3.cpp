/*3. Să se inverseze un șir de caractere și apoi să se înlocuiască toate aparițiile unui subșir dat s1 cu
un alt subșir dat s2.*/
#include <iostream>
#include <string>

std::string replaceStr(std::string str, std::string s1, std::string s2)
{
	for (auto p = str.find(s1); p != std::string::npos; p = str.find(s1))
	{
		str.replace(p, s1.size(), s2);
	}
	return str;
}

int main()
{
	std::string str, s1, s2;
	std::cout << "Please enter the string:";
	getline(std::cin, str);
	std::reverse(str.begin(), str.end());
	std::cout << "The reversed string is: " << str << std::endl;
	std::cout << "Please enter the substring from " << str << " you want to replace:";
	getline(std::cin, s1);
	std::cout << "Please enter the substring you want to be replaced with the substring " << s1 << ":";
	getline(std::cin, s2);
	std::cout << "The replaced string is: " << replaceStr(str, s1, s2) << std::endl;
	return 0;
}