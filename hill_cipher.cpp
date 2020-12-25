#include <iostream>
#include <chrono>
#include "matrix.hxx"
#include "hill_cipher.hxx"
/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Hill Cipher Tester
 *
 */
int main(){
	Matrix<char> key(2,2,1);
	Hill hill_instance = Hill(key);
	//std::cout << hill_instance << std::endl;
	//Matrix<char> key_arr = hill_instance.get_enc_key();
	//Matrix<char> dec_arr = hill_instance.get_dec_key();
	//std::cout << key_arr.get_array_size() << std::endl;
	//std::cout << dec_arr.get_array_size() << std::endl;
	std::cout << hill_instance.get_enc_key() << std::endl;
	std::cout << hill_instance.get_dec_key() << std::endl;
}