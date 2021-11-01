cmake_minimum_required(VERSION 3.21)

project(hse_crackme
	VERSION 1.0
	LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
	main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_EXTENSIONS OFF
	LINK_OPTIONS -s
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_options(${PROJECT_NAME} PRIVATE
	-static
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND upx -9 -v ${PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Compress..."
)
