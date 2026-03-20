#include <iostream>

#include "game.h"
#include "rendering.h"
#include "logger.h"

int main() {
    std::cout << "halo dziala" << std::endl;
    init_logger();

    game::init();
    rendering::init();

    while(!rendering::window.shouldClose()) {
        game::update();
        game::render();
        rendering::render();
    }

    return 0;
}