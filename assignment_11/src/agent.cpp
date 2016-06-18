/*
 * Daniel Vázquez, Kiran Vasudev, Patrick Nagel
 * AIR SS16
 * Assignment 11
 * agent.cpp
 * */
#include <agent.hpp>
#include <climits>
#include <cmath>
#include <utility> 
#include <string>

/*
 * Max_symbol: The simbol used by the agent Max
 * Min_symbol: The simbos used be the agent Min
 * */
Agent::Agent(std::string max_symbol, std::string min_symbol) :
		max_symbol(max_symbol), min_symbol(min_symbol), total_tiles(
		NUM_COLS * NUM_ROWS) {

}

Agent::~Agent() {

}

//minimax initial method, returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::minimax(Puzzle puzzle, int free_tiles) {

	Puzzle forcast_puzzle = puzzle;
	int input_col = 0;
	int round = NUM_ROWS * NUM_COLS - free_tiles;
	std::pair<int, int> result;

	// If depth an even number, then it is the turn of max agent,...
	if (round % 2 == 0) {
		result = max(forcast_puzzle, free_tiles, input_col, 0);

		// ... otherwise it is the turn of min agent.
	} else {
		result = min(forcast_puzzle, free_tiles, input_col, 0);
	}

	// return std::make_pair<int, int>(col, utility_value);
	return result;
}

//max returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::max(Puzzle puzzle, int free_tiles, int input_col, int depth) {

	std::pair<int, int> max_pair;
	int max_uv = 0;
	int max_col = 0;

	int current_utility_value = utility(puzzle, free_tiles, "O");
	if (free_tiles == 0 || depth == MINIMAX_MAX_DEPTH) {
		return std::make_pair(input_col, current_utility_value);
	}

	if (current_utility_value >= 1000 || current_utility_value <= -1000) {
		return std::make_pair(input_col, current_utility_value);
	}

	for (int col = 0; col < NUM_COLS; ++col) {

		int pos = get_free_pos(puzzle, col);
		if (pos == -1) {
			continue;
		}

		puzzle[pos][col] = "X";
		free_tiles -= 1;

		depth += 1;
		max_pair = min(puzzle, free_tiles, col, depth);
		if (max_pair.second > max_uv) {
			max_uv = max_pair.second;
			max_col = col;
		}

		puzzle[pos][col] = ".";
		free_tiles += 1;
		depth -= 1;
	}
	max_pair = std::make_pair(max_col, max_uv);

	return max_pair;
}

//min returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::min(Puzzle puzzle, int free_tiles, int input_col, int depth) {

	std::pair<int, int> min_pair;
	int min_uv = 0;
	int min_col = 0;

	int current_utility_value = utility(puzzle, free_tiles, "X");
	if (free_tiles == 0 || depth == MINIMAX_MAX_DEPTH) {
		return std::make_pair(input_col, current_utility_value);
	}

	if (current_utility_value > 1000 || current_utility_value < -1000) {
		return std::make_pair(input_col, current_utility_value);
	}

	for (int col = 0; col < NUM_COLS; ++col) {
		int pos = get_free_pos(puzzle, col);
		if (pos == -1) {
			continue;
		}

		puzzle[pos][col] = "O";
		free_tiles -= 1;

		depth += 1;
		min_pair = max(puzzle, free_tiles, col, depth);
		if (min_pair.second < min_uv) {
			min_uv = min_pair.second;
			min_col = col;
		}

		puzzle[pos][col] = ".";
		free_tiles += 1;
		depth -= 1;
	}
	min_pair = std::make_pair(min_col, min_uv);

	return min_pair;
}

int Agent::get_free_pos(Puzzle puzzle, int col) {
	int counter = 0;
//	for (int row = 0; row < NUM_ROWS; ++row) {
//		if (puzzle[row][col] != ".") {
//			counter += 1;
//		}
//	}
//
//	// In case that the column is already full, return a -1.
//	if (counter == NUM_ROWS - 1) {
//		return -1;
//
//		// Otherwise return number of row, where to insert symbol.
//	} else {
//		return counter;
//	}
	int last_row = NUM_ROWS - 1;
	for (int row = last_row; row >= 0; --row) {
		if (puzzle[row][col] != ".") {
			counter += 1;
		} else {
			return last_row - counter;
		}
	}
	// In case that the column is already full, return a -1.
	if (counter == NUM_ROWS) {
		return -1;

		// Otherwise return number of row, where to insert symbol.
	} else {
		return counter;
	}
}

//alpha_beta returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::alpha_betha(Puzzle puzzle, int free_tiles, int alpha,
		int beta) {
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

//max_value returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::max_alpha_betha(Puzzle puzzle, int free_tiles,
		int depth, int alpha, int beta) {
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

//max_value returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::min_alpha_betha(Puzzle puzzle, int free_tiles,
		int depth, int alpha, int beta) {
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

/*
 * Utility method: Computes the numerical value of the give puzzle
 */
int Agent::utility(Puzzle puzzle, int free_tiles, std::string player_symbol) {

	int utility_value = 138;

	int evaluation_table[NUM_ROWS][NUM_COLS] = { { 3, 4, 5, 7, 5, 4, 3 }, { 4,
			6, 8, 10, 8, 6, 4 }, { 5, 8, 11, 13, 11, 8, 5 }, { 6, 9, 12, 14, 12, 9, 6 }, { 5, 8, 11, 13, 11,
			8, 5 }, { 4, 6, 8, 10, 8, 6, 4 }, { 3, 4, 5, 7, 5, 4, 3 } };

	for (int row = 0; row < NUM_ROWS; ++row) {
		for (int col = 0; col < NUM_COLS; ++col) {
			if (puzzle[row][col] == "X") {
				utility_value += evaluation_table[row][col];
			}
			if (puzzle[row][col] == "O") {
				utility_value -= evaluation_table[row][col];
			}
		}
	}

	bool game_over = check_winning(puzzle, free_tiles, player_symbol);
	if (game_over) {
		if (player_symbol == "O") {
			utility_value = -(1000 + free_tiles);
		} else {
			utility_value = 1000 + free_tiles;
		}
	}

	return utility_value;
}

bool Agent::check_winning(Puzzle puzzle, int free_tiles,
		std::string player_symbol) {

	int counter;

	// There can be a soultion after at least seven moves.
	if (7 <= NUM_ROWS * NUM_COLS - free_tiles) {

		// Check if there are four in a row.
		for (int row = 0; row < NUM_ROWS; ++row) {
			counter = 0;
			for (int col = 0; col < NUM_COLS; ++col) {
				if (puzzle[row][col] == player_symbol) {
					counter += 1;
					if (counter >= 4) {
						return true;
					}
				} else {
					if (puzzle[row][col] == "."
							&& puzzle[row][col] != player_symbol)
						counter = 0;
				}
			}

		}

		// Check if there are four in a column.
		for (int col = 0; col < NUM_COLS; ++col) {
			counter = 0;
			for (int row = 0; row < NUM_ROWS; ++row) {
				if (puzzle[row][col] == player_symbol) {
					counter += 1;
					if (counter == 4) {
						return true;
					}
				} else {
					if (puzzle[row][col] != player_symbol) {
						counter = 0;
					}
				}
			}
		}

		// Four tiles in diagonal are at least possible after 11 moves.
		if (11 <= NUM_ROWS * NUM_COLS - free_tiles) {
			// Check if there are four in diagonal.
			for (int row = NUM_ROWS - 1; row >= 0; --row) {
				for (int col = 0; col < NUM_COLS; ++col) {
					if (puzzle[row][col] == player_symbol) {
						counter = 0;
						// First check diagonal going to the left.
						for (int diag = 1; diag < 4; ++diag) {
							if (row - diag >= 0  && col - diag >= 0) {
								if (puzzle[row - diag][col - diag]
										== player_symbol) {
									counter += 1;
									if (counter == 3) {
										return true;
									} else {
										break;
									}
								}
							}
						}

						// Otherwise check the diagonal going to the right.
						counter = 0;
						for (int diag = 1; diag < 4; ++diag) {
							if (row - diag >= 0 && col + diag < NUM_COLS) {
								if (puzzle[row - diag][col + diag]
										== player_symbol) {
									counter += 1;
									if (counter == 3) {
										return true;
									} else {
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

