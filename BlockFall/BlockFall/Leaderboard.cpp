#include "Leaderboard.h"

void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {
    LeaderboardEntry* current_entry = head_leaderboard_entry;
    LeaderboardEntry* previous_entry = nullptr;
    while (current_entry != nullptr && new_entry->score <= current_entry->score) {
        previous_entry = current_entry;
        current_entry = current_entry->next_leaderboard_entry;
    }

    new_entry->next_leaderboard_entry = current_entry;
    if (previous_entry == nullptr) {
        head_leaderboard_entry = new_entry;
    } else {
        previous_entry->next_leaderboard_entry = new_entry;
    }

    leaderboard_size++;

    if (leaderboard_size > 10) {
        LeaderboardEntry* last_entry = head_leaderboard_entry;
        LeaderboardEntry* previous_last_entry = last_entry;
        while (last_entry->next_leaderboard_entry != nullptr) {
            previous_last_entry = last_entry;
            last_entry = last_entry->next_leaderboard_entry;
        }

        delete last_entry;
        last_entry = nullptr;
        previous_last_entry->next_leaderboard_entry = nullptr;
        
        leaderboard_size--;
    }
}

void Leaderboard::write_to_file(const string& filename) {
    ofstream file(filename);

    LeaderboardEntry* current_entry = head_leaderboard_entry;
    while (current_entry != nullptr) {
        file << current_entry->score << " " << current_entry->last_played << " " << current_entry->player_name << endl;
        current_entry = current_entry->next_leaderboard_entry;
    }

    file.close();
}

void Leaderboard::read_from_file(const string& filename) {
    ifstream file(filename);
    LeaderboardEntry* current_entry = nullptr;
    LeaderboardEntry* head_entry = nullptr;

    unsigned long score;
    time_t lastPlayed;
    string playerName;

    while (file >> score >> lastPlayed >> playerName) {
        LeaderboardEntry* new_entry = new LeaderboardEntry(score, lastPlayed, playerName);
        if (current_entry == nullptr) {
            head_entry = new_entry;
        } else {
            current_entry->next_leaderboard_entry = new_entry;
        }
        current_entry = new_entry;
        leaderboard_size++;
    }

    this->head_leaderboard_entry = head_entry;

    file.close();
}

void Leaderboard::print_leaderboard() {
    std::cout << "Leaderboard\n-----------\n";
    LeaderboardEntry* current_entry = head_leaderboard_entry;
    int order = 1;
    while (current_entry != nullptr) {
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%H:%M:%S/%d.%m.%Y", localtime(&current_entry->last_played));

        std::cout << order << ". " << current_entry->player_name << " " << current_entry->score << " " << buffer << endl;
        order++;
        current_entry = current_entry->next_leaderboard_entry;
    }
}

Leaderboard::~Leaderboard() {
    LeaderboardEntry* current_entry = head_leaderboard_entry;
    while (current_entry != nullptr) {
        LeaderboardEntry* next_entry = current_entry->next_leaderboard_entry;
        delete current_entry;
        current_entry = next_entry;
    }

    head_leaderboard_entry = nullptr;
}