
find_package(Threads REQUIRED)


set (TestSources
	test.cpp
	CheckParser.cpp

	CheckParserRule.h
	CheckDoubleQuotedParserRule.cpp
	CheckRelationOperatorParserRule.cpp
	CheckASTBuilder.cpp

)



add_executable(compiler_test ${TestSources})
target_link_libraries(compiler_test
	${CMAKE_THREAD_LIBS_INIT}
	${GTEST_LIBRARIES}
	compiler_core
)



file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_reports)

add_test(compiler_test
	compiler_test --gtest_output=xml:${CMAKE_BINARY_DIR}/test_reports/compiler_test.xml
)
