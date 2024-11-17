#include "spellChecker.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>

namespace seneca {

	SpellChecker::SpellChecker(const char* filename)
	{
		std::ifstream file(filename);
		std::string line;
		try {
			if (!file.is_open()) {
				throw "Bad file name!";
			}
			else {
				while (getline(file, line)) {
					std::stringstream ss(line);
					std::string word;
					std::vector<std::string> words;

					while (ss >> word) {
						words.push_back(word);
					}
					
					m_goodWords.push_back(words[1]); // get first string read from file which is a good word
					m_badWords.push_back(words[0]); // get second string read from file which is a bad word


					words.clear(); // clear vector for next set of words
				}
			}
		}
		catch (const char* error) {
			std::cout << error << std::endl;
		}

	}
	void SpellChecker::operator()(std::string& text)
	{
		// WORK ON THIS, COUNTER IS NOT UPDATING!!!!!!!!
		for (size_t i = 0; i < m_badWords.size(); ++i) {
			size_t pos = 0;
			while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
				// Replace bad word with good word
				text.replace(pos, m_badWords[i].size(), m_goodWords[i]);
				m_bad_words_counter[i]++; // Increment replacement counter for this bad word

				// Move to the next position to check for more bad words
				pos += m_goodWords[i].size();
			}
		}
	}
	void SpellChecker::showStatistics(std::ostream& out) const
	{
		std::cout << "Spellchecker Statistics" << std::endl;
		for (size_t i = 0; i < m_badWords.size(); i++)
		{
			std::cout << std::left << std::setw(15) << m_badWords[i] << ": " << m_bad_words_counter[i] << " replacements" <<  std::endl;
		}

	}
}