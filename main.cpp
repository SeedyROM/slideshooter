#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

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

class Particle : public GameObject {
public:
  Particle() : GameObject() {
    weight = rand() % 255 + 15;
    rotate(rand() % 360 / 3.14);
    setPosition(rand() % 1200, rand() % 850);
    update(sf::milliseconds(10));
  }

  void update(sf::Time delta) override {
    rotate(cos(life.getElapsedTime().asSeconds() / (float)weight / 4 ));
    setScale(0.2 + life.getElapsedTime().asSeconds() * (0.01 * weight),
             0.2 + life.getElapsedTime().asSeconds() * (0.01 * weight));
    float fade = 255 - life.getElapsedTime().asSeconds() * weight - 120;
    if(fade <= 0) destroy();
    setColor(sf::Color(255, 255, 255, (fade <= 0) ? 0 : fade ));
    _update(delta);
  }
private:
  sf::Clock life;
  int weight;
};

inline void spawnParticles(std::vector<GameObject *> &objects, int amount, sf::Texture& texture) {
  for(int i=0; i<amount; i++) {
    Particle *go = new Particle();
    go->loadSprite(texture);
    go->setVelocity((rand() % 5000) - 2500, (rand() % 5000) - 2500);
    objects.push_back(go);
  }
}

inline void psuedoClear(sf::RenderWindow &window, sf::Color color, int opacity) {
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
  rectangle.setFillColor(sf::Color(color.r,color.g,color.b, opacity));
  window.draw(rectangle);
}

int main()
{
    // TODO: Read config information from a file.
    sf::RenderWindow window(sf::VideoMode(1200, 850), "slideshooter 0.1");
    sf::Clock deltaClock;
    sf::Clock gameClock;
    window.setFramerateLimit(60);
    window.clear(sf::Color(255,0,0));

    std::vector<GameObject *> objects;

    // Test the GameObject.
    sf::Texture particleTexture;
    particleTexture.loadFromFile("test3.png");
    spawnParticles(objects, 50, particleTexture);


    while (window.isOpen())
    {
        deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(auto &o : objects) {
          if(o->isDestroyed())
            objects.erase(std::remove(objects.begin(),
                                      objects.end(),
                                      o), objects.end());
          else
            o->update(deltaClock.getElapsedTime());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          spawnParticles(objects, 1, particleTexture);
        }

        // window.clear();
        psuedoClear(window, sf::Color(150, rand() % 255 + 40, 180), 0);

        for(auto &o : objects) {
          window.draw(*o);
        }
        window.display();
    }

    return 0;
}
