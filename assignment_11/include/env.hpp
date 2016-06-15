/*
 * Daniel Vázquez
 * AIR SS16
 * Assignment 11
 * env.hpp
 * */

#ifndef ENV_H
#define ENV_H

#include "agent.hpp"
#include "definitions.hpp"
#include <vector>
#include <string>



using namespace std;


class Environment
{
public:
	Environment();
	~Environment() {}
	void run();
	void play();

private:

	enum Player 
	{
		player1 = 1,
		player2
	};
	enum Method
	{
		minimax,
		alpa_beta
	};
	
	Puzzle puzzle;
	int num_tiles;
	std::string player1_symbol;
	std::string player2_symbol;
	Agent player1_agent;
	Agent player2_agent;
	bool player1_agent_on;
	bool player2_agent_on;
	Method player1_agent_method;
	Method player2_agent_method;
	
	void generate_puzzle();
	void print_puzzle();
	int set_tile(int col, std::string player_symbol);
    bool make_move(Player player);
	bool check_win(Player player);

};
#endif


