#include "tiles.hpp"
#include <iostream>

void Board::setTileSize(int tileSize)
{
    m_tileSize = tileSize;
}

void Board::setBoardSize(int width, int height)
{
    m_boardHeight = height;
    m_boardWidth = width;
}

void Board::initBoard()
{
    for (int x = 0; x < m_boardHeight; x++)
    {
        for (int y = 0; y < m_boardWidth; y++)
        {
            sf::RectangleShape rect(sf::Vector2f(m_tileSize, m_tileSize));
            rect.setFillColor(sf::Color(68, 68, 68));
            rect.setOutlineColor(sf::Color(120, 120, 120));
            rect.setOutlineThickness(1);
            rect.setPosition(y * m_tileSize, x * m_tileSize);
            m_tiles.push_back(rect);
            m_window.draw(rect);
        }
    }
}
void Board::drawWireframe()
{
    for (sf::RectangleShape tile : m_tiles) {
        m_window.draw(tile);
    }
}

void Board::drawTile(int x, int y)
{
    int relative_x = x / m_tileSize;
    int relative_y = y / m_tileSize;

    m_tiles.at((relative_y * m_boardWidth) + relative_x).setFillColor(sf::Color(255, 0, 0));
}