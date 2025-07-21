//AUTOR: KAROLINA NAPIERACZ 20.07.2025
//eraser.cpp - obs³uga gumki do mazania
#include "eraser.h"

Eraser::Eraser() //konstruktor inicjuje rozmiar gumki i jej pozycjê
    : size(25.f, 25.f), position(0.f, 0.f)
{
}

sf::Vector2f Eraser::getSize() const { //zwraca rozmiar gumki
    return size;
}

void Eraser::setPosition(const sf::Vector2f& pos) { //ustawia now¹ pozycjê gumki 
    position = pos;
}

sf::FloatRect Eraser::getBounds() const { //zwraca prostok¹t opisuj¹cy obszar gumki (pozycja + rozmiar)
    return sf::FloatRect(position, size);
}

void eraseCircles(std::vector<sf::CircleShape>& circles, const Eraser& eraser) {
    sf::FloatRect eraserBounds = eraser.getBounds();

    for (int i = static_cast<int>(circles.size()) - 1; i >= 0; --i) { //iterujemy od koñca do pocz¹tku wektora z kó³kami
        if (circles[i].getGlobalBounds().intersects(eraserBounds)) {
            circles.erase(circles.begin() + i); //usuwamy kó³ko z wektora jeœli nachodzi na gumkê
        }
    }
}

void drawEraser(sf::RenderWindow& window, const Eraser& eraser) { //podgl¹d gumki

    //³adowanie czcionki
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        font.loadFromFile("OpenSans-VariableFont_wdth,wght.ttf");
        fontLoaded = true;
    }

    //tekst informuj¹cy o gumce
    sf::Text eraser_info;
    eraser_info.setString("Eraser\nMouse R");
    eraser_info.setPosition(380, 5);
    eraser_info.setFont(font);
    eraser_info.setCharacterSize(12);
    eraser_info.setFillColor(sf::Color(136, 144, 99));
    window.draw(eraser_info);

    //podgl¹d gumki
    sf::RectangleShape eraserPreview(eraser.getSize());
    eraserPreview.setFillColor(sf::Color::White);
    eraserPreview.setPosition(385, 40);
    window.draw(eraserPreview);
}


