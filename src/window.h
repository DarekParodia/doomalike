#pragma once

#define RGFW_IMPORT
#include "RGFW.h"

#include <cstdint>

namespace rendering {
    struct Pixel {
            uint8_t r, g, b;
    };

    class Window {
        public:
            Window(int width, int height);
            ~Window();

            void        init();
            void        update();
            void        resize(int width, int height, bool changeWindow = true);
            bool        shouldClose();

            static void windowresizefunc(RGFW_window *window, int w, int h);

            size_t      drawBufferSize      = 0;
            size_t      drawBufferSizeBytes = 0;
            Pixel      *drawBuffer          = nullptr;

            int         width;
            int         height;

        private:
            RGFW_window  *win                     = nullptr;

            size_t        _framebuffer_size       = 0;
            size_t        _framebuffer_actualsize = 0;
            Pixel        *_framebuffer            = nullptr;
            RGFW_surface *_surface                = nullptr;
            RGFW_surface *_surface2               = nullptr;
    };
} // namespace rendering