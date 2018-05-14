vexcl_add_executables(simple simple.cpp ${GOOFIT_HEADERS})
target_link_libraries(simple INTERFACE goofit)
#set_target_properties(simple PROPERTIES FOLDER examples)

vexcl_add_executables(fitting fitting.cpp ${GOOFIT_HEADERS})
target_link_libraries(fitting INTERFACE goofit)
#set_target_properties(fitting PROPERTIES FOLDER examples)
