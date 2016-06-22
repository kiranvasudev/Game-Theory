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
std::pair<int, int> Agent::max(Puzzle puzzle, int free_tiles, int input_col,
		int depth) {

	int full_col = 0;
	std::pair<int, int> max_pair;
	int max_uv = 0;
	int max_col = 0;

	int current_utility_value = utility(puzzle, free_tiles, "O");
	if (free_tiles == 0) {
		return std::make_pair(input_col, current_utility_value);
	}

	if (current_utility_value == 10000 || current_utility_value == -10000) {
		return std::make_pair(input_col, current_utility_value);
	}

	if (depth == MINIMAX_MAX_DEPTH) {
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
		if (max_pair.second == 10000) {
			max_pair.first = col;
			return max_pair;
		}

		if (col == 0 || (full_col > 0 && (max_col == 0 && max_uv == 0))) {
			max_uv = max_pair.second;
			max_col = col;
			full_col = 0;
		}
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
std::pair<int, int> Agent::min(Puzzle puzzle, int free_tiles, int input_col,
		int depth) {

	int full_col = 0;
	std::pair<int, int> min_pair;
	int min_uv = 0;
	int min_col = 0;

	int current_utility_value = utility(puzzle, free_tiles, "X");
	if (free_tiles == 0) {
		return std::make_pair(input_col, current_utility_value);
	}

	if (current_utility_value == 10000 || current_utility_value == -10000) {
		return std::make_pair(input_col, current_utility_value);
	}

	if (depth == MINIMAX_MAX_DEPTH) {
		return std::make_pair(input_col, current_utility_value);
	}

	for (int col = 0; col < NUM_COLS; ++col) {
		int pos = get_free_pos(puzzle, col);
		if (pos == -1) {
			full_col = 1;
			continue;
		}

		puzzle[pos][col] = "O";
		free_tiles -= 1;

		depth += 1;
		min_pair = max(puzzle, free_tiles, col, depth);

		if (min_pair.second == -10000) {
			min_pair.first = col;
			return min_pair;
		}

		if (col == 0 || (full_col > 0 && (min_col == 0 && min_uv == 0))) {
			min_uv = min_pair.second;
			min_col = col;
			full_col = 0;
		}
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

	int last_row = NUM_ROWS - 1;
	for (int row = last_row; row >= 0; --row) {
		if (puzzle[row][col] == ".") {
			return row;
		}
	}

	return -1;
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

	int utility_value = 0;

	int counter_max = 0;
	int counter_min = 0;
	int counter_free_tile = 0;

	// check columns
	for (int col = 0; col < NUM_COLS; ++col) {
		counter_max = 0;
		counter_min = 0;
		counter_free_tile = 0;

		for (int row = 0; row < NUM_ROWS; ++row) {
			if (puzzle[row][col] == "X" && counter_min == 0) {
				counter_max += 1;
			}

			if (puzzle[row][col] == "O" && counter_max == 0) {
				counter_min += 1;
			}

			if ((puzzle[row][col] == "X" && counter_min != 0)
					|| ((puzzle[row][col] == "O" && counter_max != 0))) {
				break;
			}

			if (puzzle[row][col] == ".") {
				counter_free_tile += 1;
			}
		}

		if (counter_max != 0 && counter_free_tile + counter_max >= 4) {
			if (counter_max == 4) {
				return 10000;
			}
			utility_value += pow(2, counter_max);
		}

		if (counter_min != 0 && counter_free_tile + counter_min >= 4) {
			if (counter_min == 4) {
				return -10000;
			}
			utility_value -= pow(2, counter_min);
		}
	}

	// check rows
	counter_max = 0;
	counter_min = 0;

	int prev_free_tile = 0;
	int after_free_tile = 0;
	int in_between_free_tile = 0;

	for (int row = NUM_ROWS - 1; row >= 0; --row) {
		for (int col = 0; col < NUM_COLS; ++col) {
			if (puzzle[row][col] == "." && counter_max == 0
					&& counter_min == 0) {
				prev_free_tile += 1;
				continue;
			}

			if ((puzzle[row][col] == "X" && counter_max != 0)
					&& (after_free_tile != 0 || in_between_free_tile != 0)) {
				in_between_free_tile = after_free_tile;
				after_free_tile = 0;
				counter_max += 1;
				continue;
			}

			if ((puzzle[row][col] == "O" && counter_min != 0)
					&& after_free_tile != 0) {
				in_between_free_tile = after_free_tile;
				after_free_tile = 0;
				counter_min += 1;
				continue;
			}

			if (puzzle[row][col] == "X" && counter_min == 0) {
				counter_max += 1;
				continue;
			}

			if (puzzle[row][col] == "O" && counter_max == 0) {
				counter_min += 1;
				continue;
			}

			if (puzzle[row][col] == "."
					&& (counter_max != 0 || counter_min != 0)) {
				after_free_tile += 1;
				continue;
			}

			if (puzzle[row][col] == "X" && counter_min != 0) {
				if (prev_free_tile + in_between_free_tile + counter_min
						+ after_free_tile >= 4) {
					if (counter_min == 4 && in_between_free_tile == 0) {
						return -10000;
					}
					utility_value -= pow(2, counter_min);
				}

				counter_max += 1;

				counter_min = 0;
				prev_free_tile = after_free_tile;
				after_free_tile = 0;
				continue;
			}

			if (puzzle[row][col] == "O" && counter_max != 0) {
				if (prev_free_tile + counter_max + after_free_tile >= 4) {
					if (counter_max >= 4 && in_between_free_tile == 0) {
						return 10000;
					}
					utility_value += pow(2, counter_max);
				}

				counter_min += 1;

				counter_max = 0;
				prev_free_tile = after_free_tile;
				after_free_tile = 0;
			}
		}

		if (counter_max != 0
				&& (prev_free_tile + counter_max + after_free_tile) >= 4) {
			if (counter_max >= 4 && in_between_free_tile == 0) {
				return 10000;
			}
			utility_value += pow(2, counter_max);
		}

		if (counter_min != 0
				&& (prev_free_tile + counter_min + after_free_tile) >= 4) {
			if (counter_min >= 4 && in_between_free_tile == 0) {
				return -10000;
			}
			utility_value -= pow(2, counter_min);
		}
	}

	// check diagonal

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
					return 10000;
				}
			}

			if (puzzle[last_row - diag][col - diag] == "O") {
				counter_max = 0;
				counter_min += 1;

				if (counter_min == 4) {
					return -10000;
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
					return 10000;
				}
			}

			if (puzzle[last_row - diag][col + diag] == "O") {
				counter_max = 0;
				counter_min += 1;

				if (counter_min == 4) {
					return -10000;
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
					return 10000;
				}
			}

			if (puzzle[row - diag][last_col - diag] == "O") {
				counter_max = 0;
				counter_min += 1;

				if (counter_min == 4) {
					return -10000;
				}
			}

			if (puzzle[row - diag][last_col - diag] == ".") {
				counter_max = 0;
				counter_min = 0;
			}
		}
		limit -= 1;
	}

	// check top right corner
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
					return 10000;
				}
			}

			if (puzzle[row - diag][first_col + diag] == "O") {
				counter_max = 0;
				counter_min += 1;

				if (counter_min == 4) {
					return -10000;
				}
			}

			if (puzzle[row - diag][first_col + diag] == ".") {
				counter_max = 0;
				counter_min = 0;
			}
		}
		limit -= 1;
	}

	return utility_value;

}
