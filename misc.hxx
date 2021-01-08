//
// Created by macarthur on 12/25/20.
//

#ifndef LIBCIPHERS_MISC_HXX
#define LIBCIPHERS_MISC_HXX
template <typename T, typename S, typename K> T bin_search(S *arr,T l, T h, K x){
	//as long as the lower point is less than or equal to the
	//high we're still able to search.
	if(l<=h){
		//set the midpoint to be l+h/2. The type is the same type as our low and high data type.
		T m=(l+h)/2;
		//get the current value. The value should be the same type as our key.
		//for floating points you have to be careful due to floating point rounding.
		K cur=arr[m];
		// if key is equal to that value then we have the index.
		if(x == cur){
			//return the middle.
			return m;
		}
			//otherwise if current value is greater than x then we have went past it.
		else if(cur > x){
			//set the highest to the middle minus 1.
			h=m-1;
		}
			//otherwise we set low ot the middle+1 as we're lower than it.
		else{
			l=m+1;
		}
		//call it again with the new low and high.
		return bin_search(arr,l,h,x);
	}
	//if we ever reach this point the value wasn't found.
	//thus the index is -1.
	return -1;

}

std::string to_uppercase(std::string input){
	std::locale loc;
	std::string output;
	output.reserve(input.length());
	for(char i : input){
		output+=std::toupper(i,loc);
	}
	return output;
}

template <typename M, typename K> bool contains(M const&m,K const &k){
	if(m.find(k) == m.end()) {
		return false;
	}
	return true;
}
#endif //LIBCIPHERS_MISC_HXX
