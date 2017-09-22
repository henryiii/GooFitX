add_executable(simple simple.cpp ${GOOFIT_HEADERS})
target_link_libraries(simple PUBLIC goofit)
set_target_properties(simple PROPERTIES FOLDER examples)

add_executable(fitting fitting.cpp ${GOOFIT_HEADERS})
target_link_libraries(fitting PUBLIC goofit)
set_target_properties(fitting PROPERTIES FOLDER examples)
