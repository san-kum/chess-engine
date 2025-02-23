#ifndef PIECE_HPP
#define PIECE_HPP

#include "constants.hpp"

namespace chess {

class Piece {
public:
  Piece(PieceType type = PieceType::NONE, Color color = Color::WHITE);

  PieceType getType() const;
  Color getColor() const;
  bool isEmpty() const;

private:
  PieceType type_;
  Color color_;
};

} // namespace chess

#endif // PIECE_HPP
