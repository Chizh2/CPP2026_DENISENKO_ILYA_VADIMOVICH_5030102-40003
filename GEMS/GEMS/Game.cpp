#include "Game.h"

Game::Game() : window(sf::VideoMode(640, 640), "GEMS") {
    window.setFramerateLimit(60);
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }
}

