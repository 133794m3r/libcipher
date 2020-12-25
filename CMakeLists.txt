cmake_minimum_required(VERSION 3.18)
project(libciphers)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11 /W4")
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O2 -g3 ")
	#since CLion decides that you debug from the damn release buildl always instead of from debug and won't let you change that.
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
endif()

add_executable(matrix_test
		math.hxx
		vectors.hxx
		matrix.hxx
		matrix_test.hxx
		matrix_test.cpp)

add_executable(hill_cipher
		hill_cipher.cpp
		matrix.hxx
		hill_cipher.hxx
		math.hxx
		vectors.hxx)

add_executable(hill_test
		hill_test.cpp)