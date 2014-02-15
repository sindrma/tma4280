
cmake_minimum_required(VERSION 2.6)
project(sum)

enable_language(C)

option(OPENMP_EN "Enable OpenMP?" ON)
option(MPI_EN  "Enable MPI?"      ON)

if(OPENMP_EN)
	find_package(OpenMP)
	if(OPENMP_FOUND)
		message("OPENMP FOUND")
		set(COMMON_DEFINITIONS "${COMMON_DEFINITIONS} -DHAVE_OPENMP")
    		list(APPEND COMMON_C_FLAGS ${OpenMP_C_FLAGS})	
	endif()
endif()

if(MPI_EN)
  	find_package(MPI)
  	if(MPI_FOUND)
		message("MPI FOUND")
    		set(COMMON_DEFINITIONS "${COMMON_DEFINITIONS} -DHAVE_MPI")
    		list(APPEND COMMON_C_FLAGS ${MPI_C_FLAGS})
    		list(APPEND COMMON_LIBRARIES ${MPI_C_LIBRARIES} ${MPI_Fortran_LIBRARIES})
    		list(APPEND COMMON_INCLUDE_PATHS ${MPI_C_INCLUDE_PATH})
  	endif()
endif()

link_libraries(-lm)

include_directories(${COMMON_INCLUDE_PATHS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_C_FLAGS} ${COMMON_DEFINITIONS}")

add_executable(sum sum.c sumlib.c)
target_link_libraries(sum ${COMMON_LIBRARIES})
