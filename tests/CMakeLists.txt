#add_executable(ctp-trade-tests trade_test.c)
#target_link_libraries(ctp-trade-tests LINK_PUBLIC ctp-c)

add_executable(ctp-md-tests md_test.c)
target_include_directories(ctp-md-tests PUBLIC ${CMAKE_SOURCE_DIR}/vendor/ctp/linux/)
target_link_libraries(ctp-md-tests LINK_PUBLIC ctp-c)
