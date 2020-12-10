/*************************************************************
     * Name:  Pradhyumna Wagle                                    *
     * Project:  Project 1 Pinochle C++                           *
     * Class:  CMPS 366 01 OPL									  *
     * Date:  10/21/2020										  *
	 *************************************************************/

#pragma once

#include "Round.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <map>
#include <fstream>
#include <sstream>


class Game
{
public:
	Game();
	~Game();

	void createNewGame();

	const vector<Player*> getCurrentPlayers();
	
	char cointoss();
	void loadGame();

private:
	//a vector that stores all players in a game 
	vector<Player*> current_players;

	//The number of rounds in the current game
	int numberOfRounds;

	string parseValues(string key, string line);

	void anotherRound();
	void endOfRound(Round round);

	void endGame();
};

