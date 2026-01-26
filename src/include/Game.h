#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "ScoreText.h"
#include "GameOverText.h"
#include "RestartHintText.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Font m_font;

    Paddle m_player;
    Paddle m_bot;

    Ball m_ball;

    ScoreText m_scoreText;
    GameOverText m_gameOverText;
    RestartHintText m_restartHintText;

    enum class LaunchDirection 
    {
        ToPlayer,
        ToBot
    };

    LaunchDirection m_lastGoalScorer;

    bool m_ballWaiting;
    float m_ballWaitTimer;

    bool m_gameOver;

public:
    Game();
    void run();
    void resetGame();

    const Ball& getBall() const { return m_ball; }
    const Paddle& getPlayer() const { return m_player; }
    const Paddle& getBot() const { return m_bot; }
    int getPlayerScore() const { return m_scoreText.getPlayerScore(); }
    int getBotScore() const { return m_scoreText.getBotScore(); }
    bool isGameOver() const { return m_gameOver; }

private:
    void update(float deltaTime);
    void updateAI();
    void updatePlayerInput();

    void launchBall(LaunchDirection direction);

    void initializeGameObjects();
    void handleEvents();
    void updateScore();
    void checkGoals();
    void render();
};
