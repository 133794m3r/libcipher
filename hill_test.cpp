#include <iostream>
#include <chrono>
#include "hill_cipher.hxx"
int main(){
	std::vector<char> in = {7,11,4,11};
	matrix_char a(2,2,1);
	a.set_arr(in);
	matrix_char b(2,2,1);
	in = {1,10,4,15};
	std::string cipher_text = "PWQB";
	std::string plain_text = "HELL";
	Hill hill = Hill();
	std::cout << hill.solve_key(cipher_text,plain_text) << std::endl;
}