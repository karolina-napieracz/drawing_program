//AUTOR: KAROLINA NAPIERACZ 20.07.2025
//main.cpp

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "pen.h" //pędzel
#include "toolbar.h" //toolbar
#include "eraser.h" //gumka do mazania

//stałe globalne
const int toolbarHeight = 80; //wysokosc toolbaru
const int margin = 10; //margines
bool save_drawing = false; //bool na zapisywanie rysunku
sf::RenderWindow window(sf::VideoMode(800, 600), "Paint++", sf::Style::Default);

bool canDrawAt(const sf::Vector2i& pos) { //obszar gdzie można rysować
    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    int left = 2 * margin;
    int top = toolbarHeight + 2 * margin;

    int width = windowWidth - left - 2 * margin;
    int height = windowHeight - top - 2 * margin;

    sf::IntRect drawingArea(left, top, width, height);
    return drawingArea.contains(pos);
}

int main() {
    std::vector<sf::CircleShape> circles; //wektor kółek, które rysujemy
    Pen pen;
    Eraser eraser;
    sf::Vector2i prevMousePos = sf::Mouse::getPosition(window); //poprzednia pozycja myszki (przed przebiegiem głównej pętli)

    //ładowanie instrukcji z pliku
    bool showInstructions = false;
    sf::Texture instructionTexture;
    instructionTexture.loadFromFile("instrukcja.png");

    //onsługa zapisu rysunku
    static int saveCounter = 1;//licznik zapisanych rysunkow (bedzie dodawany do nazw)
    static bool wasSPressed = false; //czy klawisz "S" był wciśnięty
    static bool wasMousePressed = false;

    while (window.isOpen()) { //główna pętla 

        sf::Event event;
        //obsługa zdarzeń
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) //zamknięcie okna kończy program
                window.close();

            if (event.type == sf::Event::Resized) { //okno zmienia rozmiar
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            pen.handleEvent(event);
        }

        window.clear(sf::Color::White);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window); //aktualna pozycja myszki 
        bool mouseClickedLeft = sf::Mouse::isButtonPressed(sf::Mouse::Left); //czy lewy przycisk myszy jest wcisnięty
        bool mouseClickedRight = sf::Mouse::isButtonPressed(sf::Mouse::Right); //czy prawy przycisk myszy jest wcisnięty
        eraser.setPosition(sf::Vector2f(mousePos) - eraser.getSize());

        drawToolbar(window, toolbarHeight, margin); //rysowanie toolbaru
        drawPalette(window, mousePos, mouseClickedLeft, pen); //rysowanie palety kolorów
        drawPreview(window, pen); //podgląd pędzla
        drawEraser(window, eraser); //gumka do mazania 

        //wyświtlanie instrukcji
        if (instruction_button_clicked(window, mousePos, mouseClickedLeft)) {
            showInstructions = !showInstructions;
        }

        //czyszczenie okna
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || clear_drawing_clicked(window, mousePos, mouseClickedLeft)) {
            circles.clear();
        }

        //rysowanie lewym przyciskiem myszy
        Drawing(mouseClickedLeft, mousePos, prevMousePos, pen, circles, canDrawAt);

        //wymazywanie kółek prawym przyciskiem myszy
        if (mouseClickedRight && canDrawAt(mousePos)) {
            eraseCircles(circles, eraser);
        }

        //rysowanie wszystkich kółek
        for (const auto& circle : circles)
            window.draw(circle);

        //pozycja, rozmiar i wyświetlanie instrukcji
        if (showInstructions) {
            sf::Sprite instructionSprite(instructionTexture);
            instructionSprite.setPosition(300, 100);
            instructionSprite.setScale(0.25f, 0.25f);
            window.draw(instructionSprite);
        }

        //zapisywanie rysunku (klawiszem S lub nacisnięciem przycisku Save)
        bool isSPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S); //czy klawisz "S" został wciśnięty
        bool saveClicked = save_drawing_clicked(window, mousePos, mouseClickedLeft); //czy przycisk save wciśnięty

        if ((isSPressed && !wasSPressed) || (saveClicked && !wasMousePressed)) {
            std::string filename = "drawing_" + std::to_string(saveCounter) + ".png"; //nazwa rysunku
            saveDrawing(circles, filename, window.getSize());
            saveCounter++; //zwiększamy licznik zapisów
        }

        //aktualizujemy stany klawisza i myszy, by wykrywać tylko nowe wciśnięcia
        wasSPressed = isSPressed;
        wasMousePressed = mouseClickedLeft;
        prevMousePos = mousePos; //aktualizowanie porpzedniej pozycji myszy

        window.display(); //wyświetlanie tego co zostało narysowane w tej pętli
    }

    return 0;
}
