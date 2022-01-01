#include "stdafx.h"
#include "World.h"

World::World()
{
    worldSettings = std::make_shared<WorldSettings>();
    core.setWorldSettings(worldSettings);
    scene.setWorldSettings(worldSettings);
    worldSettings->load();
}

void World::handleEvents()
{
    sf::Event event {};
    while(scene.pollEvent(event))
    {
        if(event.type == sf::Event::Closed ||
           event.type == sf::Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape)
        {
            scene.close();
        }
        else if(event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space)
        {
            core.restartGame();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            scene.handleEvent(event);
        }
    }
}

int World::mainLoop()
{
    while(scene.isOpen())
    {
        handleEvents();
        const auto updatedWorldState = core.getUpdatedWorldState();
        scene.draw(updatedWorldState);
        core.iterate();
    }

    return EXIT_SUCCESS;
}
