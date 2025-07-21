//AUTOR: KAROLINA NAPIERACZ 20.07.2025
//pen.cpp - obs³uga pêdzla
#include "pen.h"

//konstruktor klasy Pen - ustawienie domyœlnego rozmiaru i koloru pêdzla
Pen::Pen()
    : size(10.f), color(sf::Color::Black)
{
}

void Pen::setColor(const sf::Color& newColor) { //ustawia nowy kolor pêdzla
    color = newColor;
}

float Pen::getSize() const { //zwraca aktualny rozmiar pêdzla
    return size;
}

sf::Color Pen::getColor() const { //zwraca aktualny kolor pêdzla
    return color;
}

void Pen::increaseSize() { //zwiêksza rozmiar pêdzla (maksymalny rozmiar to 25.f)
    if (size < 25.f)
        size += 1.f;
}

void Pen::decreaseSize() { //zmniejsza rozmiar (minimalny to 1.f)
    if (size > 1.f)
        size -= 1.f;
}

void Pen::handleEvent(const sf::Event& event) { //obs³uga zdarzeñ

    if (event.type == sf::Event::MouseWheelScrolled) { //zwiêkszanie/zmniejszanie rozmairu pêdzla przy u¿yciu scrolla myszki
        if (event.mouseWheelScroll.delta > 0) //scroll do przodu (zwiêksza pêdzel)
            increaseSize();
        else if (event.mouseWheelScroll.delta < 0) //scroll do siebie (zmniejsza pêdzel)
            decreaseSize();
    }
    else if (event.type == sf::Event::KeyPressed) { //standardowe kolory wybierane przez klawisze
        //którym klawiszom odpowiadaj¹ jakie kolory
        switch (event.key.code) {
        case sf::Keyboard::R: color = sf::Color::Red; break;
        case sf::Keyboard::G: color = sf::Color::Green; break;
        case sf::Keyboard::B: color = sf::Color::Blue; break;
        case sf::Keyboard::Y: color = sf::Color::Yellow; break;
        case sf::Keyboard::C: color = sf::Color::Cyan; break;
        case sf::Keyboard::M: color = sf::Color::Magenta; break;
        default: break;
        }
    }
}

//funkcja rysowania
void Drawing(bool mouseClickedLeft, const sf::Vector2i& mousePos, const sf::Vector2i& prevMousePos, Pen& pen, std::vector<sf::CircleShape>& circles, bool (*canDrawAt)(const sf::Vector2i&)) {

    if (mouseClickedLeft && canDrawAt(mousePos)) { //jeœli lewy przycisk myszy jest wciœniêty i mo¿na rysowaæ na tym obszarze
        sf::Vector2f current(mousePos.x, mousePos.y); //aktualna pozycja myszy (wektor z float)
        sf::Vector2f previous(prevMousePos.x, prevMousePos.y); //poprzednia pozycja myszy
        sf::Vector2f delta = current - previous; //by rysowac kó³ka miêdzy tymi dwoma pozycjamy (¿eby nie by³o przerw)

        float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y); //d³ugoœæ wektora (pierwiastek z sumy kwadratów jego wspó³rzêdnych), jak daleko przemieœci³a siê mysz
        const float step = pen.getSize() * 0.5f; //odstêp miêdzy punktami rysowanymi miêdzy poprzedni¹ a aktualn¹ pozycj¹ myszy (po³owa rozmiaru pêdzla)

        if (distance > 0.f) {
            for (float i = 0; i < distance; i += step) { //rysowanie od poprzedniej pozycji myszy do aktualnej, co po³owê d³ugoœci pêdzla
                sf::Vector2f point = previous + (delta / distance) * i;

                if (canDrawAt(sf::Vector2i(point))) {
                    sf::CircleShape circle(pen.getSize());
                    circle.setFillColor(pen.getColor());
                    circle.setPosition(point - sf::Vector2f(pen.getSize(), pen.getSize()));
                    circles.push_back(circle);
                }
            }
        }
        else {
            if (canDrawAt(mousePos)) {
                sf::CircleShape circle(pen.getSize());
                circle.setFillColor(pen.getColor());
                circle.setPosition(current - sf::Vector2f(pen.getSize(), pen.getSize()));
                circles.push_back(circle);
            }
        }
    }
}


