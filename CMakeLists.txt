cmake_minimum_required(VERSION 2.8)

project(compiler)


find_package(Boost REQUIRED)

add_executable(compiler main.cpp)





find_package(GTest)
if (GTEST_FOUND)
	include(CTest)
	enable_testing()

	add_subdirectory(tests)
endif()



include(FeatureSummary)
feature_summary(WHAT ALL)
