#include "spritesheet.hpp"

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