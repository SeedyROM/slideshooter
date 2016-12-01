#pragma once
#include "GameObject.h"

class Particle : public GameObject {
public:
  Particle() : GameObject() {
    weight = rand() % 255 + 15;
    rotate(rand() % 360 / 3.14);
    setPosition(rand() % 800, rand() % 450);
    update(sf::milliseconds(10));
  }

  void update(sf::Time delta) override {
    rotate(cos(life.getElapsedTime().asSeconds() / (float)weight / 4 ));
    setScale(0.15 + life.getElapsedTime().asSeconds() * (0.01 * weight),
             0.15 + life.getElapsedTime().asSeconds() * (0.01 * weight));
    float fade = 255 - life.getElapsedTime().asSeconds() * weight - 120;
    if(fade <= 0) destroy();
    setColor(sf::Color(255, 255, 255, (fade <= 0) ? 0 : fade ));
    _update(delta);
  }
private:
  sf::Clock life;
  int weight;
};
