/*
 * Daniel Vázquez
 * AIR SS16
 * Assignment 11
 * agent.hpp
 * */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include "definitions.hpp"



class Agent
{
	
	
	
public:
	Agent(std::string max_symbol, std::string min_symbol);
	~Agent();
	
	std::pair<int, int> minimax(Puzzle puzzle, int free_tiles);
	std::pair<int, int> alpha_betha(Puzzle puzzle, int free_tiles, int alpha, int beta);

private:
	
	int total_tiles;
	std::string max_symbol;
	std::string min_symbol;
	
	//minimax methods
	std::pair<int, int> max(Puzzle puzzle, int free_tiles, int inputCol, int depth);
	std::pair<int, int> min(Puzzle puzzle, int free_tiles, int inputCol, int depth);
	
	int get_free_pos(Puzzle puzzle, int col);

	//alpha betha methods
	std::pair<int, int> max_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta);
	std::pair<int, int> min_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta);
	
	
	int utility(Puzzle puzzle, int free_tiles, std::string player_symbol);
	
	bool check_winning(Puzzle puzzle, int free_tiles, std::string player_symbol);
};



#endif
