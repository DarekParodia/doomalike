#include "game.h"
#include "rendering.h"
#include "logger.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <format>

namespace game {
    constexpr RGFW_key forwardKey  = RGFW_w;
    constexpr RGFW_key backwardKey = RGFW_s;
    constexpr RGFW_key leftKey     = RGFW_a;
    constexpr RGFW_key rightKey    = RGFW_d;

    namespace time {
        size_t                                currentFrame     = 0;
        float                                 frameTime        = 0.0f;
        float                                 frameTimeSeconds = 0.0f;
        std::chrono::steady_clock::time_point prevFrameChrono  = std::chrono::steady_clock::now();
        float                                 framesPerSecond  = 0;
        float                                 fpsLogTimerMs    = 0.0f;
    }; // namespace time

    std::vector<Entity> entities;
    Player             *player = nullptr;

    // Player Functions
    void Player::update() {
        // Player Movement
        float verticalAxis         = 0.0f;
        float horizontalAxis       = 0.0f;
        float outputPlayerDirector = 0.0f; // degrees (0 = up, 90 = right, 180 = down, 270 = left)
        shouldMove                 = false;

        if(rendering::window.isKeyPressed(forwardKey)) {
            verticalAxis += 1.0f;
            shouldMove    = true;
        }

        if(rendering::window.isKeyPressed(backwardKey)) {
            verticalAxis -= 1.0f;
            shouldMove    = true;
        }

        if(rendering::window.isKeyPressed(leftKey)) {
            horizontalAxis -= 1.0f;
            shouldMove      = true;
        }

        if(rendering::window.isKeyPressed(rightKey)) {
            horizontalAxis += 1.0f;
            shouldMove      = true;
        }

        // Calculate direction from input axes
        if(verticalAxis != 0.0f || horizontalAxis != 0.0f) {
            constexpr float radToDeg = 57.2957795f; // 180 / pi
            float           angleRad = std::atan2(horizontalAxis, verticalAxis);
            outputPlayerDirector     = angleRad * radToDeg;

            if(outputPlayerDirector < 0.0f)
                outputPlayerDirector += 360.0f;
        }

        this->direction = outputPlayerDirector;

        // Move player based on angle
        if(shouldMove) {
            constexpr float degToRad  = 0.0174532925f; // pi / 180
            float           dirRad    = this->direction * degToRad;

            this->x                  += std::sin(dirRad) * this->moveSpeed * time::frameTimeSeconds;
            this->y                  += std::cos(dirRad) * this->moveSpeed * time::frameTimeSeconds;
        }

        logger->debug("Player Angle: {:.0f}, X: {:.3f} Y: {:.3f}", direction, x, y);
    }

    // Game Functions
    void init() {
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
        time::frameTimeSeconds                                      = time::frameTime / 1000.0f;
        time::framesPerSecond                                       = 1000.0f / time::frameTime;

        time::fpsLogTimerMs                                        += time::frameTime;

        player->update();

        if(time::fpsLogTimerMs >= 1000.0f) {
            // logger->debug("Frame Time: {:.1f} ms, FPS: {:.1f}, Player Angle: {:.2f}", time::frameTime, time::framesPerSecond, player->direction);
            time::fpsLogTimerMs = 0.0f;
        }
    }

    void render() {
    }
} // namespace game