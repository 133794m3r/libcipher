#include "affine.hxx"
#include "../ngram.hxx"

int main(){
	Ngram bigrams("../english_bigrams.txt");
	Ngram monograms("../english_monograms.txt");
	std::string test_input = "Of mice and men there are many things.";
	char a_values[12] ={1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
	//let it choose a random key so that no one knows what it is.
	Affine affine_cipher=Affine();
	std::string cipher_text = affine_cipher.encrypt(test_input);
	std::string plain_text;
	affine_cipher.print_key();
	int k =0;
	double max_score = -10000.0;
	char best_a = 1;
	char best_b = 2;
	double current_score;
	double max_mono = -10000.0;
	double current_mono;
	std::string best_text;
	for(int i=0;i<12;i++){
		k = (i == 0)?2:1;
		for(int j=k;j<=26;j++){
			affine_cipher.set_key(a_values[i], static_cast<char>(j));
			plain_text = affine_cipher.decrypt(cipher_text);
			current_score = bigrams.score(plain_text);
			current_mono = monograms.score(plain_text);
			if(current_score > max_score){
				best_a = i;
				best_b = j;
				best_text = plain_text;
				max_score = current_score;
			}
		}
	}
	std::cout << "The best key was a=" << (int) best_a << " b=" << (int)best_b << " and the plain-text of '" <<
	best_text << "'." << std::endl << "The best score was: " << max_score << std::endl;
	std::cout << "Best Monogram score: " << max_mono << std::endl;
	return 0;
}

