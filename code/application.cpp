#include "application.hpp"
#include "screen.hpp"
#include <iostream>

Application::Application(int width, int height, const char* title):
    app(sf::VideoMode(width, height), title, sf::Style::Close)
{
    screen = static_cast<Screen*>(new ScreenHome);
}

int Application::run() {
    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                app.close();
                return 0;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F5) {
                    app.close();
                    return 1;
                }
            }

            screen->update_on_event(event);
        }

        app.clear();

        Screen* nxt_screen = screen->detect_change_screen();
        screen = nxt_screen;

        screen->update_graphics();
        app.draw(*screen);
        app.display();
    }
}
