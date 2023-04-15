#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Board : public sf::Drawable, public sf::Transformable
{
public:
    Board() : m_tile_size(0), m_board_width(0), m_board_height(0) {}

    Board(int tileSize, int width, int height) : m_tile_size(tileSize), m_board_width(width), m_board_height(height) {}

    void initBoard();

    int get_board_width()
    {
        return m_board_width;
    }

    int get_board_height()
    {
        return m_board_height;
    }

    int get_board_tile_size() {
        return m_tile_size;
    }

private:
    int m_tile_size;
    int m_board_width;
    int m_board_height;
    std::vector<sf::RectangleShape> m_tiles;
    sf::VertexArray m_background;

    // mark as override TODO
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(m_background, states);
    }
};

#endif // BOARD_H