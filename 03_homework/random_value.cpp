#include <iostream>
#include "random_value.h"
#include <cstdlib>
#include <ctime>

int random_value_foo() {

	

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	const int random_value = std::rand() % max_value;

	//std::cout << random_value << std::endl;

	return random_value;
}