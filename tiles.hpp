#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Board : public sf::Drawable, public sf::Transformable
{
public:
    Board() = default;

    Board(int tileSize, int width, int height) : m_tileSize(tileSize), m_boardWidth(width), m_boardHeight(height) {}

    void initBoard();

    int get_boardWidth()
    {
        return m_boardWidth;
    }

    int get_boardHeight()
    {
        return m_boardHeight;
    }

private:
    int m_tileSize = 32;
    int m_boardWidth = 60;
    int m_boardHeight = 32;
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