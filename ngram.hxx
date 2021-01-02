//
// Created by macarthur on 1/2/21.
//
#include <vector>
#include <unordered_map>
#include "math.hxx"
#include <string>
#include <map>
#include <fstream>
#include <iostream>

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
			long long index;
			if( ( (index = line.find('\t')) != -1) || ( (index = line.find(' '))  != -1) ){
				std::cout << "index2 " << index << std::endl;
				val = std::stod(line.substr(index+1));
				key = line.substr(0,index);
				this->N += val;
			}
			else{
				throw std::invalid_argument("No valid seperator between letters and the frequency counts found in line '"+line+"'.");
			}
			this->L = index;
			this->ngrams[key] = val;
			while(getline(input,line)){
				if(line[index] != ' ' && line[index] != '\t')
					throw std::invalid_argument("Separator not found at index"+std::to_string(index)+" in the line '"+line+"'.\n Expected to find valid separator there.");
				val = std::stod(line.substr(index+1));
				key = line.substr(0,index);
				this->ngrams[key] = val;
				this->N += val;
				total_ngrams++;
			}
			for(auto &iterator: this->ngrams){
				this->ngrams[iterator.first] = std::log10(iterator.second/N);
			}
			this->floor_val = std::log10(0.01/this->N);
		}
		input.close();
	}

	void print_ngrams(){
		std::ofstream output("../nf.txt");
		for(auto &iterator: this->ngrams){
			std::cout << "[" + iterator.first + "]=" + std::to_string(iterator.second) << std::endl;
			output << "[" + iterator.first + "]=" + std::to_string(iterator.second) << std::endl;
		}
		output.close();
	}

};
#endif //LIBCIPHERS_NGRAM_HXX
