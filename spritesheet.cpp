#include "spritesheet.hpp"
#include <iostream>
#include <cmath>

bool SpriteSheet::subdivide(int boardWidth, int boardHeight)
{
    if (!m_tilesetTexture.loadFromFile(m_file_name))
    {
        return false;
        // TODO handle error loading the tileset image
    }

    m_tileset_cols = std::round(m_tilesetTexture.getSize().x / m_tile_size);
    m_tileset_rows = std::round(m_tilesetTexture.getSize().y / m_tile_size);

    m_boardHeight = boardHeight;
    m_boardWidth = boardWidth;

    m_tile_ids.resize(boardWidth * boardHeight, -1);
    return true;
}

/*
    Given an int array of tile indexes, converts each index into a sf::Vertex where
    the texture is mapped from the imported image in m_tilesetTexture
*/
void SpriteSheet::merge_tiles()
{
    // resize the vertex array to fit the level size
    m_drawn_tiles.setPrimitiveType(sf::Quads);
    m_drawn_tiles.resize(m_boardWidth * m_boardHeight * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < m_boardWidth; ++i)
    {
        for (int j = 0; j < m_boardHeight; ++j)
        {

            int id = m_tile_ids.at(i + j * m_boardWidth);

            if (id != -1)
            {
                // get a pointer to the current tile's quad
                sf::Vertex *quad = &m_drawn_tiles[(i + j * m_boardWidth) * 4];

                // calculate the tu and tv using the id and the number of columns and rows in the tileset
                int tu = id % m_tileset_cols;
                int tv = id / m_tileset_cols;

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * m_tile_size, j * m_tile_size);
                quad[1].position = sf::Vector2f((i + 1) * m_tile_size, j * m_tile_size);
                quad[2].position = sf::Vector2f((i + 1) * m_tile_size, (j + 1) * m_tile_size);
                quad[3].position = sf::Vector2f(i * m_tile_size, (j + 1) * m_tile_size);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * m_tile_size, tv * m_tile_size);
                quad[1].texCoords = sf::Vector2f((tu + 1) * m_tile_size, tv * m_tile_size);
                quad[2].texCoords = sf::Vector2f((tu + 1) * m_tile_size, (tv + 1) * m_tile_size);
                quad[3].texCoords = sf::Vector2f(tu * m_tile_size, (tv + 1) * m_tile_size);
            }
        }
    }
}

void SpriteSheet::add_tile_id(int id, int xpos, int ypos)
{
    int tile_x_pos = xpos / m_tile_size;
    int tile_y_pos = ypos / m_tile_size;

    int index = tile_x_pos + tile_y_pos * m_boardWidth;

    if (index < 1920)
    {
        m_tile_ids.at(index) = id;
    }
}