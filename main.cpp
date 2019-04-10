#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

using namespace sf;

const int WW = 300;
const int WH = 300;

//takes array?
void mouseClicked(int mouseX, int mouseY, Text grid) {
    int gridX = (int) (WW / mouseX);
    int gridY = (int) (WH / mouseY);
}

int main() {

    RenderWindow window(VideoMode(WW, WH), "tic-tac-toe");
    window.setFramerateLimit(144);

    Event event;
    Clock clock;

    const int xQuadrant = 3;
    const int yQuadrant = 3;

    RectangleShape *board [xQuadrant][yQuadrant];
    const int boxLength = WW / xQuadrant;
    for (int x = 0; x < xQuadrant; x++) {
        for (int y = 0; y < yQuadrant; y++) {
            board[x][y] = new RectangleShape(Vector2f(boxLength, boxLength));
            board[x][y]->setSize(Vector2f(boxLength, boxLength));
            board[x][y]->setPosition(x * boxLength, y * boxLength);
            board[x][y]->setOutlineColor(Color::White);
            board[x][y]->setOutlineThickness(5);
            board[x][y]->setFillColor(Color::Black);
        }
    }

    RenderTexture bgTexture;
    bgTexture.create(WW, WH);

    for (int x = 0; x < xQuadrant; x++) {
        for (int y = 0; y < yQuadrant; y++) {
            bgTexture.draw(*board[x][y]);
        }
    }

    Sprite background(bgTexture.getTexture());

    Font fontastic;
    fontastic.loadFromFile("font.ttf");

    if (!fontastic.loadFromFile("font.ttf")) { printf("RIPX"); }

    sf::Text boomshakalaka;
    boomshakalaka.setFont(fontastic);
    boomshakalaka.setCharacterSize(10);
    boomshakalaka.setStyle(sf::Text::Bold);
    boomshakalaka.setFillColor(sf::Color::White);
    boomshakalaka.setPosition(0,0);

    bool player1go = true;
    int xoSize = (int) WW / xQuadrant;

    while (window.isOpen()) {
        float framerate = 1.0 / (clock.getElapsedTime().asSeconds());
        boomshakalaka.setString(std::to_string((int)framerate));
        clock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Key::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    void mouseClicked((int) event.mouseMove.x, (int) event.mouseMove.y);
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(boomshakalaka);
        window.display();
    }

    return 0;
}
