#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "persistence.h"

int main(int argc, char *argv[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  /*
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  */
  constexpr std::size_t kScreenWidth{320};
  constexpr std::size_t kScreenHeight{320};
  constexpr std::size_t kGridWidth{16};
  constexpr std::size_t kGridHeight{16};

  std::string name;
  std::cout << "Welcome to the Snake Game!\n";
  std::cout << "Enter Your Name.\n";
  std::cin >> name;

  Persistence p;
  auto ts2 = p.readContent();  

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  
  TopScore ts;
  ts.name = name;
  ts.score = game.GetScore();
  p.writeContent(ts);
  return 0;
}