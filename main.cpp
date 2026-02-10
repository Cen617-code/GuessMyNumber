#include "GameManager.h"
#include <memory>
int main(){

    auto myLeaderboard = std::make_shared<Leaderboard>();
    GameManager gm(myLeaderboard);

    gm.run();

    myLeaderboard->printRankingList();
    return 0;
}