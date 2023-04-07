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

    // create spritesheet based on image specs
    SpriteSheet sprite_sheet("TileSet1.png", 32, 31, 30);
    if (!sprite_sheet.subdivide())
    {
        // TODO Throw error
    }

    while (m_window.isOpen())
    {
        // Handle Input
        input(board);

        // Update Window
        ImGui::SFML::Update(m_window, deltaClock.restart());
        ImGui::ShowDemoWindow();
        //  Render GUI
        gui(sprite_sheet);
        // Render SFML
        render(board);
    }

    ImGui::SFML::Shutdown();
    return true;
}

void Application::gui(SpriteSheet &sprite_sheet)
{
    int imageWidth = 0;
    int imageHeight = 0;
    char imagePath[255] = {0};

    ImGui::Begin("Import Section");

    ImGui::Text("Enter image details and file path:");
    ImGui::InputInt("Width", &imageWidth);
    ImGui::InputInt("Height", &imageHeight);
    ImGui::InputText("File Path", imagePath, 255);

    if (ImGui::Button("Import Image"))
    {
        // Your code to import the image goes here
    }

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
            ImVec2 uv0 = ImVec2(col / (float)tileset_cols, row / (float)tileset_rows);
            ImVec2 uv1 = ImVec2((col + 1) / (float)tileset_cols, (row + 1) / (float)tileset_rows);
            ImGui::Image(tilesetTextureId, imageSize, uv0, uv1);
        }
    }
    ImGui::EndTable();
    ImGui::EndChild();
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

        /*

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ImGui::GetIO().WantCaptureMouse)
        {
            sf::Vector2i position = sf::Mouse::getPosition(m_window);
            board.drawTile(position.x, position.y);
        }
        */
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
    ImGui::SFML::Render(m_window);
    m_window.display();
}
