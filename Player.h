#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
  void update(sf::Time delta) {
    //
    // TODO:
    // Custom behaviour here!
    //
    _update(delta); // Apply world velocity.
  }
};
