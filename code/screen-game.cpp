#include "screen.hpp"
#include "context.hpp"
#include <iostream>

ScreenGame::ScreenGame() {
    minefield = static_cast<Minefield*>(
        new MinefieldRandom(
            context.BOARD_ROWS,
            context.BOARD_COLUMNS,
            context.BOARD_BOMBS
        )
    );

    sidepanel = new ScreenGameSidePanel(minefield);
}

void ScreenGame::update_graphics() {
    minefield->update_graphics();
    sidepanel->update_graphics();
}

void ScreenGame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(context.window_divider);

    target.draw(*minefield);
    target.draw(*sidepanel);
}

void ScreenGame::update_on_event(sf::Event event) {
    minefield->update_on_event(event);
    sidepanel->update_on_event(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            set_pending_screen(
                static_cast<Screen*>(new ScreenHome)
            );
            return;
        }
    }
}

Screen* ScreenGame::detect_change_screen() {
    Screen* pending_screen = get_pending_screen();
    if (pending_screen != nullptr) {
        clear_pending_screen();
        return pending_screen;
    }

    if (ask_has_lost()) {
        MinefieldScore(minefield).add_to_leaderboard();
        return static_cast<Screen*>(
            new ScreenGameLose(this)
        );
    }

    if (ask_has_won()) {
        MinefieldScore(minefield).add_to_leaderboard();
        return static_cast<Screen*>(
            new ScreenGameWin(this)
        );
    }

    return static_cast<Screen*>(this);
}

//ScreenGame::~ScreenGame() {
//    delete minefield;
//    delete gametimer;
//}

bool ScreenGame::ask_has_lost() const {
    return minefield->ask_has_lost();
}

bool ScreenGame::ask_has_won() const {
    return minefield->ask_has_won();
}
