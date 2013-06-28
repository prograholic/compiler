cmake_minimum_required(VERSION 2.8)

project(compiler)


find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(core)


add_executable(compiler main.cpp)
target_link_libraries(compiler
	compiler_core
)




find_package(GTest)
if (GTEST_FOUND)
	include(CTest)
	enable_testing()

	add_subdirectory(tests)
endif()



include(FeatureSummary)
feature_summary(WHAT ALL)
