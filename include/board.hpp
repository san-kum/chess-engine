#ifndef BOARD_HPP
#define BOARD_HPP

#include "constants.hpp"
#include "piece.hpp"
#include <array>

namespace chess {

class Board {
public:
  Board(); // Constructor for initial setup

  const Piece &getPiece(int row,
                        int col) const; // Access a piece at a given square
  void setPiece(int row, int col,
                const Piece &piece); // Place a piece on the board
  void printBoard() const;           // print the board for debugging purpose.
  void clear();                      // Clear the board

private:
  std::array<std::array<Piece, BOARD_SIZE>, BOARD_SIZE> squares_;
};

} // namespace chess

#endif // BOARD_HPP
