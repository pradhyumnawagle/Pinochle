/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#pragma once
#include "Card.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>

class Deck
{
public:
	Deck();
	~Deck();
	
	vector<Card*> getNewDeck();
	void printDeck();

private:
	vector<Card*> current_deck;

	void createDeck();
	void shuffleDeck();
	vector<Card*> generateCards();
	
};

