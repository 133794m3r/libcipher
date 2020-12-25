#ifndef _CRYPTO_MATH_HEADER_
#define _CRYPTO_MATH_HEADER_
#include <cmath>
#include <limits>
//standard check to make sure that our value is still within the acceptable range for errors.
template <class T> inline T epsilon (const T& v) {
	 T e = std::numeric_limits<T>::epsilon() * 100;
	 return v > T(1) ? v * e : e;
}
//see if the values are close enough to equal such that we should consider it so. Since
//floating point is weird.
template <typename T> bool almost_equal(T a, T b){
		const float difference = std::fabs(a - b);
		a = std::fabs(a);
		b = std::fabs(b);
		const T scaledEpsilon =std::numeric_limits<T>::epsilon() * std::max(a, b);
		return difference <= scaledEpsilon;
}

//baisc modulus function for floating point numbers. Should've been a template honestly for these
double mod(double a, double b){
	double m = std::fmod(a,b);
	return m < 0?m+b:m;
}
//for 16byte floats.
long double mod(long double a,long double b){
	long double m = std::fmod(a,b);
	return m < 0?m+b:m;
}
//float version.	
float mod(float a, float b){
	double m = std::fmod(a,b);
	return m < 0?m+b:m;
}

//the template for all integral types.
template <typename T> T mod(T a, T b){
	// Get the value after modulus and store it.
	T m = a % b;
	//if the value of m is negative we must convert it such that it is properly handled.
	return m < 0?m+b:m;
}
//basic fast gcd.
template <typename T> T gcd_fast(T a, T b, T *x, T *y){
	if(a == 0){
		*x=0;
		*y=1;
		return b;
	}
	//our x1 and y1 variables.
	T x1,y1;
	//want to cast it into the type we're given.
	T gcd = gcd_fast(static_cast<T>((a+b)%a), a, &x1, &y1);
	//setting the variables.
	*x=y1-(b/a) * x1;
	*y=x1;
	return gcd;
}
/**
 * TODO: This function may return 0 so that errors can be more easily. Since I'm allowing unsigned types and the
 * inversion should never be 0 this way I can also not have to wrap every attempt inside of a try{}catch(e){} block,
 * might make it a #ifdef variable to find out if it throws the error or if it just returns 0. That or make it a
 * 3rd argument.
 */
template <typename T> T mod_inv(T a, T mod){
	T gcd;
	T x=0;
	T y=0;
	/*
	 * Sadly the code below was too good to be true. It didn't work for reasons beyond my understanding at this time.
	 *
	 */
	/*
	int sign_a = (a < 0)?-1:1;
	int sign_mod = (mod < 0)?-1:1;
	a*=sign_a;
	mod*=sign_mod;
	*/
	if(mod < 0){
		x=-mod;
	}
	else {
		x = mod;
	}
	if(a<0) {
		a += x;
	}
	//get the gcd.
	gcd=gcd_fast(a,mod,&x,&y);
	if(!(gcd == 1 || gcd == -1)){
		//may make this just return 0 which is basically the same thing.
		throw std::invalid_argument("The gcd between a and the modulus must be either 1 or -1");
	}
	
	if(gcd == -1) {
		if (x < 0)
			return mod - x;
		else
			return x + mod;
	}
	else
		return x % mod;

}
template <typename T> T *small_prime_factor(T n){
		//the first 20 primes is more than enough for the demo we're doing.
		//as one of the primes from n has to be one of these primes since NCL likes
		//small numbers.
		int primes[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};
		int remainder;
		int i;
		T p=0;
		T q=0;
		T *two_factors=new T[2];
		
		for(i=0;i<11;i++){
			remainder=n%primes[i];
			if(remainder == 0){
				q=n/primes[i];
				p=n/q;
			}
		}
		two_factors[0]=p;
		two_factors[1]=q;
		return two_factors;
}
//basic LCM function.
template <typename T> T fast_lcm(T a,T b){
	T lcm;
	T gcd;
	T x=0;
	T y=0;
	if(a == 0 || b == 0)
		return 0;
	else if(a == 1)
		return b;
	else if(b == 1)
		return a;
	gcd=gcd_fast(a,b,&x,&y);
	lcm=(a/gcd)*b;
	return lcm;
}
template <typename F,typename P> F to_fixed(F num,P precision){P modifier=pow(10,precision); return round(num*modifier)/modifier;}
#endif //_CRYPTO_MATH_HEADER_
