#include "screen.hpp"
#include "context.hpp"
#include <iostream>

ScreenGameWin::ScreenGameWin(ScreenGame* screen_game) {
    minefield = screen_game->minefield;
//    minefield->set_end_game_lost();

    sidepanel = new ScreenGameWinSidePanel(minefield);
}

void ScreenGameWin::update_graphics() {
    minefield->update_graphics();
    sidepanel->update_graphics();
}

void ScreenGameWin::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(context.window_divider);
    target.draw(*minefield);
    target.draw(*sidepanel);
}

void ScreenGameWin::update_on_event(sf::Event event) {
    minefield->update_on_event(event);
    sidepanel->update_on_event(event);

    if (sidepanel->ask_is_back()) {
        set_pending_screen(static_cast<Screen*>(
            new ScreenHome
        ));
        return;
    }
}

Screen* ScreenGameWin::detect_change_screen() {
    Screen* pending_screen = get_pending_screen();
    if (pending_screen != nullptr) {
        clear_pending_screen();
        return pending_screen;
    }

    return static_cast<Screen*>(this);
}
