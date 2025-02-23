#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdint>

namespace chess {

enum class Color : uint8_t { WHITE, BLACK };

enum class PieceType : uint8_t {
  NONE, // Represents an empty square
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING
};

constexpr int BOARD_SIZE = 8;

} // namespace chess

#endif // CONSTANTS_HPP
