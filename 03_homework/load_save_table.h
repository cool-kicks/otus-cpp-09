#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include <string>

const int MAX_USERS = 100;

int load_high_scores(const std::string& filename, std::string usernames[], int best_scores[]);
void save_high_scores(const std::string& filename, const std::string usernames[], const int best_scores[], int u_count);
void print_table_score(const std::string usernames[], const int best_scores[], int u_count);

#endif