#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "tiles.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 960), "2D Game Engine");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    Board board = Board(window);

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::ShowDemoWindow();

        ImGui::Begin("Board Config");
       
        // PIXEL SIZE
        const char *items[] = {"8 pixels", "16 pixels", "32 pixels"};
        static int item_current = 0;
        ImGui::Combo("Pixel Size", &item_current, items, IM_ARRAYSIZE(items));

        switch (item_current)
        {
        case 0:
            board.setTileSize(8);
            break;
        case 1:
            board.setTileSize(16);
            break;
        case 2:
            board.setTileSize(32);
            break;
        default:
            // Handle unexpected value
            break;
        }

        ImGui::End();

        window.clear();
        // Call board functions
        board.drawWireframe();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}