#include "screen.hpp"
#include "context.hpp"
#include <iostream>
#include <sstream>

ScreenGameSidePanel::ScreenGameSidePanel(Minefield* minefield):
    minefield(minefield)
{
    float y_half_line = context.WINDOW_SIZE.height / 2;
    clock = sf::Clock();

    text_clock.setFont(context.FONT_TIMER);
    text_clock.setCharacterSize(context.TIMER_FONTSIZE);
    text_clock.setStyle(sf::Text::Bold);
    text_clock.setFillColor(context.COLOUR_TIMER);

    cursor_box.setTexture(context.TEXTURE_CURSOR_BOX);
    cursor_box.setScale(sf::Vector2f(1.f, 1.f) * float(context.TIMER_FONTSIZE) / cursor_box.getGlobalBounds().height / 1.5f);

    tick_box.setTexture(context.TEXTURE_TICK_BOX);
    tick_box.setScale(sf::Vector2f(1.f, 1.f) * float(context.TIMER_FONTSIZE) / tick_box.getGlobalBounds().height / 1.5f);

    flag_box.setTexture(context.TEXTURE_FLAG_BOX);
    flag_box.setScale(sf::Vector2f(1.f, 1.f) * float(context.TIMER_FONTSIZE) / flag_box.getGlobalBounds().height / 1.5f);

    bomb_box.setTexture(context.TEXTURE_BOMB_BOX);
    bomb_box.setScale(sf::Vector2f(1.f, 1.f) * float(context.TIMER_FONTSIZE) / bomb_box.getGlobalBounds().height / 1.5f);

    text_cnt_reveals.setFont(context.FONT_TIMER);
    text_cnt_reveals.setCharacterSize(context.TIMER_FONTSIZE * .7f);
    text_cnt_reveals.setStyle(sf::Text::Bold);
    text_cnt_reveals.setFillColor(context.COLOUR_TIMER);

    text_cnt_open.setFont(context.FONT_TIMER);
    text_cnt_open.setCharacterSize(context.TIMER_FONTSIZE * .7f);
    text_cnt_open.setStyle(sf::Text::Bold);
    text_cnt_open.setFillColor(context.COLOUR_TIMER);

    text_cnt_flags.setFont(context.FONT_TIMER);
    text_cnt_flags.setCharacterSize(context.TIMER_FONTSIZE * .7f);
    text_cnt_flags.setStyle(sf::Text::Bold);
    text_cnt_flags.setFillColor(context.COLOUR_TIMER);

    text_cnt_bombs.setFont(context.FONT_TIMER);
    text_cnt_bombs.setCharacterSize(context.TIMER_FONTSIZE * .7f);
    text_cnt_bombs.setStyle(sf::Text::Bold);
    text_cnt_bombs.setFillColor(context.COLOUR_TIMER);
}

void ScreenGameSidePanel::update_graphics() {
    std::stringstream ss;
    ss << minefield->ask_count_reveals()        << ' '
       << minefield->ask_count_opened_cells()   << ' '
       << minefield->ask_count_flagged_cells()  << ' '
       << minefield->ask_count_bombs();

    std::string cnt_reveals, cnt_open, cnt_flags, cnt_bombs;
    ss >> cnt_reveals >> cnt_open >> cnt_flags >> cnt_bombs;

    text_clock.setString(get_seconds_elapsed());
    text_cnt_reveals.setString(cnt_reveals);
    text_cnt_open.setString(cnt_open);
    text_cnt_flags.setString(cnt_flags);
    text_cnt_bombs.setString(cnt_bombs);

    sf::Vector2f text_pos(
        (context.WINDOW_SIZE.width + context.BOARD_MAXIMUM_WIDTH) / 2.f,
        context.WINDOW_SIZE.height * .33f
    );

    text_clock.setPosition(text_pos);

    cursor_box.setPosition(text_pos + sf::Vector2f(-50, 2.f * context.TIMER_FONTSIZE - 5));
    tick_box.setPosition(text_pos + sf::Vector2f(-50, 3.f * context.TIMER_FONTSIZE - 5));
    flag_box.setPosition(text_pos + sf::Vector2f(-50, 4.f * context.TIMER_FONTSIZE - 5));
    bomb_box.setPosition(text_pos + sf::Vector2f(-50, 5.f * context.TIMER_FONTSIZE - 5));

    text_cnt_reveals.setPosition(text_pos + sf::Vector2f(30, context.TIMER_FONTSIZE * 2.f));
    text_cnt_open.setPosition(text_pos + sf::Vector2f(30, context.TIMER_FONTSIZE * 3.f));
    text_cnt_flags.setPosition(text_pos + sf::Vector2f(30, context.TIMER_FONTSIZE * 4.f));
    text_cnt_bombs.setPosition(text_pos + sf::Vector2f(30, context.TIMER_FONTSIZE * 5.f));

    sf::setOriginCenter(text_clock);

    sf::setOriginCenterBox(cursor_box);
    sf::setOriginCenterBox(tick_box);
    sf::setOriginCenterBox(flag_box);
    sf::setOriginCenterBox(bomb_box);

    sf::setOriginCenter(text_cnt_reveals);
    sf::setOriginCenter(text_cnt_open);
    sf::setOriginCenter(text_cnt_flags);
    sf::setOriginCenter(text_cnt_bombs);

//    minefield_score = MinefieldScore(minefield);
}

void ScreenGameSidePanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (not minefield->ask_has_won() and not minefield->ask_has_lost())
        target.draw(text_clock);

    target.draw(cursor_box);
    target.draw(tick_box);
    target.draw(flag_box);
    target.draw(bomb_box);

    target.draw(text_cnt_reveals);
    target.draw(text_cnt_open);
    target.draw(text_cnt_flags);
    target.draw(text_cnt_bombs);
}

void ScreenGameSidePanel::update_on_event(sf::Event event) {

}

char* ScreenGameSidePanel::get_seconds_elapsed() {
    int time_sec = round(clock.getElapsedTime().asSeconds());
    time_sec = std::min(time_sec, 999);

    char* str = new char[3 + 1];
    str[3] = '\0';
    for (int i = 2; i >= 0; i--, time_sec /= 10)
        str[i] = char(time_sec % 10 + '0');

    return str;
}

void ScreenGameSidePanel::restart_clock() {
    clock = sf::Clock();
}
