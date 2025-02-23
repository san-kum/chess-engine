#include "move.hpp"

namespace chess {
Move::Move(int startRow, int startCol, int endRow, int endCol,
           PieceType promotionType)
    : startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol),
      promotionType(promotionType) {}

bool Move::operator==(const Move &other) const {
  return (startRow == other.startRow && startCol == other.startCol &&
          endRow == other.endRow && endCol == other.endCol &&
          promotionType == other.promotionType);
}

} // namespace chess
