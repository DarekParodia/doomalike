#include "game.h"
#include "rendering.h"

#include <chrono>
#include <iostream>

namespace game {
    namespace time {
        size_t                                currentFrame    = 0;
        float                                 frameTime       = 0.0f;
        std::chrono::steady_clock::time_point prevFrameChrono = std::chrono::steady_clock::now();
        float                                 framesPerSecond = 0;
        float                                 fpsLogTimerMs   = 0.0f;
    }; // namespace time

    std::vector<Entity> entities;
    Player             *player = nullptr;

    void                init() {
        player    = new Player();
        player->x = 0;
        player->y = 0;

        entities.push_back(*player);
    }

    void update() {
        time::currentFrame++;
        std::chrono::steady_clock::time_point now                   = std::chrono::steady_clock::now();
        float                                 frameTimeNanoseconds  = std::chrono::duration_cast<std::chrono::nanoseconds>(now - time::prevFrameChrono).count();
        time::prevFrameChrono                                       = now;
        time::frameTime                                             = frameTimeNanoseconds / 1000000.0f;
        time::framesPerSecond                                       = 1000.0f / time::frameTime;

        time::fpsLogTimerMs                                        += time::frameTime;
        if(time::fpsLogTimerMs >= 1000.0f) {
            std::cout << "Frame Time: " << time::frameTime << " ms FPS: " << time::framesPerSecond << '\n';
            time::fpsLogTimerMs = 0.0f;
        }
    }

    void render() {
    }
} // namespace game