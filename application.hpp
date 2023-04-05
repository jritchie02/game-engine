#ifndef APPLICATION_H
#define APPLICATION_H

#include "include/imgui.h"
#include "include/imgui-SFML.h"
#include "spritesheet.hpp"
#include "tiles.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Application
{
public:
    Application() : m_window(sf::VideoMode(1920, 960), "2D Game Engine")
    {
        m_window.setFramerateLimit(60);
    }
    bool loop();

private:
    void input(Board &board);
    void gui(Board &board);
    void update();
    void render(Board &board, SpriteSheet &sheet);
    void drawImage();

    sf::RenderWindow m_window;
};

#endif // APPLICATION_H
