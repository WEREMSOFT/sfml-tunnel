#include <SFML/Graphics.hpp>
#include <random>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <stdio.h>

#define CANVAS_SIZE_MULTIPLIER 3
#define CANVAS_WITH 320
#define CANVAS_HEIGHT 240

void drawCircle(sf::Image &image, glm::vec2 center, int32_t radius, sf::Color color)
{
    int32_t diameter = radius * 2;
    int32_t startX = center.x - radius - 1;
    int32_t startY = center.y - radius - 1;
    int32_t endX = startX + diameter + 1;
    int32_t endY = startY + diameter + 1;

    for (int i = startX; i < endX; i++)
    {
        for (int j = startY; j < endY; j++)
        {
            glm::vec2 currentPoint((float)i + 1, (float)j + 1);

            auto l = glm::floor(glm::distance(currentPoint, center));

            if (l == radius)
                image.setPixel(i, j, color);
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(CANVAS_WITH * CANVAS_SIZE_MULTIPLIER, CANVAS_HEIGHT * CANVAS_SIZE_MULTIPLIER), "Drawing Pixels!!");

    sf::Image img;

    img.create(320, 240, {255, 0, 0});

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
        x = rand() % CANVAS_WITH;
        y = rand() % CANVAS_HEIGHT;

        img.setPixel(x, y, {0xFF, 0xFF, 0xFF});

        drawCircle(img, {100, 100}, 30, {0, 0, 0});

        tx.loadFromImage(img);

        window.draw(sp);
        window.display();
    }

    return 0;
}