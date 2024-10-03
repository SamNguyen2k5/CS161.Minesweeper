#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "screen.hpp"
#include "context.hpp"

class ApplicationState {
private:
    int code;

public:
    ApplicationState();
    ApplicationState(int code);
    static ApplicationState MENU();
    static ApplicationState IN_GAME();
    static ApplicationState LEADERBOARD();
};

class Application {
private:
    sf::RenderWindow        app;
    ApplicationState        app_state;

    Screen*                 screen;

public:
    Application(int width, int height, const char* title);
//    ~Application();

    int run();
};
