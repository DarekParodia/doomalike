#pragma once

#include <vector>
#include <fstream>
#include "math.h"

namespace map {
    class Level {
        public:
            Level(std::ifstream &file);
            ~Level();

            std::vector<std::vector<bool>> walls;
    };

    void                        loadLevels();


    extern std::vector<Level *> levels;
    extern Level               *current_level;
} // namespace map