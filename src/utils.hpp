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
    auto textureSize = texture.getSize();
    glm::vec2 screenCenter(CANVAS_WITH / 2, CANVAS_HEIGHT / 2);

    for (int i = 0; i < CANVAS_WITH; i++)
        for (int j = 0; j < CANVAS_HEIGHT; j++)
        {
            glm::vec2 currentPoint((float)i, (float)j);
            auto distance = glm::distance(currentPoint, screenCenter);

            sf::Color colorToInsert = texture.getPixel((unsigned int)distance % textureSize.x, j % textureSize.y);
            image.setPixel(i, j, colorToInsert);
        }
}

void drawCircleTexturedOld(sf::Image &image, const sf::Image texture, glm::vec2 center, int32_t radius)
{
    int32_t diameter = radius * 2;
    int32_t startX = center.x - radius - 1;
    int32_t startY = center.y - radius - 1;
    int32_t endX = startX + diameter + 1;
    int32_t endY = startY + diameter + 1;

    int32_t y = radius % texture.getSize().y;

    static int pixelCount = 0;

    for (int i = startX; i < endX; i++)
        for (int j = startY; j < endY; j++)
        {
            glm::vec2 currentPoint((float)i + 1, (float)j + 1);

            auto l = glm::floor(glm::distance(currentPoint, center));

            if (l == radius)
            {
                auto color = texture.getPixel(pixelCount, y);
                image.setPixel(i, j, color);
                pixelCount++;
                pixelCount %= texture.getSize().x;
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
    for (uint32_t i = 0; i < size.x; i++)
    {
        for (uint32_t j = 0; j < size.y; j++)
        {
            auto color = (i / checkerSize + j / checkerSize) % 2 ? color1 : color2;
            image.setPixel(i, j, color);
        }
    }
}

void createXorTexture(sf::Image &image, int32_t checkerSize, sf::Color color1, sf::Color color2)
{
    auto size = image.getSize();
    for (uint32_t i = 0; i < size.x; i++)
        for (uint32_t j = 0; j < size.y; j++)
        {
            unsigned char color = (i * 256 / size.x) ^ (j * 256 / size.y);
            image.setPixel(i, j, {color, color, color});
        }
}