#include "screen.hpp"
#include "context.hpp"
#include <iostream>

ScreenHomeSidePanel::ScreenHomeSidePanel() {
    sf::Vector2f btn_pos(
        (context.WINDOW_SIZE.width + context.BOARD_MAXIMUM_WIDTH) * .5f,
        context.WINDOW_SIZE.height / 2
    );
    sf::Vector2f btn_size(120, 40);

    btn_new_game = sf::Button(
        "New game",
        context.FONT_TEXT,
        sf::FloatRect(
            btn_pos - btn_size * .5f,
            btn_size
        ),
        context.COLOUR_TEXT,
        sf::Color::Black,
        context.COLOUR_BOX_HOVERED,
        context.COLOUR_OUTLINE,
        3
    );

    btn_settings = sf::Button(
        "Settings",
        context.FONT_TEXT,
        sf::FloatRect(
            btn_pos + sf::Vector2f(0, 50) - btn_size * .5f,
            btn_size
        ),
        context.COLOUR_TEXT,
        sf::Color::Black,
        context.COLOUR_BOX_HOVERED,
        context.COLOUR_OUTLINE,
        3
    );
}

void ScreenHomeSidePanel::update_graphics() {
    btn_new_game.update_graphics();
    btn_settings.update_graphics();
}

void ScreenHomeSidePanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(btn_new_game);
    target.draw(btn_settings);
}

void ScreenHomeSidePanel::update_on_event(sf::Event event) {
    btn_new_game.update_on_event(event);
    btn_settings.update_on_event(event);
}

bool ScreenHomeSidePanel::ask_for_new_game() { return btn_new_game.ask_is_clicked(); }
bool ScreenHomeSidePanel::ask_for_settings() { return btn_settings.ask_is_clicked(); }
