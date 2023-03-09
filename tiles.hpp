#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Board {
    public: 
        Board();

        Board(sf::RenderWindow &window) : m_window(window) {}

        Board(int tileSize, int width, int height, sf::RenderWindow &window) :
            m_tileSize(tileSize), m_boardWidth(width), m_boardHeight(height), m_window(window) {}

        void setTileSize(int tileSize); 
        void setBoardSize(int width, int height); 
        void drawWireframe();
        
        
    private:
        int m_tileSize = 32;
        int m_boardWidth = 60;
        int m_boardHeight = 32;
        sf::RenderWindow &m_window;

};

#endif // BOARD_H