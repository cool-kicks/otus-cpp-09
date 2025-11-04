#include <iostream>
#include <fstream>
#include <string>
#include "random_value.h"
#include "check_value.h"
#include "load_save_table.h"
int max_value = 100;



int main(int argc, char** argv) {

const std::string high_scores_filename = "high_scores.txt";

std::ofstream check_file(high_scores_filename, std::ios::app);
check_file.close();

std::string usernames[MAX_USERS];
    int best_scores[MAX_USERS];
    int u_count = 0;

if (argc >= 2 && (std::string(argv[1]) == "-max" || std::string(argv[1]) == "-level")){
	//std::cout << "Enter your high score:" << std::endl;
			if (argc >= 3 && (
    (std::string(argv[1]) == "-level" && std::string(argv[2]) == "-max") ||
    (std::string(argv[1]) == "-max" && std::string(argv[2]) == "-level")
)) {
    std::cout << "Incompatible arguments: '-max' and '-level' cannot be used together!" << std::endl;
    return -1;
}
		}
	if (std::string(argv[1]) == "-level" && (std::stoi(argv[2]) > 0 && std::stoi(argv[2]) < 4)){
		if(std::stoi(argv[2]) == 1)
			max_value = 10;
		else if(std::stoi(argv[2]) == 2)
			max_value = 50;
		else if(std::stoi(argv[2]) == 3)
			max_value = 100;
	}
	else if(std::string(argv[1]) == "-max"){
		max_value = std::stoi(argv[2]);
		std::cout << "Level set, max_value = " << max_value << std::endl;
	
	}

if (argc == 2 && std::string(argv[1]) == "-table"){
	std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}
	std::cout << "High scores table:" << std::endl;

		std::string username;
		int score = 0;

		while (in_file >> username >> score) {
			bool found = false;
			for(int i = 0; i < u_count; ++i){
				if(usernames[i].compare(username) == 0){
					if(score < best_scores[i]){
						best_scores[i] = score;
					}
					found = true;
					break;
				}
			}
			
			if(!found){
				if(u_count >= MAX_USERS) {
        		std::cout << "Warning: Maximum limit!" << std::endl;
        		break;
				}
				usernames[u_count] = username;
				best_scores[u_count] = score;
				++u_count;
			}

			in_file.ignore();

			if (in_file.fail()) {
				break;
			}
		
		}
		// Print the information to the screen
		print_table_score(usernames, best_scores, u_count);
	return 0;
	
};


	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

int attempts_count = check_foo(max_value);
	// Write new high score to the records table
	// Append new results to the table:
	// Read the high score file and print all results
	u_count = load_high_scores(high_scores_filename, usernames, best_scores);
    if (u_count < 0) return -1;

		bool found = false;
		for(int i = 0; i < u_count; ++i){
			if(usernames[i].compare(user_name) == 0){
				if(attempts_count < best_scores[i]){
					best_scores[i] = attempts_count;
					std::cout << "New record for " << user_name << "!\n";
				}
				found = true;
				break;
			}
		}
		
		if(!found){
			usernames[u_count] = user_name;
			best_scores[u_count] = attempts_count;
			++u_count;
		}

	save_high_scores(high_scores_filename, usernames, best_scores, u_count);
		
	print_table_score(usernames, best_scores, u_count);

	return 0;
}