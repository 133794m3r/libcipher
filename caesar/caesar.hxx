#ifndef LIBCIPHERS_CAESAR_HXX
#define LIBCIPHERS_CAESAR_HXX
#include "../includes.hxx"

class RotationCipher {
  private:
	char _n;
	bool _full_shift;
	std::string transform(std::string &input, char shift){
		std::string output;
		output.reserve(input.length());
		for(char x:input){
			if(x>=65 && x<= 90){
				x+=shift;
				if(x>= 90)
					x=(x-90)+64;
			}
			else if(x>= 97 && x<=122){
				x+=shift;
				if(x >= 122){
					x=(x-122)+96;
				}
			}
			output+=x;
		}
		return output;
	}

	std::string transform_full(std::string &input, char shift){
		std::string output;
		for(char x:input){
			x+= shift;
			if(x > 126){
				x = 32+(x-127);
			}
			else if(x < 32){
				x = 127 - (32 - x);
			}
			output+=x;
		}
	}
  public:
	RotationCipher(char n=13,bool full=false){
		if(full)
			n = n % 26;
		this->_full_shift = full;
		this->_n = n;

	}
	void set_shift(char n){
		this->_n = n;
	}
	void full_shift(bool full){
		this->_full_shift = full;
	}
	std::string encrypt(std::string pt){
		return "";
	}
	std::string decrypt(std::string ct){
		return "";
	}
};


#endif //LIBCIPHERS_CAESAR_HXX

