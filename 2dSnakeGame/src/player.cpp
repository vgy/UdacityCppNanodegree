#include "player.h"

constexpr char PlayerTitle[] = "Player";
constexpr char TopPlayerTitle[] = "TopPlayer";

Player::Player(PlayerType player_type, std::string name, int score) : 
        player_type_(player_type),
        name_(name), 
        score_(score) { }

std::string Player::Print() const
{
    return std::string{name_ + "," + std::to_string(score_)};

}

std::string Player::Title() const
{
    if (name_ == "") return "";
    
    auto type = player_type_ == PlayerType::current ? PlayerTitle : TopPlayerTitle;
    return Title(type);
}

std::string Player::Title(std::string prefix) const
{
    return std::string{prefix + "(Name: " + name_ + " Score: " + std::to_string(score_) + ")"};
}

int Player::GetScore()
{
    return score_;
}

void Player::UpdateScore(int score)
{
    if (player_type_ == PlayerType::top) return;
    
    score_ = score;
}