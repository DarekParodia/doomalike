#include <iostream>

#include "game.h"
#include "rendering.h"

int main() {
    std::cout << "halo dziala" << std::endl;

    game::init();
    rendering::init();

    while(!rendering::window.shouldClose()) {
        game::update();
        game::render();
        rendering::render();
    }

    return 0;
}