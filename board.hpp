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

    /*
        Updates this boards vertex array to create a grid of empty tiles. The "grid lines"
        are created by drawing two squares in each cell one pixel different in size. The
        larger square is a unique color to create a grid line effect.
    */
    void initBoard();
    const int m_tile_size;
    const int m_board_width;
    const int m_board_height;

private:
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