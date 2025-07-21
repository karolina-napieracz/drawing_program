// toolbar.h
#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <SFML/Graphics.hpp>
#include "pen.h"
#include "eraser.h"

template<typename ColorType, typename SizeType>
void styleText(sf::Text& text, const std::string& fontPath, ColorType color, SizeType size); //szablon funkcji do stylizowania czcionki

void drawToolbar(sf::RenderWindow& window, int toolbarHeight, int margin); //rysowanie paska narzêdzi (toolbaru) i ramki
void drawPalette(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClicked, Pen& pen); //paleta kolorów
void drawPreview(sf::RenderWindow& window, const Pen& pen); //podgl¹d pêdzla
void saveDrawing(const std::vector<sf::CircleShape>& circles, const std::string& filename, const sf::Vector2u& size); //zapisywanie rysunku
bool save_drawing_clicked(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClickedLeft); //rysuje przycisk zapisywania i zwraca czy jest klikniêty
bool instruction_button_clicked(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClickedLeft);  //przycisk instrukcji i czy jest klikniety
bool clear_drawing_clicked(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClickedLeft);  //rysuje przycisk czyszczenia i zwraca czy jest klikniêty

#endif