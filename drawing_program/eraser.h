//eraser.h
#ifndef ERASER_H
#define ERASER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Eraser {
private:
    sf::Vector2f size;
    sf::Vector2f position;

public:
    Eraser();

    sf::Vector2f getSize() const;
    void setPosition(const sf::Vector2f& pos);
    sf::FloatRect getBounds() const;

};

void eraseCircles(std::vector<sf::CircleShape>& circles, const Eraser& eraser);
void drawEraser(sf::RenderWindow& window, const Eraser& eraser);

#endif
