#ifndef PLAYER_H
#define PLAYER_H

#include <string>

enum class PlayerType
{
    current,
    top
};

class Player{
    public:
        Player(PlayerType player_type, std::string name, int score);
        std::string Print() const;
        std::string Title() const;
        int GetScore();
        void UpdateScore(int score);
    
    private:
        std::string name_{""};
        int score_{0};
        PlayerType player_type_{PlayerType::current};
};

#endif