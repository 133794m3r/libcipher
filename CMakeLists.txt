cmake_minimum_required(VERSION 3.18)
project(libciphers)

set(CMAKE_CXX_STANDARD 14)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /W4")
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O1 -g3 ")
	#since CLion decides that you debug from the damn release buildl always instead of from debug and won't let you change that.
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
endif()

add_executable(matrix_test
		includes.hxx
		math.hxx
		vectors.hxx
		matrix.hxx
		matrix_test.hxx
		matrix_test.cpp)

add_executable(hill_cipher
		includes.hxx
		math.hxx
		vectors.hxx
		matrix.hxx
		hill/hill_cipher.hxx
		hill_cipher.cpp)

add_executable(affine
		includes.hxx
		affine/affine.hxx
		affine/affine_test.cpp misc.hxx)

add_executable(hill_test
		includes.hxx
		hill/hill_test.cpp)

add_executable(ngram_test
		includes.hxx
		ngram.hxx
		ngram_test.cpp)