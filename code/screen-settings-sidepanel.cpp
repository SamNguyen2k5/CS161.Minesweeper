#include "screen.hpp"
#include "context.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

ScreenSettingsSidePanel::ScreenSettingsSidePanel() {
    float y_half_line = context.WINDOW_SIZE.height / 2;

    text_times.setFont(context.FONT_TEXT);
    text_nrow.setFont(context.FONT_TEXT);
    text_ncol.setFont(context.FONT_TEXT);

    text_times.setFillColor(context.COLOUR_TEXT);
    text_nrow.setFillColor(context.COLOUR_TEXT);
    text_ncol.setFillColor(context.COLOUR_TEXT);

    sf::Vector2f box_pos((context.BOARD_MAXIMUM_WIDTH + context.WINDOW_SIZE.width) * .5f, context.WINDOW_SIZE.height * .66f);
    sf::Vector2f box_size(100, 36);
    box_pos -= box_size * .5f;

    btn_easy = sf::Button(
        "Easy",
        context.FONT_TEXT,
        sf::FloatRect(box_pos, box_size),
        context.GET_COLOUR_CELL(2),
        context.COLOUR_BOX_OPENED,
        context.COLOUR_BOX_HOVERED,
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_medium = sf::Button(
        "Medium",
        context.FONT_TEXT,
        sf::FloatRect(box_pos + sf::Vector2f(0, box_size.y + 5), box_size),
        context.GET_COLOUR_CELL(4),
        context.COLOUR_BOX_OPENED,
        context.COLOUR_BOX_HOVERED,
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_hard = sf::Button(
        "Hard",
        context.FONT_TEXT,
        sf::FloatRect(box_pos + sf::Vector2f(0, 2 * (box_size.y + 5)), box_size),
        context.GET_COLOUR_CELL(7),
        context.COLOUR_BOX_OPENED,
        context.COLOUR_BOX_HOVERED,
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_back = sf::Button(
        "Return",
        context.FONT_TEXT,
        sf::FloatRect(box_pos + sf::Vector2f(0, 3 * (box_size.y + 5)), box_size),
        sf::Color::White,
        sf::Color::Black,
        sf::Color(0xee, 0x00, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    sf::Vector2f edit_box_size(36, 36);
    sf::Vector2f edit_box_left_pos(
        (context.BOARD_MAXIMUM_WIDTH + box_pos.x) * .5f - edit_box_size.x * .5f,
        box_pos.y
    );
    sf::Vector2f edit_box_right_pos(
        (context.WINDOW_SIZE.width + box_pos.x) * .5f + edit_box_size.x * .5f,
        box_pos.y
    );

    btn_more_rows = sf::Button(
        "R+",
        context.FONT_TEXT,
        sf::FloatRect(edit_box_left_pos, edit_box_size),
        sf::Color::White,
        sf::Color::Black,
        sf::Color(0x00, 0xee, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_less_rows = sf::Button(
        "R-",
        context.FONT_TEXT,
        sf::FloatRect(edit_box_left_pos + sf::Vector2f(0, edit_box_size.y + 5), edit_box_size),
        sf::Color::White,
        sf::Color::Black,
        sf::Color(0xee, 0x00, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_more_cols = sf::Button(
        "C+",
        context.FONT_TEXT,
        sf::FloatRect(edit_box_right_pos, edit_box_size),
        sf::Color::White,
        sf::Color::Black,
        sf::Color(0x00, 0xee, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_less_cols = sf::Button(
        "C-",
        context.FONT_TEXT,
        sf::FloatRect(edit_box_right_pos + sf::Vector2f(0, edit_box_size.y + 5), edit_box_size),
        sf::Color::White,
        sf::Color::Black,
        sf::Color(0xee, 0x00, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_more_bombs = sf::Button(
        "B+",
        context.FONT_TEXT,
        sf::FloatRect(edit_box_left_pos + 2.0f * sf::Vector2f(0, edit_box_size.y + 5), edit_box_size),
        sf::Color::White,
        sf::Color(0x99, 0x00, 0x00),
        sf::Color(0xff, 0xff, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );

    btn_less_bombs = sf::Button(
        "B-",
        context.FONT_TEXT,
        sf::FloatRect(edit_box_right_pos + 2.0f * sf::Vector2f(0, edit_box_size.y + 5), edit_box_size),
        sf::Color::White,
        sf::Color(0x99, 0x00, 0x00),
        sf::Color(0xff, 0xff, 0x00, 0xaa),
        context.COLOUR_OUTLINE,
        context.BOARD_OUTLINE_THICKNESS
    );
}

void ScreenSettingsSidePanel::update_graphics() {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << context.BOARD_ROWS << ' '
       << std::setfill('0') << std::setw(2) << context.BOARD_COLUMNS;

    std::string nrow, ncol;
    ss >> nrow >> ncol;

    text_nrow.setString(nrow);
    text_ncol.setString(ncol);
    text_times.setString("x");

    text_nrow.setCharacterSize(context.TIMER_FONTSIZE);
    text_ncol.setCharacterSize(context.TIMER_FONTSIZE);
    text_times.setCharacterSize(context.TIMER_FONTSIZE / 2);

    text_times.setPosition(
        (context.BOARD_MAXIMUM_WIDTH + context.WINDOW_SIZE.width) * .5f,
        context.WINDOW_SIZE.height * .5f
    );
    text_nrow.setPosition(text_times.getPosition() + sf::Vector2f(text_nrow.getGlobalBounds().width, 0));
    text_ncol.setPosition(text_times.getPosition() - sf::Vector2f(text_ncol.getGlobalBounds().width, 0));

    text_nrow.setOrigin(
        text_nrow.getGlobalBounds().width  * .5f,
        text_nrow.getGlobalBounds().height * .6f
    );
    text_ncol.setOrigin(
        text_ncol.getGlobalBounds().width  * .5f,
        text_ncol.getGlobalBounds().height * .6f
    );
    text_times.setOrigin(
        text_times.getGlobalBounds().width  * .5f,
        text_times.getGlobalBounds().height * .6f
    );

    int text_width  = text_nrow.getGlobalBounds().width;
    int text_height = text_nrow.getGlobalBounds().height;
}

void ScreenSettingsSidePanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(text_nrow);
    target.draw(text_ncol);
    target.draw(text_times);

    target.draw(btn_easy);
    target.draw(btn_medium);
    target.draw(btn_hard);
    target.draw(btn_back);

    target.draw(btn_more_rows);
    target.draw(btn_less_rows);
    target.draw(btn_more_cols);
    target.draw(btn_less_cols);
    target.draw(btn_more_bombs);
    target.draw(btn_less_bombs);
}

void ScreenSettingsSidePanel::update_on_event(sf::Event event) {
    btn_easy.update_on_event(event);
    btn_medium.update_on_event(event);
    btn_hard.update_on_event(event);
    btn_back.update_on_event(event);

    btn_more_rows.update_on_event(event);
    btn_less_rows.update_on_event(event);
    btn_more_cols.update_on_event(event);
    btn_less_cols.update_on_event(event);
    btn_more_bombs.update_on_event(event);
    btn_less_bombs.update_on_event(event);
}

bool ScreenSettingsSidePanel::ask_is_easy_board_chosen() { return btn_easy.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_medium_board_chosen() { return btn_medium.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_hard_board_chosen() { return btn_hard.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_back() { return btn_back.ask_is_clicked(); }

bool ScreenSettingsSidePanel::ask_is_more_rows() { return btn_more_rows.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_less_rows() { return btn_less_rows.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_more_cols() { return btn_more_cols.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_less_cols() { return btn_less_cols.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_more_bombs() { return btn_more_bombs.ask_is_clicked(); }
bool ScreenSettingsSidePanel::ask_is_less_bombs() { return btn_less_bombs.ask_is_clicked(); }
