cmake_minimum_required(VERSION 3.10)
find_package(OpenMP)
find_package(MPI)

add_custom_target(todos)
add_dependencies(todos mainMPI mainOpenMP mainOpenMP_MPI)

add_executable(mainMPI mainMPI.c)
add_executable(mainOpenMP mainOpenMP.c)
add_executable(mainOpenMP_MPI mainOpenMP_MPI.c)
if(OpenMP_CXX_FOUND)
	target_link_libraries(mainOpenMP PUBLIC OpenMP::OpenMP_CXX)
	target_link_libraries(mainOpenMP_MPI PUBLIC OpenMP::OpenMP_CXX)
endif()
target_include_directories(mainMPI PRIVATE ${MPI_INCLUDE_PATH})
target_include_directories(mainOpenMP_MPI PRIVATE ${MPI_INCLUDE_PATH})

target_link_libraries(mainMPI PRIVATE ${MPI_C_LIBRARIES})
target_link_libraries(mainOpenMP_MPI PRIVATE ${MPI_C_LIBRARIES})

#enable_testing()

#find_program(BASH_PROGRAM bash)
#add_test(testPerformance ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/performance.sh)
