#include <iostream>
#include <fstream>
#include <sstream>

#include "Persistence.h"

constexpr char persistencePath[] = "ScorePersistence.txt";

void Persistence::writeContent(const TopScore &topScore){

    std::ofstream fout(persistencePath, std::ios::trunc);  
    std::string content = topScore.name + "," + std::to_string(topScore.score); 

    if (fout.is_open()) {
        fout << content << std::endl;
        fout.close(); 
    }
}
    
TopScore Persistence::readContent(){
    
    bool valid{false};
    std::string content;
    std::ifstream myfile (persistencePath);
    TopScore topScore;

    if (myfile.is_open())
    {
        std::string line;
        while(getline(myfile,line)){
            std::istringstream ss(line);

            std::string name;
            if(std::getline(ss, name, ',')) {
                topScore.name = name;
            }

            std::string score;
            if(std::getline(ss, score, ',')) {
                topScore.score = std::stoi(score);
            }
            break;
        }
        myfile.close();
    }
    return topScore;
}