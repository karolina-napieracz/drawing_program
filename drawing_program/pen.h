//pen.h
#ifndef PEN_H
#define PEN_H

#include <SFML/Graphics.hpp>
#include <vector>

class Pen {
public:
    Pen();

    void handleEvent(const sf::Event& event);

    void setColor(const sf::Color& newColor);

    float getSize() const;
    sf::Color getColor() const;

    void increaseSize();
    void decreaseSize();

private:
    float size;
    sf::Color color;
};

void Drawing(bool mouseClickedLeft, const sf::Vector2i& mousePos, const sf::Vector2i& prevMousePos, Pen& pen, std::vector<sf::CircleShape>& circles, bool (*canDrawAt)(const sf::Vector2i&));

#endif
