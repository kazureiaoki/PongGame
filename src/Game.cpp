#include "Game.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace PongConstants;

void Game::initializeGameObjects()
{
    m_player.setSize(PADDLE_WIDTH, PADDLE_HEIGHT);
    m_player.setPosition(PADDLE_OFFSET_FROM_EDGE, WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f);
    m_player.setColor(sf::Color::Green);
    m_player.setSpeed(PADDLE_SPEED);

    m_bot.setSize(PADDLE_WIDTH, PADDLE_HEIGHT);
    m_bot.setPosition(WINDOW_WIDTH - PADDLE_OFFSET_FROM_EDGE - PADDLE_WIDTH, WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f);
    m_bot.setColor(sf::Color::Green);
    m_bot.setSpeed(PADDLE_SPEED);

    m_ball.setRadius(BALL_RADIUS);
    m_ball.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
    m_ball.setColor(sf::Color::White);
    m_ball.setSpeed(BALL_INITIAL_SPEED);

    if (m_scoreText)
    {
        m_scoreText->setPosition(WINDOW_WIDTH / 2.f, SCORE_TEXT_Y_OFFSET);
    }

    if (m_gameOverText)
    {
        m_gameOverText->setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - GAME_OVER_TEXT_Y_OFFSET);
    }
}

Game::Game()
    : m_scorePlayer(0)
    , m_scoreBot(0)
    , m_ballWaiting(true)
    , m_ballWaitTimer(0.f)
    , m_gameOver(false)
    , m_lastGoalScorer(LaunchDirection::ToBot)
{
    m_window.create(
        sf::VideoMode({ 
            static_cast<unsigned int>(WINDOW_WIDTH), 
            static_cast<unsigned int>(WINDOW_HEIGHT)
            }), 
        "Pong Game"
    );
    m_window.setFramerateLimit(60);

    const std::vector<std::string> fontPaths = 
    {
        "./Fonts/CaesarDressing-Regular.ttf",
        "../Fonts/CaesarDressing-Regular.ttf",
        "Fonts/CaesarDressing-Regular.ttf"
    };

    bool fontLoaded = false;
    for (const auto& path : fontPaths)
    {
        if (m_font.openFromFile(path))
        {
            fontLoaded = true;
            break;
        }
    }

    if (!fontLoaded)
    {
        throw std::runtime_error("ERROR: Font not found in any path");
    }

    m_scoreText = std::make_unique<ScoreText>(m_font);
    m_gameOverText = std::make_unique<GameOverText>(m_font);
    m_restartHintText = std::make_unique<RestartHintText>(m_font);

    initializeGameObjects();
}

void Game::launchBall(LaunchDirection direction)
{
    float angleRad = BALL_INITIAL_ANGLE_DEG * DEG_TO_RAD;
    float dir = static_cast<float>(direction);

    m_ball.setVelocity(
        std::cos(angleRad) * BALL_INITIAL_SPEED * dir,
        std::sin(angleRad) * BALL_INITIAL_SPEED
    );
}

void Game::run()
{
    if (!m_window.isOpen())
    {
        return;
    }

    if (!m_scoreText || !m_gameOverText)
    {
        return;
    }

    m_clock.restart();

    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();

        if (deltaTime > 0.1f)
        {
            deltaTime = 0.016f;
        }

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::update(float deltaTime)
{
    updatePlayerInput(deltaTime);
    updateAI(deltaTime);

    m_player.update(deltaTime);
    m_bot.update(deltaTime);

    m_player.clampToWindow(WINDOW_HEIGHT);
    m_bot.clampToWindow(WINDOW_HEIGHT);

    if (m_ballWaiting)
    {
        m_ballWaitTimer += deltaTime;

        m_ball.update(deltaTime);

        if (m_ballWaitTimer >= BALL_WAIT_TIME)
        {
            m_ballWaiting = false;

            if (m_lastGoalScorer == LaunchDirection::ToPlayer) 
            {
                launchBall(LaunchDirection::ToBot);
            } else {
                launchBall(LaunchDirection::ToPlayer);
            }

            updateScore();
            return;
        }
    }

    if (!m_gameOver)
    {
        m_ball.update(deltaTime);
        m_ball.updatePhysics(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);

        m_ball.checkCollision(m_player.getBounds());
        m_ball.checkCollision(m_bot.getBounds());

        checkGoals();
    }

    updateScore();
}

void Game::updatePlayerInput(float deltaTime) 
{
    float playerDirection = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
    {
        playerDirection = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) 
    {
        playerDirection = 1.f;
    }

    sf::Vector2f velocity = { 0.f, playerDirection * m_player.getSpeed() };
    m_player.setVelocity(velocity);
}

void Game::handleEvents() {
    while (const std::optional<sf::Event> event = m_window.pollEvent()) 
    {
        if (event->is<sf::Event::Closed>()) 
        {
            m_window.close();
        }

        if (event->is<sf::Event::KeyPressed>()) 
        {
            const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();

            if (keyEvent) 
            {
                if (keyEvent->code == sf::Keyboard::Key::R && m_gameOver) 
                {
                    resetGame();
                }

                if (keyEvent->code == sf::Keyboard::Key::Escape) 
                {
                    m_window.close();
                }
            }
        }
    }
}


void Game::render()
{
    m_window.clear(sf::Color::Black);

    m_player.draw(m_window);
    m_bot.draw(m_window);
    m_ball.draw(m_window);

    if (m_scoreText) 
    {
        m_scoreText->draw(m_window);
    }

    if (m_gameOverText)
    {
        m_gameOverText->draw(m_window);
    }

    if (m_restartHintText) 
    {
        m_restartHintText->draw(m_window);
    }

    m_window.display();
}

void Game::updateAI(float deltaTime)
{
    float botDirection = 0.f;
    sf::Vector2f ballPos = m_ball.getPosition();

    sf::FloatRect botBounds = m_bot.getBounds();
    float botCenterY = botBounds.position.y + botBounds.size.y / 2.f;

    if (ballPos.y < botCenterY - AI_DEAD_ZONE)
    {
        botDirection = -1.f;
    } else if (ballPos.y > botCenterY + AI_DEAD_ZONE) {
        botDirection = 1.f;
    }

    sf::Vector2f velocity = { 0.f, botDirection * m_bot.getSpeed() };
    m_bot.setVelocity(velocity);
}

void Game::checkGoals()
{
    int goal = m_ball.checkGoal(WINDOW_WIDTH);

    if (goal == -1)
    {
        ++m_scoreBot;
        m_lastGoalScorer = LaunchDirection::ToBot;
        
        m_ball.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
        m_ball.setVelocity(0.f, 0.f);

        m_ballWaiting = true;
        m_ballWaitTimer = 0.f;
    } else if (goal == +1) {
        ++m_scorePlayer;
        m_lastGoalScorer = LaunchDirection::ToPlayer;

        m_ball.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
        m_ball.setVelocity(0.f, 0.f);

        m_ballWaiting = true;
        m_ballWaitTimer = 0.f;
    }

    if (m_scorePlayer >= MAX_SCORE || m_scoreBot >= MAX_SCORE)
    {
        m_gameOver = true;
        m_ballWaiting = false;
    }
}

void Game::updateScore() 
{
    if (m_scoreText) 
    {
        m_scoreText->setScore(m_scorePlayer, m_scoreBot);
        m_scoreText->centerHorizontally(WINDOW_WIDTH);
    }

    if(m_gameOverText) 
    {
        if (m_gameOver) 
        {
            if (m_scorePlayer > m_scoreBot) 
            {
                m_gameOverText->setMessage(" GAME OVER\nPlayer wins!");
            } else if (m_scoreBot > m_scorePlayer) {
                m_gameOverText->setMessage("GAME OVER\n Bot wins!");
            } else {
                m_gameOverText->setMessage("GAME OVER\n Draw!");
            }

            m_gameOverText->centerHorizontally(WINDOW_WIDTH);

            if (m_restartHintText) 
            {
                m_restartHintText->show();

                float hintY = WINDOW_HEIGHT / 2.f + RESTART_HINT_Y_OFFSET;
                m_restartHintText->setPosition(WINDOW_WIDTH / 2.f, hintY);
                m_restartHintText->centerHorizontally(WINDOW_WIDTH);
            }

        } else {
            m_gameOverText->clear();

            if (m_restartHintText) 
            {
                m_restartHintText->hide();
            }
        }
    }
}

void Game::resetGame()
{
    m_scorePlayer = 0;
    m_scoreBot = 0;
    m_gameOver = false;
    m_ballWaiting = true;
    m_ballWaitTimer = 0.f;
    initializeGameObjects();
}