find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_reports)


add_subdirectory(tokenizer)
add_subdirectory(AST)
add_subdirectory(expressions)
