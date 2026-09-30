#include "GameEngine.h"
#include "GameContext.h"
#include "CollisionObject.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/// @brief
namespace CMPUT350 {
#include "FontData.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name) {
    mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode({width, height}), name);
    mFont = std::make_shared<sf::Font>();

    // Sample font loading code
    if (!mFont->openFromMemory(&_font, _font_len)) {
        fprintf(stderr, "WARNING: Font did not load.\n");
    }

    mWindow->setFramerateLimit(30);
}

GameEngine::~GameEngine() {
    // Cleanup resources
    if (mWindow && mWindow->isOpen()) {
        mWindow->close();
    }
}

void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    if (gameObject != nullptr) {
        mPendingGameObjects.push_back(std::move(gameObject));
    }
}

/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {
    GameContext context;
    context.mEngineView = this;
    context.ScreenContext = nullptr;  // Set this to actual DrawContext

    while (mWindow->isOpen())  // window is open
    {
        // 0. Remove any objects that are now dead
        std::vector<std::shared_ptr<GameObject>> livingObjects;
        for (const std::shared_ptr<GameObject>& gameObject : mGameObjects) {
            if (gameObject && gameObject->IsAlive()) {
                livingObjects.push_back(gameObject);
            }
        }
        mGameObjects = std::move(livingObjects);

        // 1. Activate and initialize any objects added during the last frame
        std::vector<std::shared_ptr<GameObject>> objectsToActivate = std::move(mPendingGameObjects);
        mPendingGameObjects.clear();

        for (std::shared_ptr<GameObject>& object : objectsToActivate) {
            if (object) {
                object->Initialize(&context);
                mGameObjects.push_back(std::move(object));
            }
        }

        // 2. Process events
        bool shouldClose = false;
        while (const std::optional event = mWindow->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                mWindow->close();
                shouldClose = true;
                break;
            } else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
                char key = keyPressed->unicode;

                for (const auto& object : mGameObjects) {
                    if (object) {
                        object->HandleKeyEvent(&context, key);
                    }
                }
            }
        }

        if (shouldClose) {
            break;
        }

        // 3. Update game objects
        for (const auto& object : mGameObjects) {
            if (object) {
                object->Update(&context);
            }
        }

        // 4. Process collision events
        std::vector<std::shared_ptr<CollisionObject>> collisionObjects;

        for (const auto& object : mGameObjects) {
            auto collision = std::dynamic_pointer_cast<CollisionObject>(object);

            if (collision) {
                collisionObjects.push_back(std::move(collision));
            }
        }

        for (std::size_t i = 0; i < collisionObjects.size(); i++) {
            auto& first = collisionObjects[i];
            for (std::size_t j = i + 1; j < collisionObjects.size(); j++) {
                auto& second = collisionObjects[j];

                const Rect a = first->GetBounds();
                const Rect b = second->GetBounds();

                bool overlap = a.overlaps(b);

                if (overlap) {
                    first->CollisionEnter(second);
                    second->CollisionEnter(first);
                }
            }
        }

        // 5. Late updates
        for (const auto& object : mGameObjects) {
            if (object) {
                object->LateUpdate(&context);
            }
        }

        // Clear window

        // 6. Render background

        // 7. Render foreground

        // Actually render to window
    }
}

// Sample code for processing events

// bool GameEngine::ProcessEvents(GameContext *context)
//{
//	while (const std::optional event = mWindow->pollEvent())
//	{
//		if (event->is<sf::Event::Closed>())
//		{
//		}
//		else if (event->is<sf::Event::Resized>())
//		{
//		}
//		else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>())
//		{
//			// use keyPressed->unicode to get character
//		}
//	}
// }

}  // namespace CMPUT350
