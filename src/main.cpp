#include <iostream>

#include "window.h"

int main() {
    std::cout << "halo dziala" << std::endl;

    rendering::Window window(1280, 720);
    window.init();

    while(!window.shouldClose()){
        window.update();
    }

    return 0;
}