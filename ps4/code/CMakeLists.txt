enable_language(C)
cmake_minimum_required(VERSION 2.6)
project(sum)

set(OPENMP_EN OFF)
set(MPI_EN    ON)

if(OPENMP_EN)
	find_package( OpenMP REQUIRED)
	if(OPENMP_FOUND)
		message("OPENMP FOUND")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
		add_definitions(-DHAVE_OPENMP)
	endif()
endif()

add_definitions(-std=c99)

link_libraries(-lm)

add_executable(sum sum.c sumlib.c)
