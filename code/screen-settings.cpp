#include "screen.hpp"
#include "context.hpp"
#include <iostream>

ScreenSettings::ScreenSettings() {
    minefield = static_cast<Minefield*>(
        new MinefieldRandom(
            context.BOARD_ROWS,
            context.BOARD_COLUMNS,
            context.BOARD_BOMBS
        )
    );
    minefield->set_end_game_lost();

    sidepanel = new ScreenSettingsSidePanel;

    board_occupation.setPosition(sf::Vector2f(0, 0));
    board_occupation.setFillColor(context.COLOUR_BOX_HOVERED);
}

void ScreenSettings::update_graphics() {
    minefield->update_graphics();
    sidepanel->update_graphics();

    board_occupation.setSize(sf::Vector2f(minefield->get_board_horizontal_occupation(), context.WINDOW_SIZE.height));
}

void ScreenSettings::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(context.window_divider);
    target.draw(board_occupation);

    target.draw(*minefield);
    target.draw(*sidepanel);
}

void ScreenSettings::update_on_event(sf::Event event) {
    minefield->update_on_event(event);
    sidepanel->update_on_event(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
            resize_board_more_columns();
            return;
        }
        if (event.key.code == sf::Keyboard::Left) {
            resize_board_less_columns();
            return;
        }
        if (event.key.code == sf::Keyboard::Up) {
            resize_board_more_rows();
            return;
        }
        if (event.key.code == sf::Keyboard::Down) {
            resize_board_less_rows();
            return;
        }
    }

    if (sidepanel->ask_is_easy_board_chosen()) {
        resize_board(context.DEFAULT_SIZE_ROWS_EASY, context.DEFAULT_SIZE_COLUMNS_EASY, context.DEFAULT_SIZE_BOMBS_EASY);
        return;
    }

    if (sidepanel->ask_is_medium_board_chosen()) {
        resize_board(context.DEFAULT_SIZE_ROWS_MEDIUM, context.DEFAULT_SIZE_COLUMNS_MEDIUM, context.DEFAULT_SIZE_BOMBS_MEDIUM);
        return;
    }

    if (sidepanel->ask_is_hard_board_chosen()) {
        resize_board(context.DEFAULT_SIZE_ROWS_HARD, context.DEFAULT_SIZE_COLUMNS_HARD, context.DEFAULT_SIZE_BOMBS_HARD);
        return;
    }

    if (sidepanel->ask_is_more_rows()) {
        resize_board_more_rows();
        return;
    }

    if (sidepanel->ask_is_less_rows()) {
        resize_board_less_rows();
        return;
    }

    if (sidepanel->ask_is_more_cols()) {
        resize_board_more_columns();
        return;
    }

    if (sidepanel->ask_is_less_cols()) {
        resize_board_less_columns();
        return;
    }

    if (sidepanel->ask_is_more_bombs()) {
        resize_board_more_bombs();
        return;
    }

    if (sidepanel->ask_is_less_bombs()) {
        resize_board_less_bombs();
        return;
    }

    if (sidepanel->ask_is_back()) {
        set_pending_screen(
            static_cast<Screen*>(new ScreenHome)
        );
        return;
    }
}

Screen* ScreenSettings::detect_change_screen() {
    Screen* pending_screen = get_pending_screen();
    if (pending_screen != nullptr) {
        clear_pending_screen();
        return pending_screen;
    }

    return static_cast<Screen*>(this);
}

void ScreenSettings::reload_minefield() {
    delete minefield;
    minefield = static_cast<Minefield*>(
        new MinefieldRandom(
            context.BOARD_ROWS,
            context.BOARD_COLUMNS,
            context.BOARD_BOMBS
        )
    );
    minefield->set_end_game_lost();
}

bool ScreenSettings::resize_board(int new_nrow, int new_ncol, int new_nbombs) {
    if (new_nrow <= 0 or new_ncol <= 0)
        return false;
    while (Minefield::get_board_horizontal_occupation(new_nrow, new_ncol) > context.BOARD_MAXIMUM_WIDTH)
        new_ncol--;
    new_nbombs = std::max(1, std::min(new_nrow * new_ncol, new_nbombs));

    context.BOARD_ROWS = new_nrow;
    context.BOARD_COLUMNS = new_ncol;
    context.BOARD_BOMBS = new_nbombs;
    reload_minefield();
    return true;
}

bool ScreenSettings::resize_board_delta(int dx, int dy, int db) {
    return resize_board(context.BOARD_ROWS + dx, context.BOARD_COLUMNS + dy, context.BOARD_BOMBS + db);
}

bool ScreenSettings::resize_board_more_columns() {
    return resize_board_delta(0, +1, 0);
}

bool ScreenSettings::resize_board_less_columns() {
    return resize_board_delta(0, -1, 0);
}

bool ScreenSettings::resize_board_more_rows() {
    return resize_board_delta(+1, 0, 0);
}

bool ScreenSettings::resize_board_less_rows() {
    return resize_board_delta(-1, 0, 0);
}

bool ScreenSettings::resize_board_more_bombs() {
    return resize_board_delta(0, 0, +1);
}

bool ScreenSettings::resize_board_less_bombs() {
    return resize_board_delta(0, 0, -1);
}
