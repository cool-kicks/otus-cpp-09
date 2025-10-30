cmake_minimum_required(VERSION 3.12)

project(03.homework)

add_executable(
	game
	high_scores.cpp
	random_value.cpp
	check_value.cpp
)


set_target_properties(game PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)