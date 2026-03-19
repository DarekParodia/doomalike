#pragma once

#define RGFW_IMPORT
#include "RGFW.h"

#include <cstdint>
#include <unordered_map>

namespace rendering {
    struct Pixel {
            uint8_t r, g, b;
    };

    enum KeyState {
        Released,
        Pressed,
        Held
    };

    class Window {
        public:
            Window(int width, int height);
            ~Window();

            void                                   init();
            void                                   update();
            void                                   resize(int width, int height, bool changeWindow = true);
            bool                                   shouldClose();
            KeyState                               getKeyState(RGFW_key key);

            static void                            windowresizefunc(RGFW_window *window, int w, int h);
            static void                            keyfunc(RGFW_window *win, u8 key, RGFW_keymod mod, RGFW_bool repeat, RGFW_bool pressed);

            size_t                                 drawBufferSize      = 0;
            size_t                                 drawBufferSizeBytes = 0;
            Pixel                                 *drawBuffer          = nullptr;

            std::unordered_map<RGFW_key, KeyState> keyStates;

            int                                    width;
            int                                    height;

        private:
            RGFW_window  *win                     = nullptr;


            size_t        _framebuffer_size       = 0;
            size_t        _framebuffer_actualsize = 0;
            Pixel        *_framebuffer            = nullptr;
            RGFW_surface *_surface                = nullptr;
            RGFW_surface *_surface2               = nullptr;
    };
} // namespace rendering