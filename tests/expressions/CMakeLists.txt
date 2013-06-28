
find_package(Threads REQUIRED)


set (CheckExpressionsSources
	test.cpp
)



add_executable(expressions_test ${CheckExpressionsSources})
target_link_libraries(expressions_test
	${CMAKE_THREAD_LIBS_INIT}
	${GTEST_LIBRARIES}
	compiler_core_expressions
	compiler_core
)



file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_reports)

add_test(expressions_test
	expressions_test --gtest_output=xml:${CMAKE_BINARY_DIR}/test_reports/expressions_test.xml
)
