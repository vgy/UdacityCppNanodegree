#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "player.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::shared_ptr<Player> player, std::shared_ptr<Player> top_player);
  void Run(std::unique_ptr<Controller const> controller, std::unique_ptr<Renderer const> renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  std::shared_ptr<Player> player_;
  std::shared_ptr<Player> top_player_;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif