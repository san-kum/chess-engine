#include "piece.hpp"

namespace chess {

Piece::Piece(PieceType type, Color color) : type_(type), color_(color) {}

PieceType Piece::getType() const { return type_; }

Color Piece::getColor() const { return color_; }

bool Piece::isEmpty() const { return type_ == PieceType::NONE; }

} // namespace chess
