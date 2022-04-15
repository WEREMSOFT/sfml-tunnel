#include <SFML/Graphics.hpp>
#include <random>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <stdio.h>
#include "utils.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(CANVAS_WITH * CANVAS_SIZE_MULTIPLIER, CANVAS_HEIGHT * CANVAS_SIZE_MULTIPLIER), "Drawing Pixels!!");

    sf::Image img;

    img.create(320, 240, {255, 0, 0});

    createChecker(img, 10, {0xFF, 0, 0}, {0, 0, 0xFF});

    sf::Texture tx;

    tx.loadFromImage(img);

    sf::Sprite sp;
    sp.setTexture(tx);

    sp.setScale(CANVAS_SIZE_MULTIPLIER, CANVAS_SIZE_MULTIPLIER);

    int x, y;

    while (window.isOpen())
    {
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

        drawCircle(img, {100, 100}, 30, {0, 0, 0});

        tx.loadFromImage(img);

        window.draw(sp);
        window.display();
    }

    return 0;
}