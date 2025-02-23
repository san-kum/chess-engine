#ifndef MOVE_GENERATOR_HPP
#define MOVE_GENERATOR_HPP

#include "board.hpp"
#include "move.hpp"
#include <vector>
namespace chess {
class MoveGenerator {
public:
  std::vector<Move> generateMoves(const Board &board, Color color) const;

private:
  void generatePawnMoves(const Board &board, int row, int col,
                         std::vector<Move> &moves) const;
  void generateKnightMoves(const Board &board, int row, int col,
                           std::vector<Move> &moves) const;
  void generateBishopMoves(const Board &board, int row, int col,
                           std::vector<Move> &moves) const;
  void generateRookMoves(const Board &board, int row, int col,
                         std::vector<Move> &moves) const;
  void generateQueenMoves(const Board &board, int row, int col,
                          std::vector<Move> &moves) const;
  void generateKingMoves(const Board &board, int row, int col,
                         std::vector<Move> &moves) const;
  bool isValidSquare(int row, int col) const;
  bool isOpponentPiece(const Board &board, int row, int col, Color color) const;
};
} // namespace chess

#endif // MOVE_GENERATOR_HPP
