#include <SFML/Graphics.hpp>

using namespace sf;

const int WW = 300;
const int WH = 300;

int main() {

    RenderWindow window(VideoMode(WW, WH), "tic-tac-toe");

    Event event;

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

    RenderTexture texture;
    texture.create(WW, WH);

    for (int x = 0; x < xQuadrant; x++) {
        for (int y = 0; y < yQuadrant; y++) {
            texture.draw(*board[x][y]);
        }
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }
        window.clear();
        Sprite sprite(texture.getTexture());
        window.draw(sprite);
        window.display();
    }

    return 0;
}
