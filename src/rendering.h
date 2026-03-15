#pragma once

#include <cstdint>
#include "window.h"

namespace rendering {
    extern rendering::Window window;
    extern size_t            currentFrame;

    void                     init();
    void                     render();

    void                     clear();
    void                     drawPixel(int x, int y, Pixel color);
    void                     drawLine(int x1, int y1, int x2, int y2, int width, Pixel color);
    void                     drawRect(int x, int y, int width, int height, Pixel color);

    size_t                   getIndexFromPosition(int x, int y);
} // namespace rendering