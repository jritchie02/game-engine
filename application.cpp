#include "application.hpp"
#include <iostream>

bool Application::loop()
{
    if (!ImGui::SFML::Init(m_window))
    {
        // TODO throw error
    }
    Board board = Board(m_window);

    sf::Clock deltaClock;
    board.initBoard();

    while (m_window.isOpen())
    {
        // Handle Input
        input(board);

        // Update Window
        ImGui::SFML::Update(m_window, deltaClock.restart());

        //   Render GUI
        gui(board);

        // Render SFML
        render(board);
    }

    ImGui::SFML::Shutdown();
    return true;
}

void Application::gui(Board &board)
{
    ImGui::Begin("Import Section");

    ImGui::Text("Enter image tile size in px and file path:");
    static char file_path[128] = "";
    ImGui::InputText("File Path", file_path, 128);
    static char tile_size[3] = "";
    ImGui::InputText("Tile Size (px)", tile_size, 3);

    if (ImGui::Button("Import Image"))
    {
        try
        {
            int tile_size_int = std::stoi(tile_size);
            SpriteSheet sprite_sheet(file_path, tile_size_int);

            if (!sprite_sheet.import(board.get_boardWidth(), board.get_boardHeight()))
            {
                // TODO Throw error
            }

            m_sprite_sheet = sprite_sheet;
            m_imported_sheet = true;
        }
        catch (const std::invalid_argument &ex)
        {
            std::cerr << "Invalid argument: " << ex.what() << std::endl;
            // Handle the error appropriately, e.g. show an error message, set a default value, etc.
        }
    }

    if (m_imported_sheet)
    {
        // Create a child window with scrolling
        ImGui::BeginChild("Tileset", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

        sf::Texture &tileset_Texture = m_sprite_sheet.get_tileset_texture();
        int tileset_cols = m_sprite_sheet.get_sheet_width();
        int tileset_rows = m_sprite_sheet.get_sheet_height();
        int tile_size = m_sprite_sheet.get_tile_size();

        ImTextureID tilesetTextureId = (ImTextureID)(intptr_t)tileset_Texture.getNativeHandle(); // Cast the texture ID to ImTextureID
        ImVec2 imageSize = ImVec2(tile_size, tile_size);

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

                if (ImGui::ImageButton((ImTextureID)tilesetTextureId, imageSize, uv0, uv1, 0, ImVec4(0, 0, 0, 1), ImVec4(1, 1, 1, 1)))
                {
                    m_selected_tile_id = row * tileset_cols + col;
                }

                if (selected)
                {
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();
                }

                // Pop the ID after using it for this button
                ImGui::PopID();
            }
        }
        ImGui::EndTable();
        ImGui::EndChild();
    }


    if (ImGui::Button("Export Image")) {
        m_sprite_sheet.export_world("ExportedFile.png");
    }

    ImGui::End();
}

void Application::input(Board &board)
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(m_window, event);

        if (event.type == sf::Event::Closed)
        {
            m_window.close();
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
}

void Application::update()
{
}

void Application::render(Board &board)
{
    m_window.clear();
    // Call board functions
    board.drawWireframe();

    m_sprite_sheet.merge_tiles();
    m_window.draw(m_sprite_sheet);

    ImGui::SFML::Render(m_window);
    m_window.display();
}
