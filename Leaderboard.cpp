#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include "Leaderboard.h"
#include <iomanip>

const std::string RESET = "\033[0m";
const std::string RED   = "\033[31m";
//const std::string GREEN = "\033[32m";
//const std::string YELLOW= "\033[33m";
const std::string BLUE  = "\033[34m";
const std::string BOLD  = "\033[1m";

void Leaderboard::loadFromFile(){
    std::ifstream inFile(fileName);
    if(inFile.is_open()){
        GameRecord temp;
        while(std::getline(inFile, temp.playerName, ':')){
            inFile >> temp.attempts;
            inFile.ignore(1);
            inFile >> temp.isWin;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            rankingList.push_back(temp);
        }
        inFile.close();
    }
};

void Leaderboard::saveToFile(){
    std::ofstream outFile(fileName);
    if(outFile.is_open()){
        for(const auto& record : rankingList){
            outFile << record.playerName << ":" << record.attempts << ":" << record.isWin << std::endl;
        }
        outFile.close();
    }
};

void Leaderboard::addRecord(const GameRecord& record){
    bool found = false;
    for(auto& existing : rankingList){
        if(existing.playerName == record.playerName){
            found = true;
            if(record.isWin && (!existing.isWin || record.attempts < existing.attempts)){
                existing.isWin = record.isWin;
                existing.attempts = record.attempts;
                isDirty = true;
                std::cout << "个人新纪录！数据榜已更新。" << std::endl;
            }else if(!existing.isWin && !record.isWin && existing.attempts > record.attempts){
                existing.attempts = record.attempts;
                isDirty = true;
            }break;
        }
    }
    if(!found){
        rankingList.push_back(record);
        isDirty = true;
    }
}

void Leaderboard::printRankingList(){
    if(isDirty){ensureSorted();}
    std::cout << "\n" << BOLD << " ———————————— 🏆RANKS LIST(TOP 10) ———————————— " << std::endl;
    std::cout << std::left << std::setw(10) << "RANKING"
              << std::setw(15) << "PLAYER"
              << std::setw(12) << "TIMES"
              << "RESULT" << RESET << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    int rank = 1;
    for(const auto& record : rankingList) {
        std::string statusColor = record.isWin ? RED : BLUE;
        std::string statusText = record.isWin ? "WIN" : "FALSE";

        std::cout << std::left << std::setw(10) << rank++
                  << std::setw(15) << record.playerName 
                  << std::setw(12) << record.attempts
                  << statusColor << statusText << RESET << std::endl;
    }
    std::cout << "--------------------------------------------\n" << std::endl;
}

void Leaderboard::ensureSorted(){
    sort(rankingList.begin(),rankingList.end(),[](const GameRecord& a, const GameRecord& b){
    if(a.isWin != b.isWin){
        return a.isWin > b.isWin;
    }
    return a.attempts < b.attempts;
});
    if(rankingList.size() > 10){
        rankingList.erase(rankingList.begin() + 10, rankingList.end());
    }
    saveToFile();
    isDirty = false;
}