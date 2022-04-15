#include <SFML/Graphics.hpp>
#include <random>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <stdio.h>
#include "utils.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(CANVAS_WITH * CANVAS_SIZE_MULTIPLIER, CANVAS_HEIGHT * CANVAS_SIZE_MULTIPLIER), "Drawing Pixels!!");
    sf::RenderTexture renderTexture;

    renderTexture.create(320, 240);
    renderTexture.clear({255, 0, 0});

    sf::CircleShape circle(30, 30);

    circle.setPosition(160, 120);

    renderTexture.draw(circle);

    sf::Vertex triangle[] = {
        sf::Vertex(sf::Vector2f(160, 0), sf::Color::Red),
        sf::Vertex(sf::Vector2f(320, 240), sf::Color::Green),
        sf::Vertex(sf::Vector2f(0, 240), sf::Color::Blue),
    };

    sf::Sprite sprite(renderTexture.getTexture());

    renderTexture.draw(triangle, 3, sf::Triangles);

    sprite.scale(3, 3);

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

        window.draw(sprite);

        window.display();
    }

    return 0;
}