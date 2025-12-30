#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Paddle.h"
#include "Ball.h"

class Game
{
private:
    // Window
    sf::RenderWindow window;

    // Window rations
    const float windowWidth;
    const float windowHeight;

    // Game objects
    Paddle player;
    Paddle bot;
    Ball   ball;

    // Score
    int scorePlayer;
    int scoreBot;
    const int maxScore;

    // Font & Text
    sf::Font font; 
    std::unique_ptr<sf::Text> scoreText;
    std::unique_ptr<sf::Text> gameOverText;


    // Time
    sf::Clock clock;

    // Game states
    bool ballWaiting;
    float ballWaitTimer;
    const float ballWaitTime;
    bool gameOver;

public:
    // Constructor
    Game();

    // MAIN game method: game running
    void run();

private:
    // Clear logic separation methods
    void handleEvents();
    void update(float deltaTime);
    void render();

    // Auxiliary methods
    void updateAI(float deltaTime);
    void checkGoals();
    void updateScore();
    void centerText(sf::Text& text, float yPos);
};
