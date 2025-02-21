#pragma once

#include <optional>
#include <vector>

namespace chess {
enum class PieceType { None, Pawn, Knight, Bishop, Rook, Queen, King };
enum class PieceColor { White, Black };

struct Piece {
  PieceType type;
  PieceColor color;
};

struct Move {
  int fromRow;
  int fromCol;
  int toRow;
  int toCol;
  std::optional<PieceType> promotionType;
};

class Board {
public:
  Board();

  // Accessors
  Piece getPiece(int row, int col) const;
  PieceColor getCurrentTurn() const;

  // Move Generation and Validation
  std::vector<Move> getLegalMoves(int row, int col) const;
  std::vector<Move> getAllLegalMoves() const;
  bool isLegalMove(const Move &move) const;

  // Move Application
  void applyMove(const Move &move);
  void undoMove(const Move &move);

  bool isInCheck(PieceColor color) const;
  bool isInCheckMate(PieceColor color) const;
  bool isInStaleMate(PieceColor color) const;

private:
  Piece board[8][8];
  PieceColor currentTurn;

  bool whiteCanCastleKingside;
  bool whiteCanCastleQueenSide;
  bool blackCanCastleKingside;
  bool blackCanCastleQueenSide;
  std::optional<int> enPassantTarget;
  std::vector<Move> moveHistory;

  bool isValidSquare(int row, int col) const;
  std::vector<Move> generatePawnMoves(int row, int col) const;
  std::vector<Move> generateKnightMoves(int row, int col) const;
  std::vector<Move> generateBishopMoves(int row, int col) const;
  std::vector<Move> generateRookMoves(int row, int col) const;
  std::vector<Move> generateQueenMoves(int row, int col) const;
  std::vector<Move> generateKingMoves(int row, int col) const;
  std::vector<Move> generateSlidingMoves(int row, int col, int rowDir,
                                         int colDir) const;

  bool isUnderAttack(int row, int col, PieceColor attackColor) const;
  void addMoveIfValid(std::vector<Move> &moves, int fromRow, int fromCol,
                      int toRow, int toCol) const;
};

}; // namespace chess
