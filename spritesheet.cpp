#include "spritesheet.hpp"
#include <iostream>
bool SpriteSheet::subdivide()
{
    if (!m_tilesetTexture.loadFromFile(m_file_name))
    {
        return false;
        // TODO handle error loading the tileset image
    }

    m_tileset_cols = m_tilesetTexture.getSize().x / m_tile_size;
    m_tileset_rows = m_tilesetTexture.getSize().y / m_tile_size;

    return true;
}

/*
    Given an int array of tile indexes, converts each index into a sf::Vertex where 
    the texture is mapped from the imported image in m_tilesetTexture
*/
void SpriteSheet::draw_board(const int *tiles, int height, int width)
{
    // resize the vertex array to fit the level size
    m_drawn_tiles.setPrimitiveType(sf::Quads);
    m_drawn_tiles.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // get a pointer to the current tile's quad
            sf::Vertex *quad = &m_drawn_tiles[(i + j * width) * 4];
            int id = tiles[(i + j * width)];

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