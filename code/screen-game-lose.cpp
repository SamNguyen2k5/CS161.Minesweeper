#include "screen.hpp"
#include "context.hpp"
#include <iostream>

ScreenGameLose::ScreenGameLose(ScreenGame* screen_game) {
    minefield = screen_game->minefield;
    minefield->set_end_game_lost();

    sidepanel = new ScreenGameLoseSidePanel(minefield);
}

void ScreenGameLose::update_graphics() {
    minefield->update_graphics();
    sidepanel->update_graphics();
}

void ScreenGameLose::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(context.window_divider);

    target.draw(*minefield);
    target.draw(*sidepanel);
}

void ScreenGameLose::update_on_event(sf::Event event) {
//     minefield->update_on_event(event);
    sidepanel->update_on_event(event);

    if (sidepanel->ask_is_back()) {
        set_pending_screen(static_cast<Screen*>(
            new ScreenHome
        ));
        return;
    }
}

Screen* ScreenGameLose::detect_change_screen() {
    Screen* pending_screen = get_pending_screen();
    if (pending_screen != nullptr) {
        clear_pending_screen();
        return pending_screen;
    }

    return static_cast<Screen*>(this);
}

