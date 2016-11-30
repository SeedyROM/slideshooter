#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

class GameObject : public sf::Sprite {
public:
  GameObject() : sf::Sprite() {}
  virtual ~GameObject() {}

  sf::Vector2f getVelocity() { return m_velocity; }
  void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
  void setVelocity(float x, float y) { m_velocity = sf::Vector2f(x, y); }

  int loadSprite(std::string location) {
    if(!m_texture.loadFromFile(location)) return -1;
    setTexture(m_texture);
    setOrigin(sf::Vector2f(getTextureRect().width / 2,
                           getTextureRect().height / 2));
    return  0;
  }
  int loadSprite(sf::Texture &texture) {
    setTexture(texture);
    setOrigin(sf::Vector2f(getTextureRect().width / 2,
                           getTextureRect().height / 2));
    return  0;
  }

  void destroy() { m_destroyed = true; }
  bool isDestroyed() { return m_destroyed; }

  virtual void update(sf::Time) {}

protected:
  void _update(sf::Time delta) {
    setPosition(getPosition() + ( getVelocity() * (float)delta.asSeconds() * 8.0f ));
  }

private:
  sf::Vector2f m_velocity;
  sf::Texture  m_texture;
  bool         m_destroyed = false;
};

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

class Kanye : public GameObject {
public:
  Kanye() : GameObject() {
    weight = rand() % 255 + 15;
    setPosition(rand() % 850, rand() % 550);
  }

  void update(sf::Time delta) override {
    rotate(cos(life.getElapsedTime().asSeconds() * (float)weight ));
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

inline void spawnYeezuses(std::vector<GameObject *> &objects, int amount, sf::Texture& texture) {
  for(int i=0; i<amount; i++) {
    Kanye *go = new Kanye();
    go->loadSprite(texture);
    go->setVelocity((rand() % 5000) - 2500, (rand() % 5000) - 2500);
    objects.push_back(go);
  }
}

int main()
{
    // TODO: Read config information from a file.
    sf::RenderWindow window(sf::VideoMode(900, 550), "slideshooter 0.1");
    sf::Clock deltaClock;
    sf::Clock gameClock;
    window.setFramerateLimit(60);

    std::vector<GameObject *> objects;

    // Test the GameObject.
    sf::Texture kanyeTexture;
    kanyeTexture.loadFromFile("test.png");
    spawnYeezuses(objects, 50, kanyeTexture);


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
          spawnYeezuses(objects, 2, kanyeTexture);
        }

        window.clear();

        for(auto &o : objects) {
          window.draw(*o);
        }
        window.display();
    }

    return 0;
}
