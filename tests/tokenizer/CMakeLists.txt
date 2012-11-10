
find_package(Threads REQUIRED)


set (CheckTokenizerSources
	test.cpp
	CheckTokenizer.cpp

	CheckTokenizerRule.h
	CheckDoubleQuotedTokenizerRule.cpp
	CheckRelationOperatorTokenizerRule.cpp
	CheckPredefinedNameTokenizerRule.cpp
)



add_executable(tokenizer_test ${CheckTokenizerSources})
target_link_libraries(tokenizer_test
	${CMAKE_THREAD_LIBS_INIT}
	${GTEST_LIBRARIES}
	compiler_core_tokenizer
	compiler_core
	compiler_core_tokenizer_rules
)



file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_reports)

add_test(tokenizer_test
	tokenizer_test --gtest_output=xml:${CMAKE_BINARY_DIR}/test_reports/tokenizer_test.xml
)
