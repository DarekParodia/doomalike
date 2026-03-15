#pragma once

#include <vector>

namespace game {
    struct Entity {
            int x, y;
    };

    struct Player : Entity {
    };


    extern std::vector<Entity> entities;
    extern Player             *player;

    void                       init();
    void                       update();
    void                       render();
} // namespace game