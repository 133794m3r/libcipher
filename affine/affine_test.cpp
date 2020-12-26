#include "affine.hxx"
void test_affine();
int main(){
	s_xor_128();
	std::cout << "Testing Affine Cipher" << std::endl;
	test_affine();
	return 0;
}

void test_affine(){
	int k = 0;
	std::string test_string = "TEST_STRING";
	std::string cipher_text;
	std::string plain_text;
	char a_vals[12] ={1,3,5,7,9,11,15,17,19,21,23,25};
	Affine affine_cipher = Affine();
	for(int i=0;i<12;i++){
		k = (i == 0)?2:1;
		for(int j=k;j<=26;j++){
			std::cout << "Testing with a=" << static_cast<int>(a_vals[i]) << " b=" << static_cast<int>(j) << std::endl;
			affine_cipher.set_key(a_vals[i],j);
			cipher_text = affine_cipher.encrypt(test_string);
			plain_text = affine_cipher.decrypt(cipher_text);
			if(plain_text != test_string) {
				std::cout << "error values don't match. \nts: " << test_string << "\npt: " << plain_text << std::endl;
				std::cout << "a " << (int) a_vals[i] << "b " << (int) j << std::endl;
				break;
			}
		}
	}
}