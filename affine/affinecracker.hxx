#ifndef LIBCIPHERS_AFFINECRACKER_HXX
#define LIBCIPHERS_AFFINECRACKER_HXX
#include "affine.hxx"
#include "../ngram.hxx"
class AffineCracker: Affine {
  private:
	Ngram _ngrams;
  public:
	explicit AffineCracker(std::string ngram_file=""){
		if(ngram_file.empty())
			ngram_file = "../english_bigrams.txt"
		this->_ngrams = Ngram(ngram_file);
	}

	crack(std::string &ct){
		char cur_b = 0;
		std::string pt;
		double best_score = -1000000.00;
		double score = 0;
		char best_a = 0;
		char best_b = 0;
		for(char cur_a : this->_coprimes){
			this->a = cur_a;
			this->a_inv = mod_inv(cur_a, (char)26);
			for(cur_b = (cur_a == 1) ? 2 : 1; cur_b < 26; cur_b++){
				this->b = cur_b;
				pt = this->decrypt(ct);
				score = _ngrams.score(pt);
				if(score > best_score){
					score = best_score;
					best_a = cur_a;
					best_b = cur_b;
				}
			}
		}
		this->a = best_a;
		this->b = best_b;
		this->_a_inv = mod_inv(best_a, (char) 26);
		return this->decrypt(ct);
	}
};


#endif //LIBCIPHERS_AFFINECRACKER_HXX
