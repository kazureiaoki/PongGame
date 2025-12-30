#include <iostream>
#include "Game.h"

// Constructor: initializing window, players, ball, font
Game::Game()
    : clock()
    , windowWidth(1280.f)
    , windowHeight(960.f)
    , player(50.f, windowHeight / 2.f - 50.f)
    , bot(windowWidth - 70.f, windowHeight / 2.f - 50.f)
    , ball(windowWidth / 2.f, windowHeight / 2.f, 10.f)
    , scorePlayer(0)
    , scoreBot(0)
    , maxScore(5)
    , ballWaiting(true)
    , ballWaitTimer(0.f)
    , ballWaitTime(1.f)
    , gameOver(false)
{
    // Window creation
    window.create(sf::VideoMode(sf::Vector2u(static_cast<unsigned int>(windowWidth),
        static_cast<unsigned int>(windowHeight))),
        "Pong Game");
    window.setVerticalSyncEnabled(true);

    // Font loading
    if (!font.openFromFile("Fonts/CaesarDressing-Regular.ttf"))
    {
        std::cout << "ERROR: Font not found" << std::endl;
        window.close();
        return;
    }

    scoreText = std::make_unique<sf::Text>(font);
    scoreText->setCharacterSize(64);
    scoreText->setFillColor(sf::Color::Blue);
    scoreText->setString("0 : 0");
    centerText(*scoreText, 10.f);

    gameOverText = std::make_unique<sf::Text>(font);
    gameOverText->setCharacterSize(64);
    gameOverText->setFillColor(sf::Color::Blue);
    gameOverText->setString("");
}

// MAIN method: game running
void Game::run()
{

    // Some time for system to initialize
    sf::sleep(sf::milliseconds(100));

    clock.restart();

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        handleEvents();

        // Pause after goal
        if (ballWaiting)
        {
            ballWaitTimer += deltaTime;

            float playerDir = 0.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                playerDir = -1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                playerDir = 1.f;

            player.move(playerDir, deltaTime);
            updateAI(deltaTime);
            player.clampToWindow(windowHeight);
            bot.clampToWindow(windowHeight);

            if (ballWaitTimer >= ballWaitTime)
                ballWaiting = false;

            render();
            continue;
        }

        update(deltaTime);
        render();
    }
}


// Events handler (window closure, keybind)
void Game::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

// Game logic update
void Game::update(float deltaTime)
{
    // Player's controls
    float playerDirection = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        playerDirection = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        playerDirection = 1.f;

    player.move(playerDirection, deltaTime);

    updateAI(deltaTime);

    player.clampToWindow(windowHeight);
    bot.clampToWindow(windowHeight);

    // Ball's update (only if not game over)
    if (!gameOver)
    {
        ball.update(deltaTime, windowWidth, windowHeight);
        ball.checkCollision(player.getShape());
        ball.checkCollision(bot.getShape());

        checkGoals();
    }

    updateScore();
}

// Render
void Game::render()
{
    window.clear(sf::Color::Black);

    player.draw(window);
    bot.draw(window);
    ball.draw(window);

    window.draw(*scoreText);
    window.draw(*gameOverText);

    window.display();
}


// Bot's script
void Game::updateAI(float deltaTime)
{
    float botDirection = 0.f;

    sf::Vector2f ballPos = ball.getPosition();
    sf::RectangleShape& botShape = bot.getShape();
    float botCenterY = botShape.getPosition().y + botShape.getSize().y / 2.f;

    const float deadZone = 40.f;

    if (ballPos.y < botCenterY - deadZone)
        botDirection = -1.f;
    else if (ballPos.y > botCenterY + deadZone)
        botDirection = 1.f;

    bot.move(botDirection, deltaTime);
}

// Goal check
void Game::checkGoals()
{
    int goal = ball.checkGoal(windowWidth);

    // Left wing goal
    if (goal == -1)
    {
        ++scoreBot;
        ball.reset(windowWidth / 2.f, windowHeight / 2.f, -1);
        ballWaiting = true;
        ballWaitTimer = 0.f;
    }

    // Right wing goal
    else if (goal == +1)
    {
        ++scorePlayer;
        ball.reset(windowWidth / 2.f, windowHeight / 2.f, +1);
        ballWaiting = true;
        ballWaitTimer = 0.f;
    }

    // Game over check
    if (scorePlayer >= maxScore || scoreBot >= maxScore)
    {
        gameOver = true;
        ballWaiting = false;
    }
}

// Score update
void Game::updateScore()
{
    std::string scoreStr = std::to_string(scorePlayer) + " : " + std::to_string(scoreBot);
    scoreText->setString(scoreStr);
    centerText(*scoreText, 10.f);

    if (gameOver)
    {
        if (scorePlayer > scoreBot)
            gameOverText->setString(" GAME OVER\nPlayer wins!");
        else if (scoreBot > scorePlayer)
            gameOverText->setString("GAME OVER\n Bot wins!");
        else
            gameOverText->setString("GAME OVER\n Draw!");

        centerText(*gameOverText, windowHeight / 2.f - 350.f);
    }
    else
    {
        gameOverText->setString("");
    }
}


// Text centering
void Game::centerText(sf::Text& text, float yPos)
{
    sf::FloatRect bounds = text.getLocalBounds();
    float centerX = windowWidth / 2.f - bounds.size.x / 2.f;
    text.setPosition(sf::Vector2f(centerX, yPos));
}
