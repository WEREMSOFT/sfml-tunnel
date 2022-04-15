#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <stdio.h>

#define CANVAS_SIZE_MULTIPLIER 3
#define CANVAS_WITH 320
#define CANVAS_HEIGHT 240

void drawCircleTextured(sf::Image &image, const sf::Image texture, glm::vec2 center, int32_t radius)
{
    int32_t diameter = radius * 2;
    int32_t startX = center.x - radius - 1;
    int32_t startY = center.y - radius - 1;
    int32_t endX = startX + diameter + 1;
    int32_t endY = startY + diameter + 1;

    float perimeter = 2 * glm::pi<float>() * radius;

    int32_t y = radius % texture.getSize().y;
    float xRatio = (float)texture.getSize().x / perimeter;
    int32_t x = 0;
    float phase = 0;

    for (int i = startX; i < endX; i++)
    {
        for (int j = startY; j < endY; j++)
        {
            glm::vec2 currentPoint((float)i + 1, (float)j + 1);

            auto l = glm::floor(glm::distance(currentPoint, center));

            if (l == radius)
            {
                x = glm::floor(phase * xRatio);
                auto color = texture.getPixel(x, y);
                image.setPixel(i, j, color);
                phase++;
            }
        }
    }
}

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
            auto color = (i / checkerSize + j / checkerSize) % 2 ? color1 : color2;
            image.setPixel(i, j, color);
        }
    }
}