#include <SFML/Graphics.hpp>
#include <random>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <stdio.h>
#include "utils.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(CANVAS_WIDTH * CANVAS_SIZE_MULTIPLIER, CANVAS_HEIGHT * CANVAS_SIZE_MULTIPLIER), "Drawing Pixels!!");

    sf::Image img, checkerI;
    sf::Texture tx, checkerT;
    sf::Sprite sp, checkerS;

    img.create(320, 240, {0, 0, 0});

    checkerI.create(256, 256, {0, 0, 0});

    createChecker(checkerI, 16, {0xFF, 0, 0xFF}, {0, 0, 0xFF});
    // createXorTexture(checkerI, 16, {0xFF, 0, 0xFF}, {0, 0, 0xFF});
    checkerT.loadFromImage(checkerI);
    tx.loadFromImage(img);

    sp.setTexture(tx);
    checkerS.setTexture(checkerT);

    sp.setScale(CANVAS_SIZE_MULTIPLIER, CANVAS_SIZE_MULTIPLIER);

    initTables(checkerI);

    sf::Clock deltaClock;
    auto prevDeltaTime = deltaClock.getElapsedTime();

    while (window.isOpen())
    {
        auto currentTime = deltaClock.getElapsedTime();
        auto deltaTime = (currentTime - prevDeltaTime);
        prevDeltaTime = currentTime;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        drawCircleTextured(img, checkerI, {160, 120}, deltaTime.asSeconds());

        tx.loadFromImage(img);

        window.draw(sp);
        // window.draw(checkerS);
        window.display();
    }

    return 0;
}