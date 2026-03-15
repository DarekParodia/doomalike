#pragma once

#define RGFW_IMPORT
#include "RGFW.h"
#include "rendering.h"

#include <cstdint>

namespace rendering {
    class Window {
        public:
            Window(int width, int height);
            ~Window();

            void init();
            void update();
            void resize(int width, int height, bool changeWindow = true);
            bool shouldClose();

            static void windowresizefunc(RGFW_window* window, int w, int h);
        private:
            RGFW_window* win = nullptr;
            int width;
            int height;

            size_t _framebuffer_size = 0;
            size_t _framebuffer_actualsize = 0;
            Pixel *_framebuffer = nullptr;
            RGFW_surface* _surface = nullptr;
    };
}