add_library(libctp SHARED IMPORTED)
set_target_properties(libctp PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/vendor/ctp/linux/thosttraderapi_se.so)

add_library(ctp-c SHARED ctp-c.cpp)

target_include_directories(ctp-c PUBLIC ${CMAKE_SOURCE_DIR}/vendor/ctp/linux/)
# target_link_directories(ctp-c PUBLIC ${CMAKE_SOURCE_DIR}/vendor/ctp/linux/)
target_link_libraries(ctp-c libctp)
