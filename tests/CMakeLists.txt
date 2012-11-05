find_package(Threads REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_reports)


add_subdirectory(tokenizer)
add_subdirectory(AST)
