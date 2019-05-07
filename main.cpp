// replace text grid with image grid
//

#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

using namespace sf;

int WW = 300;
int WH = 300;

const int xQuadrant = 3;
const int yQuadrant = 3;

const int boxLength = WW / xQuadrant;

bool player1go = true;
// X always go first! (i think)

//takes array?
void mouseClicked(int mouseX, int mouseY, Text *grid) {
    int gridX = (int) rint(mouseX / boxLength);
    int gridY = (int) rint(mouseY / boxLength);
    int quadrantIndex = (gridY) * xQuadrant + gridX;
    int drawX = gridX * boxLength;
    int drawY = gridY * boxLength;
    if (grid[quadrantIndex].getString() == " ") {
        if (player1go) {
            grid[quadrantIndex].setString("x");
        } else {
            grid[quadrantIndex].setString("0");
        }
        player1go = !player1go;
        grid[quadrantIndex].setPosition(drawX, drawY);
    }
    printf("drawX: %i drawY: %i", drawX, drawY);
    //printf("x: %i, y: %i, index: %i \n", gridX, gridY, quadrantIndex);
}

int main() {

    RenderWindow window(VideoMode(WW, WH), "tic-tac-toe");
    window.setFramerateLimit(144);

    Event event;
    Clock clock;

    RectangleShape *board [xQuadrant * yQuadrant];
    for (int i = 0; i < xQuadrant * yQuadrant; i++) {
        board[i] = new RectangleShape(Vector2f(boxLength, boxLength));
        board[i]->setSize(Vector2f(boxLength, boxLength));
        board[i]->setPosition((i % xQuadrant) * boxLength, ceil(i / xQuadrant) * boxLength);
        board[i]->setOutlineColor(Color::White);
        board[i]->setOutlineThickness(5);
        board[i]->setFillColor(Color::Black);
    }

    RenderTexture bgTexture;
    bgTexture.create(WW, WH);

    for (int i = 0; i < xQuadrant * yQuadrant; i++) {
        bgTexture.draw(*board[i]);
    }

    Sprite background(bgTexture.getTexture());

    Font fontastic;
    fontastic.loadFromFile("font.ttf");

    if (!fontastic.loadFromFile("font.ttf")) {
        printf("RIPX");
    }

    sf::Text boomshakalaka;
    boomshakalaka.setFont(fontastic);
    boomshakalaka.setCharacterSize(10);
    boomshakalaka.setStyle(sf::Text::Bold);
    boomshakalaka.setFillColor(sf::Color::White);
    boomshakalaka.setPosition(0,0);

    int xoSize = (int) WW / xQuadrant;

    Text grid[xQuadrant * yQuadrant];


    for (int i = 0; i < xQuadrant; i++) {
        for (int j = 0; j < yQuadrant; j++) {
            grid[i * j].setFont(fontastic);
            grid[i * j].setString(" ");
            grid[i * j].setCharacterSize(xoSize);
            grid[i * j].setStyle(sf::Text::Bold);
            grid[i * j].setFillColor(sf::Color::White);
            float length = grid[i * j].getLocalBounds().width;
            //grid[i * j].setPosition(i * boxLength, j * boxLength);
        }
    }

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
                     // int mouseX = (int) event.mouseMove.x;
                     // int mouseY = (int) event.mouseMove.y;
                     mouseClicked(event.mouseButton.x, event.mouseButton.y, grid);
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(boomshakalaka);
        for (int i = 0; i < xQuadrant * yQuadrant; i++) {
            window.draw(grid[i]);
        }
        window.display();
        fflush(stdout);
    }

    return 0;
}
