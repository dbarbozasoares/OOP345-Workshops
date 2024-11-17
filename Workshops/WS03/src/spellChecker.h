#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <string>
#include <vector>

namespace seneca {
	class SpellChecker {
		std::vector<std::string> m_badWords;
		std::vector<std::string> m_goodWords;
		int m_bad_words_counter[6] = { 0 }; // bad words change counter based on index from badWords container
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;
	};

}
#endif // !SENECA_SPELLCHECKER_H
