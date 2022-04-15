#pragma once

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

void createChecker(sf::Image &image, int32_t checkerSize, sf::Color color1, sf::Color color2)
{
    auto size = image.getSize();
    for (int i = 0; i < size.x; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            auto color = (i * j + checkerSize) % 2 ? color1 : color2;
            image.setPixel(i, j, color);
        }
    }
}