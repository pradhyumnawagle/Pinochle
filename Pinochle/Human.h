/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#pragma once
#include "Player.h"
class Human :
	public Player
{
public:
	Human();
	~Human();

	Card* play(Card* card);
	void playNewTurn();
	vector<Card*> showMeld();

	void meldHelp();
};

