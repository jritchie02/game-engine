#include "tiles.hpp"
#include <iostream>

void Board::initBoard()
{
    // Create a single vertex array to represent the entire grid
    m_background.setPrimitiveType(sf::Quads);

    m_tiles.resize(m_boardHeight * m_boardWidth);

    for (int x = 0; x < m_boardHeight; x++)
    {
        for (int y = 0; y < m_boardWidth; y++)
        {
            // Define the vertices of the current cell
            sf::Vector2f topLeft(y * m_tileSize, x * m_tileSize);
            sf::Vector2f topRight((y + 1) * m_tileSize, x * m_tileSize);
            sf::Vector2f bottomRight((y + 1) * m_tileSize, (x + 1) * m_tileSize);
            sf::Vector2f bottomLeft(y * m_tileSize, (x + 1) * m_tileSize);

            // Add the vertices of cell with background outline color
            sf::Color grid_outline_color(18, 18, 18);
            m_background.append(sf::Vertex(topLeft, grid_outline_color));
            m_background.append(sf::Vertex(topRight, grid_outline_color));
            m_background.append(sf::Vertex(bottomRight, grid_outline_color));
            m_background.append(sf::Vertex(bottomLeft, grid_outline_color));

            // Add vertices of cell with the cell color
            sf::Color grid_cell_color(30, 48, 74);
            m_background.append(sf::Vertex(sf::Vector2f(topLeft.x + 1, topLeft.y + 1), grid_cell_color));
            m_background.append(sf::Vertex(sf::Vector2f(topRight.x - 1, topRight.y + 1), grid_cell_color));
            m_background.append(sf::Vertex(sf::Vector2f(bottomRight.x - 1, bottomRight.y - 1), grid_cell_color));
            m_background.append(sf::Vertex(sf::Vector2f(bottomLeft.x + 1, bottomLeft.y - 1), grid_cell_color));
        }
    }
}
