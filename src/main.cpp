#include <map>
#include <iostream>
#include <cmath>

using namespace std;

enum BoardPiece
{
  X,
  O
};

class Player
{
private:
  BoardPiece board_piece;
  string name;
  Player *next{nullptr};

public:
  Player()
  {
    string name;
    string piece;
    cout << "type in a username: ";
    cin >> name;
    cout << "choose your board piece (x or o): ";
    cin >> piece;
    this->set_name(name);
    this->set_board_piece(piece);
  }
  auto get_next() -> Player *
  {
    return this->next;
  }
  auto set_next(Player *player) -> void
  {
    this->next = player;
  }
  auto set_board_piece(string bp) -> void
  {
    BoardPiece piece;
    if (bp == "x" || bp == "X")
    {
      piece = BoardPiece::X;
    }
    else if (bp == "o" || bp == "O")
    {
      piece = BoardPiece::O;
    }
    else
    {
      throw runtime_error("Incorrect board piece submitted.");
    }
    // mount the board piece onto the player.
    this->board_piece = piece;
  }
  auto get_board_piece() -> BoardPiece
  {
    return this->board_piece;
  }
  auto set_name(string name) -> void
  {
    this->name = name;
  }
  auto get_name() -> string
  {
    return this->name;
  };
};

class Board
{
private:
  const int size;
  map<int, Player *> Map;

public:
  Board(int size) : size{size}
  {
    for (int i = 0; i < this->size; i++)
    {
      this->Map.insert(make_pair((i + 1), nullptr));
    }
  }
  auto print_board() -> void
  {
    int square_root = sqrt(this->size);

    for (int i = 0; i < size; i++)
    {
      string board_piece;
      if (Map[i] == nullptr)
        board_piece = to_string((i + 1));
      else if (Map[i]->get_board_piece() == BoardPiece::X)
        board_piece = "X";
      else if (Map[i]->get_board_piece() == BoardPiece::O)
        board_piece = "O";
      else
      {
        throw runtime_error("Couldnt match the board piece");
      }

      cout << " " << board_piece << ((i + 1) % square_root == 0 && i > 0 ? "\n" : "");
    }
  }
  auto get_location(int loc) -> Player *
  {
    return Map[(loc - 1)];
  }
  auto insert_piece(int loc, Player *player) noexcept -> bool
  {
    if (this->get_location(loc) == nullptr && loc > 0 && loc <= this->size)
    {
      this->Map[(loc - 1)] = player;
      return true;
    }
    cout << "This spot is already taken..." << endl;
    return false;
  }
  auto is_winning_move(int loc) noexcept -> bool
  {
    int square_root = sqrt(this->size);
    // todo: finish this.
    // top left corner.
    if (loc == 1)
    {
      Player *player = Map[loc - 1];
      // horizontal
      if (player != nullptr && player == Map[loc] && player == Map[loc + 1])
      {
        return true;
      }
      // vertical
      else if (player == Map[(loc - 1) + square_root] && player == Map[(loc - 1) + (square_root * 2)])
      {
        return true;
      }
      // diagnal
      else if (player == Map[(loc + 1) + square_root] && player == Map[(loc + 2) + (square_root * 2)])
      {
        return true;
      }
    }
    else if (loc == 2)
    {
      Player *player = Map[loc - 1];
    }
    return false;
  }
};

class Game
{
private:
  Player *player;

public:
  Board board;
  Game(Player *player, int board_size)
      : player{player}, board{board_size}
  {
  }
  auto play() -> void
  {
    int loc;
    for (; player != nullptr; player = player->get_next())
    {
      // player actions
      cout << "   Tic Tac Toe" << endl;
      this->board.print_board();
      do
      {
        cout << player->get_name() << " enter the location of your board piece (1-9): ";
        cin >> loc;
      } while (!this->board.insert_piece(loc, player));
      if (this->board.is_winning_move(loc))
      {
        cout << "Congrats " << player->get_name() << " you won!";
        break;
      }
    };
  }
};

static int MAX_PLAYERS = 2;

auto main() -> int
{
  string msg;
  while (true)
  {
    cout << "Player 1" << endl;
    Player player1{};
    cout << "Player 2" << endl;
    Player player2{};

    // setting a circular iterator.
    player1.set_next(&player2);
    player2.set_next(&player1);

    Game game(&player1, 9);
    game.play();

    cout << " would you like to play again? (y or Y): ";
    cin >> msg;
    if (msg == "n" || msg == "N")
      break;
  }
  return 0;
}