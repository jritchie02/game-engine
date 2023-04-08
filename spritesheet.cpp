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

    /*

    for (int row = 0; row < m_tileset_rows; ++row)
    {
        for (int col = 0; col < m_tileset_cols; ++col)
        {
            sf::IntRect tileRect(col * m_tile_size, row * m_tile_size, m_tile_size, m_tile_size);
            sf::Sprite sprite;
            sprite.setTexture(m_tilesetTexture);
            sprite.setTextureRect(tileRect);
            sprite.setPosition(col * m_tile_size, row * m_tile_size);
            m_tileSprites.push_back(sprite);
        }
    }
    */
    return true;
}

bool SpriteSheet::load(const std::string &tileset, sf::Vector2u tileSize,
                       int width, int height)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
        {
            // get a pointer to the current tile's quad
            sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].texCoords = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].texCoords = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
        }

    return true;
}

bool SpriteSheet::load_tile(const std::string &tileset, sf::Vector2u tileSize,
                            int x_pos, int y_pos)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    // m_vertex.setPrimitiveType(sf::Quads);
    // m_vertex.resize(4);

    // get a pointer to the current tile's quad
    sf::Vertex *quad = &m_vertex;

    // define its 4 corners
    quad[0].position = sf::Vector2f(x_pos * tileSize.x, y_pos * tileSize.y);
    quad[1].position = sf::Vector2f((x_pos + 1) * tileSize.x, y_pos * tileSize.y);
    quad[2].position = sf::Vector2f((x_pos + 1) * tileSize.x, (y_pos + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(x_pos * tileSize.x, (y_pos + 1) * tileSize.y);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(x_pos * tileSize.x, y_pos * tileSize.y);
    quad[1].texCoords = sf::Vector2f((x_pos + 1) * tileSize.x, y_pos * tileSize.y);
    quad[2].texCoords = sf::Vector2f((x_pos + 1) * tileSize.x, (y_pos + 1) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(x_pos * tileSize.x, (y_pos + 1) * tileSize.y);

    return true;
}

void SpriteSheet::draw_board(sf::RenderWindow &window, const int *tiles, int height, int width)
{
    /*
    1 2 3 4 5 6 7
    8 9 10 11 12 13
    */
    /*
    0 1 1 0 2 3 0
    1 1 1 1 1 0 0
    0 0 1 0 1 0 1
    */


    sf::VertexArray m_world;
    m_world.setPrimitiveType(sf::Quads);
    m_world.resize(height * width * 4);

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < height; ++col)
        {
            // Define the vertices of the current cell
            sf::Vector2f topLeft(col * m_tile_size, row * m_tile_size);
            sf::Vector2f topRight((col + 1) * m_tile_size, row * m_tile_size);
            sf::Vector2f bottomRight((col + 1) * m_tile_size, (row + 1) * m_tile_size);
            sf::Vector2f bottomLeft(col * m_tile_size, (row + 1) * m_tile_size);

            // Determine the texture of the quad based on its ID
            int curr_id = tiles[row + col * m_tileset_cols];
            // find its position in the tileset texture
            // int tu = curr_id % (m_tilesetTexture.getSize().x / m_tile_size);
            // int tv = curr_id / (m_tilesetTexture.getSize().x / m_tile_size);
           
            // world[0].texCoords = sf::Vector2f(tu * m_tile_size, tv * m_tile_size);
            // world[1].texCoords = sf::Vector2f((tu + 1) * m_tile_size, tv * m_tile_size);
            // world[2].texCoords = sf::Vector2f((tu + 1) * m_tile_size, (tv + 1) * m_tile_size);
            // world[3].texCoords = sf::Vector2f(tu * m_tile_size, (tv + 1) * m_tile_size);
            m_world[(row + col * height) * 4].texCoords = sf::Vector2f(0, 0);
            m_world[(row + col * height) * 4 + 1].texCoords = sf::Vector2f(32, 0);
            m_world[(row + col * height) * 4 + 2].texCoords = sf::Vector2f(32, 32);
            m_world[(row + col * height) * 4 + 3].texCoords = sf::Vector2f(0, 32);
        }
    }
    window.draw(m_world, &m_tilesetTexture);
}