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

    SpriteSheet sprite_sheet("TileSet1.png", 32);
    if (!sprite_sheet.subdivide(board.get_boardWidth(), board.get_boardHeight()))
    {
        // TODO Throw error
    }

    while (m_window.isOpen())
    {
        // Handle Input
        input(board, sprite_sheet);

        // Update Window
        ImGui::SFML::Update(m_window, deltaClock.restart());
        // ImGui::ShowDemoWindow();
        //   Render GUI
        gui(sprite_sheet);
        // Render SFML
        render(board, sprite_sheet);
    }

    ImGui::SFML::Shutdown();
    return true;
}

void Application::gui(SpriteSheet &sprite_sheet)
{
    ImGui::Begin("Import Section");

    ImGui::Text("Enter image tile size in px and file path:");
    static char buf1[128] = "";
    ImGui::InputText("File Path", buf1, 128);
    static char buf2[3] = "";
    ImGui::InputText("Tile Size (px)", buf2, 3);

    if (ImGui::Button("Import Image"))
    {
        m_imported_sheet = true;
    }

    if (m_imported_sheet)
    {
        // Create a child window with scrolling
        ImGui::BeginChild("Tileset", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

        sf::Texture &tileset_Texture = sprite_sheet.get_tileset_texture();
        int tileset_cols = sprite_sheet.get_sheet_width();
        int tileset_rows = sprite_sheet.get_sheet_height();
        int tile_size = sprite_sheet.get_tile_size();

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

    ImGui::End();
}

void Application::input(Board &board, SpriteSheet &sheet)
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
            sf::Vector2i position = sf::Mouse::getPosition(m_window);
            sheet.add_tile_id(m_selected_tile_id, position.x, position.y);
        }
    }
}

void Application::update()
{
}

void Application::render(Board &board, SpriteSheet &sheet)
{
    m_window.clear();
    // Call board functions
    board.drawWireframe();

    sheet.merge_tiles();
    m_window.draw(sheet);

    ImGui::SFML::Render(m_window);
    m_window.display();
}
