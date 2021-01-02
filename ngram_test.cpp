#include <stdexcept>
#include "ngram.hxx"
int main() {
	Ngram bi_grams("../english_bigrams.txt");
	bi_grams.print_ngrams();

}