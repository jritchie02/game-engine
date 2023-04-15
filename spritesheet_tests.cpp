#include "unit_test_framework.h"
#include "spritesheet.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

using std::operator""s;

TEST(board_constructor)
{
    Board board;
    
    // Width/Height zero, default tile size 32
    ASSERT_EQUAL(0, board.get_board_height());
    ASSERT_EQUAL(0, board.get_board_width());
    ASSERT_EQUAL(0, board.get_board_tile_size());

    Board board2(8, 20, 10);
    
    // Width/Height zero, default tile size 32
    ASSERT_EQUAL(10, board2.get_board_height());
    ASSERT_EQUAL(20, board2.get_board_width());
    ASSERT_EQUAL(8, board2.get_board_tile_size());
}

TEST(spritesheet_import)
{
    Board board;
    SpriteSheet sheet;

    // Check default width/height
    ASSERT_EQUAL(0, sheet.get_sheet_height());
    ASSERT_EQUAL(0, sheet.get_sheet_width());

    // Call second constructor
    SpriteSheet sheet2("TileSet8bit.png", 8);
    ASSERT_EQUAL(8, sheet2.get_tile_size());

    // Test importing file updates sheet width/height/texture info
    ASSERT_EQUAL(true, sheet2.import(board));

    ASSERT_EQUAL(9, sheet2.get_sheet_height());
    ASSERT_EQUAL(7, sheet2.get_sheet_width());

    ASSERT_EQUAL((unsigned int)56, sheet2.get_tileset_texture().getSize().x);
    ASSERT_EQUAL((unsigned int)72, sheet2.get_tileset_texture().getSize().y);
}

TEST(spritesheet_assignment)
{
    Board board;
    SpriteSheet sheet;

    SpriteSheet sheet2("TileSet8bit.png", 8);

    sheet = sheet2;

    // Check the original sheet has correct member values
    ASSERT_EQUAL(true, sheet.import(board));

    ASSERT_EQUAL(9, sheet.get_sheet_height());
    ASSERT_EQUAL(7, sheet.get_sheet_width());

    ASSERT_EQUAL((unsigned int)56, sheet.get_tileset_texture().getSize().x);
    ASSERT_EQUAL((unsigned int)72, sheet.get_tileset_texture().getSize().y);
}

TEST(invalid_file_name)
{
    Board board;
    SpriteSheet sheet;

    SpriteSheet sheet2("TileSet8bit.png", 8);

    try
    {
        sheet.import(board);
    }
    catch (engine::SpriteError &ex)
    {
        ASSERT_EQUAL("Invalid File Path!"s, ex.what());
    }
}

TEST_MAIN()