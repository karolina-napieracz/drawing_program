//AUTOR: KAROLINA NAPIERACZ 20.07.2025
//toolbar.cpp - obs³uga paska narzêdzi
#include "toolbar.h"
#include <string>
#include <iostream>

//szablon funkcji do stylizowania czcionki
template<typename ColorType, typename SizeType>
void styleText(sf::Text& text, const std::string& fontPath, ColorType color, SizeType size) {
    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        if (!font.loadFromFile(fontPath)) { //obs³uga b³êdu ³adowania czcionki
            throw std::runtime_error("Nie mo¿na za³adowaæ czcionki: " + fontPath);
        }
        fontLoaded = true;
    }

    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(static_cast<unsigned int>(size));
}

void drawToolbar(sf::RenderWindow& window, int toolbarHeight, int margin) { //rysowanie paska narzêdzi (toolbaru) i ramki
    //rysowanie t³a toolbaru
    sf::Vector2u winSize = window.getSize();
    sf::RectangleShape toolbar_bcg(sf::Vector2f(winSize.x, toolbarHeight));
    toolbar_bcg.setFillColor(sf::Color(229, 215, 196));
    window.draw(toolbar_bcg);

    //ramka wokó³ obszaru rysowania
    sf::RectangleShape frame(sf::Vector2f(winSize.x - 2 * margin, winSize.y - toolbarHeight - 2 * margin));
    frame.setPosition(margin, toolbarHeight + margin);
    frame.setFillColor(sf::Color::Transparent); //prostok¹t, który ma pusty œrodek i obramowanie to ramka
    frame.setOutlineColor(sf::Color(229, 215, 196));
    frame.setOutlineThickness(margin); //outline tego prostok¹ta = margines
    window.draw(frame);
}

void drawPalette(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClicked, Pen& pen) { //paleta kolorów
    //rysowanie t³a palety kolorów
    sf::RectangleShape palette_bcg(sf::Vector2f(260, 40)); //rozmiar t³a
    palette_bcg.setFillColor(sf::Color(207, 187, 163));
    palette_bcg.setPosition(93, 30);
    window.draw(palette_bcg);

    sf::Color palette[] = { //kolory obecne w palecie, tablica kolorów
        sf::Color::Black, sf::Color::White,sf::Color(193,18,31),sf::Color(255,107,53), sf::Color(251,218,75), sf::Color(121,180,37),
        sf::Color(26,101,158), sf::Color(95,90,165),sf::Color(234,157,174),sf::Color(76, 61, 25)
    };

    const int boxSize = 20; //wielkoœci podgl¹dów kolorów w palecie
    const int spacing = 5; //odstêpy miêdzy kolorami
    const int startX = 100;
    const int startY = 40;

    for (int i = 0; i < sizeof(palette) / sizeof(palette[0]); ++i) //rysowanie podgl¹dów kolorów w palecie
    {
        sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
        box.setFillColor(palette[i]);
        box.setOutlineColor(sf::Color::Black);
        box.setPosition(startX + i * (boxSize + spacing), startY);
        window.draw(box);

        if (mouseClicked &&
            box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
        {
            pen.setColor(palette[i]);
        }
    }

    std::string colorName;
    const sf::Color color = pen.getColor(); //zale¿nie od tego jaki kolor ma pêdzel

    //jakie nazwy maj¹ wyœwietlaæ siê po wybraniu danego koloru
    if (color == sf::Color(193, 18, 31) || color == sf::Color::Red) colorName = "Czerwony"; //lub || w przypadku wybrania koloru z klawiatury
    else if (color == sf::Color(255, 107, 53))  colorName = "Pomaranczowy";
    else if (color == sf::Color(251, 218, 75) || color == sf::Color::Yellow)   colorName = "Zolty";
    else if (color == sf::Color(121, 180, 37) || color == sf::Color::Green) colorName = "Zielony";
    else if (color == sf::Color(26, 101, 158) || color == sf::Color::Blue)   colorName = "Niebieski";
    else if (color == sf::Color(95, 90, 165) || color == sf::Color::Magenta) colorName = "Fioletowy";
    else if (color == sf::Color(234, 157, 174)) colorName = "Rozowy";
    else if (color == sf::Color(76, 61, 25)) colorName = "Brazowy";
    else if (color == sf::Color::Black)  colorName = "Czarny";
    else if (color == sf::Color::White)  colorName = "Bialy";

    //tekst z nazw¹ koloru:
    sf::Text text_pen_color;
    text_pen_color.setString("Kolor: " + colorName);
    text_pen_color.setPosition(90, 5);
    styleText(text_pen_color, "OpenSans-VariableFont_wdth,wght.ttf", sf::Color(76, 61, 25), 16);


    window.draw(text_pen_color);
}

void drawPreview(sf::RenderWindow& window, const Pen& pen) { //podgl¹d pêdzla
    //podgl¹d ma taki sam rozmiar i kolor jak pêdzel, w lewym górnym rogu
    sf::CircleShape previewCircle(pen.getSize());
    previewCircle.setFillColor(pen.getColor());
    previewCircle.setPosition(20.f, 25.f);
    window.draw(previewCircle);

    //tekst informuj¹cy o rozmiarze pêdzla
    sf::Text text_pen_size;
    text_pen_size.setString("Size: " + std::to_string(static_cast<int>(pen.getSize())));
    text_pen_size.setPosition(15, 5);
    styleText(text_pen_size, "OpenSans-VariableFont_wdth,wght.ttf", sf::Color(76, 61, 25), 16);

    window.draw(text_pen_size);
}

void saveDrawing(const std::vector<sf::CircleShape>& circles, const std::string& filename, const sf::Vector2u& size) { //zapisywanie rysunku
    //próba utworzenia tekstury renderuj¹cej o podanym rozmiarze
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(size.x, size.y)) {
        std::cout << "Failed to create render texture!" << std::endl;
        return;
    }

    renderTexture.clear(sf::Color::White);

    //narysuj wszystkie kó³ka na renderTexture
    for (const auto& circle : circles) {
        renderTexture.draw(circle);
    }

    //wyœwietlenie zawartoœci na renderTexture
    renderTexture.display();

    //zapisanie rysunku
    sf::Image screenshot = renderTexture.getTexture().copyToImage();

    if (screenshot.saveToFile(filename)) {
        std::cout << "Zapisano jako " << filename << std::endl;
    }
    else {
        std::cout << "Nie uda³o siê zapisaæ." << std::endl;
    }
}

bool save_drawing_clicked(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClickedLeft) { //rysuje przycisk zapisywania i zwraca czy jest klikniêty

    //rysowanie przycisku save
    sf::RectangleShape save_button(sf::Vector2f(100, 35));
    save_button.setPosition(685, 35);
    save_button.setFillColor(sf::Color(53, 64, 36));
    window.draw(save_button);

    //tekst "save"
    sf::Text save_text;
    save_text.setString("Save");
    save_text.setPosition(715, 42);
    styleText(save_text, "OpenSans-VariableFont_wdth,wght.ttf", sf::Color(136, 144, 99), 16);

    window.draw(save_text);

    sf::Vector2f mousePosF(mousePos.x, mousePos.y);

    return mouseClickedLeft && save_button.getGlobalBounds().contains(mousePosF);
}

bool instruction_button_clicked(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClickedLeft) { //przycisk instrukcji i czy jest klikniety

    //rysowanie przycisku do instrukcji
    sf::RectangleShape instruction_button(sf::Vector2f(100, 35));
    instruction_button.setPosition(565, 35);
    instruction_button.setFillColor(sf::Color(136, 144, 99));

    //tekst "instruction"
    sf::Text buttonText;
    buttonText.setString("Instruction");
    buttonText.setPosition(575, 42);
    styleText(buttonText, "OpenSans-VariableFont_wdth,wght.ttf", sf::Color::Black, 16);

    window.draw(instruction_button);
    window.draw(buttonText);

    sf::Vector2f mousePosF(mousePos.x, mousePos.y);

    static bool wasPreviouslyPressed = false; //czy byl wczesniej klikniety
    bool clicked = mouseClickedLeft && !wasPreviouslyPressed && instruction_button.getGlobalBounds().contains(mousePosF); //czy jest przycisniety

    wasPreviouslyPressed = mouseClickedLeft;

    return clicked;
}


bool clear_drawing_clicked(sf::RenderWindow& window, const sf::Vector2i& mousePos, bool mouseClickedLeft) { //rysuje przycisk czyszczenia i zwraca czy jest klikniêty

    //rysowanie przycisku czyszczenia
    sf::RectangleShape clearButton(sf::Vector2f(100, 35));
    clearButton.setPosition(450, 35);
    clearButton.setFillColor(sf::Color(136, 144, 99));

    //tekst "clear"
    sf::Text clearText;
    clearText.setString("Clear");
    clearText.setPosition(480, 42);
    styleText(clearText, "OpenSans-VariableFont_wdth,wght.ttf", sf::Color::Black, 16);

    window.draw(clearButton);
    window.draw(clearText);
    sf::Vector2f mousePosF(mousePos.x, mousePos.y);

    return mouseClickedLeft && clearButton.getGlobalBounds().contains(mousePosF);
}
