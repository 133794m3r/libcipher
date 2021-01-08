#include <stdexcept>
#include "ngram.hxx"
int main() {
	Ngram bi_grams("../english_bigrams.txt");
	bi_grams.print_ngrams();
	std::string a = "ABCDOFTH";
	std::cout << bi_grams.score(a) << std::endl;

}