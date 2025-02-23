#include "board.hpp"
#include "catch_amalgamated.hpp" // Include Catch2
#include "move_generator.hpp"

TEST_CASE("Pawn Moves", "[MoveGenerator]") {
  chess::MoveGenerator moveGen;
  chess::Board board; // Use the default constructor for the initial board state

  SECTION("Initial White Pawn Moves") {
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    // Check for the expected number of initial pawn moves (2 per pawn * 8 pawns
    // = 16 moves)
    // + 4 moves for knights = 20.
    REQUIRE(moves.size() == 20);

    // Check for specific pawn moves (using the overloaded == operator in Move)
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(1, 0, 2, 0)) !=
            moves.end()); // a2 to a3
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(1, 0, 3, 0)) !=
            moves.end()); // a2 to a4
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(1, 1, 2, 1)) !=
            moves.end()); // b2 to b3
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(1, 1, 3, 1)) !=
            moves.end()); // b2 to b4
                          // ... add checks for other pawns ...
  }
  SECTION("Initial Black Pawn Moves") {
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::BLACK);
    REQUIRE(moves.size() == 20);
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(6, 0, 5, 0)) !=
            moves.end());
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(6, 0, 4, 0)) !=
            moves.end());
  }

  SECTION("Pawn Captures") {
    board.clear();
    board.setPiece(3, 3,
                   chess::Piece(chess::PieceType::PAWN, chess::Color::WHITE));
    board.setPiece(4, 4,
                   chess::Piece(chess::PieceType::PAWN, chess::Color::BLACK));
    board.setPiece(4, 2,
                   chess::Piece(chess::PieceType::KNIGHT, chess::Color::BLACK));

    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    REQUIRE(moves.size() == 3); // One forward, two captures
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(3, 3, 4, 4)) !=
            moves.end()); // Capture to d4
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(3, 3, 4, 2)) !=
            moves.end()); // Capture to b4
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(3, 3, 4, 3)) !=
            moves.end());
  }
}
TEST_CASE("Knight Moves", "[MoveGenerator]") {
  chess::MoveGenerator moveGen;
  chess::Board board;

  SECTION("Initial Knight Moves") {
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(0, 1, 2, 0)) !=
            moves.end());
    REQUIRE(std::find(moves.begin(), moves.end(), chess::Move(0, 1, 2, 2)) !=
            moves.end());
  }
  SECTION("Knight Moves Middle of the Board") {
    board.clear();
    board.setPiece(3, 3,
                   chess::Piece(chess::PieceType::KNIGHT, chess::Color::WHITE));
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    REQUIRE(moves.size() == 8); // A knight in the center has 8 possible moves
  }
}
TEST_CASE("Bishop, Rook and Queen Moves", "[MoveGenerator]") {
  chess::MoveGenerator moveGen;
  chess::Board board;
  board.clear();
  SECTION("Bishop Moves") {
    board.setPiece(3, 3,
                   chess::Piece(chess::PieceType::BISHOP, chess::Color::WHITE));
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    REQUIRE(moves.size() == 13);
  }
  SECTION("Rook Moves") {
    board.setPiece(3, 3,
                   chess::Piece(chess::PieceType::ROOK, chess::Color::WHITE));
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    REQUIRE(moves.size() == 14);
  }
  SECTION("Queen Moves") {
    board.setPiece(3, 3,
                   chess::Piece(chess::PieceType::QUEEN, chess::Color::WHITE));
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    REQUIRE(moves.size() == 27);
  }
}
TEST_CASE("King Moves", "[MoveGenerator]") {
  chess::MoveGenerator moveGen;
  chess::Board board;
  board.clear();
  SECTION("King Moves") {
    board.setPiece(3, 3,
                   chess::Piece(chess::PieceType::KING, chess::Color::WHITE));
    std::vector<chess::Move> moves =
        moveGen.generateMoves(board, chess::Color::WHITE);
    REQUIRE(moves.size() == 8);
  }
}
