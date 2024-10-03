#include "application.hpp"

ApplicationState::ApplicationState():
    code(0) {}
ApplicationState::ApplicationState(int code):
    code(code) {}

ApplicationState ApplicationState::MENU() { return ApplicationState(0); }
ApplicationState ApplicationState::IN_GAME() { return ApplicationState(1); }
ApplicationState ApplicationState::LEADERBOARD() { return ApplicationState(2); }
