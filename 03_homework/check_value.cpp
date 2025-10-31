#include <iostream>
#include "check_value.h"
#include "random_value.h"

int check_foo(int max_value) {

	
	
	int rv = random_value_foo(max_value);
	
	int current_value = 0;

	int count_attempt = 0;

	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;

		if (current_value < rv) {
			count_attempt++;
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value > rv) {
			count_attempt++;
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			count_attempt++;
			std::cout << "you win!" << std::endl;
			break;
		}

	} while(true);

	return count_attempt;
}