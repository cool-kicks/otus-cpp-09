#include <iostream>
#include <fstream>
#include <string>
#include "load_save_table.h"

int load_high_scores(const std::string& filename, std::string usernames[], int best_scores[]) {
    std::ifstream in_file{filename};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << filename << "!" << std::endl;
        return -1;
    }

    int u_count = 0;
    std::string username;
    int score;

    while (in_file >> username >> score) {
        bool found = false;
        for (int i = 0; i < u_count; ++i) {
            if (usernames[i] == username) {
                if (score < best_scores[i]) {
                    best_scores[i] = score;
                }
                found = true;
                break;
            }
        }

        if (!found) {
            if (u_count >= MAX_USERS) {
                std::cout << "Warning: Maximum limit reached!" << std::endl;
                break;
            }
            usernames[u_count] = username;
            best_scores[u_count] = score;
            ++u_count;
        }
    }

    return u_count;
}

void save_high_scores(const std::string& filename, const std::string usernames[], const int best_scores[], int u_count) {
    std::ofstream out_file{filename, std::ios_base::trunc};
    if (!out_file.is_open()) {
        std::cout << "Failed to open file for write: " << filename << "!" << std::endl;
        return;
    }

    for (int i = 0; i < u_count; ++i) {
        out_file << usernames[i] << ' ' << best_scores[i] << '\n';
    }
}

void print_table_score(const std::string usernames[], const int best_scores[], int u_count){
    std::cout << "\nHigh scores table:\n";
    for (int i = 0; i < u_count; ++i) {
        std::cout << usernames[i] << '\t' << best_scores[i] << '\n';
    }
}