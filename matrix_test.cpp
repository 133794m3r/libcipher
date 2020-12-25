#include <iostream>
#include <iomanip>
#include "matrix.hxx"
//#include "vectors.hxx"
#include "matrix_test.hxx"
/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Matrix Class Module
 *
 */

//forward declarations.
void test_comparisons();
void test_arithmetic_int();
void test_arithmetic_double();
void test_det_int();
void test_det_double();
void test_adj_int();
void test_inv_dbl();
void test_inv_mod();
//the actual driver program to do the testing.  It just calls all of them in order and prints tests.
int main(void) {
	test_comparisons();
	test_arithmetic_int();
	test_arithmetic_double();
	test_det_int();
	test_det_double();
	test_adj_int();
	std::cout << "\n\ndbl\n4x4 tests." << std::endl;
	std::vector<double> input_dbl;
	matrix_double test_dbl(4,4);
	std::vector<double> output_dbl;
	matrix_double result_dbl(4,4);
	matrix_double adj_dbl(4,4);
	input_dbl={88, 20, 88, 79, 90, 57, 56, 55, 40, 120, 73, 118, 51, 12, 15, 19};
	test_dbl.set_arr(input_dbl);
	output_dbl={-19395, 10696, -17987, 161389, -88213, 182283, 1582, -170706, 67266, 264368, -85209, -515768, 54669, -352548, 114552, 437968};
	adj_dbl.set_arr(output_dbl);
	result_dbl=test_dbl.adj();
	test_print("Matrix A.adj() == B", result_dbl, adj_dbl);
	std::cout << result_dbl << std::endl;
	test_inv_dbl();
	test_inv_mod();
	return 0;
}

/*
 * This function will go through all of the comparison operators to verify that they work.
 */


void test_comparisons() {
	matrix_int least(2, 2, 1);
	matrix_int most(2, 2, 3);
	matrix_int equals_least(2, 2, 1);
	int scalar = 0;
	bool result;
	bool expected;
	std::cout << "Comparison operators " << std::endl;
	result = (least != most);
	expected = true;
	test_print("Matrix A !=(Not Equals) Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least == equals_least);
	expected = true;
	test_print("Matrix A ==(Equals) Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least >= most);
	expected = false;
	test_print("Matrix A >=Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least <= most);
	expected = true;
	test_print("Matrix A <= Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least == scalar);
	expected = false;
	test_print("Matrix A == scalar", expected, result);
	if (result != expected) {
		test_print_m_scalar(least, scalar);
	}
	result = (scalar != least);
	expected = true;
	test_print("scalar != Matrix A", expected, result);
	if (result != expected) {
		test_print_m_scalar(scalar, least);
	}
}

void test_arithmetic_int() {
	matrix_int lhs_int(2, 2, 1);
	lhs_int(0, 0) = 1;
	lhs_int(0, 1) = 2;
	lhs_int(1, 0) = 3;
	lhs_int(1, 1) = 4;
	matrix_int rhs_int(2, 2, 1);
	rhs_int(0, 0) = 4;
	rhs_int(0, 1) = 3;
	rhs_int(1, 0) = 2;
	rhs_int(1, 1) = 1;
	std::vector<int> int_vec = {1, 1, 1, 1};
	/*
	 * the result matrices for the basic operations.
	 * Baiscally I do each operation defined seperately, I may change my mind and just redefine the result each and
	 * everytime that we do an operation for the expected result but I don't know yet.
	 */
	matrix_int result_int(2, 2, 1);
	matrix_int expected_int(2, 2, 1);
	int scalar = 10;
	std::cout << "Matrix<int> Arithmetic tests" << std::endl;
	result_int = lhs_int + rhs_int;
	int_vec = {5, 5, 5, 5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A + Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A + Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int - rhs_int;
	int_vec = {-3, -1, 1, 3};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A - Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A - Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int * rhs_int;
	int_vec = {8, 5, 20, 13};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A * Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A * Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int / rhs_int;
	int_vec = {1, -3, 1, -5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A / Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A / Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int + scalar;
	int_vec = {11, 12, 13, 14};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A + scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A + scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = scalar + lhs_int;
	if (result_int != expected_int) {
		std::cout << "(scalar + Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(scalar + Matrix A) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int - scalar;
	int_vec = {-9, -8, -7, -6};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A - scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A - scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = scalar - lhs_int;
	if (result_int != expected_int) {
		std::cout << "(scalar - Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(scalar - Matrix A) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int * scalar;
	int_vec = {10, 20, 30, 40};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A * scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A * scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = scalar * lhs_int;
	if (result_int != expected_int) {
		std::cout << "(scalar * Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(scalar * Matrix A) == Matrix C test succeeded" << std::endl;
	}
	//of course this is going to be zero but still have to make sure.
	result_int = lhs_int / scalar;
	int_vec = {0, 0, 0, 0};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A / scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A / scalar) == Matrix C test succeeded" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Matrix<int> inplace arithematic operators" << std::endl;
	result_int = lhs_int;
	result_int += rhs_int;
	int_vec = {5, 5, 5, 5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Marix A += Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A += Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int -= rhs_int;
	int_vec = {-3, -1, 1, 3};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int *= rhs_int;
	int_vec = {8, 5, 20, 13};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int /= rhs_int;
	int_vec = {1, -3, 1, -5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int += scalar;
	int_vec = {11, 12, 13, 14};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A += scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A += scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int -= scalar;
	int_vec = {-9, -8, -7, -6};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A -= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A -= scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int *= scalar;
	int_vec = {10, 20, 30, 40};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A *= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A *= scalar) == Matrix C test succeeded" << std::endl;
	}
	//of course this is going to be zero but still have to make sure.
	result_int = lhs_int;
	result_int /= scalar;
	int_vec = {0, 0, 0, 0};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A /= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A /= scalar) == Matrix C test succeeded" << std::endl;
	}
	std::cout << std::endl;
}

void test_arithmetic_double() {
	matrix_double lhs_dbl(2, 2, 1.0);
	lhs_dbl(0, 0) = 1.4;
	lhs_dbl(0, 1) = 2.3;
	lhs_dbl(1, 0) = 3.2;
	lhs_dbl(1, 1) = 4.1;
	matrix_double rhs_dbl(2, 2, 1.0);
	rhs_dbl(0, 0) = 4.1;
	rhs_dbl(0, 1) = 3.2;
	rhs_dbl(1, 0) = 2.3;
	rhs_dbl(1, 1) = 1.4;
	std::vector<double> dbl_vec = {1.0, 1.0, 1.0, 1.0};
	matrix_double result_dbl(2, 2, 1.0);
	matrix_double expected_dbl(2, 2, 1.0);
	double scalar = 10.5;

	std::cout << "Matrix<double> Arithmetic tests" << std::endl;
	result_dbl = lhs_dbl + rhs_dbl;
	dbl_vec = {5.5, 5.5, 5.5, 5.5};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A + Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A + Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl + scalar;
	dbl_vec = {11.9, 12.8, 13.7, 14.6};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A + scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A + scalar) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = scalar + lhs_dbl;
	if (result_dbl != expected_dbl) {
		std::cout << "(scalar + Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(scalar + Matrix A) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl - rhs_dbl;
	dbl_vec = {-2.7, -0.9, 0.9, 2.7};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A - Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A - Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl - scalar;
	dbl_vec = {-9.1, -8.2, -7.3, -6.4};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A - scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A - scalar) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = scalar - lhs_dbl;
	if (result_dbl != expected_dbl) {
		std::cout << "(scalar - Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(scalar - Matrix A) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl * rhs_dbl;
	dbl_vec = {11.03, 7.7, 22.55, 15.98};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A * Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A * Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl * scalar;
	dbl_vec = {14.7, 24.15, 33.6, 43.05};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A * scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A * scalar) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = scalar * lhs_dbl;
	if (result_dbl != expected_dbl) {
		std::cout << "(scalar * Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(scalar * Matrix A) == Matrix C test succeeded" << std::endl;
	}

	//we have to round it because it's a repeating fraction.
	result_dbl = matrix_round(lhs_dbl / rhs_dbl);
	dbl_vec = {2.0556, -3.0556, 3.0556, -4.0556};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A / Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A / Matrix B) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = matrix_round(lhs_dbl / scalar);
	dbl_vec = {0.1333, 0.2190, 0.3048, 0.3905};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A / scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A / scalar) == Matrix C test succeeded" << std::endl;
	}
	std::cout << std::endl;


	std::cout << "Matrix<dbl> inplace arithematic operators" << std::endl;
	result_dbl = lhs_dbl;
	result_dbl += rhs_dbl;
	dbl_vec = {5.5, 5.5, 5.5, 5.5};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Marix A += Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A += Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl += scalar;
	dbl_vec = {11.9, 12.8, 13.7, 14.6};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A += scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A += scalar) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl;
	result_dbl -= rhs_dbl;
	dbl_vec = {-2.7, -0.9, 0.9, 2.7};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl -= scalar;
	dbl_vec = {-9.1, -8.2, -7.3, -6.4};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A -= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A -= scalar) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl;
	result_dbl *= rhs_dbl;
	dbl_vec = {11.03, 7.7, 22.55, 15.98};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl *= scalar;
	dbl_vec = {14.7, 24.15, 33.6, 43.05};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A *= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A *= scalar) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl;
	result_dbl /= rhs_dbl;
	result_dbl = matrix_round(result_dbl);
	dbl_vec = {2.0556, -3.0556, 3.0556, -4.0556};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl /= scalar;
	result_dbl = matrix_round(result_dbl);
	dbl_vec = {0.1333, 0.2190, 0.3048, 0.3905};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A /= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A /= scalar) == Matrix C test succeeded" << std::endl;
	}

	std::cout << std::endl;
}

void test_det_int() {
	std::vector<int> vec_int = {7, 11, 8, 11};
	matrix_int test_int(vec_int, 2, 2);
	int det = test_int.det();
	int expect_int = -11;
	std::cout << "Matrix<int> determinant tests." << std::endl;
	std::cout << "2x2 tests." << std::endl;
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " <<test_int << std::endl;;

	double det2 = 0.0;
	test_int.lud(det2);
	test_print("Lud calculation directly --> test_int.lud(det) == " + std::to_string(expect_int), expect_int, det);

	std::cout << "3x3 tests" << std::endl;
	//can't loop here b/c compiling with Optimizations is undefined behavior somehow. Not worth the effort.
	expect_int = 0;
	vec_int = {3, 5, 7, 13, 15, 17, 22, 24, 26};
	test_int = matrix_int(vec_int, 3, 3);
	det = test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " <<test_int << std::endl;

	vec_int = {211,312,415,514,223,213,789,897,978};
	expect_int = 19618908;
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " <<test_int << std::endl;

	expect_int=-176;
	vec_int = {3, 5, 7, 11, 19, 21, 22, 27, 31};
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " <<test_int << std::endl;

	std::cout << "4x4 tests" << std::endl;
	expect_int = 12;
	vec_int = {0, 1, 3, 5, 5, 3, 1, 0, 0, 4, 6, 8, 8, 6, 2, 0};
	test_int = matrix_int(vec_int, 4, 4);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " <<test_int << std::endl;

	expect_int=-1270230;
	vec_int={31, 21, 41, 55, 66, 76, 81, 90, 91, 93, 95, 97, 99, 100, 35, 41};
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " <<test_int << std::endl;

	vec_int={51, 51, 41, 55, 66, 76, 81, 90, 91, 93, 95, 97, 103, 200, 351, 411};
	expect_int=965609;
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " <<test_int << std::endl;

}
////TODO: Figure out why the hell I'm getting FP error propagation. Might do long double.
void test_det_double() {
	std::vector<double> vec_dbl = {7.5, 11.5, 8.5, 11.5};
	matrix_double test_dbl(vec_dbl, 2, 2);
	double det = test_dbl.det();
	double expect_dbl = -11.5;
	std::cout << "Matrix<double> determinant tests." << std::endl;
	std::cout << "2x2 tests." << std::endl;
	det=to_fixed(det,5);
	test_print("Matrix A.det() == " + std::to_string(expect_dbl), expect_dbl, det);
	if (expect_dbl != det)
		std::cout << "Matrix A = " << std::setw(3) <<test_dbl << std::endl;
	double det2 = 0.0;
	test_dbl.lud(det2);
	det2=to_fixed(det2,5);
	test_print("Lud calculation directly --> test_dbl.lud(det) == " + std::to_string(expect_dbl), expect_dbl, det);

	std::cout << "3x3 tests" << std::endl;
	//can't loop here b/c compiling with Optimizations is undefined behavior somehow. Not worth the effort.
	expect_dbl = -0.14057098;
	vec_dbl = {1.06, 1.755, 1.717, 1.204, 1.806, 1.758, 1.462, 1.135, 1.757};
	test_dbl = matrix_double(vec_dbl, 3, 3);
	det = test_dbl.det();
	det=to_fixed(test_dbl.det(),8);
	test_print("Matrix A.det() == " + std::to_string(expect_dbl), expect_dbl, det);
	if (expect_dbl != det)
		std::cout << "Matrix A = " <<test_dbl << std::endl;

	vec_dbl = {335.397, 537.152, 938.085, 526.995, 335.988, 342.176, 703.787, 565.472, 525.516};
	expect_dbl = 32645885.0;
	test_dbl.set_arr(vec_dbl);
	det=round(test_dbl.det());
	test_print("Matrix A.det() == " + std::to_string(expect_dbl), expect_dbl, det);
	if (expect_dbl != det)
		std::cout << "Matrix A = " <<test_dbl << std::endl;

	test_dbl.lud(det);
	std::cout << "direct det " << std::to_string(det) << std::endl;
	expect_dbl=189403211.0;
	vec_dbl = {689.487, 117.733, 488.985, 261.032, 871.987, 232.306, 375.025, 631.979, 630.354};
	test_dbl.set_arr(vec_dbl);
	det=floor(test_dbl.det());
	test_print("Matrix A.det() == " + std::to_string(expect_dbl), expect_dbl, det);
	if (expect_dbl != det)
		std::cout << "Matrix A = " <<test_dbl << std::endl;

	std::cout << "4x4 tests" << std::endl;
	expect_dbl = 27064975180.0;
	vec_dbl = {746.223, 213.029, 162.938, 342.047, 566.813, 826.29, 162.789, 666.067, 706.131, 884.913, 208.152, 654.047, 368.807, 285.234, 656.547, 652.029};
	test_dbl = matrix_double(vec_dbl, 4, 4);
	det=floor(test_dbl.det());
	test_print("Matrix A.det() == " + std::to_string(expect_dbl), expect_dbl, det);
	if (expect_dbl != det)
		std::cout << "Matrix A = " <<test_dbl << std::endl;

	expect_dbl=7907416068.0;
	vec_dbl={775.653, 800.148, 773.827, 681.509, 426.544, 881.081, 992.778, 556.79, 549.59, 606.377, 176.841, 62.495, 976.632, 454.591, 158.727, 467.028};
	test_dbl.set_arr(vec_dbl);
	det=round(test_dbl.det());
	test_print("Matrix A.det() == " + std::to_string(expect_dbl), expect_dbl, det);
	if (expect_dbl != det)
		std::cout << "Matrix A = " <<test_dbl << std::endl;

	vec_dbl={51, 51, 41, 55, 66, 76, 81, 90, 91, 93, 95, 97, 103, 200, 351, 411};
	expect_dbl=965610;
	test_dbl.set_arr(vec_dbl);
	det=to_fixed(test_dbl.det(),5);
	test_print("Matrix A.det() == " + std::to_string(expect_dbl), expect_dbl, det);
	if (expect_dbl != det)
		std::cout << "Matrix A = " <<test_dbl << std::endl;

}

void test_adj_int(){
	std::vector<int> input_int(4);
	std::vector<int> output_int(4);
	std::cout << "Matrix<int> Adjugate tests." << std::endl;
	std::cout << "2x2 tests." << std::endl;

	input_int={11, 9, 94, 23};
	output_int={23, -9, -94, 11};
	matrix_int test_int(input_int,2,2);
	matrix_int result_int(2,2,1);
	matrix_int adj_int(output_int,2,2);
	result_int = test_int.adj();
	test_print("Matrix A.adj() == B", adj_int,result_int);

	input_int={70, 97, 98, 60};
	test_int.set_arr(input_int);
	output_int={60, -97, -98, 70};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	input_int={9, 109, 115, 66};
	test_int.set_arr(input_int);
	output_int={66, -109, -115, 9};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	input_int={44, 48, 118, 21};
	test_int.set_arr(input_int);
	output_int={21, -48, -118, 44};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	std::cout << "3x3 tests." << std::endl;
	test_int=matrix_int(3,3);
	adj_int = matrix_int(3,3);
	input_int={16, 26, 54, 116, 110, 61, 94, 70, 85};
	test_int.set_arr(input_int);
	output_int={5080, 1570, -4354, -4126, -3716, 5288, -2220, 1324, -1256};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	input_int={16, 26, 54, 116, 110, 61, 94, 70, 85};
	test_int.set_arr(input_int);
	output_int={5080, 1570, -4354, -4126, -3716, 5288, -2220, 1324, -1256};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	input_int={50, 117, 79, 108, 98, 75, 27, 13, 86};
	test_int.set_arr(input_int);
	output_int={7453, -9035, 1033, -7263, 2167, 4782, -1242, 2509, -7736};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	std::cout << "4x4 tests." << std::endl;
	test_int = matrix_int(4,4);
	adj_int = matrix_int(4,4);
	input_int={88, 20, 88, 79, 90, 57, 56, 55, 40, 120, 73, 118, 51, 12, 15, 19};
	test_int.set_arr(input_int);
	output_int={-19395, 10696, -17987, 161389, -88213, 182283, 1582, -170706, 67266, 264368, -85209, -515768, 54669, -352548, 114552, 437968};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	input_int={123,31,32,35,11,12,13,14,21,22,23,24,31,32,33,34};
	test_int.set_arr(input_int);
	output_int={0,20,-40,20,0,970,1940,-970,0,1880,-3760,1880,0,-930,1860,-930};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);

	input_int={74, 107, 62, 94, 23, 97, 115, 29, 72, 70, 106, 57, 110, 60, 36, 55};
	test_int.set_arr(input_int);
	output_int={205656, -16626, 21825, -365337, -89572, -429600, 601124, -243380, 135940, 38730, -401255, 163091, -402576, 476556, -436782, 457074};
	adj_int.set_arr(output_int);
	result_int=test_int.adj();
	test_print("Matrix A.adj() == B", result_int, adj_int);
}

/* Inverting an integer matrix isn't really possible in approximate form thus only some double test are done.
 * I do 2 2x2s, 2 3x3s, 2 4x4s, 2 5x5s.
 * First I do the slow variant, then the fast variant.
*/
void test_inv_dbl(){
	std::vector<double> input_dbl(4);
	std::vector<double> output_dbl(4);
	std::cout << "Matrix<double> Inverse tests." << std::endl;
	std::cout << "2x2 tests." << std::endl;
	input_dbl={88.0, 5.0, 41.0, 113.0};
	output_dbl={0.0116028, -0.0005134, -0.00420988, 0.00903584};
	Matrix<double> result_dbl(2,2,1);
	Matrix<double> inv_dbl(2,2,1);
	Matrix<double> test_dbl(2,2,1);
	test_dbl.set_arr(input_dbl);
	result_dbl.set_arr(output_dbl);
	test_dbl.inv_slow();
	inv_dbl=to_fixed(test_dbl,5);
	test_print("1 Matrix A.inv == B", result_dbl,test_dbl);

	input_dbl={32.0, 45.0, 21.0, 55.0};
	output_dbl={0.0674847,-0.0552147,-0.0257669,0.0392638};
	test_dbl.set_arr(input_dbl);
	result_dbl.set_arr(output_dbl);
	test_dbl.inv_slow();
	inv_dbl=to_fixed(test_dbl,7);
	test_print("2 Matrix A.inv == B", result_dbl,test_dbl);

}

void test_inv_mod(){
	Matrix<int> matrix_a(2,2,1);
	//std::vector<char> vec = {25,22,15,13};
	//matrix_a.set_arr(vec);
	matrix_a[0] = 25; matrix_a[1] = 22;
	matrix_a[2] = 15; matrix_a[3] = 13;
	std::cout << "initial array values" << std::endl;
	//for(int i=0;i<4;i++){
	//	std::cout << matrix_a[i] + 65 << std::endl;
	//}
	//std::cout << "array size and values" << matrix_a.get_array_size() << std::endl;
	std::cout << matrix_a << std::endl;
//	std::cout << (int) matrix_a.get_array_size() << std::endl;
	std::cout << matrix_a.inv_mod((int)26) << std::endl;
	//for(int i=0;i<4;i++){
	//	std::cout << matrix_a[i] + 65 << std::endl;
	//}
	char modulus = 26;

}
