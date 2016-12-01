#pragma once
#include <algorithm>
#include "GameObject.h"
#include "Misc.h"

class Player : public GameObject {
public:
  float movementSpeed = 80;
  float damping = 0.83;


  void update(sf::Time delta) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      setVelocity(getVelocity().x, getVelocity().y - 7);
      setVelocity(getVelocity().x, clamp(getVelocity().y, -movementSpeed, movementSpeed));
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      setVelocity(getVelocity().x, getVelocity().y + 7);
      setVelocity(getVelocity().x, clamp(getVelocity().y, -movementSpeed, movementSpeed));
    } else {
      setVelocity(getVelocity().x * damping, getVelocity().y * damping);
    }
    _update(delta); // Apply world velocity.
  }
};
