set (CheckASTSources
	test.cpp
	CheckASTBuilder.cpp
)



add_executable(AST_test ${CheckASTSources})
target_link_libraries(AST_test
	${CMAKE_THREAD_LIBS_INIT}
	${GTEST_LIBRARIES}
	compiler_core_tokenizer
	compiler_core
	compiler_core_tokenizer_rules
)


add_test(AST_test
	AST_test --gtest_output=xml:${CMAKE_BINARY_DIR}/test_reports/AST_test.xml
)
