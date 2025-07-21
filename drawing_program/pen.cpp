//AUTOR: KAROLINA NAPIERACZ 20.07.2025
//pen.cpp - obs�uga p�dzla
#include "pen.h"

//konstruktor klasy Pen - ustawienie domy�lnego rozmiaru i koloru p�dzla
Pen::Pen()
    : size(10.f), color(sf::Color::Black)
{
}

void Pen::setColor(const sf::Color& newColor) { //ustawia nowy kolor p�dzla
    color = newColor;
}

float Pen::getSize() const { //zwraca aktualny rozmiar p�dzla
    return size;
}

sf::Color Pen::getColor() const { //zwraca aktualny kolor p�dzla
    return color;
}

void Pen::increaseSize() { //zwi�ksza rozmiar p�dzla (maksymalny rozmiar to 25.f)
    if (size < 25.f)
        size += 1.f;
}

void Pen::decreaseSize() { //zmniejsza rozmiar (minimalny to 1.f)
    if (size > 1.f)
        size -= 1.f;
}

void Pen::handleEvent(const sf::Event& event) { //obs�uga zdarze�

    if (event.type == sf::Event::MouseWheelScrolled) { //zwi�kszanie/zmniejszanie rozmairu p�dzla przy u�yciu scrolla myszki
        if (event.mouseWheelScroll.delta > 0) //scroll do przodu (zwi�ksza p�dzel)
            increaseSize();
        else if (event.mouseWheelScroll.delta < 0) //scroll do siebie (zmniejsza p�dzel)
            decreaseSize();
    }
    else if (event.type == sf::Event::KeyPressed) { //standardowe kolory wybierane przez klawisze
        //kt�rym klawiszom odpowiadaj� jakie kolory
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

    if (mouseClickedLeft && canDrawAt(mousePos)) { //je�li lewy przycisk myszy jest wci�ni�ty i mo�na rysowa� na tym obszarze
        sf::Vector2f current(mousePos.x, mousePos.y); //aktualna pozycja myszy (wektor z float)
        sf::Vector2f previous(prevMousePos.x, prevMousePos.y); //poprzednia pozycja myszy
        sf::Vector2f delta = current - previous; //by rysowac k�ka mi�dzy tymi dwoma pozycjamy (�eby nie by�o przerw)

        float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y); //d�ugo�� wektora (pierwiastek z sumy kwadrat�w jego wsp�rz�dnych), jak daleko przemie�ci�a si� mysz
        const float step = pen.getSize() * 0.5f; //odst�p mi�dzy punktami rysowanymi mi�dzy poprzedni� a aktualn� pozycj� myszy (po�owa rozmiaru p�dzla)

        if (distance > 0.f) {
            for (float i = 0; i < distance; i += step) { //rysowanie od poprzedniej pozycji myszy do aktualnej, co po�ow� d�ugo�ci p�dzla
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


