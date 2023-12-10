# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.16.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME ORBITSIM)

# Set name of the project
project(${PROJECT_NAME})

set(PROJECT_SOURCE
	main.cc
)

set(PROJECT_LIBRARIES_DIR
    libs
)

set(PROJECT_LIBRARIES 
    GravityModel
    OrbitModeling
)

set(PROJECT_LIBRARIES_SUBDIR
    gravity_model
    orbit_modeling
)


SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_NO_ABI_WARNING_FLAG} ${GCC_OPT_FLAG}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_ALL_STATIC_FLAG}")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

foreach(LIBRARY ${PROJECT_LIBRARIES_SUBDIR})
    add_subdirectory("${PROJECT_LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBRARIES})