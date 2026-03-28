#include "map.h"
#include <filesystem>

#include <string>
#include "logger.h"

namespace map {
    Level::Level(std::ifstream &file) {
        int         counter = 0;
        std::string line;

        while(std::getline(file, line)) {
            this->walls.push_back(std::vector<bool>());
            for(int i = 0; i < line.length(); i++)
                this->walls[counter].push_back(line.at(i) == '1');
            counter++;
        }

        for(int i = 0; i < walls.size(); i++) {
            std::string line;
            for(int j = 0; j < walls[i].size(); j++)
                line.push_back(walls[i][j] ? '1' : '0');

            logger->debug(line);
        }

        levels.push_back(this);
    }

    Level::~Level() {
    }

    void loadLevels() {
        const std::string levelsDir = "./assets/levels";

        // list files in the levels dir
        for(const auto &entry : std::filesystem::directory_iterator(levelsDir)) {
            logger->debug("Entry: " + std::string(entry.path()));

            std::ifstream file(entry.path());

            if(file.is_open()) {
                Level *lvl = new Level(file);
                levels.push_back(lvl);
            }
        }
    }

    std::vector<Level *> levels;
    Level               *current_level = nullptr;

} // namespace map