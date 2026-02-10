#ifndef GAME_RECORD_H
#define GAME_RECORD_H
#include <string>

struct GameRecord {
    std::string playerName;
    int attempts;
    bool isWin;
};

#endif