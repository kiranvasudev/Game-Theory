/*
 * Daniel Vázquez
 * AIR SS16
 * Assignment 11
 * agent.cpp
 * */
#include <agent.hpp>
#include <climits>
#include <cmath>
#include <utility> 


/*
 * Max_symbol: The simbol used by the agent Max
 * Min_symbol: The simbos used be the agent Min
 * */
Agent::Agent(std::string max_symbol, std::string min_symbol):
max_symbol(max_symbol),
min_symbol(min_symbol),
total_tiles(NUM_COLS * NUM_ROWS)
{

}

Agent::~Agent()
{

}

//minimax initial method, returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::minimax(Puzzle puzzle, int free_tiles)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}


//max returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::max(Puzzle puzzle, int free_tiles, int depth)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

//min returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::min(Puzzle puzzle, int free_tiles, int depth)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

//alpha_beta returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::alpha_betha(Puzzle puzzle, int free_tiles, int alpha, int beta)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

//max_value returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::max_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}


//max_value returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::min_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

/*
 * Utility method: Computes the numerical value of the give puzzle
*/
double Agent::utility(Puzzle puzzle, std::string player_symbol)
{
	
	return 0;
}





