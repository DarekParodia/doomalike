#pragma once

#include <vector>

namespace game {
    namespace time {
        extern size_t currentFrame;
        extern float  frameTime;
        extern float  framesPerSecond;
    }; // namespace time

    struct Entity {
            int x, y;
    };

    struct Player : Entity {
            float direction;
    };


    extern std::vector<Entity> entities;
    extern Player             *player;

    void                       init();
    void                       update();
    void                       render();
} // namespace game