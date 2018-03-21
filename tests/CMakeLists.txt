
add_executable(test_main test_main.cpp test_fitting.cpp ${GOOFIT_HEADERS})
target_link_libraries(test_main goofit Catch2::Catch)
set_target_properties(test_main PROPERTIES FOLDER tests)
add_test(test_main test_main)
