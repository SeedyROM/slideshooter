#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Engine/GameState.h"
#include "Engine/Stage.h"

#include "Player.h"
#include "Cloud.h"

#include "Engine/Helpers/Misc.h"
#include "Engine/GUI/Menu.h"

int main()
{
    // TODO: Read config information from a file.

    // Window state and timers.

    GSInit(1000, 600, "Testing!");
    window.setVerticalSyncEnabled(true);

    // Test the GameObject.
    sf::Texture particleTexture;
    particleTexture.loadFromFile("Resources/Images/cloud.png");

    // Debug level.
    Stage *level = new Stage();
    GSSetCurrentStage(level);

    Player *p1 = new Player();
    p1->setTextureRect(sf::IntRect(96*3, 0, 96, 96));
    p1->loadSprite("Resources/Images/ship.png");
    p1->setScale(0.75, 0.75);
    p1->setPosition(100, GSGetWindowSize.y/2);
    level->addObjectToStage(5, p1);

    // Debug Menu
    // Holy fuck this worked on the first try.
    MenuItem i1("Fuck", []() {
      std::cout << "I've been acted upon! : " << GSGetWindowSize.x << std::endl;
    });
    MenuItem i2("Ass", []() {
      std::cout << "I've also been seen!\n";
    });
    Menu m;
    m.addMenuItem(i1);
    m.addMenuItem(i2);
    m.activateItem();

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
                   (GSGetTime.asMilliseconds() <= 500) ? 255 : 200);

        if(GSGetTime.asMilliseconds() % 10 == 0 ) {
          for(int i=0; i < 8; i++) {
            Cloud *c = new Cloud();
            c->loadSprite(particleTexture);
            level->addObjectToStage(rand() % 4 + 2, c);
          }
        }

        //GSGetCurrentStage->update(sf::seconds(1.f / GSGetMaxFPS));
        GSGetCurrentStage->draw(window);

        window.display();
    }

    return 0;
}
