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
            float direction     = 0.0f; // Degrees
            float moveDirection = 0.0f; // Degrees

            float panSpeed      = 90.0f; // Degrees per second

            float x             = 0.0f;
            float y             = 0.0f;

            float moveSpeed     = 1.0f; // Units per second
            bool  shouldMove    = false;

            void  update();
    };

    struct Player : Entity {
            void update();
    };


    extern std::vector<Entity> entities;
    extern Player             *player;

    void                       init();
    void                       update();
    void                       render();
} // namespace game