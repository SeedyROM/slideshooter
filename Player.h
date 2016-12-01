#pragma once
#include <algorithm>
#include "GameObject.h"
#include "Misc.h"

class Player : public GameObject {
public:
  void update(sf::Time delta) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      setVelocity(getVelocity().x, getVelocity().y + 5);
      setVelocity(getVelocity().x, clamp(getVelocity().y, -120, 120));
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      setVelocity(getVelocity().x, getVelocity().y - 5);
      setVelocity(getVelocity().x, clamp(getVelocity().y, -120, 120));
    } else {
      setVelocity(getVelocity().x * 0.7, getVelocity().y * 0.88);
    }
    _update(delta); // Apply world velocity.
  }
};
