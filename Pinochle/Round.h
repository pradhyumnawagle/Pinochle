/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/
#pragma once

#include "Card.h"
#include "Deck.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

class Round
{
public:
	Round();
	Round(vector<Player*> players);
	~Round();
	
	//Set up and start round
	void distributeCards();
	void setRoundNumber(int roundNumber);
	void startRound();
	

	//Load from saved files
	void setLoadTrumpCard(string card);
	void updateStockFromLoad(string cards);

	Card* getTrumpCard();
	const int getWinner();

	//Put all cards in a vector 
	void setAllCards(vector<Card*> cards);

private:
	vector<Card*> current_deck;
	vector<Player*> current_players;

	Card* trump_card;
	char trump_suite;

	int round_number;

	vector<Card*> all_cards;

	void printCurrentDeck();

	void showDashboard(Player* player);

	void newTurn();

	void selectTurnWinner();
	string turnWinnerCard(Card* leadCard, Card* chaseCard);

	const int getCardPrecedence(char cardFace);

	void pickCard(Player* player);

	void saveGame(Player* player);

};

