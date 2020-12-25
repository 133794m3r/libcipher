/**
 * Vector Operators
 * By Macarthur Inbody AGPLv3 <admin-contact@transcendental.us>
 * This source file overloads the templated vectors so that I can store this somewhere else.
 * Basically it does, +,-,*,/, and %. No operator equals is included in here.
 * It also does the << operator so that I can print it to the terminal/file so that I can easily debug it.
 * All of this _assumes_ that the class T of each vector is one that already has the operators defined for each element
 * If they are not, then it's up to _you_ to figure out how to do it. This will work for my Matrix class, and also
 * all scalar types.
 */

#ifndef _VECTORS_HXX_
#define _VECTORS_HXX_
#include <vector>
#include "math.hxx"
#include <stdexcept>

template <class T,class Allocator> std::vector<T,Allocator> operator+(const std::vector<T, Allocator> &lhs, std::vector<T, Allocator> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For addition between vectors to work both must be the same size! lhs.size()="
		+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]+rhs[i];
	}
	return tmp_vec;
}
template <class T,class Allocator> std::vector<T, Allocator> operator-(const std::vector<T, Allocator> &lhs, std::vector<T, Allocator> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For subtraction between vectors to work both must be the same size! lhs.size()="
									+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T, Allocator> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]-rhs[i];
	}
	return tmp_vec;
}
template <class T,class Allocator> std::vector<T,Allocator> operator*(const std::vector<T,Allocator> &lhs, std::vector<T,Allocator> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For multiplication between vectors to work both must be the same size! lhs.size()="
									+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T,Allocator> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]*rhs[i];
	}
	return tmp_vec;
}
template <class T,class Allocator> std::vector<T,Allocator> operator/(const std::vector<T,Allocator> &lhs, std::vector<T,Allocator> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For division between vectors to work both must be the same size! lhs.size()="
									+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T,Allocator> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]/rhs[i];
	}
	return tmp_vec;
}


template <class T,class Allocator> std::ostream& operator<<(std::ostream& os, const std::vector<T,Allocator> &m){
	size_t m_size=m.size();
	os << "[";
	for(size_t i=0; i < m.size(); i++) {
		os << m[i]  <<(i == m_size - 1 ? "" : ",");
	}
	os << "]" << std::endl;
	return os;
}
template <class T,class Allocator> std::istream& operator>>(std::istream& is, std::vector<T,Allocator> &m){
	size_t n=m.size();
	for(size_t i=0;i<n;i++){
		is >> m[i];
	}
	return is;
}
/**
* for all comparison operators I'm going to _assume_ that they're already predefined as I'm not doing C++20. And also
* I don't want to have to write pre-processor macros to define them here maybe in the future I'll redefine them.
*/
#endif //_VECTORS_HXX_
