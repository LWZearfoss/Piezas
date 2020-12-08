/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, pieceAtNewBoardIsBlank)
{
  Piezas board;
  for (int i = 0; i < BOARD_ROWS; ++i) {
    for (int j = 0; j < BOARD_COLS; ++j) {
      ASSERT_EQ(board.pieceAt(i, j), Blank);
    }
  }
}

TEST(PiezasTest, pieceAtRowLessThanBoardFails)
{
  Piezas board;
  ASSERT_EQ(board.pieceAt(-1, 0), Invalid);
}

TEST(PiezasTest, pieceAtRowGreaterThanBoardFails)
{
  Piezas board;
  ASSERT_EQ(board.pieceAt(BOARD_ROWS, 0), Invalid);
}

TEST(PiezasTest, pieceAtColumnLessThanBoardFails)
{
  Piezas board;
  ASSERT_EQ(board.pieceAt(0, -1), Invalid);
}

TEST(PiezasTest, pieceAtColumnGreaterThanBoardFails)
{
  Piezas board;
  ASSERT_EQ(board.pieceAt(0, BOARD_COLS), Invalid);
}

TEST(PiezasTest, dropPieceValidPlacementSucceeds)
{
  Piezas board;
  ASSERT_EQ(board.dropPiece(0), X);
  ASSERT_EQ(board.pieceAt(0, 0), X);
}

TEST(PiezasTest, dropPieceValidPlacementTogglesTurnAndSucceeds)
{
  Piezas board;
  ASSERT_EQ(board.dropPiece(0), X);
  ASSERT_EQ(board.pieceAt(0, 0), X);
  ASSERT_EQ(board.dropPiece(0), O);
  ASSERT_EQ(board.pieceAt(1, 0), O);
}

TEST(PiezasTest, dropPieceColumnFullTogglesTurnAndFails)
{
  Piezas board;
  ASSERT_EQ(board.dropPiece(0), X);
  ASSERT_EQ(board.dropPiece(0), O);
  ASSERT_EQ(board.dropPiece(0), X);
  ASSERT_EQ(board.dropPiece(0), Blank);
  ASSERT_EQ(board.pieceAt(2, 0), X);
  ASSERT_EQ(board.dropPiece(1), X);
}

TEST(PiezasTest, dropPieceColumnLessThanBoardTogglesTurnAndFails)
{
  Piezas board;
  ASSERT_EQ(board.dropPiece(-1), Invalid);
  ASSERT_EQ(board.dropPiece(0), O);
}

TEST(PiezasTest, dropPieceColumnGreaterThanBoardTogglesTurnAndFails)
{
  Piezas board;
  ASSERT_EQ(board.dropPiece(BOARD_COLS), Invalid);
  ASSERT_EQ(board.dropPiece(0), O);
}

TEST(PiezasTest, resetSucceeds)
{
  Piezas board;
  board.dropPiece(0);
  board.dropPiece(0);
  board.dropPiece(0);
  board.reset();
  for (int i = 0; i < BOARD_ROWS; ++i) {
    for (int j = 0; j < BOARD_COLS; ++j) {
      ASSERT_EQ(board.pieceAt(i, j), Blank);
    }
  }
}

TEST(PiezasTest, gameStateHorizontalWinnerSucceeds)
{
  Piezas board;
  board.dropPiece(0);
  board.dropPiece(0);
  board.dropPiece(1);
  board.dropPiece(0);
  board.dropPiece(2);
  board.dropPiece(1);
  board.dropPiece(3);
  board.dropPiece(1);
  board.dropPiece(3);
  board.dropPiece(2);
  board.dropPiece(3);
  board.dropPiece(2);
  ASSERT_EQ(board.gameState(), X);
}

TEST(PiezasTest, gameStateVerticalWinnerSucceeds)
{
  Piezas board;
  board.dropPiece(0);
  board.dropPiece(1);
  board.dropPiece(0);
  board.dropPiece(1);
  board.dropPiece(0);
  board.dropPiece(2);
  board.dropPiece(3);
  board.dropPiece(3);
  board.dropPiece(1);
  board.dropPiece(3);
  board.dropPiece(2);
  board.dropPiece(2);
  ASSERT_EQ(board.gameState(), X);
}

TEST(PiezasTest, gameStateOWinnerSucceeds)
{
  Piezas board;
  board.dropPiece(0);
  board.dropPiece(1);
  board.dropPiece(2);
  board.dropPiece(1);
  board.dropPiece(3);
  board.dropPiece(1);
  board.dropPiece(0);
  board.dropPiece(0);
  board.dropPiece(2);
  board.dropPiece(2);
  board.dropPiece(3);
  board.dropPiece(3);
  ASSERT_EQ(board.gameState(), O);
}

TEST(PiezasTest, gameStateTieFails)
{
  Piezas board;
  board.dropPiece(0);
  board.dropPiece(0);
  board.dropPiece(1);
  board.dropPiece(0);
  board.dropPiece(2);
  board.dropPiece(1);
  board.dropPiece(3);
  board.dropPiece(1);
  board.dropPiece(3);
  board.dropPiece(3);
  board.dropPiece(2);
  board.dropPiece(2);
  ASSERT_EQ(board.gameState(), Blank);
}

TEST(PiezasTest, gameStateBoardEmptyFails)
{
  Piezas board;
  ASSERT_EQ(board.gameState(), Invalid);
}

TEST(PiezasTest, gameStateNotOverFails)
{
  Piezas board;
  board.dropPiece(0);
  board.dropPiece(0);
  board.dropPiece(0);
  ASSERT_EQ(board.gameState(), Invalid);
}
