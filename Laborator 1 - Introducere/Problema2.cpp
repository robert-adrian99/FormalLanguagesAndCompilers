/*2. Să se determine dacă un șir de caractere este un numar natural, întreg sau real.
Exemplu:
• 23 este număr natural (evident că și întreg sau real), 23.04 este număr real, -14 este număr întreg,
24.345E-10 este număr real în formă exponențială,
• 2a37 NU este număr, 23.4.5 NU este număr, 34E Nu este număr, 34-E NU este număr.*/
#include <iostream>
#include <regex>



int main()
{
	//	std::string str;
	//	std::cout << "Please enter the possible number:";
	//	std::cin >> str;
	//	std::regex reg("(\d)+");
	//	std::smatch m;
	//	if (std::regex_match(str, reg))
	//	{
	//		std::cout << "YES";
	//	}
	//	else
	//	{
	//		std::cout << "NO";
	//	}

	std::string a = "22";

	// Here b is an object of regex (regular expression) 
	std::regex b("(\d)+"); // Geeks followed by any character 

	// regex_match function matches string a against regex b 
	if (std::regex_match(a, b))
		std::cout << "String 'a' matches regular expression 'b' \n";

	std::cout << std::endl;
	return 0;
}