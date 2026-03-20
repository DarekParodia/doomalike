#include "window.h"
#include "config.h"

#include <iostream>
#include <format>

namespace rendering {
    Window::Window(int width, int height) {
        this->width  = width;
        this->height = height;
    }

    Window::~Window() {
    }

    void Window::init() {
        win = RGFW_createWindow(
        PROJECT_DISPLAYNAME,
        0,
        0,
        width,
        height,
        RGFW_windowCenter);

        RGFW_window_setUserPtr(win, this);
        RGFW_window_setExitKey(win, RGFW_escape);
        RGFW_setWindowResizedCallback(windowresizefunc);
        RGFW_setKeyCallback(keyfunc);
        // init buffer
        resize(width, height, false);

        // render random things for testing
        int i = 0;

        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                _framebuffer[i].r = x % 255;
                _framebuffer[i].g = y % 255;
                _framebuffer[i].b = i % 255;
                i++;
            }
        }

        update();
    }

    void Window::update() {
        RGFW_event event;
        while(RGFW_window_checkEvent(win, &event))
            if(event.type == RGFW_quit) break;

        // swap buffers
        Pixel *temp            = _framebuffer;
        _framebuffer           = drawBuffer;
        drawBuffer             = temp;

        RGFW_surface *tempSurf = _surface;
        _surface               = _surface2;
        _surface2              = tempSurf;

        RGFW_window_blitSurface(win, _surface);
    }

    void Window::resize(int width, int height, bool changeWindow) {
        this->width  = width;
        this->height = height;

        if(changeWindow)
            RGFW_window_resize(win, width, height);


        if(_framebuffer != nullptr)
            delete[] _framebuffer;

        _framebuffer            = new Pixel[width * height];
        _framebuffer_size       = width * height;
        _framebuffer_actualsize = width * height * sizeof(Pixel);

        if(drawBuffer != nullptr)
            delete[] drawBuffer;

        drawBuffer          = new Pixel[width * height];
        drawBufferSize      = width * height;
        drawBufferSizeBytes = width * height * sizeof(Pixel);


        if(_surface != nullptr)
            RGFW_surface_free(_surface);

        _surface = RGFW_createSurface((uint8_t *) _framebuffer, width, height, RGFW_formatRGB8);

        if(_surface2 != nullptr)
            RGFW_surface_free(_surface2);

        _surface2 = RGFW_createSurface((uint8_t *) drawBuffer, width, height, RGFW_formatRGB8);

        std::cout << std::format("Window resized {}, {}\n", width, height);
    }

    bool Window::shouldClose() {
        return RGFW_window_shouldClose(win) != RGFW_FALSE;
    }

    bool Window::isKeyPressed(RGFW_key key) {
        KeyState state = getKeyState(key);
        return state == KeyState::Pressed || state == KeyState::Held;
    }

    KeyState Window::getKeyState(RGFW_key key) {
        // check if key value is registered
        if(this->keyStates.find(key) == this->keyStates.end())
            return KeyState::Released;
        else
            return this->keyStates.at(key);
    }

    void Window::windowresizefunc(RGFW_window *window, int w, int h) {
        auto tis = reinterpret_cast<Window *>(RGFW_window_getUserPtr(window));
        tis->resize(w, h, false);
    }

    void Window::keyfunc(RGFW_window *win, u8 key, RGFW_keymod mod, RGFW_bool repeat, RGFW_bool pressed) {
        (void) mod;

        auto tis = reinterpret_cast<Window *>(RGFW_window_getUserPtr(win));
        if(pressed)
            if(repeat)
                tis->keyStates[key] = KeyState::Held;
            else
                tis->keyStates[key] = KeyState::Pressed;
        else
            tis->keyStates[key] = KeyState::Released;
    }
} // namespace rendering