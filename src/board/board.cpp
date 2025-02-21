#include "../../include/board/board.hpp"
#include <vector>

namespace chess {

Board::Board()
    : currentTurn(PieceColor::White), whiteCanCastleKingside(true),
      whiteCanCastleQueenSide(true), blackCanCastleKingside(true),
      blackCanCastleQueenSide(true), enPassantTarget(std::nullopt) {
  for (int i = 0; i < 8; ++i) {
    board[1][i] = {PieceType::Pawn, PieceColor::White};
    board[6][i] = {PieceType::Pawn, PieceColor::Black};
  }

  // Rooks
  board[0][0] = {PieceType::Rook, PieceColor::White};
  board[0][7] = {PieceType::Rook, PieceColor::White};
  board[7][0] = {PieceType::Rook, PieceColor::Black};
  board[7][7] = {PieceType::Rook, PieceColor::Black};

  // Knights
  board[0][1] = {PieceType::Knight, PieceColor::White};
  board[0][6] = {PieceType::Knight, PieceColor::White};
  board[7][1] = {PieceType::Knight, PieceColor::Black};
  board[7][6] = {PieceType::Knight, PieceColor::Black};

  // Bishops
  board[0][2] = {PieceType::Bishop, PieceColor::White};
  board[0][5] = {PieceType::Bishop, PieceColor::White};
  board[7][2] = {PieceType::Bishop, PieceColor::Black};
  board[7][5] = {PieceType::Bishop, PieceColor::Black};

  // Queens
  board[0][3] = {PieceType::Queen, PieceColor::White};
  board[7][3] = {PieceType::Queen, PieceColor::Black};

  // Kings
  board[0][4] = {PieceType::King, PieceColor::White};
  board[7][4] = {PieceType::King, PieceColor::Black};

  // Empty squares
  for (int i = 2; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = {PieceType::None, PieceColor::White};
    }
  }
}

Piece Board::getPiece(int row, int col) const {
  if (!isValidSquare(row, col))
    return {PieceType::None, PieceColor::White};
  return board[row][col];
}

PieceColor Board::getCurrentTurn() const { return currentTurn; }

bool Board::isValidSquare(int row, int col) const {
  return row >= 0 && row < 8 && col >= 0 && col < 8;
}

// Move Generation

std::vector<Move> Board::getLegalMoves(int row, int col) const {
  Piece piece = getPiece(row, col);
  if (piece.type == PieceType::None || piece.color != currentTurn)
    return {}; // no legal moves for an empty square

  std::vector<Move> moves;

  switch (piece.type) {
  case PieceType::Pawn:
    moves = generatePawnMoves(row, col);
    break;
  case PieceType::Knight:
    moves = generateKnightMoves(row, col);
    break;
  case PieceType::Bishop:
    moves = generateBishopMoves(row, col);
    break;
  case PieceType::Rook:
    moves = generateRookMoves(row, col);
    break;
  case PieceType::Queen:
    moves = generateQueenMoves(row, col);
    break;
  case PieceType::King:
    moves = generateKingMoves(row, col);
    break;
  default:
    break;
  }

  std::vector<Move> legalMoves;
  for (const auto &move : moves) {
    if (isLegalMove(move))
      legalMoves.push_back(move);
  }
  return legalMoves;
}

std::vector<Move> Board::getAllLegalMoves() const {
  std::vector<Move> allMoves;
  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      Piece piece = getPiece(row, col);
      if (piece.color == currentTurn) {
        std::vector<Move> pieceMoves = getLegalMoves(row, col);
        allMoves.insert(allMoves.end(), pieceMoves.begin(), pieceMoves.end());
      }
    }
  }
  return allMoves;
}

std::vector<Move> Board::generatePawnMoves(int row, int col) const {
  std::vector<Move> moves;
  Piece piece = getPiece(row, col);
  int direction = (piece.color == PieceColor::White) ? 1 : -1;

  // Forward Movement
  int forwardRow = row + direction;
  if (isValidSquare(forwardRow, col) &&
      getPiece(forwardRow, col).type == PieceType::None) {
    // promotion check
    if (forwardRow == 0 || forwardRow == 2)
      addMoveIfValid(moves, row, col, forwardRow, col);
    else
      addMoveIfValid(moves, row, col, forwardRow, col);
  }

  // Initial double step
  int startRow = (piece.color == PieceColor::White) ? 1 : 6;
  int doubleForwardRow = row + 2 * direction;

  if (row == startRow && isValidSquare(doubleForwardRow, col) &&
      getPiece(forwardRow, col).type == PieceType::None &&
      getPiece(doubleForwardRow, col).type == PieceType::None) {
    addMoveIfValid(moves, row, col, doubleForwardRow, col);
  }

  // Diagonals
  int captureCols[] = {col, -1, col + 1};
  for (int captureCol : captureCols) {
    if (isValidSquare(forwardRow, captureCol)) {
      Piece targetPiece = getPiece(forwardRow, captureCol);
      if (targetPiece.type != PieceType::None &&
          targetPiece.color != piece.color) {
        if (forwardRow == 0 || forwardRow == 7)
          addMoveIfValid(moves, row, col, forwardRow, captureCol);
        else
          addMoveIfValid(moves, row, col, forwardRow, captureCol);
      } else if (enPassantTarget && *enPassantTarget == captureCol &&
                 forwardRow == (piece.color == PieceColor::White ? 5 : 2)) {
        addMoveIfValid(moves, row, col, forwardRow, captureCol);
      }
    }
  }
  return moves;
}

std::vector<Move> Board::generateKnightMoves(int row, int col) const {
  std::vector<Move> moves;
  int possibleMoves[8][2] = {{row - 2, col - 1}, {row - 2, col + 1},
                             {row - 1, col - 2}, {row - 1, col + 2},
                             {row + 1, col - 2}, {row + 1, col + 2},
                             {row + 2, col - 1}, {row + 2, col + 1}};
  for (int i = 0; i < 8; ++i) {
    int newRow = possibleMoves[i][0];
    int newCol = possibleMoves[i][1];
    addMoveIfValid(moves, row, col, newRow, newCol);
  }
  return moves;
}

}; // namespace chess
