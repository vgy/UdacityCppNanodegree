#include <iostream>
#include <memory>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "persistence.h"

int main(int argc, char *argv[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  std::string name;
  std::cout << "Welcome to the Snake Game!\n";
  std::cout << "Enter Your Name.\n";
  std::cin >> name;
  std::shared_ptr<Player> player = std::make_shared<Player>(PlayerType::current, name, 0);

  Persistence persistence;
  std::shared_ptr<Player> top_player = std::make_shared<Player>(persistence.ReadContent());

  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  std::unique_ptr<Controller> controller = std::make_unique<Controller>();
  Game game(kGridWidth, kGridHeight, player, top_player);
  game.Run(std::move(controller), std::move(renderer), kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  player->UpdateScore(game.GetScore());
  std::cout << "Score: " << player->GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  
  auto player_persist = player->GetScore() >= top_player->GetScore() ? player : top_player;
  persistence.WriteContent(player_persist);
  return 0;
}