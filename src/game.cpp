#include "game.h"

namespace game {
    std::vector<Entity> entities;
    Player             *player = nullptr;

    void                init() {
        player    = new Player();
        player->x = 0;
        player->y = 0;

        entities.push_back(*player);
    }

    void update() {
    }

    void render() {
    }
} // namespace game