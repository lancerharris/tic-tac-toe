#include <iostream>
#include <vector>
#include <string>

void print_grid(const std::vector<std::vector<std::string>> &matrix)
{
  std::string grid_header = "    1   2   3";
  std::string grid_row_spacer = "    ---------";

  std::string row_one = "A   " + matrix[0][0] + " | " + matrix[0][1] + " | " + matrix[0][2];
  std::string row_two = "B   " + matrix[1][0] + " | " + matrix[1][1] + " | " + matrix[1][2];
  std::string row_three = "C   " + matrix[2][0] + " | " + matrix[2][1] + " | " + matrix[2][2];

  std::cout << grid_header << std::endl;
  std::cout << row_one << std::endl;
  std::cout << grid_row_spacer << std::endl;
  std::cout << row_two << std::endl;
  std::cout << grid_row_spacer << std::endl;
  std::cout << row_three << std::endl;
}

bool check_winner(const std::vector<std::vector<std::string>> &matrix, const std::string &token)
{
  // Check rows
  for (int i = 0; i < 3; i++)
  {
    if (matrix[i][0] == token && matrix[i][1] == token && matrix[i][2] == token)
    {
      return true;
    }
  }

  // Check columns
  for (int i = 0; i < 3; i++)
  {
    if (matrix[0][i] == token && matrix[1][i] == token && matrix[2][i] == token)
    {
      return true;
    }
  }

  // Check diagonals
  if (matrix[0][0] == token && matrix[1][1] == token && matrix[2][2] == token)
  {
    return true;
  }
  if (matrix[0][2] == token && matrix[1][1] == token && matrix[2][0] == token)
  {
    return true;
  }

  return false;
}

bool is_cell_free(const std::vector<std::vector<int>> &ind_matrix, int i, int j)
{
  return ind_matrix[i][j] == 0;
}

void update_matrices(std::vector<std::vector<int>> &ind_matrix, std::vector<std::vector<std::string>> &matrix, int i, int j, const std::string &player_token)
{
  ind_matrix[i][j] = 1;
  matrix[i][j] = player_token;
}

std::pair<int, int> get_user_input(const std::string &input)
{
  if (input == "A1")
    return {0, 0};
  if (input == "A2")
    return {0, 1};
  if (input == "A3")
    return {0, 2};
  if (input == "B1")
    return {1, 0};
  if (input == "B2")
    return {1, 1};
  if (input == "B3")
    return {1, 2};
  if (input == "C1")
    return {2, 0};
  if (input == "C2")
    return {2, 1};
  if (input == "C3")
    return {2, 2};
  return {-1, -1}; // Invalid input
}

int main()
{
  std::vector<std::vector<std::string>> matrix(3, std::vector<std::string>(3, " "));
  std::vector<std::vector<int>> ind_matrix(3, std::vector<int>(3, 0));

  std::cout << "Welcome to Tic-Tac-Toe" << std::endl;
  std::cout << "Here is your grid:" << std::endl;

  print_grid(matrix);

  std::cout << "First player will be x, second player will be o" << std::endl;

  bool winner_found = false;
  int current_player = 0;
  std::string player_token;
  int move_count = 0;

  while (!winner_found || move_count < 9)
  {
    if (current_player == 0)
    {
      std::cout << "Player 1's turn (x)" << std::endl;
      player_token = 'x';
    }
    else
    {
      std::cout << "Player 2's turn (o)" << std::endl;
      player_token = 'o';
    }

    std::cout << "Make a choice for your position, like A1" << std::endl;

    std::string user_input;
    std::cin >> user_input;

    std::pair<int, int> grid_pos = get_user_input(user_input);
    int i = grid_pos.first;
    int j = grid_pos.second;

    if (i != -1 && j != -1 && is_cell_free(ind_matrix, i, j))
    {
      update_matrices(ind_matrix, matrix, i, j, player_token);
      print_grid(matrix);
      if (check_winner(matrix, player_token))
      {
        std::cout << "Player " << (current_player + 1) << " wins!" << std::endl;
        break;
      }
      current_player = (current_player + 1) % 2;
      move_count++;
    }
    else
    {
      std::cout << "Invalid or occupied position, try again." << std::endl;
    }
  }

  if (!winner_found)
  {
    std::cout << "It's a draw!" << std::endl;
  }
}
