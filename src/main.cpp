#include <SFML/Graphics.hpp>

#define CANVAS_SIZE_MULTIPLIER 3
#define CANVAS_WITH (320 * CANVAS_SIZE_MULTIPLIER)
#define CANVAS_HEIGHT (240 * CANVAS_SIZE_MULTIPLIER)
int main()
{
    sf::RenderWindow window(sf::VideoMode(CANVAS_WITH, CANVAS_HEIGHT), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}