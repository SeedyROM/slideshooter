#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Particle.h"

#include "Misc.h"

int main()
{
    // TODO: Read config information from a file.

    // Window state and timers.
    sf::RenderWindow window(sf::VideoMode(800, 450), "slideshooter 0.1");
    sf::Clock deltaClock;
    sf::Clock gameClock;
    long frameCount = 0;
    window.setFramerateLimit(60);

    // Debug implementation of the GameObject system.
    std::vector<GameObject *> objects;

    // Test the GameObject.
    sf::Texture particleTexture;
    particleTexture.loadFromFile("test3.png");

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
        for(auto &o : objects) {
          if(o->isDestroyed()) {
            objects.erase(std::remove(objects.begin(),
                                      objects.end(),
                                      o), objects.end());
          } else {
            o->update(sf::seconds(1.f / 60.f));
          }
        }

        //
        // BEGIN Debug.
        //
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          spawnParticles(objects, 1, particleTexture);
        }

        psuedoClear(window, sf::Color(150, rand() % 100 + 40, 180),
                   (frameCount <= 2) ? 255 : 25);
        //
        // END Debug.
        //

        // Now draw the objects.
        for(auto &o : objects) {
          window.draw(*o);
        }
        window.display();
    }

    return 0;
}
