#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdio.h>

#define CANVAS_SIZE_MULTIPLIER 3
#define CANVAS_WIDTH 320
#define CANVAS_HEIGHT 240

static glm::vec2 up(0, 1);
static glm::vec2 down(0, -1);

uint32_t distanceTable[CANVAS_WIDTH][CANVAS_HEIGHT] = {0};
uint32_t angleTable[CANVAS_WIDTH][CANVAS_HEIGHT] = {0};
glm::vec2 screenCenter(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2);

float calculateClockwiseAngle(glm::vec2 v1, glm::vec2 v2)
{
    float clockwiseAngle = 0.0;

    auto dot = glm::dot(v1, v2);
    auto det = v1.x * v2.y - v1.y * v2.x;

    clockwiseAngle = atan2(det, dot);

    return clockwiseAngle;
}

void initTables(const sf::Image texture)
{
    auto textureSize = texture.getSize();
    for (int y = 0; y < CANVAS_HEIGHT; y++)
        for (int x = 0; x < CANVAS_WIDTH; x++)
        {
            glm::vec2 currentPoint((float)x, (float)y);
            distanceTable[x][y] = glm::distance(currentPoint, screenCenter);
            // angleTable[x][y] = calculateClockwiseAngle(currentPoint, screenCenter); // glm::angle(glm::normalize(currentPoint - screenCenter), up) * textureSize.y;
            if (x < (CANVAS_WIDTH / 2.0))
            {
                angleTable[x][y] = glm::angle(glm::normalize(currentPoint - screenCenter), down) * textureSize.y;
            }
            else
            {
                angleTable[x][y] = glm::angle(glm::normalize(currentPoint - screenCenter), up) * textureSize.y;
            }
        }
}

float distanceOffset = 0;
float angleOffset = 0;
float phase = 0;
float phaseDistance = 0;
void drawCircleTextured(sf::Image &image, const sf::Image texture, glm::vec2 center, float deltaTime)
{
    phase += 0.001;
    phaseDistance += 0.001;
    distanceOffset -= glm::sin(phaseDistance) * 100.f * deltaTime;
    angleOffset += glm::sin(phase) * 500.0 * deltaTime;
    auto textureSize = texture.getSize();

    for (int y = 0; y < CANVAS_HEIGHT; y++)
        for (int x = 0; x < CANVAS_WIDTH; x++)
        {
            auto distance = distanceTable[x][y] + distanceOffset;
            auto angle = angleTable[x][y] + angleOffset;
            sf::Color colorToInsert = texture.getPixel((uint32_t)distance % textureSize.x, (uint32_t)angle % textureSize.y);
            auto colorAttenuation = distanceTable[x][y] == 0 ? 1 : distanceTable[x][y];
            colorToInsert.r *= 255 - colorAttenuation;
            colorToInsert.g *= 255 - colorAttenuation;
            colorToInsert.b *= 255 - colorAttenuation;

            image.setPixel(x, y, colorToInsert);
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