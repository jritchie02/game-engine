#ifndef APPLICATION_H
#define APPLICATION_H

#include "../include/imgui.h"
#include "../include/imgui-SFML.h"
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
    /*
        Handles user input. Returns false if the window is closed. If the mouse is
        clicked on the grid after delegates to the spritesheet add_tile function
    */
    int input();

    /*
        Calls all of the ImGui helper methods. Responsible for the entire panel
    */
    void gui();

    // Gui import section with file path, tile size and import button
    void gui_import_section();
    // Gui export section with file path and export button
    void gui_export_section();
    // Gui grid section. Subdivides the SpriteSheet texture into selectable grid elements
    void gui_grid_section();

    /*
        Updates the window with the SFML drawing functions. The window calls draw on the
        board every loop and on the spritesheet if the tile set has been imported
    */
    void render();

    sf::RenderWindow m_window;
    SpriteSheet m_sprite_sheet;
    Board m_board;

    // Gui fields to track error messages and application state
    bool m_imported_sheet = false;
    bool m_size_error_msg = false;
    bool m_file_error_msg = false;
    int m_selected_tile_id = 0;
};

#endif // APPLICATION_H
