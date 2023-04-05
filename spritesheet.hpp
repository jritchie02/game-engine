
#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

class SpriteSheet : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string &tileset, sf::Vector2u tileSize, int width, int height);
    bool load_tile(const std::string &tileset, sf::Vector2u tileSize, int x_pos, int y_pos);

private:
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
};

#endif // SPRITESHEET_H