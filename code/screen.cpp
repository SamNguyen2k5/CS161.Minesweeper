#include "screen.hpp"

void Screen::set_pending_screen(Screen *screen) {
    pending_screen = screen;
}

void Screen::clear_pending_screen() {
    pending_screen = nullptr;
}

Screen* Screen::get_pending_screen() {
    return pending_screen;
}
