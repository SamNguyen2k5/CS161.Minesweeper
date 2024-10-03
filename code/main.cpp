#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "application.hpp"
#include "context.hpp"
#include <string>
#include <fstream>

int main() {
    while (true) {
//        context.load_from_default();
        context.load_from_file("data/config.dat");

        Application* app = new Application(
            context.WINDOW_SIZE.width,
            context.WINDOW_SIZE.height,
            context.WINDOW_TITLE.c_str()
        );

        int return_code = app->run();
        if (return_code == 0)
            return 0;
    }

    return 0;
}
