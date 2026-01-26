#pragma once

#include <string_view>

namespace PongConstants
{
    constexpr float WINDOW_WIDTH = 1280.0f;
    constexpr float WINDOW_HEIGHT = 960.0f;
    constexpr float HALF_DIVISOR = 2.0f;
    constexpr unsigned int TARGET_FPS = 60;

    constexpr float LAUNCH_DIRECTION_TO_PLAYER = -1.0f;
    constexpr float LAUNCH_DIRECTION_TO_BOT = 1.0f;

    constexpr float DIRECTION_UP = -1.0f;
    constexpr float DIRECTION_DOWN = 1.0f;
    constexpr float DIRECTION_NONE = 0.0f;

    constexpr float PADDLE_WIDTH = 20.0f;
    constexpr float PADDLE_HEIGHT = 100.0f;
    constexpr float PADDLE_SPEED = 500.0f;
    constexpr float PADDLE_OFFSET_FROM_EDGE = 50.0f; 

    constexpr float BALL_RADIUS = 10.0f;
    constexpr float BALL_INITIAL_SPEED = 400.0f;
    constexpr float BALL_SPEED_INCREMENT = 20.0f;
    constexpr float BALL_MAX_SPEED = 800.0f;
    constexpr float BALL_INITIAL_ANGLE_DEG = 30.0f;
    constexpr float BALL_MAX_BOUNCE_ANGLE_DEG = 45.0f;

    constexpr int MAX_SCORE = 2;
    constexpr float BALL_WAIT_TIME = 1.0f;
    constexpr float AI_DEAD_ZONE = 40.0f;

    constexpr float PI = 3.14159265358979323846f;
    constexpr float DEG_TO_RAD = PI / 180.0f;
    constexpr float RAD_TO_DEG = 180.0f / PI;

    constexpr float MAX_DELTA_TIME = 0.1f;
    constexpr float FIXED_DELTA_TIME = 0.016f;

    constexpr unsigned int FONT_SIZE_SCORE = 64;
    constexpr unsigned int FONT_SIZE_GAME_OVER = 72;
    constexpr unsigned int FONT_SIZE_RESTART_HINT = 32;
    constexpr float SCORE_TEXT_Y_OFFSET = 10.0f;
    constexpr float GAME_OVER_TEXT_Y_OFFSET = 150.0f;
    constexpr float RESTART_HINT_Y_OFFSET = 50.0f;

    constexpr std::string_view FONT_FILENAME = "CaesarDressing-Regular.ttf";
    constexpr std::string_view FONT_DIR_CURRENT = "./Fonts/";
    constexpr std::string_view FONT_DIR_PARENT = "./Fonts/";
    constexpr std::string_view FONT_DIR_RELATIVE = "Fonts/";
}