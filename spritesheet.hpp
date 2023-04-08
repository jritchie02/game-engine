
#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp> // TODO remove import
#include <iostream>

class SpriteSheet : public sf::Drawable, public sf::Transformable
{
public:
    SpriteSheet();
    SpriteSheet(const std::string &file_name, int tile_size)
        : m_file_name(file_name), m_tile_size(tile_size) {}
    bool load(const std::string &tileset, sf::Vector2u tileSize, int width, int height);
    bool load_tile(const std::string &tileset, sf::Vector2u tileSize, int x_pos, int y_pos);
    bool subdivide();
    void draw_board(sf::RenderWindow &window, const int* tiles, int height, int width);

    // Getters to Access SpriteSheet info
    sf::Texture &get_tileset_texture()
    {
        return m_tilesetTexture;
    }
    int get_tile_size()
    {
        return m_tile_size;
    }
    int get_sheet_width()
    {
        return m_tileset_cols;
    }
    int get_sheet_height()
    {
        return m_tileset_rows;
    }

private:
    // Sprite Sheet V1
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    sf::Vertex m_vertex;
    sf::Texture m_tileset;

    // Sprite Sheet V2
    // Rendering spritesheet in imgui
    sf::Texture m_tilesetTexture;
    const std::string &m_file_name;
    int m_tile_size;
    int m_tileset_cols;
    int m_tileset_rows;
    std::vector<sf::Sprite> m_tileSprites;
};

#endif // SPRITESHEET_H