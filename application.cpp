#include "application.hpp"

bool Application::loop()
{

    ImGui::SFML::Init(m_window);
    Board board = Board(m_window);

    sf::Clock deltaClock;
    board.initBoard();

    // create the tilemap from the level definition
    SpriteSheet map;
    if (!map.load("TileSet1.png", sf::Vector2u(32, 32), 30, 30))
    {
        return false;
    }

    if (!m_tilesetTexture.loadFromFile("TileSet1.png"))
    {
        // handle error loading the tileset image
        // TODO
    }

    for (int row = 0; row < m_tileset_rows; ++row)
    {
        for (int col = 0; col < m_tileset_col; ++col)
        {
            sf::IntRect tileRect(col * m_tile_size, row * m_tile_size, m_tile_size, m_tile_size);
            m_tileSprites[row * m_tileset_col + col].setTexture(m_tilesetTexture);
            m_tileSprites[row * m_tileset_col + col].setTextureRect(tileRect);
            m_tileSprites[row * m_tileset_col + col].setPosition(col * m_tile_size, row * m_tile_size);
        }
    }

    while (m_window.isOpen())
    {
        // Handle Input
        input(board);

        // Update GUI
        ImGui::SFML::Update(m_window, deltaClock.restart());
        ImGui::ShowDemoWindow();
        //  Render GUI
        gui(board);
        // Render SFML
        render(board, map);
    }

    ImGui::SFML::Shutdown();
    return true;
}

void Application::gui(Board &board)
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

    ImTextureID tilesetTextureId = (ImTextureID)(intptr_t)m_tilesetTexture.getNativeHandle(); // Cast the texture ID to ImTextureID
    ImVec2 imageSize = ImVec2(m_tile_size, m_tile_size);

    ImGui::BeginTable("TilesetTable", m_tileset_col, ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY);
    for (int row = 0; row < m_tileset_rows; row++)
    {
        ImGui::TableNextRow();
        for (int col = 0; col < m_tileset_col; col++)
        {
            ImGui::TableNextColumn();
            ImVec2 uv0 = ImVec2(col / (float)m_tileset_col, row / (float)m_tileset_rows);
            ImVec2 uv1 = ImVec2((col + 1) / (float)m_tileset_col, (row + 1) / (float)m_tileset_rows);
            ImGui::Image(tilesetTextureId, imageSize, uv0, uv1);
        }
    }
    ImGui::EndTable();

    ImGui::EndChild();

    ImGui::End();
    /*

    ImGui::Begin("Board Config");

    // PIXEL SIZE
    const char *items[] = {"8 pixels", "16 pixels", "32 pixels"};
    static int item_current = 2;
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
    */
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
            sf::Vector2i position = sf::Mouse::getPosition(m_window);
            board.drawTile(position.x, position.y);
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
    // m_window.draw(sheet);
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void Application::drawImage()
{
    sf::Texture texture;
    texture.loadFromFile("TileSet1.png");

    sf::Sprite sprite(texture);
    m_window.draw(sprite);
}
