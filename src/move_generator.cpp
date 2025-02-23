#include "move_generator.hpp"
#include "constants.hpp"
#include "move.hpp"

namespace chess {

std::vector<Move> MoveGenerator::generateMoves(const Board &board,
                                               Color color) const {
  std::vector<Move> moves;

  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      const Piece &piece = board.getPiece(row, col);
      if (piece.getColor() == color) {
        switch (piece.getType()) {
        case PieceType::PAWN:
          generatePawnMoves(board, row, col, moves);
          break;
        case PieceType::KNIGHT:
          generateKnightMoves(board, row, col, moves);
          break;
        case PieceType::BISHOP:
          generateBishopMoves(board, row, col, moves);
          break;
        case PieceType::ROOK:
          generateRookMoves(board, row, col, moves);
          break;
        case PieceType::QUEEN:
          generateQueenMoves(board, row, col, moves);
          break;
        case PieceType::KING:
          generateKingMoves(board, row, col, moves);
          break;
        case PieceType::NONE:
          break;
        }
      }
    }
  }
  return moves;
}

bool MoveGenerator::isValidSquare(int row, int col) const {
  return row >= 0 && row < BOARD_SIZE && col >= 0 && BOARD_SIZE;
}
bool MoveGenerator::isOpponentPiece(const Board &board, int row, int col,
                                    Color color) const {
  return isValidSquare(row, col) && !board.getPiece(row, col).isEmpty() &&
         board.getPiece(row, col).getColor() != color;
}

void MoveGenerator::generatePawnMoves(const Board &board, int row, int col,
                                      std::vector<Move> &moves) const {
  int direction =
      (board.getPiece(row, col).getColor() == Color::WHITE) ? 1 : -1;
  int startRow = (board.getPiece(row, col).getColor() == Color::WHITE) ? 1 : 6;
  if (isValidSquare(row + direction, col) &&
      board.getPiece(row + direction, col).isEmpty()) {
    moves.emplace_back(row, col, row + direction, col);
    if (row == startRow && isValidSquare(row + 2 * direction, col) &&
        board.getPiece(row + 2 * direction, col).isEmpty())
      moves.emplace_back(row, col, row + 2 * direction, col);
  }

  if (isValidSquare(row + direction, col + 1) &&
      isOpponentPiece(board, row + direction, col + 1,
                      board.getPiece(row, col).getColor()))
    moves.emplace_back(row, col, row + direction, col + 1);

  if (isValidSquare(row + direction, col - 1) &&
      isOpponentPiece(board, row + direction, col - 1,
                      board.getPiece(row, col).getColor()))
    moves.emplace_back(row, col, row + direction, col - 1);

  // TODO: Add End Passant
  // TODO Add Promotion
}

void MoveGenerator::generateKnightMoves(const Board &board, int row, int col,
                                        std::vector<Move> &moves) const {
  int offsets[][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                      {1, -2},  {1, 2},  {2, -1},  {2, 1}};
  for (auto offset : offsets) {
    int newRow = row + offset[0];
    int newCol = col + offset[1];
    if (isValidSquare(newRow, newCol)) {
      if (board.getPiece(newRow, newCol).isEmpty() ||
          isOpponentPiece(board, newRow, newCol,
                          board.getPiece(row, col).getColor()))
        moves.emplace_back(row, col, newRow, newCol);
    }
  }
}

void MoveGenerator::generateBishopMoves(const Board &board, int row, int col,
                                        std::vector<Move> &moves) const {
  int rowOffsets[] = {-1, -1, 1, 1};
  int colOffsets[] = {-1, 1, -1, 1};
  for (int i = 0; i < 4; ++i) {
    for (int j = 1; j < BOARD_SIZE; ++j) {
      int newRow = row + j * rowOffsets[i];
      int newCol = col + j * colOffsets[i];
      if (!isValidSquare(newRow, newCol))
        break;
      if (board.getPiece(newRow, newCol).isEmpty())
        moves.emplace_back(row, col, newRow, newCol);
      else if (isOpponentPiece(board, newRow, newCol,
                               board.getPiece(row, col).getColor())) {

        moves.emplace_back(row, col, newRow, newCol);
        break;
      } else
        break;
    }
  }
}

void MoveGenerator::generateRookMoves(const Board &board, int row, int col,
                                      std::vector<Move> &moves) const {
  int rowOffsets[] = {-1, -1, 1, 1};
  int colOffsets[] = {-1, 1, -1, 1};
  for (int i = 0; i < 4; ++i) {
    for (int j = 1; j < BOARD_SIZE; ++j) {
      int newRow = row + j * rowOffsets[i];
      int newCol = col + j * colOffsets[i];
      if (!isValidSquare(newRow, newCol))
        break;
      if (board.getPiece(newRow, newCol).isEmpty())
        moves.emplace_back(row, col, newRow, newCol);
      else if (isOpponentPiece(board, newRow, newCol,
                               board.getPiece(row, col).getColor())) {

        moves.emplace_back(row, col, newRow, newCol);
        break;
      } else
        break;
    }
  }
}

void MoveGenerator::generateQueenMoves(const Board &board, int row, int col,
                                       std::vector<Move> &moves) const {
  generateRookMoves(board, row, col, moves);
  generateBishopMoves(board, row, col, moves);
}

void MoveGenerator::generateKingMoves(const Board &board, int row, int col,
                                      std::vector<Move> &moves) const {
  int offsets[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                      {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  for (auto offset : offsets) {
    int newRow = row + offset[0];
    int newCol = col + offset[1];
    if (isValidSquare(newRow, newCol)) {
      if (board.getPiece(newRow, newCol).isEmpty() ||
          isOpponentPiece(board, newRow, newCol,
                          board.getPiece(row, col).getColor()))
        moves.emplace_back(row, col, newRow, newCol);
    }
  }
}

} // namespace chess
