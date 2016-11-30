#pragma once
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
