#include "affine.hxx"
int main(){
	s_xor_128();
	Affine affine = Affine();
	std::string test = "test_string";
	affine.print_key();
	std::string ct = affine.encrypt(test);
	std::string pt = affine.decrypt(ct);
	std::cout << test << std::endl << ct << std::endl << pt << std::endl;
	return 1;
}
