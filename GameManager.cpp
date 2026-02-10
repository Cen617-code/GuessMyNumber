#include "Leaderboard.h"
#include "GameManager.h"
#include <algorithm>
#include <cmath>

const std::string RESET = "\033[0m";
const std::string RED   = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW= "\033[33m";
const std::string BLUE  = "\033[34m";
const std::string BOLD  = "\033[1m";

void GameManager::printWelcome(){ std::cout << "欢迎来到猜数字游戏！" << std::endl;}

bool GameManager::isGameOver(int guess, int secret){ return guess == secret;}

int GameManager::getGuess(){
    int guess;
    while(true){
        if(std::cin >> guess){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return guess;
        }
        else{
            std::cout << "输入无效，请输入一个数字" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void GameManager::printHistory(std::vector<int>& history){
    std::cout << "你猜过的数字是" << std::endl;
    for(int i = 0;i < history.size(); i++){
        std::cout << history[i] << " " ;
    }
    std::cout << std::endl;
}

void GameManager::run(){
    srand(time(0)); 
    while(true){
    int secret = rand() % 100 + 1;
    printWelcome();

    GameRecord currentResult = playSession(secret);
    leaderboard->addRecord(currentResult);

    std::cout << "你想继续游戏吗？是请输入yes,否则结束" << std::endl;
    std::string choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(choice != "yes") break;
}
};

GameRecord GameManager::playSession(int secret){
    struct GameRecord gameRecord;
    std::vector<int> history;
    int guess = 0;
    int maxAttempts;
    int currentMin = 1, currentMax = 100, diff = 0;
    std::string playerName;
    std::cout << "输入你的游戏名" << std::endl;
    std::getline(std::cin, playerName);
    std::replace(playerName.begin(),playerName.end(), ':','_');
    std::cout << "输入你想尝试的次数" << std::endl;
    std::cin >> maxAttempts;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "这是个 0～100 之间的数，你猜是多少？" << std::endl;
    while(history.size() < maxAttempts){
        guess = getGuess();
        history.push_back(guess);
        diff = std::abs(guess - secret);
        if(guess > secret){
            std::cout << "📈 太大了" << std::endl;
            currentMax = guess - 1;
        }else if(guess < secret){
            std::cout << "📉 太小了" << std::endl;
            currentMin = guess + 1;
        }else if(guess == secret){
            std::cout << GREEN << "🎊 恭喜猜中" << RESET << std::endl;
            break;
        }
        if(diff < 5){
            std::cout << RED << BOLD << "🔥 烫手！非常接近了" << RESET << std::endl;
        }else if(diff < 30){
            std::cout << YELLOW << "还有些距离" << RESET << std::endl;
        }else{
            std::cout << BLUE << "❄️ 冰凉！还差的很远" << RESET<< std::endl;
        }
        std::cout << "剩余" << maxAttempts - history.size() << "次机会" << ",范围是" << currentMin << " ~ " << currentMax << std::endl;
    }
    gameRecord.playerName = playerName; 
    gameRecord.isWin = isGameOver(guess,secret);
    gameRecord.attempts = history.size();
    if(!gameRecord.isWin){
        std::cout << "很遗憾，你的机会用完了，正确数字是" << secret << std::endl;
    }
    printHistory(history);
    return gameRecord;
    };

