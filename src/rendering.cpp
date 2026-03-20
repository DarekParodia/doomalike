#include "rendering.h"
#include "game.h"

namespace rendering {
    rendering::Window window(800, 600);
    size_t            currentFrame = 0;

    //
    void init() {
        window.init();
    }

    void render() {
        clear();

        // draw player
        int x = game::player->x * zoom + window.width / 2;
        int y = -game::player->y * zoom + window.height / 2;
        drawRect(x, y, zoom, zoom, { 255, 255, 255 });

        window.update();

        currentFrame++;
    }

    void clear() {
        memset(window.drawBuffer, 0x00, window.drawBufferSizeBytes);
    }

    void drawPixel(int x, int y, Pixel color) {
        window.drawBuffer[getIndexFromPosition(x, y)] = color;
    }

    void drawLine(int x1, int y1, int x2, int y2, int width, Pixel color) {
        if(width <= 0) return;

        int dx    = std::abs(x2 - x1);
        int sx    = (x1 < x2) ? 1 : -1;
        int dy    = -std::abs(y2 - y1);
        int sy    = (y1 < y2) ? 1 : -1;
        int err   = dx + dy;

        int x     = x1;
        int y     = y1;
        int start = -width / 2;
        int end   = start + width - 1;

        while(true) {
            for(int oy = start; oy <= end; ++oy) {
                for(int ox = start; ox <= end; ++ox) {
                    int px = x + ox;
                    int py = y + oy;
                    if(px >= 0 && px < window.width && py >= 0 && py < window.height)
                        drawPixel(px, py, color);
                }
            }

            if(x == x2 && y == y2) break;

            int e2 = err * 2;
            if(e2 >= dy) {
                err += dy;
                x   += sx;
            }
            if(e2 <= dx) {
                err += dx;
                y   += sy;
            }
        }
    }

    void drawRect(int x, int y, int width, int height, Pixel color) {
        if(width <= 0 || height <= 0) return;

        int startX = (x < 0) ? 0 : x;
        int startY = (y < 0) ? 0 : y;
        int endX   = x + width;
        int endY   = y + height;

        if(endX > window.width) endX = window.width;
        if(endY > window.height) endY = window.height;

        if(startX >= endX || startY >= endY) return;

        for(int py = startY; py < endY; ++py)
            for(int px = startX; px < endX; ++px)
                drawPixel(px, py, color);
    }

    size_t getIndexFromPosition(int x, int y) {
        return y * window.width + x;
    }

} // namespace rendering