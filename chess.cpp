#include <SFML/Graphics.hpp>
#include <iostream>

const int SIZE = 80;
sf::Sprite pieces[32];

int boardLayout[8][8] = {
    -1, -2, -3, -4, -5, -3, -2, -1,
    -6, -6, -6, -6, -6, -6, -6, -6,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     6,  6,  6,  6,  6,  6,  6,  6,
     1,  2,  3,  4,  5,  3,  2,  1
};

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess Game");

    sf::Texture boardTexture, piecesTexture;
    if (!boardTexture.loadFromFile("C:/Users/User/source/repos/chess/chess/images") ||
        !piecesTexture.loadFromFile("C:/Users/User/source/repos/chess/chess/images/pieces.png")) {
        std::cout << "Failed to load textures!" << std::endl;
        return -1;
    }

    sf::Sprite boardSprite(boardTexture);

    int index = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int piece = boardLayout[i][j];
            if (piece == 0) continue;

            int type = abs(piece) - 1;
            int color = (piece > 0) ? 1 : 0;

            if (index >= 32) continue;  // prevent array overflow
            pieces[index].setTexture(piecesTexture);
            pieces[index].setTextureRect(sf::IntRect(type * SIZE, color * SIZE, SIZE, SIZE));
            pieces[index].setPosition(j * SIZE, i * SIZE);
            index++;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(boardSprite);
        for (int i = 0; i < index; ++i)
            window.draw(pieces[i]);
        window.display();
    }

    return 0;
}
