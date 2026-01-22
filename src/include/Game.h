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

    std::unique_ptr<ScoreText> m_scoreText;
    std::unique_ptr<GameOverText> m_gameOverText;
    std::unique_ptr<RestartHintText> m_restartHintText;

    enum class LaunchDirection 
    {
        ToPlayer = -1,
        ToBot = 1
    };


    LaunchDirection m_lastGoalScorer;

    int m_scorePlayer;
    int m_scoreBot;

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
    int getPlayerScore() const { return m_scorePlayer; }
    int getBotScore() const { return m_scoreBot; }
    bool isGameOver() const { return m_gameOver; }

private:
    void update(float deltaTime);
    void updateAI(float deltaTime);
    void updatePlayerInput(float deltaTime);

    void launchBall(LaunchDirection direction);

    void initializeGameObjects();
    void handleEvents();
    void updateScore();
    void checkGoals();
    void render();
};
