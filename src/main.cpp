#include "board.hpp"
#include "move_generator.hpp"
#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {

  chess::Board board;
  board.printBoard();

  chess::MoveGenerator moveGen;
  std::vector<chess::Move> whiteMoves =
      moveGen.generateMoves(board, chess::Color::WHITE);

  std::cout << "Generated move for White:\n";
  for (const auto &move : whiteMoves) {
    std::cout << "Start: (" << move.startRow << ", " << move.startCol
              << ") End: (" << move.endRow << ", " << move.endCol << ")\n";
  }

  std::vector<chess::Move> blackMoves =
      moveGen.generateMoves(board, chess::Color::BLACK);

  std::cout << "\nGenerated move for White:\n";
  for (const auto &move : blackMoves) {
    std::cout << "Start: (" << move.startRow << ", " << move.startCol
              << ") End: (" << move.endRow << ", " << move.endCol << ")\n";
  }

  // SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Could not be initlaized! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }
  std::cout << "SDL initlaized successfully\n";

  SDL_Delay(1000);

  SDL_Quit();
  return 0;
}
