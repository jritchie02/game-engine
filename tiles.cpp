#include "tiles.hpp"

void Board::setTileSize(int tileSize)
{
    m_tileSize = tileSize;
}

void Board::setBoardSize(int width, int height)
{
    m_boardHeight = height; 
    m_boardWidth = width; 
}

void Board::drawWireframe()
{
    for (int x = 0; x < m_boardWidth; x++)
    {
        for (int y = 0; y < m_boardHeight; y++)
        {
            sf::RectangleShape rect(sf::Vector2f(m_tileSize, m_tileSize));
            rect.setFillColor(sf::Color(68, 68, 68));
            rect.setOutlineColor(sf::Color(120, 120, 120));
            rect.setOutlineThickness(1);
            rect.setPosition(x * m_tileSize, y * m_tileSize);
            m_window.draw(rect);
        }
    }
}