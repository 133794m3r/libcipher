#ifndef _LIBCIPHERS_AFFINE_
#define _LIBCIPHERS_AFFINE_
#include "../includes.hxx"
#include "../random.h"
#include "../misc.hxx"
#include "../math.hxx"
#ifndef WARN_AFFINE_MSG
#define WARN_AFFINE_MSG (0)
#endif
class Affine{
  private:
	char coprimes[12] = {1,3,5,7,9,11,15,17,19,21,23,25};
	char a;
	char b;
	char a_inv;
  public:
	Affine(char _a, char _b){
		a = _a;
		a_inv = mod_inv(_a, static_cast<char>(26));
		b = _b;
	}
	explicit Affine(){
		if(!XOR_SHIFT_128_SEEDED){
			s_xor_128();
		}
		a = coprimes[xorshift128(0,11)];
		a_inv = mod_inv(a,static_cast<char>(26));
		if(a == 1){
			b = xorshift128(2, 26);
		}
		else {
			b = xorshift128(1, 26);
		}
	}

	std::string encrypt(const std::string &plaintext) const{
		std::string ciphertext;
		ciphertext.reserve(plaintext.length());
		for(char x:plaintext){

			if (!( (x >= 65 && x<=90) || (x>=97 && x<=122) ) ) {
				//I don't care during debugging.
#if WARN_AFFINE_MSG
				std::cout << "Warning. The character \"" << x << "\" is not an alphabetic character so we've simply skipped over it.\"" << std::endl;
#endif
				ciphertext.append(1,x);
				continue;
			}
			else if(x >= 97){
#if WARN_AFFINE_MSG
				std::cout << "Warning the character x \"" << x << "\" is lowercase. We are converting it to uppercase."
#endif
				x -= 32;
			}
			ciphertext.append(1, static_cast<char>((( (a*(x-65)) +b) % 26)+65));
		}
		return ciphertext;
	}

	void set_key(char _a, char _b){
		if (bin_search(coprimes,0,11,_a) != -1){
			a = _a;
		}
		else{
			throw std::invalid_argument("A must be coprime with 26. Chose one of these values. You are setting the encryption key not decryption key.\n1,3,5,7,9,11,15,17,19,21,23,25\n");
		}
		a_inv = mod_inv(a,(char)26);
		b = _b;
	}

	void print_key() const{
		printf("a=%d b=%d a_inv=%d\r\n",a,b,a_inv);
	}

	/**
	 * Decryption method
	 * @param ciphertext text to decrypt
	 * @return std::string plaintext
	 */
	std::string decrypt(const std::string &ciphertext) const{
		std::string plaintext;
		plaintext.reserve(ciphertext.length());
		for(char x:ciphertext){
			if(!( (x >= 65 && x<=90) || (x>=97 && x<=122) ) ) {
#if WARN_AFFINE_MSG
				std::cout << "Warning. The character \"" << x << "\" is not an alphabetic character so we've simply skipped over it.\"" << std::endl;
#endif
				plaintext.append(1,x);
				continue;
			}
			else if(x >= 97){
#if WARN_AFFINE_MSG
				std::cout << "Warning the character x \"" << x << "\" is lowercase. We are converting it to uppercase."
#endif
				x -= 97;
			}

			plaintext.append(1,mod( ( ( (x-65) - b) * a_inv),26)+65);
		}
		return plaintext;
	}

};
#endif //_LIBCIPHERS_AFFINE_
