template <typename T> Matrix<T> matrix_round(const Matrix<T> &mat,size_t precision=4){
	size_t max=mat.get_cols()*mat.get_rows();
	Matrix<T> tmp_matrix(mat.get_cols(),mat.get_rows());
	tmp_matrix=mat;
	for(size_t i=0;i<max;i++){
		tmp_matrix[i]=to_fixed(mat[i],precision);
	}
	return tmp_matrix;
}
//TODO: Once I can read from files I'll read the matrices to test from from there but for now, it's fine to just do it like this.
template <typename T> void test_print(std::string input,T expected,T result){
	if(expected != result){
		std::cout << input << " test failed expected "<< std::to_string(expected) << " but got " << std::to_string(result) << "."  << std::endl;
	}
	else{
		std::cout << input << " test succeeded." << std::endl;
	}
}

template <typename T> void test_print(std::string input, Matrix<T> &expected, Matrix<T> &result){
	if(expected != result){
		std::cout << "expected = " << expected << std::endl << "but we got " << result << std::endl;
	}
	else{
		std::cout << input << " test succeeded." << std::endl;
	}
}
template <typename T> void test_print(std::string input,double expected,double result){

	if(almost_equal(expected,result)){
		std::cout << input << " test failed expected "<< std::to_string(expected) << " but we got " << std::to_string(result) << "."  << std::endl;
	}
	else{
		std::cout << input << " test succeeded." << std::endl;
	}
}
template <typename T> void test_print_matrix(Matrix<T> &lhs, Matrix<T> &rhs){
	std::cout << "Matrix A=" << lhs << "Matrix B=" << rhs << std::endl;
}
template <typename T,typename U> void test_print_m_scalar(Matrix<T> &lhs, U &rhs){
	std::cout << "Matrix A " << lhs << "scalar=" << rhs << std::endl;
}

template <typename T,typename U> void test_print_m_scalar(const U &lhs,const Matrix<T> &rhs){
std::cout << "scalar=" << rhs << "Matrix A " << lhs  << std::endl;
}

template <typename T, typename U> Matrix<T> to_fixed(const Matrix<T> &a, U precision){
	size_t max=a.get_rows()*a.get_cols();
	Matrix<T> tmp_matrix(2,2,1);
	U modifier=pow(10,precision);
	for(size_t i=0;i<max;i++){
		tmp_matrix[i]=round(a[i]*modifier)/modifier;
	}
	return tmp_matrix;
}
 //had to do this little hack to check for equality when using doubles/floats/long doubles.
 //I'll likely have to do the _same_ thing when doing the other operators too but for now
 //I'll let the end-user deal with it.
template <typename T> bool almost_equal(const Matrix<T> &a, const Matrix<T> b){
	if((a.get_rows() != b.get_rows())&&(a.get_cols() != b.get_cols())){
		return false;
	}
	size_t max=a.get_rows()*a.get_cols();
	T a_i,b_i;
	for(size_t i=0;i<max;i++) {
		const T difference = std::abs(a[i] - b[i]);
		a_i= abs(a[i]);
		b_i = abs(b[i]);
		const T scaled_epsilon = std::numeric_limits<T>::epsilon() * std::max(a_i, b_i);
		if(difference >= scaled_epsilon)
			return false;
	}
	return true;
}
void test_print(std::string input, Matrix<double> &expected, Matrix<double> &result){
	if(almost_equal(expected,result)){
		std::cout << "expected = " << expected << std::endl << "but we got " << result << std::endl;
	}
	else{
		std::cout << input << " test succeeded." << std::endl;
	}
}