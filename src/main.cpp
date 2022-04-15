#include <SFML/Graphics.hpp>
#include <random>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <stdio.h>
#include "utils.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(CANVAS_WITH * CANVAS_SIZE_MULTIPLIER, CANVAS_HEIGHT * CANVAS_SIZE_MULTIPLIER), "Drawing Pixels!!");

    sf::Image img, checkerI;
    sf::Texture tx, checkerT;
    sf::Sprite sp, checkerS;

    img.create(320, 240, {0, 0, 0});

    checkerI.create(100, 100, {0, 0, 0});

    createChecker(checkerI, 30, {0xFF, 0, 0}, {0, 0, 0xFF});
    checkerT.loadFromImage(checkerI);
    tx.loadFromImage(img);

    sp.setTexture(tx);
    checkerS.setTexture(checkerT);

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
        for (int i = 1; i < 100; i++)
        {
            drawCircleTextured(img, checkerI, {100, 100}, i);
        }

        tx.loadFromImage(img);

        window.draw(sp);
        window.draw(checkerS);
        window.display();
    }

    return 0;
}