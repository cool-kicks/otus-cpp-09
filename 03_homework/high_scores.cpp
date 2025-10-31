#include <iostream>
#include <fstream>
#include <string>
#include "random_value.h"
#include "check_value.h"
int max_value = 100;



int main(int argc, char** argv) {

const std::string high_scores_filename = "high_scores.txt";

if (argc >= 2 && (std::string(argv[1]) == "-max" || std::string(argv[1]) == "-level")){
	// Get the last high score
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
	
	//std::cin >> attempts_count;
	//if (std::cin.fail()) {
		//std::cout << "Bad value!" << std::endl;
		//return -1;
	//}
};

if (argc >= 2 && std::string(argv[1]) == "-table"){
	std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}
	std::cout << "High scores table:" << std::endl;

		std::string usernames[100];
		int best_scores[100];
		int u_count = 0; 

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
			for(int i = 0; i < u_count; ++i){
			std::cout << usernames[i] << '\t' << best_scores[i] << std::endl;
			}
	return 0;
	
};


	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

int attempts_count = check_foo();
	// Write new high score to the records table

	//{
		// We should open the output file in the append mode - we don't want
		// to erase previous results.
		//std::ofstream out_file{high_scores_filename, std::ios_base::app};
		//if (!out_file.is_open()) {
			//std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			//return -1;
		//}

		// Append new results to the table:
	//} // end of score here just to mark end of the logic block of code

	// Read the high score file and print all results

	std::string usernames[100];
    int best_scores[100];
    int u_count = 0;

	{
		std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		std::string username;
        int score;
		while (in_file >> username >> score){

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
				usernames[u_count] = username;
				best_scores[u_count] = score;
				++u_count;
			}
		}

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

		{
        std::ofstream out_file{high_scores_filename, std::ios_base::trunc};
        if (!out_file.is_open()) {
            std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
            return -1;
        }

        for (int i = 0; i < u_count; ++i) {
            out_file << usernames[i] << ' ' << best_scores[i] << '\n';
        }
    }
		

		std::cout << "\nHigh scores table:\n";
    for (int i = 0; i < u_count; ++i) {
        std::cout << usernames[i] << '\t' << best_scores[i] << '\n';
    }

	}

	return 0;
}