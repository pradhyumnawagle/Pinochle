/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#pragma once
#include "Player.h"
class Computer :
	public Player
{
public:
	Computer();
	~Computer();

	Card* play(Card* card);
	vector<Card*> showMeld();
};

