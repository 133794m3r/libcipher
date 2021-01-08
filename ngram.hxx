#include "includes.hxx"
#include "math.hxx"
#include "misc.hxx"
#include <fstream>
#include <vector>
#include <unordered_map>

/**
 *  Ngram Class File
 */


#ifndef LIBCIPHERS_NGRAM_HXX
#define LIBCIPHERS_NGRAM_HXX
class Ngram{
  private:
	std::unordered_map<std::string, double> ngrams;
//	std::map<std::string, double> ngrams;
	double N = 0.00f;
	size_t L = 0;
	double floor_val = 0;
  public:
	explicit Ngram(const std::string& ngram_file){
		std::ifstream input(ngram_file);
		std::string line;
		std::string key;
		double val;
		size_t total_ngrams=0;
		if(getline(input,line)){
			long long int index;
			if( ( (index = line.find('\t')) != -1) || ( (index = line.find(' '))  != -1) ){
				val = std::stod(line.substr(static_cast<unsigned long>(index + 1)));
				key = line.substr(0, static_cast<unsigned long>(index));
				this->N += val;
			}
			// here we see if the total is already precomputed the 2 values.
			else if( ((index = line.find(';') ) != -1 ) ){
				total_ngrams = std::stoull(line.substr(0,index));
				this->N = std::stod(line.substr(index+1));
				if( ( (index = line.find('\t')) != -1) || ( (index = line.find(' '))  != -1) ){
					val = std::stod(line.substr(static_cast<unsigned long>(index + 1)));
					key = line.substr(0, static_cast<unsigned long>(index));
				}
				else{
					throw std::invalid_argument("No valid separator between letters and the frequency counts found in line '"+line+"'.");
				}
			}
			else{
				throw std::invalid_argument("No valid separator between letters and the frequency counts found in line '"+line+"'.");
			}

			this->L = static_cast<size_t>(index);
			this->ngrams[key] = val;
			if(total_ngrams >0){
				while (getline(input, line)) {
					if (line[index] != ' ' && line[index] != '\t')
						throw std::invalid_argument(
								"Separator not found at index" + std::to_string(index) + " in the line '" + line +
								"'.\n Expected to find valid separator there.");
					val = std::stod(line.substr(static_cast<unsigned long>(index + 1)));
					key = line.substr(0, static_cast<unsigned long>(index));
					this->ngrams[key] = val;
				}
			}
			else {
				while (getline(input, line)) {
					if (line[index] != ' ' && line[index] != '\t')
						throw std::invalid_argument(
								"Separator not found at index" + std::to_string(index) + " in the line '" + line +
								"'.\n Expected to find valid separator there.");
					val = std::stod(line.substr(static_cast<unsigned long>(index + 1)));
					key = line.substr(0, static_cast<unsigned long>(index));
					this->ngrams[key] = val;
					this->N += val;
					total_ngrams++;
				}
			}
			for(auto &iterator: this->ngrams){
				this->ngrams[iterator.first] = std::log10(iterator.second/N);
			}
			this->floor_val = std::log10(0.01/this->N);
		}
		input.close();
	}

	double get_floor(){
		return this->floor_val;
	}

	double score(std::string &text){
		double weight=0;
		//have to make sure that it's uppercase as all ngrams are uppercase.
		std::string new_str = to_uppercase(text);
		std::string test_gram;
		for(size_t i=0;i<=(new_str.length()-this->L);i++){
			test_gram=new_str.substr(i,this->L);
			if( contains(this->ngrams,test_gram)){
				weight += this->ngrams[test_gram];
			}
			else{
				weight += this->floor_val;
			}
		}
		return weight;
	}

	void print_ngrams(){
		std::vector<std::pair<std::string,double>> items(this->ngrams.begin(), this->ngrams.end());
		std::sort(items.begin(), items.end());
		for(auto &iterator: items){
			std::cout << "[" + iterator.first + "]=" + std::to_string(iterator.second) << std::endl;
		}
	}

};
#endif //LIBCIPHERS_NGRAM_HXX
