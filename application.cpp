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
        // Your code to import the image goes here
        // create spritesheet based on image specs

        // Create a child window with scrolling
        ImGui::BeginChild("Tileset", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

        sf::Texture &tileset_Texture = sprite_sheet.get_tileset_texture();
        int tileset_cols = sprite_sheet.get_sheet_width();
        int tileset_rows = sprite_sheet.get_sheet_height();
        int tile_size = sprite_sheet.get_tile_size();

        ImTextureID tilesetTextureId = (ImTextureID)(intptr_t)tileset_Texture.getNativeHandle(); // Cast the texture ID to ImTextureID
        ImVec2 imageSize = ImVec2(tile_size, tile_size);

        std::vector<bool> selectedTiles(tileset_cols * tileset_rows);

        ImGui::BeginTable("TilesetTable", tileset_cols, ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY);
        for (int row = 0; row < tileset_rows; row++)
        {
            ImGui::TableNextRow();
            for (int col = 0; col < tileset_cols; col++)
            {
                ImGui::TableNextColumn();

                ImVec2 uv0 = ImVec2(col / (float)tileset_cols, row / (float)tileset_rows);
                ImVec2 uv1 = ImVec2((col + 1) / (float)tileset_cols, (row + 1) / (float)tileset_rows);

                bool tileSelected = selectedTiles.at(row * tileset_cols + col);

                ImVec4 selectColor = tileSelected ? ImVec4(0.5f, 0.5f, 1.0f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

                if (ImGui::ImageButton((ImTextureID)tilesetTextureId, imageSize, uv0, uv1, -1, ImVec4(0, 0, 0, 1), selectColor))
                {
                    std::cout << "Selecting button at " << row << " " << col << std::endl;
                    selectedTiles.at(row * tileset_cols + col) = !selectedTiles.at(row * tileset_cols + col);
                }
            }
        }
        ImGui::EndTable();
        ImGui::EndChild();
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

void Application::render(Board &board, SpriteSheet &sheet)
{
    m_window.clear();
    // Call board functions
    board.drawWireframe();
    const int level[] =
        {0, 0,
         0, 0};
    sheet.draw_board(m_window, level, 2, 2);
    ImGui::SFML::Render(m_window);
    m_window.display();
}
