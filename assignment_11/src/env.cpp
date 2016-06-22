/*
 * Daniel Vázquez
 * AIR SS16
 * Assignment 11
 * env.cpp
 * */

#include <env.hpp>
#include <iostream> 
#include <climits>

/*
 * Player two always plays as an agent
 * 
 * The  user can play as player one.
 * If the player wants to play, player1_agent is turned off and the user selects the desired 
 * algorithm for player two.
 * 
 * If the user does not want to play, player1_agent plays against player2_agent
 * where: 
 * 	player1_agent = minimax
 * 	player2_agent = alpa_beta
 * */

Environment::Environment() :
		puzzle(NUM_ROWS, std::vector<std::string>(NUM_COLS, ".")), num_tiles(
		NUM_ROWS * NUM_COLS), player1_symbol("X"), player2_symbol("O"), player1_agent(
				player1_symbol, player2_symbol), player2_agent(player2_symbol,
				player1_symbol), player1_agent_on(true), player2_agent_on(true), player1_agent_method(
				minimax), player2_agent_method(alpa_beta) {

}

void Environment::run() {

	std::cout << "Welcome to Connect4 game " << std::endl;
	std::cout << "Please select the game mode" << std::endl;

	int op = 0;

	std::cout << "(0) user vs computer (1) computer vs computer" << std::endl;
	std::cin >> op;

	if (op == 0) {
		player1_agent_on = false;

		std::cout << "Please select the search type for the computer"
				<< std::endl;
		std::cout << "(0) minimax (1) alpha_beta" << std::endl;
		std::cin >> op;
		if (op == 0) {
			std::cout << "Player 1 vs Player 2 (minimax)" << std::endl;
			player2_agent_method = minimax;
		} else {
			std::cout << "Player 1 vs Player 2 (alpha_beta) " << std::endl;
		}

	} else {
		std::cout << "Player 1 (minimax) vs Player 2 (alpha_beta)" << std::endl;

	}

	play();

}

void Environment::play() {
	std::cout << "New game " << std::endl;
	print_puzzle();

	bool player1_turn = false;
	bool player2_turn = false;

	while (!player1_turn && !player2_turn && num_tiles > 0) {
		player1_turn = make_move(Environment::player1);
		std::cout << "player1: " << player1 << std::endl;
		if (!player1_turn && num_tiles > 0) {
			player2_turn = make_move(Environment::player2);
			std::cout << "player2: " << player2 << std::endl;
		}
	}
	cout << "****************" << endl;
	if (!player1_turn && !player2_turn)
		std::cout << "Draw" << std::endl;
	else if (player1_turn)
		std::cout << "Player 1 won " << std::endl;
	else
		std::cout << "Player 2 won " << std::endl;

}

void Environment::generate_puzzle() {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			puzzle[rows][cols] = ".";
		}
	}
}

void Environment::print_puzzle() {
	for (int rows = 0; rows < NUM_ROWS; rows++) {

		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}

		std::cout << "|" << std::endl;
	}

	for (int cols = 0; cols < NUM_COLS; cols++) {
		std::cout << "-" << cols;
	}
	cout << std::endl << "Remaining tiles: " << num_tiles << std::endl;

}

int Environment::set_tile(int col, std::string player_symbol) {
	if (col >= 0 && col < NUM_COLS) {
		for (int row = NUM_ROWS - 1; row >= 0; row--) {
			if (puzzle[row][col] == ".") {
				puzzle[row][col] = player_symbol;
				num_tiles--;
				return 1;
			}
		}
	}

	return 0;
}

bool Environment::make_move(Player player) {
	int col;
	string player_symbol;

	std::cout << "***********************" << std::endl;
	std::cout << "Player " << player << std::endl;
	std::cout << "***********************" << std::endl;
	print_puzzle();

	if (player == Environment::player1) {
		player_symbol = player1_symbol;
		if (player1_agent_on) {
			std::cout << "Player 1 is computing next choice (minimax)  "
					<< std::endl;
			std::pair<int, int> result = player1_agent.minimax(puzzle,
					num_tiles);
			cout << "UT: " << result.second << std::endl;
			col = result.first;
		} else {
			std::cout << "Next move (0-" << NUM_COLS - 1 << "): " << std::endl;
			std::cin >> col;
		}
	} else {
		player_symbol = player2_symbol;
		if (player2_agent_on) {

			if (player2_agent_method == minimax) {
				std::cout << "Player 2 is computing next choice (minimax) "
						<< std::endl;
				std::pair<int, int> result = player1_agent.minimax(puzzle,
						num_tiles);
				cout << "UT: " << result.second << std::endl;
				col = result.first;
			} else if (player2_agent_method == alpa_beta) {
				std::cout << "Player 2 is computing next choice (alpha_beta)"
						<< std::endl;
				col = player2_agent.alpha_betha(puzzle, num_tiles, INT_MIN,
				INT_MAX).first;
			}
		}
	}

	std::cout << "Player" << player << " selected col: " << col << std::endl;
	set_tile(col, player_symbol);

	print_puzzle();

	return check_win(player);

}

//Check if the player in turn has won the game
bool Environment::check_win(Player player) {
	int counter;

	// reminde: num_tiles is the amount of remaining tiles

	std::string player_symbol;

	// There can be a soultion after at least seven moves.
	if (NUM_ROWS * NUM_COLS - 7 >= num_tiles) {

		if (player == Environment::player1) {
			player_symbol = player1_symbol;
		} else {
			player_symbol = player2_symbol;
		}

		counter = 0;
		for (int row = NUM_ROWS - 1; row >= 0; --row) {
			for (int col = 0; col < NUM_COLS; ++col) {
				if (puzzle[row][col] == player_symbol) {
					counter += 1;
				} else {
					counter = 0;
				}

				if (counter == 4) {
					return true;
				}
			}
			counter = 0;
		}

		counter = 0;
		for (int col = 0; col < NUM_COLS; ++col) {
			for (int row = NUM_ROWS - 1; row >= 0; --row) {
				if (puzzle[row][col] == player_symbol) {
					counter += 1;
				} else {
					counter = 0;
				}

				if (counter == 4) {
					return true;
				}
			}
			counter = 0;
		}

		if (NUM_ROWS * NUM_COLS - 11 >= num_tiles) {

			// check diagonal
			int counter_max = 0;
			int counter_min = 0;

			int last_row = NUM_ROWS - 1;
			int last_col = NUM_COLS - 1;

			// check bottom left corner
			int limit = 7;
			for (int col = last_col; col >= 3; --col) {
				counter_max = 0;
				counter_min = 0;

				for (int diag = 0; diag < limit; ++diag) {
					if (puzzle[last_row - diag][col - diag] == "X") {
						counter_min = 0;
						counter_max += 1;

						if (counter_max == 4) {
							return true;
						}
					}

					if (puzzle[last_row - diag][col - diag] == "O") {
						counter_max = 0;
						counter_min += 1;

						if (counter_min == 4) {
							return true;
						}
					}

					if (puzzle[last_row - diag][col - diag] == ".") {
						counter_max = 0;
						counter_min = 0;
					}
				}
				limit -= 1;
			}

			// check bottom right corner
			limit = 7;
			for (int col = 0; col < 4; ++col) {
				counter_max = 0;
				counter_min = 0;

				for (int diag = 0; diag < limit; ++diag) {
					if (puzzle[last_row - diag][col + diag] == "X") {
						counter_min = 0;
						counter_max += 1;

						if (counter_max == 4) {
							return true;
						}
					}

					if (puzzle[last_row - diag][col + diag] == "O") {
						counter_max = 0;
						counter_min += 1;

						if (counter_min == 4) {
							return true;
						}
					}

					if (puzzle[last_row - diag][col + diag] == ".") {
						counter_max = 0;
						counter_min = 0;
					}
				}
				limit -= 1;
			}

			// check top left corner
			limit = 6;
			for (int row = last_row; row >= 3; --row) {
				counter_max = 0;
				counter_min = 0;

				for (int diag = 0; diag < limit; ++diag) {
					if (puzzle[row - diag][last_col - diag] == "X") {
						counter_min = 0;
						counter_max += 1;

						if (counter_max == 4) {
							return true;
						}
					}

					if (puzzle[row - diag][last_col - diag] == "O") {
						counter_max = 0;
						counter_min += 1;

						if (counter_min == 4) {
							return true;
						}
					}

					if (puzzle[row - diag][last_col - diag] == ".") {
						counter_max = 0;
						counter_min = 0;
					}
				}
				limit -= 1;
			}

			// check top right corner.
			int first_col = 0;
			limit = 6;
			for (int row = last_row; row >= 3; --row) {
				counter_max = 0;
				counter_min = 0;

				for (int diag = 0; diag < limit; ++diag) {
					if (puzzle[row - diag][first_col + diag] == "X") {
						counter_min = 0;
						counter_max += 1;

						if (counter_max == 4) {
							return true;
						}
					}

					if (puzzle[row - diag][first_col + diag] == "O") {
						counter_max = 0;
						counter_min += 1;

						if (counter_min == 4) {
							return true;
						}
					}

					if (puzzle[row - diag][first_col + diag] == ".") {
						counter_max = 0;
						counter_min = 0;
					}
				}
				limit -= 1;
			}
		}
	}
	return false;
}

