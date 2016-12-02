#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "GameState.h"

#include "Player.h"
#include "Cloud.h"
#include "Stage.h"

#include "Misc.h"

int main()
{
    // TODO: Read config information from a file.

    // Window state and timers.

    GSInit(1000, 600, "Testing!");
    window.setVerticalSyncEnabled(true);

    // Test the GameObject.
    sf::Texture particleTexture;
    particleTexture.loadFromFile("cloud.png");

    // Debug level.
    Stage *level = new Stage();
    GSSetCurrentStage(level);

    Player *p1 = new Player();
    p1->setTextureRect(sf::IntRect(96*3, 0, 96, 96));
    p1->loadSprite("ship.png");
    p1->setScale(0.75, 0.75);
    p1->setPosition(100, GSGetWindowSize.y/2);
    level->addObjectToStage(5, p1);

    // Game loop...
    while (window.isOpen())
    {
        // Handle timers.
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

        //
        // Debug.
        //
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          for(int i=0; i<1; i++) {
            Particle *go = new Particle();
            go->loadSprite(particleTexture);
            go->setVelocity((rand() % 100) - 50, (rand() % 100) - 50);
            l.addToQueue(rand() % 20 + 6, go);
          }
        }
        */

        psuedoClear(window, sf::Color(94, 152, 171),
                   (GSGetTime.asMilliseconds() <= 500) ? 255 : 105);

        if(GSGetTime.asMilliseconds() % 8 == 0 ) {
          Cloud *c = new Cloud();
          c->loadSprite(particleTexture);
          level->addObjectToStage(rand() % 6 + 5, c);
        }

        //GSGetCurrentStage->update(sf::seconds(1.f / GSGetMaxFPS));
        GSGetCurrentStage->draw(window);

        window.display();
    }

    return 0;
}
