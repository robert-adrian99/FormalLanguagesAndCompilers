/*4. Determinați numarul de cuvinte dintr-o frază introdusă de la tastatură, precum și ce cuvinte
sunt în fraza respectivă, sub forma:
ex: &quot;Ce cuvinte sunt in fraza? Determina!!&quot;
1. Ce
2. cuvinte
3. sunt
4. in
5. fraza
6. Determina
Ignorați , . ? ! ...*/
#include <iostream>
#include <string>
#include <vector>

std::string readSentence()
{
	std::string sentence;
	std::cout << "Please enter the sentence:";
	getline(std::cin, sentence);
	return sentence;
}

uint16_t numberOfWords(std::vector<std::string>& vecStr, const std::string& str)
{
	uint16_t nr = 0;
	std::string word = "";
	for (auto chr : str)
	{
		if (strchr(" .,;:!?-", chr))
		{
			if (word != "")
			{
				vecStr.push_back(word);
				nr++;
			}
			word = "";
		}
		else
		{
			word = word + chr;
		}
	}
	return nr;
}

int main()
{
	std::string sentence = readSentence();
	std::vector<std::string> vectorWords;
	uint16_t nr = numberOfWords(vectorWords, sentence);
	std::cout << "The sentence above contains " << nr << " words:" << std::endl;
	for (int index = 0; index < vectorWords.size(); index++)
		std::cout << index + 1 << ". " << vectorWords[index] << std::endl;
	std::cout << std::endl;
	return 0;
}