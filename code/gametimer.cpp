#include "gametimer.hpp"
#include "context.hpp"
#include <algorithm>

GameTimer::GameTimer() {
    clock = sf::Clock();

    text.setFont(context.FONT_TIMER);
    text.setCharacterSize(context.TIMER_FONTSIZE);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(context.COLOUR_TIMER);
}

void GameTimer::update_graphics() {
    text.setString(get_seconds_elapsed());
    text.setPosition(
        context.WINDOW_SIZE.width - text.getGlobalBounds().width - context.TIMER_MARGIN,
        context.WINDOW_SIZE.height / 2.f
    );
}

void GameTimer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(text);
}

void GameTimer::update_on_event(sf::Event event) {
}

char* GameTimer::get_seconds_elapsed() {
    int time_sec = round(clock.getElapsedTime().asSeconds());
    time_sec = std::min(time_sec, 999);

    char* str = new char[3 + 1];
    for (int i = 2; i >= 0; i--, time_sec /= 10)
        str[i] = char(time_sec % 10 + '0');
    return str;
}
