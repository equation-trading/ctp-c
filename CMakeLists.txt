cmake_minimum_required(VERSION 3.0.0)

project(ctp-c VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(include)
add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
