#include <iostream>
#include <fstream>
#include <sstream>

#include "Persistence.h"

constexpr char PersistencePath[] = "ScorePersistence.txt";

void Persistence::WriteContent(const std::shared_ptr<Player> player){

    std::ofstream fout(PersistencePath, std::ios::trunc);

    if (fout.is_open()) {
        fout << player->Print() << std::endl;
        fout.close(); 
    }
}
    
Player Persistence::ReadContent(){
    
    bool valid{false};
    std::string content;
    std::ifstream my_file (PersistencePath);

    if (my_file.is_open())
    {
        std::string line;
        while(getline(my_file,line)){
            std::istringstream ss(line);
            bool valid = true;

            std::string name;
            if(!std::getline(ss, name, ',')) {
                valid = false;
            }

            std::string score;
            if(!std::getline(ss, score, ',')) {
                valid = false;
            }

            if (valid)
            {
                return Player(PlayerType::top, name, std::stoi(score));
            }

            break;
        }
        my_file.close();
    }
    return Player(PlayerType::top, "", 0);
}