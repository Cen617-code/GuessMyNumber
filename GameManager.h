#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include "Leaderboard.h"
class GameManager{

private:
    std::shared_ptr<Leaderboard> leaderboard;

    void printWelcome();

    bool isGameOver(int guess, int secret);

    int getGuess();

    void printHistory(std::vector<int>& history);

public:

    GameManager(std::shared_ptr<Leaderboard> lb) : leaderboard(lb) {}

    void run();

private:
    GameRecord playSession(int secret);
};


#endif