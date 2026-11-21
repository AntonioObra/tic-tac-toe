#include <iostream>

int numberOfEmptyFields = 9;
bool isGameOver = false;
std::string currentPlayer = "X";
std::array<std::array<std::string, 3>, 3> board;

bool playMove(std::string input);
void showBoard(bool goldBoard = false);
bool didPlayerWin();

std::string winnerColorStart = "\033[1;32m";
std::string winnerColorEnd = "\033[m";

std::string loserColorStart = "\033[1;31m";
std::string loserColorEnd = "\033[m";

int main() {
  std::string input;

  std::cout << "Hy welcome to Tic Tac Toe!" << std::endl;

  while (!isGameOver) {
    showBoard();

    if (numberOfEmptyFields == 0) {
      std::cout << "Game Over..." << std::endl;
      break;
    }

    std::cout << "Place your " << currentPlayer << " move: ";
    std::cin >> input;

    if (!playMove(input)) {
      continue;
    }

    if (didPlayerWin()) {
      std::cout << "Congrats player:" << currentPlayer << "! You WON!"
                << std::endl;

      showBoard(true);
      break;
    };

    if (currentPlayer == "X") {
      currentPlayer = "O";
    } else {
      currentPlayer = "X";
    }
  }

  return 0;
}

bool playMove(std::string input) {
  if (input.length() != 2) {
    std::cout << "Your move needs to be 2 chars: Example 02... Try again."
              << std::endl;
    return false;
  }

  int row = input[0] - '0';
  int col = input[1] - '0';

  if (row < 0 || row > 2 || col < 0 || col > 2) {
    std::cout << "Your move must be in the range of the board: 00, 01, 02, 10, "
                 "11, 12, 20, 21, 22... Try again."
              << std::endl;
    return false;
  }

  if (!board[row][col].empty()) {
    std::cout << "This move cannot be played as it has already been played:"
              << std::endl;
    return false;
  }

  board[row][col] = currentPlayer;
  numberOfEmptyFields--;

  return true;
}

void showBoard(bool goldBoard) {
  std::cout << "\033[1;33m     0   1   2\033[0m" << std::endl;

  for (unsigned int i = 0; i < 3; i++) {
    std::cout << "\033[1;33m " << i << "\033[0m";

    for (unsigned int j = 0; j < 3; j++) {
      std::cout << " | ";

      std::string value = !board[i][j].empty() ? board[i][j] : " ";

      if (goldBoard) {
        if (value == currentPlayer) {
          std::cout << winnerColorStart << value << winnerColorEnd;
        } else if (value != " ") {
          std::cout << loserColorStart << value << loserColorEnd;
        } else {
          std::cout << value;
        }
      } else {
        std::cout << value;
      }
    }

    std::cout << " |" << std::endl;
  }
}

bool didPlayerWin() {
  if (numberOfEmptyFields > 4) {
    return false;
  }

  // Check row
  for (unsigned int i = 0; i < 3; i++) {
    int sameStreak = 0;

    for (unsigned int j = 0; j < 3; j++) {
      if (board[i][j] != currentPlayer) {
        break;
      }

      sameStreak++;
    }

    if (sameStreak == 3) {
      return true;
    }
  }

  // Check col
  for (unsigned int i = 0; i < 3; i++) {
    int sameStreak = 0;

    for (unsigned int j = 0; j < 3; j++) {
      if (board[j][i] != currentPlayer) {
        break;
      }

      sameStreak++;
    }

    if (sameStreak == 3) {
      return true;
    }
  }

  // Check diagonal
  if (board[0][0] == currentPlayer && board[1][1] == currentPlayer &&
      board[2][2] == currentPlayer) {
    return true;
  }

  if (board[0][2] == currentPlayer && board[1][1] == currentPlayer &&
      board[2][0] == currentPlayer) {
    return true;
  }

  return false;
}
