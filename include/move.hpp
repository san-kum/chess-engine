#ifndef MOVE_HPP
#define MOVE_HPP

#include "constants.hpp"
namespace chess {
struct Move {
  int startRow;
  int startCol;
  int endRow;
  int endCol;
  PieceType promotionType;

  Move(int startRow, int startCol, int endRow, int endCol,
       PieceType promotionType = PieceType::NONE);
  bool operator==(const Move &other) const;
};
} // namespace chess
#endif
