#include "application.hpp"

void Application::loop()
{

    ImGui::SFML::Init(m_window);

    Board board = Board(m_window);

    sf::Clock deltaClock;
    board.initBoard();

    // create the tilemap from the level definition
    SpriteSheet map;
    map.load("TileSet1.png", sf::Vector2u(32, 32), 30, 30);

    while (m_window.isOpen())
    {
        // Handle Input
        input(board);

        // Update GUI
        ImGui::SFML::Update(m_window, deltaClock.restart());
        ImGui::ShowDemoWindow();
        // Render GUI
        gui(board);
        // Render SFML
        render(board, map);
    }

    ImGui::SFML::Shutdown();
}

void Application::gui(Board &board)
{

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(m_window);
            board.drawTile(position.x, position.y);
        }
    }
}

void Application::update()
{
}

void Application::render(Board &board, Spritesheet &sheet)
{
    m_window.clear();
    // Call board functions
    board.drawWireframe();
    m_window.draw(map);
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
