#include "application.hpp"
#include <iostream>
using namespace engine;

bool Application::loop()
{
    if (!ImGui::SFML::Init(m_window))
    {
        // TODO throw error
    }

    m_board.initBoard();

    sf::Clock deltaClock;

    while (m_window.isOpen())
    {
        // Handle Input
        if (!input())
        {
            return false;
        };

        // Update Window
        ImGui::SFML::Update(m_window, deltaClock.restart());

        // Render GUI
        gui();

        // Render SFML SpriteSheet and Background
        render();
    }

    ImGui::SFML::Shutdown();
    return true;
}

void Application::gui_import_section()
{
    ImGui::Text("Enter image tile size in px and file path:");
    static char file_path[128] = "";
    ImGui::InputText("File Path", file_path, 128);
    if (m_file_error_msg)
    {
        ImVec4 redColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red color (RGBA)
        ImGui::TextColored(redColor, "Error: %s", "Unable to Open File with given path!");
    }
    static char tile_size[3] = "";
    ImGui::InputText("Tile Size (px)", tile_size, 3);
    if (m_size_error_msg)
    {
        ImVec4 redColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red color (RGBA)
        ImGui::TextColored(redColor, "Error: %s", "Tile Size should be 8, 16, or 32!");
    }

    if (ImGui::Button("Import Image"))
    {
        try
        {
            int tile_size_int = std::stoi(tile_size);
            SpriteSheet sprite_sheet(file_path, tile_size_int);

            sprite_sheet.import(m_board);

            m_size_error_msg = false;
            m_file_error_msg = false;
            m_sprite_sheet = sprite_sheet;
            m_imported_sheet = true;
        }
        catch (const std::exception &ex)
        {
            // If an integer is not entered display tile size error
            if (dynamic_cast<const std::invalid_argument *>(&ex))
            {
                m_size_error_msg = true;
            }
            // If file path is not valid catch sprite error
            if (dynamic_cast<const engine::SpriteError *>(&ex))
            {
                m_file_error_msg = true;
            }
        }
    }
}

void Application::gui_export_section()
{
    static char export_path[128] = "";
    ImGui::InputText("Export File Path", export_path, 128);

    if (ImGui::Button("Export Image"))
    {
        m_sprite_sheet.export_world(export_path);
    }
}

void Application::gui_grid_section()
{
    if (m_imported_sheet)
    {
        // Create a child window with scrolling
        ImGui::BeginChild("Tileset", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

        static int value = 32;   // Initial scale value
        const int minValue = 8;  // Minimum scale value
        const int maxValue = 64; // Maximum scale value

        ImGui::SliderInt("Scale", &value, minValue, maxValue);

        sf::Texture &tileset_Texture = m_sprite_sheet.get_tileset_texture();
        int tileset_cols = m_sprite_sheet.get_sheet_width();
        int tileset_rows = m_sprite_sheet.get_sheet_height();

        ImTextureID tilesetTextureId = (ImTextureID)(intptr_t)tileset_Texture.getNativeHandle(); // Cast the texture ID to ImTextureID

        ImVec2 scale_factor = ImVec2(value, value);

        ImGui::BeginTable("TilesetTable", tileset_cols, ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY);
        for (int row = 0; row < tileset_rows; row++)
        {
            ImGui::TableNextRow();
            for (int col = 0; col < tileset_cols; col++)
            {
                ImGui::TableNextColumn();

                // Create a unique ID for the button using row and column indices
                ImGui::PushID(row * tileset_cols + col);

                ImVec2 uv0 = ImVec2(col / (float)tileset_cols, row / (float)tileset_rows);
                ImVec2 uv1 = ImVec2((col + 1) / (float)tileset_cols, (row + 1) / (float)tileset_rows);

                int current_id = row * tileset_cols + col;
                bool selected = m_selected_tile_id == current_id;

                if (selected)
                {
                    // You can adjust the border color and width here
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 3.0f);
                }

                if (ImGui::ImageButton((ImTextureID)tilesetTextureId, scale_factor, uv0, uv1, 0, ImVec4(0, 0, 0, 1), ImVec4(1, 1, 1, 1)))
                {
                    m_selected_tile_id = row * tileset_cols + col;
                }

                if (selected)
                {
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();
                }

                ImGui::PopID();
            }
        }
        ImGui::EndTable();
        ImGui::EndChild();
    }
}

void Application::gui()
{
    ImGui::Begin("Options");
    gui_import_section();
    gui_export_section();
    gui_grid_section();
    ImGui::End();
}

int Application::input()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(m_window, event);

        if (event.type == sf::Event::Closed)
        {
            m_window.close();
            return false;
            // TODO exit loop istantly
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ImGui::GetIO().WantCaptureMouse)
        {
            if (m_imported_sheet)
            {
                sf::Vector2i position = sf::Mouse::getPosition(m_window);
                m_sprite_sheet.add_tile_id(m_selected_tile_id, position.x, position.y);
            }
        }
    }
    return true;
}

void Application::render()
{
    m_window.clear();

    m_window.draw(m_board);

    if (m_imported_sheet)
    {
        m_sprite_sheet.merge_tiles();
        m_window.draw(m_sprite_sheet);
    }

    ImGui::SFML::Render(m_window);
    m_window.display();
}
