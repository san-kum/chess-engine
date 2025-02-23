#include "board.hpp"
#include <iostream>

namespace chess {

Board::Board() {
  clear(); // Start with an empty board

  // Set up pawns
  for (int col = 0; col < BOARD_SIZE; ++col) {
    setPiece(1, col, Piece(PieceType::PAWN, Color::WHITE));
    setPiece(6, col, Piece(PieceType::PAWN, Color::BLACK));
  }

  // Set up other pieces (White)
  setPiece(0, 0, Piece(PieceType::ROOK, Color::WHITE));
  setPiece(0, 1, Piece(PieceType::KNIGHT, Color::WHITE));
  setPiece(0, 2, Piece(PieceType::BISHOP, Color::WHITE));
  setPiece(0, 3, Piece(PieceType::QUEEN, Color::WHITE));
  setPiece(0, 4, Piece(PieceType::KING, Color::WHITE));
  setPiece(0, 5, Piece(PieceType::BISHOP, Color::WHITE));
  setPiece(0, 6, Piece(PieceType::KNIGHT, Color::WHITE));
  setPiece(0, 7, Piece(PieceType::ROOK, Color::WHITE));

  // Set up other pieces (Black)
  setPiece(7, 0, Piece(PieceType::ROOK, Color::BLACK));
  setPiece(7, 1, Piece(PieceType::KNIGHT, Color::BLACK));
  setPiece(7, 2, Piece(PieceType::BISHOP, Color::BLACK));
  setPiece(7, 3, Piece(PieceType::QUEEN, Color::BLACK));
  setPiece(7, 4, Piece(PieceType::KING, Color::BLACK));
  setPiece(7, 5, Piece(PieceType::BISHOP, Color::BLACK));
  setPiece(7, 6, Piece(PieceType::KNIGHT, Color::BLACK));
  setPiece(7, 7, Piece(PieceType::ROOK, Color::BLACK));
}

const Piece &Board::getPiece(int row, int col) const {
  return squares_[row][col];
}

void Board::setPiece(int row, int col, const Piece &piece) {
  squares_[row][col] = piece;
}

void Board::clear() {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      squares_[row][col] =
          Piece(); // Default constructor creates an empty piece
    }
  }
}

void Board::printBoard() const {
  for (int row = BOARD_SIZE - 1; row >= 0; --row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      const Piece &piece = getPiece(row, col);
      char symbol;
      switch (piece.getType()) {
      case PieceType::NONE:
        symbol = '.';
        break;
      case PieceType::PAWN:
        symbol = 'P';
        break;
      case PieceType::KNIGHT:
        symbol = 'N';
        break;
      case PieceType::BISHOP:
        symbol = 'B';
        break;
      case PieceType::ROOK:
        symbol = 'R';
        break;
      case PieceType::QUEEN:
        symbol = 'Q';
        break;
      case PieceType::KING:
        symbol = 'K';
        break;
      default:
        symbol = '?';
        break;
      }
      if (piece.getColor() == Color::BLACK) {
        symbol = tolower(symbol); // Lowercase for black pieces
      }
      std::cout << symbol << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

} // namespace chess
