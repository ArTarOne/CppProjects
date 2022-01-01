#include "stdafx.h"
#include "Core.h"
#include <optional>
#include <functional>
#include "WorldSettings.h"

void Core::restartGame()
{
    auto& ws = worldState;

    if(!ws.isPlaying)
    {
        // (re)start the game
        ws.isPlaying = true;
        clock.restart();

        // Reset the position of the paddles and ball
        ws.leftPaddleCenter = {
            10 + ws.leftPaddleSize.x / 2.f, ws.screenSize.y / 2.f
        };
        ws.rightPaddleCenter = {
            ws.screenSize.x - 10 - ws.rightPaddleSize.x / 2.f,
            ws.screenSize.y / 2.f
        };
        ws.ballCenter = { ws.screenSize.x / 2.f, ws.screenSize.y / 2.f };

        // Reset the ball angle
        do
        {
            // Make sure the ball initial angle is not too much vertical
            ballAngle = Math::degToRad(std::rand() % 360);
        } while(std::abs(std::cos(ballAngle)) < 0.7f);
    }
}

bool Core::checkPaddlesCollision()
{
    bool isCollision = false;
    auto& ws = worldState;

    // Left Paddle
    if(ws.ballCenter.x - ws.ballRadius <
        ws.leftPaddleCenter.x + ws.leftPaddleSize.x / 2 &&
       ws.ballCenter.y + ws.ballRadius >= 
        ws.leftPaddleCenter.y - ws.leftPaddleSize.y / 2 &&
       ws.ballCenter.y - ws.ballRadius <= 
        ws.leftPaddleCenter.y + ws.leftPaddleSize.y / 2)
    {
        if(ws.ballCenter.y > ws.leftPaddleCenter.y)
            ballAngle = M_PI - ballAngle + Math::degToRad(std::rand() % 50);
        else
            ballAngle = M_PI - ballAngle - Math::degToRad(std::rand() % 50);

        isCollision = true;

        ws.ballCenter = {
            ws.leftPaddleCenter.x + ws.ballRadius + ws.leftPaddleSize.x / 2,
            ws.ballCenter.y
        };
    }

    // Right Paddle
    if(ws.ballCenter.x + ws.ballRadius >
        ws.rightPaddleCenter.x - ws.rightPaddleSize.x / 2 &&
       ws.ballCenter.y + ws.ballRadius >= 
        ws.rightPaddleCenter.y - ws.rightPaddleSize.y / 2 &&
       ws.ballCenter.y - ws.ballRadius <= 
        ws.rightPaddleCenter.y + ws.rightPaddleSize.y / 2)
    {
        if(ws.ballCenter.y > ws.rightPaddleCenter.y)
            ballAngle = M_PI - ballAngle + Math::degToRad(std::rand() % 50);
        else
            ballAngle = M_PI - ballAngle - Math::degToRad(std::rand() % 50);

        isCollision = true;

        ws.ballCenter = {
            ws.rightPaddleCenter.x - ws.ballRadius - ws.rightPaddleSize.x / 2,
            ws.ballCenter.y
        };
    }

    return isCollision;
}

bool Core::checkScreenCollision()
{
    bool isCollision = false;
    auto& ws = worldState;

    // Check collisions between the ball and the screen
    // LEFT / RIGHT
    if(ws.ballCenter.x - ws.ballRadius < 0.f
       || ws.ballCenter.x + ws.ballRadius > ws.screenSize.x)
    {
        ws.isPlaying = false;
    }

    // TOP
    if(ws.ballCenter.y - ws.ballRadius < 0.f)
    {
        isCollision = true;
        ballAngle = -ballAngle;
        ws.ballCenter = { ws.ballCenter.x, ws.ballRadius + 0.1f };
    }
    // BOTTOM
    if(ws.ballCenter.y + ws.ballRadius > ws.screenSize.y)
    {
        isCollision = true;
        ballAngle = -ballAngle;
        ws.ballCenter = {
            ws.ballCenter.x, ws.screenSize.y - ws.ballRadius - 0.1f
        };
    }

    correctPaddlePosition(ws.leftPaddleCenter, ws.leftPaddleSize);
    correctPaddlePosition(ws.rightPaddleCenter, ws.rightPaddleSize);

    return isCollision;
}

void Core::movePaddles(const float deltaTime)
{
    auto& ws = worldState;

    switch(client01->getClientState())
    {
    case ClientState::PaddleUp:
        ws.moveLeftPaddle(0.f, -ws.paddleSpeed * deltaTime);
        break;
    case ClientState::PaddleDown:
        ws.moveLeftPaddle(0.f, ws.paddleSpeed * deltaTime);
        break;
    case ClientState::None:
    default: ;
    }

    switch(client02->getClientState())
    {
    case ClientState::PaddleUp:
        ws.moveRightPaddle(0.f, -ws.paddleSpeed * deltaTime);
        break;
    case ClientState::PaddleDown:
        ws.moveRightPaddle(0.f, ws.paddleSpeed * deltaTime);
        break;
    case ClientState::None:
    default: ;
    }
}

void Core::moveBall(const float deltaTime)
{
    auto& ws = worldState;
    const auto factor = ws.ballSpeed * deltaTime;
    ws.moveBall(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
}

void Core::correctPaddlePosition(sf::Vector2f& paddlePos,
                                 sf::Vector2f& paddleSize)
{
    auto& ws = worldState;

    std::pair<float, float> verticalBounds {
        0 + paddleSize.x / 2, ws.screenSize.x - paddleSize.x / 2
    };
    std::pair<float, float> horizontalBounds {
        0 + paddleSize.y / 2, ws.screenSize.y - paddleSize.y / 2
    };

    std::optional<float> xPos;
    std::optional<float> yPos;

    if(paddlePos.x > verticalBounds.second)
        xPos = std::make_optional(verticalBounds.second);
    else if(paddlePos.x < verticalBounds.first)
        xPos = std::make_optional(verticalBounds.first);
    else if(paddlePos.y > horizontalBounds.second)
        yPos = std::make_optional(horizontalBounds.second);
    else if(paddlePos.y < horizontalBounds.first)
        yPos = std::make_optional(horizontalBounds.first);

    if(xPos.has_value())
        paddlePos = { xPos.value(), paddlePos.y };

    if(yPos.has_value())
        paddlePos = { paddlePos.x, yPos.value() };
}

void Core::onSettingsUpdate()
{
    worldState.screenSize = { worldSettings->width, worldSettings->height };
    createClients();
}

void Core::iterate()
{
    if(!worldState.isPlaying)
        return;

    const auto deltaTime = clock.restart().asSeconds();

    movePaddles(deltaTime);
    moveBall(deltaTime);
    worldState.isBallCollision = checkAllCollision();
}

void Core::setWorldSettings(std::shared_ptr<WorldSettings> _worldSettings)
{
    worldSettings = _worldSettings;
    std::function<void()> cb = std::bind(&Core::onSettingsUpdate, this);
    worldSettings->subscribe(cb);
}

WorldState Core::getUpdatedWorldState() const
{
    client01->setWorldState(worldState);
    client01->updateState();
    client02->setWorldState(worldState);
    client02->updateState();
    return worldState;
}

bool Core::checkAllCollision()
{
    bool isCollision = false;
    isCollision = checkPaddlesCollision() || isCollision;
    isCollision = checkScreenCollision() || isCollision;
    return isCollision;
}

void Core::createClients()
{
    client01 = clientFactory.createClient(
                                          worldSettings->firstClientType,
                                          worldSettings->firstPlayerControl);
    client02 = clientFactory.createClient(
                                          worldSettings->secondClientType,
                                          worldSettings->secondPlayerControl);
}
