#include "screen.hpp"
#include "context.hpp"
#include <iostream>

ScreenHome::ScreenHome() {
    minefield = static_cast<Minefield*>(
        new MinefieldBlank(
            context.BOARD_ROWS,
            context.BOARD_COLUMNS
        )
    );

    sidepanel = new ScreenHomeSidePanel;
}

void ScreenHome::update_graphics() {
    minefield->update_graphics();
    sidepanel->update_graphics();
}

void ScreenHome::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(context.window_divider);
    target.draw(*minefield);
    target.draw(*sidepanel);
}

void ScreenHome::update_on_event(sf::Event event) {
    minefield->update_on_event(event);
    sidepanel->update_on_event(event);

    if (sidepanel->ask_for_new_game()) {
        set_pending_screen(
            static_cast<Screen*>(new ScreenGame)
        );
        return;
    }
    if (sidepanel->ask_for_settings()) {
        set_pending_screen(
            static_cast<Screen*>(new ScreenSettings)
        );
        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            set_pending_screen(
                static_cast<Screen*>(new ScreenGame)
            );
            return;
        }
    }
}

Screen* ScreenHome::detect_change_screen() {
    Screen* pending_screen = get_pending_screen();
    if (pending_screen != nullptr) {
        clear_pending_screen();
        return pending_screen;
    }

    return static_cast<Screen*>(this);
}
