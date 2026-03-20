#pragma once

#include <vector>

namespace game {
    namespace time {
        extern size_t currentFrame;
        extern float  frameTime; // miliseconds
        extern float  frameTimeSeconds;
        extern float  framesPerSecond;
    }; // namespace time

    struct Entity {
            float x, y;

            float moveSpeed  = 1.0f;
            bool  shouldMove = false;
    };

    struct Player : Entity {
            float direction;     // Degrees
            float moveDirection; // Degrees

            void  update();
    };


    extern std::vector<Entity> entities;
    extern Player             *player;

    void                       init();
    void                       update();
    void                       render();
} // namespace game