#pragma once
#include "GameObject.h"

class Cloud : public GameObject {
public:
  Cloud() {
    setPosition(GSGetWindowSize.x + 500, rand() % GSGetWindowSize.y);
    setVelocity(-(rand() % 100 + 60), getVelocity().y);
    setScale(randFloat() * 1.5f, randFloat() * 1.5f);
    setColor(sf::Color(255, 255, 255, 128 + randFloat() * 128 ));
  }
  void update(sf::Time delta) {
    //int ms = life.getElapsedTime().asMilliseconds();
    if(getPosition().x <= -300) destroy();
    _update(delta);
  }
private:
  sf::Clock life;
  int size = 0;
};
