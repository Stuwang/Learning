SET(CMAKE_CXX_COMPILER "clang++")
message(STATUS "COMPILER:clang++")

# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# if(CMAKE_COMPILER_IS_GNUCXX)
add_compile_options(-std=c++11)
message(STATUS "optional:-std=c++11")

# add_compile_options(-Werror -Wall)
# message(STATUS "optional:-Werror -Wall")

# -Wc++1y-extensions
add_compile_options(-Wc++1y-extensions)
message(STATUS "optional:-Wc++1y-extensions")

add_compile_options(-o2)
message(STATUS "optional:-o2")

add_compile_options(-pthread)
message(STATUS "optional:-pthread")

# if("${CMAKE_BUILD_TYPE}" equal "debug")
# 	add_compile_options(-g)
# 	message(STATUS "optional:-g")
# else()


# 项目信息
project (function)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	)

aux_source_directory(. SRCS)

add_executable(main test.cpp)