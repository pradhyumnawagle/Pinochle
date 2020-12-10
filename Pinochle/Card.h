/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#pragma once
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

class Card
{
public:
	Card();
	~Card();

	const char getFace();
	const char getSuit();
	const int getPointsWorth();

	void setFace(char str);
	void setSuit(char str);
	void setPointsWorth(int value);

	bool meldExists(string meld);
	bool noOldMelds();

	void setMeldInMap(string meldName, vector<Card*> cards);
	void printMelds();

	void setAtLeastOneMeld(bool selection);

	const map<string, vector<Card*>> getMeldsMap();

	const int getUniqueIndex();
	void setUniqueIndex(int i);

	void removeMeld(string meldName);

private:
	char face, suite;
	int points_worth;
	int unique_index;

	//bool to store if the card is used in at least one meld
	bool at_least_one_meld;

	//map where all melds that the card is involved in are stored 
	map<string, vector<Card*>> melds;
};

