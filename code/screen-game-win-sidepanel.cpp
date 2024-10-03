#include "screen.hpp"
#include "context.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

ScreenGameWinSidePanel::ScreenGameWinSidePanel(Minefield* minefield):
    ScreenGameSidePanel(minefield)
{
    sf::Vector2f box_pos((context.BOARD_MAXIMUM_WIDTH + context.WINDOW_SIZE.width) * .5f, context.WINDOW_SIZE.height * .66f);
    sf::Vector2f box_size(100, 36);
    box_pos -= box_size * .5f;

    background_panel.setSize(sf::Vector2f(
        context.WINDOW_SIZE.width - context.BOARD_MAXIMUM_WIDTH,
        context.WINDOW_SIZE.height
    ));
    background_panel.setPosition(sf::Vector2f(
        context.BOARD_MAXIMUM_WIDTH,
        0
    ));
    background_panel.setFillColor(context.COLOUR_BACKGROUND_WIN);

    btn_back = sf::Button(
        "Return",
        context.FONT_TEXT,
        sf::FloatRect(box_pos + sf::Vector2f(0, 3 * (box_size.y + 5)), box_size),
        sf::Color::White,
        sf::Color::Black,
        sf::Color(0x00, 0xee, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    text_status.setString("YOU WIN!");
    text_status.setFont(context.FONT_TEXT);
    text_status.setCharacterSize(context.TIMER_FONTSIZE);
    text_status.setPosition(
        (context.BOARD_MAXIMUM_WIDTH + context.WINDOW_SIZE.width) * .5f,
        context.WINDOW_SIZE.height * .33f
    );
    text_status.setFillColor(context.COLOUR_TEXT);
    sf::setOriginCenter(text_status);
}

void ScreenGameWinSidePanel::update_graphics() {
    ScreenGameSidePanel::update_graphics();
}

void ScreenGameWinSidePanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background_panel);
    ScreenGameSidePanel::draw(target, states);
    target.draw(btn_back);

    // Blink
    if (int(context.global_clock.getElapsedTime().asMilliseconds()) % 300 < 150)
        target.draw(text_status);
}

void ScreenGameWinSidePanel::update_on_event(sf::Event event) {
    ScreenGameSidePanel::update_on_event(event);
    btn_back.update_on_event(event);
}

bool ScreenGameWinSidePanel::ask_is_back() { return btn_back.ask_is_clicked(); }
