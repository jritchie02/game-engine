#ifndef APPLICATION_H
#define APPLICATION_H

#include "include/imgui.h"
#include "include/imgui-SFML.h"
#include "spritesheet.hpp"
#include "board.hpp"
#include "exceptions.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

class Application
{
public:
    Application() : m_window(sf::VideoMode(1920, 960), "2D Game Engine"), m_board(32, 60, 32)
    {
        m_window.setFramerateLimit(60);
    }
    bool loop();

private:
    int input();
    void gui();
    void render();

    sf::RenderWindow m_window;
    SpriteSheet m_sprite_sheet;
    Board m_board;
    bool m_imported_sheet = false;
    bool m_size_error_msg = false;
    bool m_file_error_msg = false;
    int m_selected_tile_id = 0;
};

#endif // APPLICATION_H
