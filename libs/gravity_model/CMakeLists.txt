cmake_minimum_required(VERSION 3.16.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME
    GravityModelLib
)
set(LIBRARY_NAME
    GravityModel
)
set(LIBRARY_HEADERS_DIR
    include
)

file(GLOB LIBRARY_HEADERS CONFIGURE_DEPENDS "${LIBRARY_HEADERS_DIR}/*.h")

set(LIBRARY_SOURCE_DIR
    src
)

file(GLOB LIBRARY_SOURCE CONFIGURE_DEPENDS "${LIBRARY_SOURCE_DIR}/*.cc")

project(${PROJECT_NAME})

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCE}
)

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(GravityModel)