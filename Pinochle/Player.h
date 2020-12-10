/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#pragma once

#include "Card.h"
#include "Graph.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>
#include <limits>
#include <fstream>


class Player
{
public:
	Player();
	~Player();

	//Cards in hand
	void setCardsInHand(vector<Card*> cards_received){cards_in_hand = cards_received;}
	void addCardToHand(Card* card);

	//Print
	void printCards(vector<Card*> cards);
	void printCardsToFile(vector<Card*> cards,ofstream& outfile);
	void printMeldPile();
	void printMeldCardsToFile(ofstream& outfile);
	void printMenu(vector<int> menuItems);
	void printMeldMenu();

	bool duplicateExists(Card* card, vector<vector<Card*>> cards);

	const string getName(){ return name; }
	void setName(string str) { name = str; }
	
	char tossSelection();	

	//Leader
	void setLeader(bool isLeader){ leader = isLeader; }
	bool isLeader(){ return leader; }
	
	int getPlayerInput(int min, int max);

	Card* getTurnCard(){ return turn_card; }

	//Scores
	const int getRoundScore(){ return round_score; }
	void addRoundScore(int score){ round_score += score; }
	const int getGameScore(){ return game_score; }
	void addGameScore(int score){ game_score = game_score + score; }


	void addCardToCapturePile(Card* card){ capture_pile.push_back(card); }

	//Player's cards
	const vector<Card*> getHandPile(){ return cards_in_hand; }
	const vector<Card*> getCapturePile(){ return capture_pile; }


	//Melds
	bool validateMeld(vector<Card*> cards, string meldName);
	bool atLeastOneNewCard(vector<Card*> cards);
	void setCardSelectedForMeld(vector<Card*> cards);
	string getMeldName(vector<Card*> cards);
	int getMeldPoints(string meldName);
	bool sameFacedCards(vector<Card*> cards);
	bool sameSuitdCards(vector<Card*> cards);
	bool isMarriage(vector<Card*> cards);
	bool isPinochle(vector<Card*> cards);
	bool containsNine(vector<Card*> cards);
	bool hasDuplicates(vector<Card*> cards, string basis);
	void updateMeldPile(vector<Card*> cards);
	void setMeldsFromLoad(string cards);

	void updateCardMeldsMap(vector<Card*> cards);

	bool noCardsLeftInHand();


	//Virtual functions
	virtual vector<Card*> showMeld() = 0;
	virtual Card* play(Card* card) = 0;

	void setTrumpCard(Card* card){
		trump_card = card;
		trump_suite = card->getSuit();
	}

	//Save
	const bool getSaveGame(){ return save_game; }
	void setSaveGame(bool val){ save_game = val; }

	//Load from file and store
	void storeHandCards(string cards);
	void storeCapturedCards(string cards);

	void updateLoadScores(string scores);
	void setTrumpSuit(char c){ trump_suite = c; }

	
	const int getAvailableCardsSize(){ return (int)availableCardsForSelection.size(); }	
	void updateAvailableCardsForSelection();

	//Clear
	void clearRoundScore(){ round_score = 0; }
	void clearAllCards();
	vector<Card*> getAllCards();

protected:
	vector<Card*> cards_in_hand;
	vector<Card*> capture_pile;
	vector<vector<Card*>> meld_pile;
	vector<Card*> availableCardsForSelection;
	map<string, vector<vector<Card*>>> allPossibleMelds;

	string name;
	bool save_game = false;
	string play_reason;
	int round_score = 0;
	int game_score = 0;
	bool leader = false;
	Card* turn_card;
	Card* trump_card;
	char trump_suite;
	string meldsByPoints[9] = { "flush","four Aces","four Kings", "four Queens" ,"royal marriage",
							"four Jacks", "pinochle", "marriage", "dix" };


	bool searchCard(string cardName, vector<Card*> cards);
	bool checkCardInput(string cardName);

	
	void printCardsForSelection();
	vector<int> getCardsSelection(int maxSize);

	void replaceCorrespondingCards(Card* card);
	

	void putBackToHand(vector<Card*> cards, Card* card);

	void createAllPossibleMelds();
	bool duplicateFacedCard(Card* card1, Card* card2);

	vector<vector<int>> getPathPairs(vector<Card*> vec1, vector<Card*> vec2);
	vector<vector<int>> getPossibleMeldPaths(vector<Card*> suitCards, vector<vector<Card*>> sameSuitDifferentFace);
	vector<vector<Card*>> allMeldCombinations(vector<Card*> cards, vector<vector<Card*>> sameSuitDifferentFace);

	vector<vector<Card*>> sameSuitButDifferent(vector<Card*> cards);
	vector<vector<Card*>> checkFlush(vector<Card*> cards);
	vector<vector<Card*>> checkRoyalMarriage(vector<Card*> cards);
	vector<vector<Card*>> checkMarriage(vector<Card*> cards);

	vector<vector<Card*>> checkFourSameCards(vector<Card*> cards);
	vector<vector<Card*>> sameFaceButDifferentSuit(vector<Card*> cards);

	vector<vector<Card*>> checkPinochle(vector<Card*> cards);
	
	vector<Card*> cardsNotCreatingMelds();

	Card* getCardWithMaxPoints(vector<Card*> cards);

	Card* getCardWithMinPoints(vector<Card*> cards);

	Card* helpLeadCard();
	Card* helpChaseCard(Card* leadCard);

	void updateHandPile(Card* card);

	bool moreThanOneActiveMeld(Card* card);
	bool searchInMeldsMap(Card* mainCard, Card* secondaryCard);

	string removeSpaceFromFrontAndBack( const string& str);
	vector<Card*> makeCardsFromString(vector<string> strCards);

	Card* getCardWithSameFace(string cardName, vector<Card*> cards);
	Card* getAnotherCardWithSameFace(string cardName, vector<Card*> cards);


	bool checkMeldNameInMap(string meldName, Card* card);
	void replaceCardWithOriginalCard(Card* card, vector<Card*>& cards);

	int getCountOfSimilarCards(Card* card, vector<Card*> cards);

	bool checkForStar(Card* card);

	int countCardsWithSameInfo(vector<vector<Card*>> cards, string cardName, Card*& cardWithSingleMeld, Card*& cardWithMultipleMelds);
	

	string getMissingMeldName(Card* oneMeldCard, Card* multipleMeldsCard);
	vector<Card*> replaceMissingMeld(Card* oneMeldCard, Card* multipleMeldsCard, string meldName);

	void replaceAllMeldsInVec(vector<vector<Card*>>& allMeldsVec, vector<Card*> cards);

};

