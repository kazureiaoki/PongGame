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
    m_player.setPosition(PADDLE_OFFSET_FROM_EDGE, WINDOW_HEIGHT / HALF_DIVISOR - PADDLE_HEIGHT / HALF_DIVISOR);
    m_player.setColor(sf::Color::Green);
    m_player.setSpeed(PADDLE_SPEED);

    m_bot.setSize(PADDLE_WIDTH, PADDLE_HEIGHT);
    m_bot.setPosition(WINDOW_WIDTH - PADDLE_OFFSET_FROM_EDGE - PADDLE_WIDTH, WINDOW_HEIGHT / HALF_DIVISOR - PADDLE_HEIGHT / HALF_DIVISOR);
    m_bot.setColor(sf::Color::Green);
    m_bot.setSpeed(PADDLE_SPEED);

    m_ball.setRadius(BALL_RADIUS);
    m_ball.setPosition(WINDOW_WIDTH / HALF_DIVISOR, WINDOW_HEIGHT / HALF_DIVISOR);
    m_ball.setColor(sf::Color::White);
    m_ball.setSpeed(BALL_INITIAL_SPEED);

    m_scoreText.setPosition(WINDOW_WIDTH / HALF_DIVISOR, SCORE_TEXT_Y_OFFSET);
    m_gameOverText.setPosition(WINDOW_WIDTH / HALF_DIVISOR, WINDOW_HEIGHT / HALF_DIVISOR - GAME_OVER_TEXT_Y_OFFSET);
}

Game::Game()
    : m_ballWaiting(true)
    , m_ballWaitTimer(0.f)
    , m_gameOver(false)
    , m_scoreText(m_font)
    , m_gameOverText(m_font)
    , m_restartHintText(m_font)
    , m_lastGoalScorer(LaunchDirection::ToBot)
{
    m_window.create(
        sf::VideoMode({ 
            static_cast<unsigned int>(WINDOW_WIDTH), 
            static_cast<unsigned int>(WINDOW_HEIGHT)
            }), 
        "Pong Game"
    );
    m_window.setFramerateLimit(TARGET_FPS);

    const std::vector<std::string> fontPaths = 
    {
        std::string(FONT_DIR_CURRENT) + std::string(FONT_FILENAME),
        std::string(FONT_DIR_PARENT) + std::string(FONT_FILENAME),
        std::string(FONT_DIR_RELATIVE) + std::string(FONT_FILENAME)
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

    m_scoreText.setVisible(true);
    m_gameOverText.setVisible(false);
    m_restartHintText.setVisible(false);

    initializeGameObjects();
}

void Game::launchBall(LaunchDirection direction)
{
    const float angleRad = BALL_INITIAL_ANGLE_DEG * DEG_TO_RAD;
    const float dir = (direction == LaunchDirection::ToPlayer)
        ? LAUNCH_DIRECTION_TO_PLAYER
        : LAUNCH_DIRECTION_TO_BOT;

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

    m_clock.restart();

    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();

        if (deltaTime > MAX_DELTA_TIME)
        {
            deltaTime = FIXED_DELTA_TIME;
        }

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::update(float deltaTime)
{
    updatePlayerInput();
    updateAI();

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
        }
    }

    if (!m_gameOver)
    {
        m_ball.update(deltaTime);

        checkGoals();
    }

    updateScore();
}

void Game::updatePlayerInput() 
{
    float playerDirection = DIRECTION_NONE;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
    {
        playerDirection = DIRECTION_UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) 
    {
        playerDirection = DIRECTION_DOWN;
    }

    sf::Vector2f velocity = { 0.f, playerDirection * m_player.getSpeed() };
    m_player.setVelocity(velocity);
}

void Game::updateAI()
{
    float botDirection = DIRECTION_NONE;
    const sf::Vector2f ballPos = m_ball.getPosition();
    const sf::FloatRect botBounds = m_bot.getBounds();

    const float botCenterY = botBounds.position.y + botBounds.size.y / HALF_DIVISOR;

    if (ballPos.y < botCenterY - AI_DEAD_ZONE)
    {
        botDirection = DIRECTION_UP;
    }
    else if (ballPos.y > botCenterY + AI_DEAD_ZONE) {
        botDirection = DIRECTION_DOWN;
    }

    sf::Vector2f velocity = { 0.f, botDirection * m_bot.getSpeed() };
    m_bot.setVelocity(velocity);
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

    m_scoreText.draw(m_window);
    m_gameOverText.draw(m_window);
    m_restartHintText.draw(m_window);

    m_window.display();
}

void Game::checkGoals()
{
    const FieldCollision goal = m_ball.handleFieldCollision({ { 0.f, 0.f }, { WINDOW_WIDTH, WINDOW_HEIGHT } });

    if (goal == FieldCollision::BotGoal)
    {
        m_scoreText.addBotPoint();
        m_lastGoalScorer = LaunchDirection::ToBot;
        
        m_ball.setPosition(WINDOW_WIDTH / HALF_DIVISOR, WINDOW_HEIGHT / HALF_DIVISOR);
        m_ball.setVelocity(0.f, 0.f);

        m_ballWaiting = true;
        m_ballWaitTimer = 0.f;
    } else if (goal == FieldCollision::PlayerGoal) {
        m_scoreText.addPlayerPoint();
        m_lastGoalScorer = LaunchDirection::ToPlayer;

        m_ball.setPosition(WINDOW_WIDTH / HALF_DIVISOR, WINDOW_HEIGHT / HALF_DIVISOR);
        m_ball.setVelocity(0.f, 0.f);

        m_ballWaiting = true;
        m_ballWaitTimer = 0.f;
    }

    m_ball.handlePaddleCollision(m_player.getBounds());
    m_ball.handlePaddleCollision(m_bot.getBounds());

    if (m_scoreText.getPlayerScore() >= MAX_SCORE|| m_scoreText.getBotScore() >= MAX_SCORE)
    {
        m_gameOver = true;
        m_ballWaiting = false;

        m_gameOverText.setVisible(true);
        m_restartHintText.setVisible(false);
    }
}

void Game::updateScore() 
{
    m_scoreText.centerHorizontally(WINDOW_WIDTH);

    if (m_gameOver) 
    {
        if (m_scoreText.getPlayerScore() > m_scoreText.getBotScore())
        {
            m_gameOverText.setMessage(" GAME OVER\nPlayer wins!");
        } else if (m_scoreText.getBotScore() > m_scoreText.getPlayerScore()) {
            m_gameOverText.setMessage("GAME OVER\n Bot wins!");
        } else {
            m_gameOverText.setMessage("GAME OVER\n  Draw!");
        }

        m_ball.setVisible(false);

        m_gameOverText.centerHorizontally(WINDOW_WIDTH);
        m_gameOverText.setVisible(true);

        float hintY = WINDOW_HEIGHT / HALF_DIVISOR + RESTART_HINT_Y_OFFSET;

        m_restartHintText.setPosition(WINDOW_WIDTH / HALF_DIVISOR, hintY);
        m_restartHintText.centerHorizontally(WINDOW_WIDTH);
        m_restartHintText.setVisible(true);

    } else {
        m_gameOverText.setVisible(false);
        m_restartHintText.setVisible(false);
    }
}

void Game::resetGame()
{
    m_scoreText.reset();

    m_gameOver = false;

    m_ball.setVisible(true);

    m_gameOverText.setVisible(false);
    m_restartHintText.setVisible(false);

    m_ballWaiting = true;
    m_ballWaitTimer = 0.f;
    initializeGameObjects();
}