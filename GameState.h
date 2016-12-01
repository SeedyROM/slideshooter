#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
  static GameState * pInstance;

  GameState() {}
  GameState(const GameState& rs) {
    pInstance = rs.pInstance;
  }

  GameState& operator = (const GameState& rs) {
    if (this != &rs) {
       pInstance = rs.pInstance;
    }

    return *this;
  }

~GameState () {}

public:
  sf::RenderWindow *window;
  sf::Clock *deltaClock;
  sf::Clock *gameClock;
  long *frameCount;
  static constexpr float FPS = 60.f;

  void setup(sf::RenderWindow *_window, sf::Clock *_deltaClock,
             sf::Clock *_gameClock, long *_frameCount) {
    window = _window;
    deltaClock = _deltaClock;
    window->setFramerateLimit(FPS);
  }

  static GameState& getInstance()
  {
    static GameState theInstance;
    pInstance = &theInstance;

    return *pInstance;
  }

  void demo() { std::cout << "other singleton # next - your code ..." << std::endl; }
};

GameState * GameState::pInstance = nullptr;
