#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

const int WW = 300;
const int WH = 300;

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
    fontastic.loadFromFile("KOMIKAP_.tff");

    if (!fontastic.loadFromFile("KOMIKAP_.tff")) { printf("RIPX"); }

    Text exampleText;
    exampleText.setFont(fontastic);
    exampleText.setString("abcdefghiklmnopqrstuvwxyz");
    exampleText.setFillColor(Color::Red);
    exampleText.setCharacterSize(32);
    exampleText.setPosition(150.0, 150.0);

    sf::Text atext;
    atext.setFont(fontastic);
    atext.setCharacterSize(20);
    atext.setStyle(sf::Text::Bold);
    atext.setFillColor(sf::Color::White);
    atext.setPosition(0,0);

    atext.setString("WOWOWOW");

    while (window.isOpen()) {
        float framerate = 1.0 / (clock.getElapsedTime().asSeconds());
        //boomshakalaka.setString(std::to_string(framerate));
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
        }
        window.clear();
        window.draw(background);
    //    window.draw(boomshakalaka);
        window.draw(atext);
        window.display();
        //printf("%f\n", framerate);
    }

    return 0;
}
