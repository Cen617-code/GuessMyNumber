#ifndef LEADERBOARD_H   
#define LEADERBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include "GameRecord.h"
class Leaderboard{
private:

    std::vector<GameRecord> rankingList;
    const std::string fileName = "ranking.txt";
    bool isDirty = false;

public:
    Leaderboard(){ loadFromFile(); }
        
    ~Leaderboard() { saveToFile(); }

    void loadFromFile();

    void saveToFile();

    void addRecord(const GameRecord& record);

    void printRankingList();

    void ensureSorted();
};

#endif