#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Particle.h"
#include "Level.h"

#include "Misc.h"

int main()
{
    // TODO: Read config information from a file.

    // Window state and timers.
    sf::RenderWindow window(sf::VideoMode(800, 450), "slideshooter 0.1");
    sf::Clock deltaClock;
    sf::Clock gameClock;
    long frameCount = 0;
    constexpr float FPS = 60.f;
    window.setFramerateLimit(FPS);

    // Debug implementation of the GameObject system.
    std::vector<GameObject *> objects;

    // Test the GameObject.
    sf::Texture particleTexture;
    particleTexture.loadFromFile("cloud.png");

    // Debug level.
    Level l;
    Player *p1 = new Player();
    p1->loadSprite("test3.png");
    p1->setPosition(200, 100);
    p1->setVelocity(5, 2);
    l.addToQueue(7, p1);
    Player *p2 = new Player();
    p2->loadSprite("test.png");
    p2->setVelocity(3, 5);
    l.addToQueue(5, p2);

    // Game loop...
    while (window.isOpen())
    {
        // Handle timers.
        frameCount++;
        deltaClock.restart();

        // Check for window events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Ctrl-C to quit.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) &&
           sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
          window.close();
        }

        // Handle updating and destroying GameObjects.
        /*for(auto &o : objects) {
          if(o->isDestroyed()) {
            objects.erase(std::remove(objects.begin(),
                                      objects.end(),
                                      o), objects.end());
          } else {
            // Update at constant rate FPS.
            o->update(sf::seconds(1.f / FPS));
          }
        }*/

        //
        // BEGIN Debug.
        //
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          for(int i=0; i<1; i++) {
            Particle *go = new Particle();
            go->loadSprite(particleTexture);
            go->setVelocity((rand() % 100) - 50, (rand() % 100) - 50);
            l.addToQueue(rand() % 20 + 6, go);
          }
        }

        psuedoClear(window, sf::Color(0, 0, 0),
                   (frameCount <= 2) ? 255 : 35);
        //
        // END Debug.
        //

        // Now draw the objects.
        //for(auto &o : objects) {
        //  window.draw(*o);
        //}
        l.update(sf::seconds(1.f / FPS));
        l.draw(window);

        window.display();
    }

    return 0;
}
