/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#include "Player.h"


/* *********************************************************************
Function Name: Player
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Player::Player()
{
	 name = "";
	 save_game = false;
	 play_reason = "";
	 round_score = 0;
	 game_score = 0;
	 leader = false;

	 cards_in_hand = {};
	 capture_pile = {};
	 meld_pile = {};
	 availableCardsForSelection = {};
	 allPossibleMelds = {};

	 turn_card = NULL;
	 trump_card = NULL;
}

/* *********************************************************************
Function Name: ~Player
Purpose: To delete all objects of the class
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Player::~Player()
{
}



/* *********************************************************************
Function Name: printCards
Purpose: To print all cards received in the parameter in a vector
Parameters: 
		cards, A vector containing card pointers
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::printCards(vector<Card*> cards) {
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		cout <<(*it)->getFace() << (*it)->getSuit() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: printCardsToFile
Purpose: To print all cards received in the parameter to a file
Parameters:
		cards, A vector containing card pointers
		outfile, An ofstream object passed by reference, that has the file to write to
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::printCardsToFile(vector<Card*> cards, ofstream& outfile) {
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		outfile << (*it)->getFace() << (*it)->getSuit() << " ";
	}
	cout << '\n';
}

/* *********************************************************************
Function Name: printMeldPile
Purpose: To print all cards from the meld pile
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Iterate over the meld pile
		2) Check if each card has more than one active meld 
		3) If more than one active meld, print a star next to the card
Assistance Received: None
********************************************************************* */
void Player::printMeldPile() {
	vector<vector<Card*>>::iterator it;
	for (it = meld_pile.begin(); it != meld_pile.end(); ++it) {
		vector<Card*>::iterator cardIt;
		if (!(*it).empty()) {
			for (cardIt = (*it).begin(); cardIt != (*it).end(); ++cardIt) {
				//if card is in more than one meld and needs a star
				if (moreThanOneActiveMeld(*cardIt) && checkForStar(*cardIt)) {
					cout << (*cardIt)->getFace() << (*cardIt)->getSuit() << "* ";
				}
				else {
					cout << (*cardIt)->getFace() << (*cardIt)->getSuit() << " " ;
				}
			}
			
		}
		//no comma after last card
		if (!(meld_pile.end() - it == 1)) {
			vector<vector<Card*>>::iterator it2 = it + 1;
			if ((*it2).size() > 0) {
				cout << ", ";
			}
		}
	}
	
}

/* *********************************************************************
Function Name: printMeldCardsToFile
Purpose: To write all cards from the meld pile in a file
Parameters: 
		outfile, An ofstream object passed by reference, that has the file to write to 
Return Value: None
Local Variables: None
Algorithm:
		1) Iterate over the meld pile
		2) Check if each card has more than one active meld
		3) If more than one active meld, write a star next to the card
Assistance Received: None
********************************************************************* */
void Player::printMeldCardsToFile(ofstream& outfile) {
	vector<vector<Card*>>::iterator it;
	for (it = meld_pile.begin(); it != meld_pile.end(); ++it) {
		vector<Card*>::iterator cardIt;
		if (!(*it).empty()) {
			for (cardIt = (*it).begin(); cardIt != (*it).end(); ++cardIt) {
				//if card is in more than one meld and needs a star
				if (moreThanOneActiveMeld(*cardIt)) {
					outfile << (*cardIt)->getFace() << (*cardIt)->getSuit() << "* ";
				}
				else {
					outfile << (*cardIt)->getFace() << (*cardIt)->getSuit() << " ";
				}
			}

			if (!(meld_pile.end() - it == 1)) {
				vector<vector<Card*>>::iterator it2 = it + 1;
				if ((*it2).size() > 0) {
					outfile << ", ";
				}
			}
		}
	}
}

/* *********************************************************************
Function Name: duplicateExists
Purpose: To check if a card exists more than once in a meld pile 
Parameters:
		outfile, An ofstream object passed by reference, that has the file to write to
Return Value: Boolean true if card found more than once, false if not
Local Variables: None
Algorithm:
		1) Iterate over the meld pile
		2) Count the number of times the card is found
		3) If the card is found more than once, return true
Assistance Received: None
********************************************************************* */
bool Player::duplicateExists(Card* card, vector<vector<Card*>> cards) {
	int count = 0;
	vector<vector<Card*>>::iterator it;
	for (it = meld_pile.begin(); it != meld_pile.end(); ++it) {
		vector<Card*>::iterator cardIt;
		for (cardIt = (*it).begin(); cardIt != (*it).end(); ++cardIt) {
			if (card == *cardIt) {
				count += 1;
			}			
		}
	}
	if (count > 1) {
		return true;
	}
	return false;
}


/* *********************************************************************
Function Name: addCardToHand
Purpose: To add a card to hand pile
Parameters:
		card, a Card pointer 
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::addCardToHand(Card* card) {
	cards_in_hand.push_back(card);
}

/* *********************************************************************
Function Name: printMenu
Purpose: To print menu before each turn
Parameters:
		menuItems, a vector of integers containing menu items to display
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::printMenu(vector<int> menuItems) {

	vector<string> menuList;
	menuList.push_back(" Play a move");
	menuList.push_back(" Save the game");
	menuList.push_back(" Help");
	menuList.push_back(" Quit");

	cout << "\n" << name <<  " Please select an option:" << endl;
	
	for (auto i = 0; i < menuItems.size(); i++) {
		cout <<"\t"<< i+1 << "." << menuList[menuItems[i]-1] << endl;
	}
}

/* *********************************************************************
Function Name: tossSelection
Purpose: To get a selection for toss from the user
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
char Player::tossSelection() {

	char input;
	do {

		cout << "\n" << name << " Please select h/t for toss: ";
		cin >> input;
		if (input != 'h' && input != 't') {
			cout << "Invalid input!!! \n" << endl;
		}
	} while (input != 'h' && input != 't');

	return input;
}

/* *********************************************************************
Function Name: getPlayerInput
Purpose: To get user input for the menu
Parameters: 
		min, integer value that is the minimum input value
		max, integer value that is the maximum input value
Return Value: Integer input from the user
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
int Player::getPlayerInput(int min, int max) {
	
	int input;
	
	do {		
		cin >> input;
		cin.clear();
		if ((input <min || input >max) || !cin ) {
			cout << "Invalid input!!! Please select an option again: " << endl;
			cin.ignore();
		}
	} while ((input < min || input > max) || !cin);

	cin.clear();
	return input;
}


/* *********************************************************************
Function Name: searchCard
Purpose: To search if a card with same face and suit exists in a vector of cards
Parameters:
		cardName, string value of a card
		cards, vector of Card pointers
Return Value: Boolean true if found, false if not
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::searchCard(string cardName, vector<Card*> cards) {

	char cardFace = cardName[0];
	char cardSuit = cardName[1];
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (cardFace == (*it)->getFace() && cardSuit == (*it)->getSuit()) {
			return true;
		}		
	}

	return false;
}

/* *********************************************************************
Function Name: checkCardInput
Purpose: To check if user input value is has valid face and suit
Parameters:
		cardName, string value of a card
		cards, vector of Card pointers
Return Value: Boolean true if valid, false if not
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::checkCardInput(string cardName) {

	//O is the first index in string which is face, ! is the second value which is suit
	if (cardName[0] == '9' || cardName[0] == 'J' || cardName[0] == 'Q' || cardName[0] == 'K' ||
		cardName[0] == 'X' || cardName[0] == 'A') {
		if (cardName[1] == 'H' || cardName[1] == 'S' || cardName[1] == 'D' || cardName[1] == 'C') {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: validateMeld
Purpose: To check if the meld is valid
Parameters:		
		cards, vector of Card pointers having cards in the meld
		meldName, string meld name
Return Value: Boolean true if valid, false if not
Local Variables: None
Algorithm: 
		1) If the card already has the meld in its melds map, return false
		2) Use helper function meldExists to check if the meld exists in the map
Assistance Received: None
********************************************************************* */
bool Player::validateMeld(vector<Card*> cards, string meldName) {	
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->meldExists(meldName)) {
			return false;
		}
	}
	return true;
}


/* *********************************************************************
Function Name: atLeastOneNewCard
Purpose: To check if the meld has at least one new card which is not in meld pile
Parameters:
		cards, vector of Card pointers having cards in the meld
Return Value: Boolean true if valid, false if not
Local Variables: None
Algorithm:
		1) If the card already has an old meld in its melds map, return false
		2) Use helper function noOldMelds to check if a meld exists in the map
Assistance Received: None
********************************************************************* */
bool Player::atLeastOneNewCard(vector<Card*> cards) {
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->noOldMelds()) {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: setCardSelectedForMeld
Purpose: To set that the card has been used in at least one meld
Parameters:
		cards, vector of Card pointers having cards in the meld
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::setCardSelectedForMeld(vector<Card*> cards) {
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		(*it)->setAtLeastOneMeld(true);
	}
}

/* *********************************************************************
Function Name: updateMeldPile
Purpose: To update the meld pile and remove the card from hand
Parameters:
		cards, vector of Card pointers having cards in the meld
Return Value: None
Local Variables: None
Algorithm: 
		1) Push back the cards into meld pile
		2) If the card is in hand, delete from hand 
Assistance Received: None
********************************************************************* */
void Player::updateMeldPile(vector<Card*> cards) {

	meld_pile.push_back(cards);

	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		for (vector<Card*>::iterator innerIt = cards_in_hand.begin(); innerIt != cards_in_hand.end(); ++innerIt) {
			if (*it == *innerIt) {
				cards_in_hand.erase(innerIt);
				break;
			}
		}
	}		
}

/* *********************************************************************
Function Name: printMeldMenu
Purpose: To print the menu displayed before showing meld cards
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::printMeldMenu() {
	cout << name << " Please select a choice(1/3): " << endl;
	cout << "\t1. Show new meld" << endl;
	cout << "\t2. Help " << endl;
	cout << "\t3. No meld" << endl;
}

/* *********************************************************************
Function Name: updateAvailableCardsForSelection
Purpose: To update the cards available to select for a turn
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Add all cards from hand and meld pile to availableCardsforSelection
Assistance Received: None
********************************************************************* */
void Player::updateAvailableCardsForSelection() {

	availableCardsForSelection = cards_in_hand;

	vector<vector<Card*>>::iterator it;
	for (it = meld_pile.begin(); it != meld_pile.end(); ++it) {
		vector<Card*>::iterator cardIt;
		for (cardIt = (*it).begin(); cardIt != (*it).end(); ++cardIt) {
			//If not i available card for selection, add to it
			if (find(availableCardsForSelection.begin(), availableCardsForSelection.end(), *cardIt) == availableCardsForSelection.end()) {
				availableCardsForSelection.push_back(*cardIt);
			}
		}
	}
}

/* *********************************************************************
Function Name: printCardsForSelection
Purpose: To print cards available for selection to play in a turn
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
		1) Show all cards available for selection with index
Assistance Received: None
********************************************************************* */
void Player::printCardsForSelection() {
	int i = 1;
	int size = (int)cards_in_hand.size();
	vector<Card*>::iterator it;
	cout << endl << "Hand Pile:  ";
	for (it = availableCardsForSelection.begin(); i<=size; ++it) {
			cout << (*it)->getFace() << (*it)->getSuit() << "->" << i << "   ";		
		i += 1;
	}
	cout << " Meld pile:  ";
	for (it; it != availableCardsForSelection.end(); ++it) {
		cout << (*it)->getFace() << (*it)->getSuit() << "->" << i << "   ";
		i += 1;
	}
	cout << endl;
}

/* *********************************************************************
Function Name: getCardsSelection
Purpose: To get user's input for cards selection while showing melds
Parameters: 
		maxsize, integer that is the maximum value which can be selected
Return Value: A vector of integers containing selected numbers
Local Variables: 
		meldCards, a vector of itegers that stores all user input values
Algorithm:
		1) Get user input and validate 
		2) Store all input values in a vector and return the vector
Assistance Received: None
********************************************************************* */
vector<int> Player::getCardsSelection(int maxSize) {

	vector<int> meldCards;
	cin.ignore();
	do {
		//cin.ignore();
		string input;
		int each;
		stringstream ss;
		getline(cin, input);
		ss << input;
		while (ss >> each)
		{
			if ((each) >= 1 && (each) <= availableCardsForSelection.size()) {
				meldCards.push_back(each);
			}
		}
		if (meldCards.size() < 1 || meldCards.size() > maxSize) {
			cout << "Invalid input. Please try again." << endl;
			meldCards.clear();
		}
	} while (meldCards.size() < 1);

	return meldCards;
}


/* *********************************************************************
Function Name: noCardsLeftInHand
Purpose: To verify if hand pile is empty or not
Parameters: None
Return Value: Boolean true if no cards left in hand, false otherwise
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::noCardsLeftInHand() {
	if (cards_in_hand.empty()) {
		return true;
	}
	return false;
}


/* *********************************************************************
Function Name: replaceCorrespondingCards
Purpose: To delete a meld from meld pile once card is shown in turn and 
			replace corresponding cards in melds back to hand 
Parameters: 
		card, A Card pointer that has the turn card
Return Value: Boolean true if no cards left in hand, false otherwise
Local Variables: 
		correspondingCards, the melds map of the turn card received in the parameter
		meldsUsed, A vector with the names of all melds the card is used in
		pos, a vector that stores the position of the melds in the meld pile
Algorithm: 
		1) Iterate over the melds map of the turn card and get all melds with names
		2) If card is not involved in more than one active meld, put back to hand
		3) If card is 9 of trump suit, it will have the same card stored so don't replace 
		4) Use the meld names stored to delete the melds from the turn card's melds map
		5) Get the position of the melds in the melds pile
		6) Remove the melds from the meld pile
Assistance Received: None
********************************************************************* */
void Player::replaceCorrespondingCards(Card* card) {

	map<string, vector<Card*>> correspondingCards = card->getMeldsMap();	
	vector<string> meldsUsed;
	
	//Iterate over the melds map of a card and push back all other cards in the meld 
	//to hand
	for (const auto &myKey : correspondingCards) {
		vector<Card*> vec = (myKey).second;
		vector<Card*>::iterator it;
		for (it = vec.begin(); it != vec.end(); ++it) {
			//If card is not involved in more than one active meld and is not 9
			if (!moreThanOneActiveMeld(*it) && ((card->getFace()!='9' && card->getSuit()!=trump_suite))) {
				cards_in_hand.push_back(*it);
			}
		}		
		meldsUsed.push_back(myKey.first);
	}
	cout << endl;
	
	//Remove the meld from the card's meld's map
	for (vector<string>::iterator it = meldsUsed.begin(); it != meldsUsed.end(); ++it) {
		card->removeMeld(*it);
	}
	
	//Get the position of the melds the card is involved in meld pile 
	vector<vector<Card*>>::iterator it2;
	vector<int> pos;

	int index = 0;
	for (it2 = meld_pile.begin(); it2 != meld_pile.end(); ++it2) {
		vector<Card*> vec = *it2;
		if (find(vec.begin(), vec.end(), card) != vec.end()) {
			pos.push_back(index);
		}
		index += 1;
	}

	//Delete the melds by position from meld pile
	for (vector<int>::iterator it3 = pos.begin(); it3 != pos.end(); ++it3) {
		meld_pile[*it3].clear();
	}
	
}


/* *********************************************************************
Function Name: putBackToHand
Purpose: To put the corresponding cards back to hand 
Parameters: 
		cards, A vector with Card pointers of cards in a meld
		card, the turn card
Return Value:None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::putBackToHand(vector<Card*> cards, Card* card) {//check if involved in multiple melds

	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (*it != card) {
			cards_in_hand.push_back(*it);
		}		
	}
}


/* *********************************************************************
Function Name: getMeldName
Purpose: Get the name of the meld
Parameters:
		cards, A vector with Card pointers of cards in a meld
Return Value:String meldname, the name of the melds formed by cards
Local Variables: None
Algorithm: 
		1) If 5 cards, if has no duplicate faced card, all are same and trump suit and no nine, return flush
		2) If 4 cards, has same faced duplicates, then return four Aces/Kings/Queens/Jacks according
			to the face
		3) If 2 cards, Check pinochle using a helper function IsPinochle, if true return pinochle
		4) If not pinochle, check marriage and return marriage
		5) If trump suit and marriage, return royal marriage
		6) If just 1 card, is of trump suit, return dix
		7) For everything else, return invalid
Assistance Received: None
********************************************************************* */
string Player::getMeldName(vector<Card*> cards) {
	int numberOfCards = cards.size();

	switch (numberOfCards) {
	case 5:
		//Check if Ace, Ten, King, Queen and Jack-------That means no nine---------------------------	
		if (!hasDuplicates(cards, "face") && sameSuitdCards(cards) && !containsNine(cards) && trump_suite == cards[0]->getSuit()) {
			return "flush";
		}
		break;
	case 4:
		//unique suites and same faced cards
		if (!hasDuplicates(cards, "suite") && sameFacedCards(cards)) {
			if ('A' == cards[0]->getFace()) { return "four Aces"; }
			else if ('K' == cards[0]->getFace()) { return "four Kings"; }
			else if ('Q' == cards[0]->getFace()) { return "four Queens"; }
			else if ('J' == cards[0]->getFace()) { return "four Jacks"; }
		}
		break;
	case 2:
		if (isPinochle(cards)) { return "pinochle"; }
		else {
			if (isMarriage(cards)) {
				if (trump_suite == cards[0]->getSuit()) { return "royal marriage"; }
				else {
					return "marriage";
				}
			}
		}
		break;
	case 1:
		if ('9' == cards[0]->getFace() && cards[0]->getSuit() == trump_suite) { return "dix"; }
		break;
	default:
		return "invalid";
	}

	return "";
}

/* *********************************************************************
Function Name: getMeldPoints
Purpose: To get the points by the name of meld
Parameters:
		meldName, the name of the meld to return corresponding points
Return Value:integer value that is the point for the meld 
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
int Player::getMeldPoints(string meldName) {
	if ("flush" == meldName) { return 150; }
	else if ("four Aces" == meldName) { return 100; }
	else if ("four Kings" == meldName) { return 80; }
	else if ("four Queens" == meldName) { return 60; }
	else if ("four Jacks" == meldName) { return 40; }
	else if ("pinochle" == meldName) { return 40; }
	else if ("royal marriage" == meldName) { return 40; }
	else if ("marriage" == meldName) { return 20; }
	else if ("dix" == meldName) { return 10; }
	else { return 0; }
}

/* *********************************************************************
Function Name: sameFacedCards
Purpose: To know if all cards have same face
Parameters:
		cards, A vector containing Card pointers 
Return Value:boolean true if all cards have same suit, if not then false
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::sameFacedCards(vector<Card*> cards) {

	char face = cards[0]->getFace();
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (face != (*it)->getFace()) {
			return false;
		}
	}
	return true;
}

/* *********************************************************************
Function Name: sameSuitdCards
Purpose: To know if all cards have same suit
Parameters:
		cards, A vector containing Card pointers
Return Value:boolean true if all cards have same suit, if not then false
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */ 
bool Player::sameSuitdCards(vector<Card*> cards) {

	char suite = cards[0]->getSuit();
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (suite != (*it)->getSuit()) {
			return false;
		}
	}
	return true;
}

/* *********************************************************************
Function Name: isMarriage
Purpose: To know if the cards make Marriage meld
Parameters:
		cards, A vector containing Card pointers 
Return Value: boolean true if the meld is Marriage, if not then false
Local Variables: 
		kingCount, integer value that keeps count of cards that are Kings
		queenCount, integer value that keeps count of cards that are Queens
Algorithm: 
		1) If both cards do not have same suit, return false
		2) If both cards are of same suit, if the count of King cards is 1
			and that of Queen cards is 1, return true
Assistance Received: None
********************************************************************* */
bool Player::isMarriage(vector<Card*> cards) {
	if (cards.size() > 2) { return false; }

	vector<Card*>::iterator it;
	int kingCount = 0;
	int queenCount = 0;
	char suite = cards[0]->getSuit();
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ('K' == (*it)->getFace()) {
			kingCount++;
		}
		else if ('Q' == (*it)->getFace()) {
			queenCount++;
		}
		if (suite != (*it)->getSuit()) {
			return false;
		}
	}

	if (1 == kingCount && 1 == queenCount) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: isPinochle
Purpose: To know if the cards make Pinochle meld
Parameters:
		cards, A vector containing Card pointers
Return Value: boolean true if the meld is Pinochle, if not then false
Local Variables:
		queenOfSpadesCount, integer value that keeps count of cards that are QS
		jackOfDiamondCount, integer value that keeps count of cards that are JD
Algorithm:
		1) If cards size is greater than 2, return false
		2) If there are 2 cards, if queenOfSpadesCount and jackOfDiamondCount are both 1
			return true.
Assistance Received: None
********************************************************************* */
bool Player::isPinochle(vector<Card*> cards) {
	if (cards.size() > 2) { return false; }

	vector<Card*>::iterator it;
	int queenOfSpadesCount = 0, jackOfDiamondCount = 0;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ('Q' == (*it)->getFace() && 'S' == (*it)->getSuit()) {
			queenOfSpadesCount++;
		}
		else if ('J' == (*it)->getFace() && 'D' == (*it)->getSuit()) {
			jackOfDiamondCount++;
		}
	}
	if (1 == queenOfSpadesCount && 1 == jackOfDiamondCount) {
		return true;
	}
	return false;
}


/* *********************************************************************
Function Name: containsNine
Purpose: To know if the cards contain a 9
Parameters:
		cards, A vector containing Card pointers
Return Value:boolean true if all cards contain 9, if not then false
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::containsNine(vector<Card*> cards) {
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ('9' == (*it)->getFace()) {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: hasDuplicates
Purpose: To know if the cards have duplicates based on the string 'basis'
Parameters:
		cards, A vector containing Card pointers
		basis, a string based on which duplicates is searched
Return Value:boolean true if duplicates are found, if not then false
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::hasDuplicates(vector<Card*> cards, string basis) {

	for (size_t i = 0; i < cards.size(); ++i) {
		for (size_t j = i + 1; j < cards.size(); ++j) {
			if ("suite" == basis) {
				if (cards[i]->getSuit() == cards[j]->getSuit())
					return true;
			}
			else if ("face" == basis) {
				if (cards[i]->getFace() == cards[j]->getFace())
					return true;
			}
		}
	}
	return false;
}

/* *********************************************************************
Function Name: cardsNotCreatingMelds
Purpose: To create a vector of Card pointers that are not involved in any melds
Parameters: None
Return Value:A vector of Card pointers that do not create any melds
Local Variables: 
		cardsNotInMelds, A vector that contains pointer to Cards that are not 
							involved in any melds
Algorithm: 
		1) From all cards that are available for selection, find if the 
			card is included in the map all possible melds
		2) If the card is not found, add to the vector and return the vector
Assistance Received: None
********************************************************************* */
vector<Card*> Player::cardsNotCreatingMelds() {
	vector<Card*>::iterator it;
	vector<Card*> cardsNotInMelds;

	for (it = availableCardsForSelection.begin(); it != availableCardsForSelection.end(); ++it) {
		int count = 0;
		for (const auto &myPair : allPossibleMelds) {
			for (int i = 0; i < (myPair.second).size(); i++) {
				if (find(myPair.second[i].begin(), myPair.second[i].end(), *it) != myPair.second[i].end())
					count += 1;
			}
		}
		if (count == 0) {
			cardsNotInMelds.push_back(*it);
		}
	}

	return cardsNotInMelds;
}


/* *********************************************************************
Function Name: createAllPossibleMelds
Purpose: To create all possible melds from a player's cards and store in the 
			class member allPossibleMelds
Parameters: None
Return Value: None
Local Variables:
		cardsBySuits,A map where all cards are seperated by suits
		cardsByFace, A map where all cards are seperated by face
		trumpSuitCards, A vector where all trump suit cards are stored
		marriageMelds, A vector where vectors of Marriage melds are stored
Algorithm:
		1) Seperate cards by suit and faces into separate maps
		2) Use checkFlush function to check flush for cards of trump suit
		3) Use checkRoyalMarriage function to check royal marriage for trump suit cards
		4) Use checkPinochle function to check Pinochle from all available cards
		5) Form Marriage, use checkMarriage function on same suit cards
		6) From cards of smae face, check for four of same cards and get the melds if present
		7) From available cards for seleection check if 9 of trumo suit is present to get dix
		8) Insert all melds into allPossibleMelds map of the class
Assistance Received: None
********************************************************************* */
void Player::createAllPossibleMelds() {

	vector<Card*>::iterator it;

	map<char, vector<Card*>> cardsBySuits;
	map<char, vector<Card*>> cardsByFace;
	
	//Separate cards by suit
	for (it = availableCardsForSelection.begin(); it != availableCardsForSelection.end(); ++it) {
		if ('H' == (*it)->getSuit()) {
			cardsBySuits['H'].push_back(*it);
		} else if ('D' == (*it)->getSuit()) {
			cardsBySuits['D'].push_back(*it);
		}
		else if ('C' == (*it)->getSuit()) {
			cardsBySuits['C'].push_back(*it);
		}
		else if ('S' == (*it)->getSuit()) {
			cardsBySuits['S'].push_back(*it);
		}

	}
	//Separate cards by Face
	for (it = availableCardsForSelection.begin(); it != availableCardsForSelection.end(); ++it) {
		if ('A' == (*it)->getFace()) {
			cardsByFace['A'].push_back(*it);
		}
		else if ('K' == (*it)->getFace()) {
			cardsByFace['K'].push_back(*it);
		}
		else if ('Q' == (*it)->getFace()) {
			cardsByFace['Q'].push_back(*it);
		}
		else if ('J' == (*it)->getFace()) {
			cardsByFace['J'].push_back(*it);
		}
	}

	vector<Card*> trumpSuitCards = cardsBySuits[trump_suite];
	//Check flush and add all possible melds to allMelds map
	allPossibleMelds["flush"] = checkFlush(trumpSuitCards);
	//Check Royal Marriage and add all possible melds to allMelds map
	allPossibleMelds["royal marriage"] = checkRoyalMarriage(trumpSuitCards);
	//Check Pinochle and add all possible melds to allMelds map
	allPossibleMelds["pinochle"] = checkPinochle(availableCardsForSelection);

	//Get all possible marriage melds
	vector<vector<Card*>> marriageMelds;
	for (const auto &myPair : cardsBySuits) {
		if (myPair.first != trump_suite) {
			vector<vector<Card*>> vec = checkMarriage(myPair.second);
			marriageMelds.insert(marriageMelds.end(), vec.begin(), vec.end());
		}
	}
	allPossibleMelds["marriage"] = marriageMelds;

	
	//Check for four same cards
	for (const auto &myPair : cardsByFace) {
		vector<vector<Card*>> vec = checkFourSameCards(myPair.second);
		if (myPair.first == 'A') {
			allPossibleMelds["four Aces"] = vec;
		}
		else if (myPair.first == 'K') {
			allPossibleMelds["four Kings"] = vec;
		}
		else if (myPair.first == 'Q') {
			allPossibleMelds["four Queens"] = vec;
		}
		else if (myPair.first == 'J') {
			allPossibleMelds["four Jacks"] = vec;
		}
	}

	//Check for dix from all available cards for selection
	for (it = availableCardsForSelection.begin(); it != availableCardsForSelection.end(); ++it) {		
		if ((*it)->getFace() == '9' && (*it)->getSuit() == trump_suite) {
			if ((*it)->getMeldsMap().count("dix") == 0) {
				vector<Card*> vec;
				vec.push_back(*it);
				allPossibleMelds["dix"].push_back(vec);
			}
		}
		
	}
	
}

/* *********************************************************************
Function Name: checkPinochle
Purpose: To know if the cards make Pinochle meld
Parameters:
		cards, A vector containing Card pointers
Return Value: A vector containing vectors with Card pointers that make Pinochle
Local Variables:
		pinochleCards, a vector containing vectors with Card pointers that make Pinochle 
		sameFaceDifferentSuit, Has all cards of same face but cards having same suit in 
								separate vector 
		mCards, A vector containing cards that are not already involved in pinochle
Algorithm:
		1) From cards, check if each card is QS or JD
		2) If the validation above is true, check if it already has been involved in Pinochle
		3) If the card does not have Pinochle, add to a vector and push the vector to separate by suit
		4) If the vector separated by suit has size less than 2, no pinochle
		5) Use helper function allMeldCombinations to get all meld combinations from the vector
		6) Return the vector containing vectors with Card pointers that make Pinochle 
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::checkPinochle(vector<Card*> cards) {
	vector<vector<Card*>> pinochleCards;
	int index = 0;
	vector<Card*> mCards;
	vector<Card*>::iterator it;

	//Check if the cards are JD or QS and not involved in any melds and are not 
	//involved in a pinochle already
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (((*it)->getFace() == 'Q' && (*it)->getSuit() == 'S') || ((*it)->getFace() == 'J' && (*it)->getSuit() == 'D')) {
			if ((*it)->getMeldsMap().count("pinochle") == 0) {
				(*it)->setUniqueIndex(index);
				index += 1;
				mCards.push_back(*it);
			}
		}
	}

	//Separate cards by suit and face
	vector<vector<Card*>> sameFaceDifferentSuit = sameFaceButDifferentSuit(mCards);

	if (sameFaceDifferentSuit.size() < 2) { return pinochleCards; }

	//Generate all meld combinations and return the card
	pinochleCards = allMeldCombinations(mCards, sameFaceDifferentSuit);

	return pinochleCards;

}

/* *********************************************************************
Function Name: checkFourSameCards
Purpose: To create a vector of Card pointers that are include four cards of 
			same face but different suit to meld (Four of same cards from different suit)
Parameters: 
		cards, A vector containing Card pointers
Return Value: A vector of vector containing Card pointers that create four cards of same 
				face but different suit
Local Variables:
		fourSame, a vector containing vectors with Card pointers that make meld of 
					four cards of same face but different suit
		mCards, A vector containing cards that are not already involved in four same meld
		face, a character that is the face of the cards
		sameFaceDifferentSuit, Has all cards of same face but cards having same suit in 
					separate vector

Algorithm:
		1) Check the face of a card and set the name of possible meld
		2) If the card is not involved in the meld with set name, add to a 
			vector
		3) Separate cards by suit
		4) If the size of separated cards is less than 4, no meld
		5) Generate all possible meld combinations and return the melds
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::checkFourSameCards(vector<Card*> cards) {
	vector<vector<Card*>> fourSame;
	int index = 0;
	vector<Card*> mCards;
	vector<Card*>::iterator it;
	char face = cards[0]->getFace();
	string name = "";

	//Check the card and set name
	if (face == 'A') {
		name = "four Aces";
	}
	else if (face == 'K') {
		name = "four Kings";
	}
	else if (face == 'Q') {
		name = "four Queens";
	}
	else if (face == 'J') {
		name = "four Jacks";
	}

	//Check if the cards do not have a meld already present and add to a vector
	for (it = cards.begin(); it != cards.end(); ++it) {	
		if ((*it)->getMeldsMap().count(name) == 0) {
			(*it)->setUniqueIndex(index);
			index += 1;
			mCards.push_back(*it);
		}
		
	}
	//Separate cards by suit 
	vector<vector<Card*>> sameFaceDifferentSuit = sameFaceButDifferentSuit(mCards);

	if (sameFaceDifferentSuit.size() < 4) { return fourSame; }

	//Generate all possible meld combinations and return
	fourSame = allMeldCombinations(mCards, sameFaceDifferentSuit);

	return fourSame;
}

/* *********************************************************************
Function Name: sameFaceButDifferentSuit
Purpose: To separate cards having same face by suit
Parameters: cards, A vector containing Card pointers
Return Value: A vector of vectors where cards of same face are separated by suit
Local Variables:
		sameFaceDifferentSuit, Has all cards of same face but cards having same suit in 
								separate vectors
Algorithm:
		1) If the vector is empty, add the card
		2) Check if duplicate faced card exists in the vector passed in parameter
		3) If exists, push the card into the vector
		4) Else, create a new vector with same suit and add the card to the vector
		5) Push the vector with same suit to the main vector containing vectors where 
			cards of same face are separeated by suit
		6) Return the main vector containing vector of Card pointers
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::sameFaceButDifferentSuit(vector<Card*> cards) {

	vector<vector<Card*>> sameFaceDifferentSuit;
	vector<Card*>::iterator it;

	for (it = cards.begin(); it != cards.end(); ++it) {
		if (sameFaceDifferentSuit.size() > 0) {
			for (int i = 0; i < sameFaceDifferentSuit.size(); i++) {
				//Check if duplicate faced card exists 
				if (duplicateFacedCard(sameFaceDifferentSuit[i][0], *it)) {
					sameFaceDifferentSuit[i].push_back(*it);
					break;
				}
				//If no duplicate faced cards, create a new vector for cards with same suit
				//and push back to the main vector
				else if (i == sameFaceDifferentSuit.size() - 1) {
					vector<Card*> sameSuit;
					sameSuit.push_back(*it);
					sameFaceDifferentSuit.push_back(sameSuit);
					break;
				}
			}
		}
		else {
			vector<Card*> sameSuit;
			sameSuit.push_back(*it);
			sameFaceDifferentSuit.push_back(sameSuit);
		}
	}
	return sameFaceDifferentSuit;
}


/* *********************************************************************
Function Name: checkMarriage
Purpose: To know if the cards make Marriage meld
Parameters:
		cards, A vector containing Card pointers
Return Value: A vector containing vectors with Card pointers that make Marriage
Local Variables:
		marriageCards, a vector containing vectors with Card pointers that make Marriage
		sameFaceDifferentSuit, Has all cards of same face but cards having same suit in
								separate vector
		mCards, A vector containing cards that are not already involved in marriage
Algorithm:
		1) From cards, check if each card has face Q or K
		2) If the validation above is true, check if it already has been involved in Marriage
		3) If the card does not have Marriage, add to a vector and push the vector to separate by suit
		4) If the vector separated by suit has size less than 2, no marriage
		5) Use helper function allMeldCombinations to get all meld combinations from the vector
		6) Return the vector containing vectors with Card pointers that make Marriage
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::checkMarriage(vector<Card*> cards) {
	vector<vector<Card*>> marriageCards;
	int index = 0;
	vector<Card*> mCards;
	vector<Card*>::iterator it;

	//Check if each card is a king or a queen
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->getFace() == 'Q' || (*it)->getFace() == 'K') {
			if ((*it)->getMeldsMap().count("marriage") == 0) {
				(*it)->setUniqueIndex(index);
				index += 1;
				mCards.push_back(*it);
			}
		}
	}

	//separate by face and keep same suit together
	vector<vector<Card*>> sameSuitDifferentFace = sameSuitButDifferent(mCards);

	if (sameSuitDifferentFace.size() < 2) { return marriageCards; }

	//generate all meld combinations
	marriageCards = allMeldCombinations(mCards, sameSuitDifferentFace);

	return marriageCards;
}

/* *********************************************************************
Function Name: checkRoyalMarriage
Purpose: To know if the cards make Royal Marriage meld
Parameters:
		cards, A vector containing Card pointers
Return Value: A vector containing vectors with Card pointers that make Royal Marriage
Local Variables:
		marriageCards, a vector containing vectors with Card pointers that make Royal Marriage
		sameFaceDifferentSuit, Has all cards of same face but cards having same suit in
								separate vectors
		mCards, A vector containing cards that are not already involved in marriage
Algorithm:
		1) From cards, check if each card has face Q or K of trump suit
		2) If the validation above is true, check if it already has been involved in Royal Marriage
		3) If the card does not have Marriage, add to a vector and push the vector to separate by suit
		4) If the vector separated by suit has size less than 2, no Royal Marriage
		5) Use helper function allMeldCombinations to get all meld combinations from the vector
		6) Return the vector containing vectors with Card pointers that make Royal Marriage
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::checkRoyalMarriage(vector<Card*> cards) {
	vector<vector<Card*>> royalMarriageCards;
	int index = 0;
	vector<Card*> rmCards;
	vector<Card*>::iterator it;

	//Check if each card is a queen or king among trump suit cards
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->getFace() == 'Q' || (*it)->getFace() == 'K') {
			if ((*it)->getMeldsMap().count("royal marriage") == 0) {
				(*it)->setUniqueIndex(index);
				index += 1;
				rmCards.push_back(*it);
			}
		}
	}
	//separate by face and keep same suit together
	vector<vector<Card*>> sameSuitDifferentFace = sameSuitButDifferent(rmCards);

	if (sameSuitDifferentFace.size() < 2) { return royalMarriageCards; }

	//generate all meld combinations
	royalMarriageCards = allMeldCombinations(rmCards, sameSuitDifferentFace);

	return royalMarriageCards;
}

/* *********************************************************************
Function Name: checkFlush
Purpose: To know if the cards make flush meld
Parameters:
		cards, A vector containing Card pointers
Return Value: A vector containing vectors with Card pointers that make flush
Local Variables:
		marriageCards, a vector containing vectors with Card pointers that make flush
		sameFaceDifferentSuit, Has all cards of same face but cards having same suit in
								separate vectors
		mCards, A vector containing cards that are not already involved in flush
Algorithm:
		1) From cards, check if each card is not a 9
		2) If the validation above is true, check if it already has been involved in flush
		3) If the card does not have flush, add to a vector and push the vector to separate by face
		4) If the vector separated by face has size less than 5, no flush
		5) Use helper function allMeldCombinations to get all meld combinations from the vector
		6) Return the vector containing vectors with Card pointers that make flush
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::checkFlush(vector<Card*> cards) {
	
	int index = 0;
	vector<Card*> flushCards;
	vector<vector<Card*>> flushMelds;
	vector<Card*>::iterator it;

	//Check if each card is not 9 and has no previous flush
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->getFace() != '9') {
			if ((*it)->getMeldsMap().count("flush") == 0) {
				(*it)->setUniqueIndex(index);
				index += 1;
				flushCards.push_back(*it);
			}
		}		
	}

	//Cards separated by face 
	vector<vector<Card*>> sameSuitDifferentFace = sameSuitButDifferent(flushCards);

	if (sameSuitDifferentFace.size() < 5) { return flushMelds; }

	//generate meld combinations
	flushMelds = allMeldCombinations(flushCards, sameSuitDifferentFace);
	
	return flushMelds;		
}


/* *********************************************************************
Function Name: allMeldCombinations
Purpose: To create all possible meld combinations
Parameters: 
		cards, A vector containing Card pointers
		sameSuitDifferentFace, Has all cards of same suit but cards having same face in
								separate vectors
Return Value: A vector containing vectors with all meld combinations
Local Variables:
		meldCombinations, A vector containing vectors with all meld combinations
		possibleMelds, A vector containing vectors of integers that contain all meld
						combinations as an integer
Algorithm:
		1) Get all possible paths using a helper function to generate meldcombinations
		2) Store all combinations in a vector containing vector of integers
		3) The integers are unique indexes of each card so from the integer meld 
			combianations, get the corresponding cards and push into the vector
		4) Return the vector that contains all meld combinations
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::allMeldCombinations(vector<Card*> cards, vector<vector<Card*>> sameSuitDifferentFace) {

	vector<vector<Card*>> meldCombinations;
	vector<vector<int>> possibleMelds = getPossibleMeldPaths(cards, sameSuitDifferentFace);

	for (int i = 0; i < possibleMelds.size(); i++) {
		vector<Card*> temp;
		for (int j = 0; j < possibleMelds[i].size(); j++) {
			for (Card* card : cards) {
				if (card->getUniqueIndex() == possibleMelds[i][j]) {
					temp.push_back(card);
				}
			}
		}
		meldCombinations.push_back(temp);
		temp.empty();
	}

	return meldCombinations;
}

/* *********************************************************************
Function Name: sameSuitButDifferent
Purpose: To separate cards having same suit by face
Parameters: cards, A vector containing Card pointers
Return Value: A vector of vectors where cards of same suit are separated by face
Local Variables:
		sameSuitDifferentFace, Has all cards of same suit but cards having same face in
								separate vectors
Algorithm:
		1) If the vector is empty, add the card
		2) Check if duplicate faced card exists in the vector passed in parameter
		3) If exists, push the card into the vector
		4) Else, create a new vector with same face and add the card to the vector
		5) Push the vector with same face to the main vector containing vectors where
			cards of same suit are separeated by face
		6) Return the main vector containing vector of Card pointers
Assistance Received: None
********************************************************************* */
vector<vector<Card*>> Player::sameSuitButDifferent(vector<Card*> cards) {

	vector<vector<Card*>> sameSuitDifferentFace;
	vector<Card*>::iterator it;

	for (it = cards.begin(); it != cards.end(); ++it) {
		if (sameSuitDifferentFace.size() > 0) {
			for (int i = 0; i < sameSuitDifferentFace.size(); i++) {
				//The 0 here is the first index for a vector containing card pointers
				if (duplicateFacedCard(sameSuitDifferentFace[i][0], *it)) {
					sameSuitDifferentFace[i].push_back(*it);
					break;
				}
				else if (i == sameSuitDifferentFace.size() - 1) {
					vector<Card*> sameFace;
					sameFace.push_back(*it);
					sameSuitDifferentFace.push_back(sameFace);
					break;
				}
			}
		}
		else {
			vector<Card*> sameFace;
			sameFace.push_back(*it);
			sameSuitDifferentFace.push_back(sameFace);
		}
	}

	return sameSuitDifferentFace;
}


/* *********************************************************************
Function Name: getPossibleMeldPaths
Purpose: To get all possible paths using DFS in a graph
Parameters:
		suitCards, A vector containing Card pointers
		sameSuitDifferentFace, Has all cards of same suit but cards having same face in
							   separate vectors or same face but having same suit in separate 
							   vectors
Return Value:A vector containing vector of integers that contain paths 
Local Variables: 
		possibleMelds, A vector containing vector of integers having paths returned from Graph
Algorithm: 
		1) Generate edges for graph using each card's unique index and send to Graph for DFS
		2) Include paths starting from all cards in the starting vector to all cards in the 
				last vector element so all possible paths are received.
		3) Return the vector containing vector of integers that contain paths
Assistance Received: None
********************************************************************* */
vector<vector<int>> Player::getPossibleMeldPaths(vector<Card*> suitCards ,vector<vector<Card*>> sameSuitDifferentFace) {

	//This part evaluates indexes for all cards and sends to graph

	Graph graph(suitCards.size());

	//generates edges for graph now send to graph 
	if (sameSuitDifferentFace.size() > 1) {
		for (int i = 0; i < sameSuitDifferentFace.size(); i++) {
			if (i < sameSuitDifferentFace.size() - 1) {
				vector<vector<int>> pairs = getPathPairs(sameSuitDifferentFace[i], sameSuitDifferentFace[i + 1]);
				for (int i = 0; i < pairs.size(); i++) {
					graph.addEdge(pairs[i][0], pairs[i][1]);
				}
			}
		}
	}
	
	graph.evaluateAllPaths(sameSuitDifferentFace[0][0]->getUniqueIndex(), sameSuitDifferentFace[sameSuitDifferentFace.size() - 1][0]->getUniqueIndex());
	if (sameSuitDifferentFace[0].size() > 1) {
		graph.evaluateAllPaths(sameSuitDifferentFace[0][1]->getUniqueIndex(), sameSuitDifferentFace[sameSuitDifferentFace.size() - 1][0]->getUniqueIndex());
	}
	if (sameSuitDifferentFace[sameSuitDifferentFace.size() - 1].size() > 1) {
		graph.evaluateAllPaths(sameSuitDifferentFace[0][0]->getUniqueIndex(), sameSuitDifferentFace[sameSuitDifferentFace.size() - 1][1]->getUniqueIndex());
		if (sameSuitDifferentFace[0].size() > 1) {
			graph.evaluateAllPaths(sameSuitDifferentFace[0][1]->getUniqueIndex(), sameSuitDifferentFace[sameSuitDifferentFace.size() - 1][1]->getUniqueIndex());
		}
	}
	//Get all paths and return the paths
	vector<vector<int>> possibleMelds = graph.getAllPaths();
	return possibleMelds;
	
}

/* *********************************************************************
Function Name: getPathPairs
Purpose: To generate integer values as vertices to evaluate all paths between two 
			adjacent vectors
Parameters:
		vec1, A vector containing Card pointers
		vec1, A vector containing Card pointers		
Return Value:A vector containing vector of integers that contain pair values for the Graph
Local Variables:
		pairs, A vector containing vector of integers that contain pair values for the Graph
Algorithm:
		1) For each card in one vector, iterate over all cards in another vector
		2) Get the unique integer index from each card, create pair and push it to the vector 
			containing all pairs
		3) Return the vector containing vectors with integer pairs
Assistance Received: None
********************************************************************* */
vector<vector<int>> Player::getPathPairs(vector<Card*> vec1, vector<Card*> vec2) {

	vector<vector<int>> pairs;

	for (int i = 0; i < vec1.size(); i++) {
		//Iterate over all elements of the adjacent vector to get pairs
		for (int j = 0; j < vec2.size(); j++) {
			vector<int> myVec;
			myVec.push_back(vec1[i]->getUniqueIndex());
			myVec.push_back(vec2[j]->getUniqueIndex());
			pairs.push_back(myVec);
		}
	}
	return pairs;
}

/* *********************************************************************
Function Name: duplicateFacedCard
Purpose: To know if the cards are exact duplicates 
Parameters:
		card1, A Card pointer
		card2, Another Card pointer
Return Value:boolean true if cards are duplicates, if not then false
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::duplicateFacedCard(Card* card1, Card* card2) {

	if (card1->getFace() == card2->getFace() && card1->getSuit() == card2->getSuit()) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: getCardWithMaxPoints
Purpose: To get the card with maximum worth points 
Parameters:
		cards, A vector containing card pointers 
Return Value:A Card pointer for the card having maximum points
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Card* Player::getCardWithMaxPoints(vector<Card*> cards) {

	Card* maxCard = cards[0];

	vector<Card*>::iterator it;

	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->getPointsWorth() >= maxCard->getPointsWorth()) {
			maxCard = *it;
		}
	}

	return maxCard;
}

/* *********************************************************************
Function Name: getCardWithMinpoints
Purpose: To get the card with minimum points
Parameters:
		cards, A vector containing card pointers
Return Value:A Card pointer for the card having minimum points
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Card* Player::getCardWithMinPoints(vector<Card*> cards) {
	Card* minCard = cards[0];

	vector<Card*>::iterator it;

	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->getPointsWorth() < minCard->getPointsWorth()) {
			minCard = *it;
		}
	}
	return minCard;
}

/* *********************************************************************
Function Name: helpLeadCard
Purpose: To deal with help regarding lead card selection
Parameters: None
Return Value:A Card pointer for the lead card
Local Variables: 
		playedCard, The card about to be played for the turn
		cardsNotInMelds, A vector of Card pointers that have cards not in any melds
		trumpCardsNotInMelds, A vector of trump Card pointers not in melds 
		nonTrumpCardsNotInMelds, A vector of non trump Card pointers not in melds
		reason, reason for playing the card
Algorithm: 
		1) Update all cards for selection
		2) Create all possible melds
		3) Get separate vectors for trump and non trump cards that are not in any melds
		4) Among trump cards not in melds, get the card with maximum points and play the card
		5) If non trump card not in melds is available, play the card having maximum points from non
			trump cards not in any melds
		6) If no cards are not in any melds, get the card having maximum points from the meld 
			having lowest points worth and play the card
		7) Set the reason for all steps accordingly
Assistance Received: None
********************************************************************* */
Card* Player::helpLeadCard() {

	updateAvailableCardsForSelection();
	createAllPossibleMelds();
	Card* playedCard = new Card;
	string reason = "";

	vector<Card*> cardsNotInMelds = cardsNotCreatingMelds();
	vector<Card*> trumpCardsNotInMelds;
	vector <Card*> nonTrumpCardsNotInMelds;

	//Update the vectors declared above

	for (auto i = 0; i < cardsNotInMelds.size(); i++) {
		if (cardsNotInMelds[i]->getSuit() == trump_suite) {
			trumpCardsNotInMelds.push_back(cardsNotInMelds[i]);
		}
		else {
			nonTrumpCardsNotInMelds.push_back(cardsNotInMelds[i]);
		}
	}

	//Among trump cards not in melds, get the card with maximum points and play the card
	if (trumpCardsNotInMelds.size() > 0) {
		playedCard = getCardWithMaxPoints(trumpCardsNotInMelds);
		play_reason = " as it does not affect any melds and is the card with highest point.";
	}
	//If non trump card not in melds is available, play the card having maximum points from non
	//trump cards not in any melds
	else if (nonTrumpCardsNotInMelds.size() > 0) {
		playedCard = getCardWithMaxPoints(nonTrumpCardsNotInMelds);
		play_reason = " as it does not affect any melds and is the card with highest point.";
	}
	else {
		//* is because there are total 9 possible melds in the meldsByPoints string array sorted by points max to min 
		for (int i = 8; i >= 0; i--) {
			if (allPossibleMelds[meldsByPoints[i]].size() > 0) {
				vector<Card*> tempVec = allPossibleMelds[meldsByPoints[i]][0];
				playedCard = getCardWithMaxPoints(tempVec);
			}
		}
		play_reason = " as it uses the meld with least point.";
	}

	return playedCard;		

}

/* *********************************************************************
Function Name: helpChaseCard
Purpose: To deal with help regarding chase card selection
Parameters: 
		leadCard, A Card pointer for lead card
Return Value:A Card pointer for the chase card
Local Variables:
		min, The card about to be played for the turn
		cardsWithMorePoints, A vector of Card pointers of cards with more points than lead card and same suit
		trumpCardWithMorePoints, A vector of pointers of trump Card with more points than lead card
		trumpCards, A vector of Card pointers of cards of trump suit
		nontrumpCards, A vector with pointers for cards not of trump suite
		play_reason, reason for playing the card
Algorithm:
		1) Update all cards for selection
		2) Update all vectors for trumpCards, nonTrumpCards, cards with more points than the lead card and 
			trump cards with more points than the lead card
		3) If cards of same suit and more points are available, select the card with min points and play
		4) Else, check if trumpo cards are available and play the trump card with lease point
		5) If no winning card is found, get card with minimum points from non trump cards and play
		6) Return the played card and update the play_reason accordingly
Assistance Received: None
********************************************************************* */
Card* Player::helpChaseCard(Card* leadCard) {

	updateAvailableCardsForSelection();
	play_reason = " to win the turn.";

	Card*  minCard;
	// cards with more points than lead card and same suit
	vector<Card*> cardsWithMorePoints;

	//trump cards with more points than lead card
	vector<Card*> trumpCardWithMorePoints;

	//cards of trump suit
	vector<Card*> trumpCards;

	//cards not of trump suite
	vector<Card*> nontrumpCards;

	//Update all card vectors above
	for (auto i = 0; i < availableCardsForSelection.size(); i++) {
		if ( availableCardsForSelection[i]->getSuit() == trump_suite) {
			trumpCards.push_back(availableCardsForSelection[i]);
		}
		else {
			nontrumpCards.push_back(availableCardsForSelection[i]);
		}
	}

	for (auto i = 0; i < availableCardsForSelection.size(); i++) {
		if (availableCardsForSelection[i]->getPointsWorth() > leadCard->getPointsWorth() && availableCardsForSelection[i]->getSuit() == leadCard->getSuit()) {
			cardsWithMorePoints.push_back(availableCardsForSelection[i]);
		}
	}

	//search for larger card of same suite
	if (cardsWithMorePoints.size() > 0 ) {
		minCard = getCardWithMinPoints(cardsWithMorePoints);
		if (minCard->getPointsWorth() > leadCard->getPointsWorth()) {
			minCard = minCard;			
			play_reason = " as it is a larger card of the same suit.";
		}
	}
	//If needed to play trump card
	else if (trumpCards.size() > 0 && leadCard->getSuit() != trump_suite) {
		minCard = getCardWithMinPoints(trumpCards);
		play_reason = " as it is a trump card and there is no winning card of other suit.";
	}
	else {
		//get the card with lowest points
		minCard = getCardWithMinPoints(nontrumpCards);
		play_reason = " as there is no winning card and it is the card with least points.";
	}		
	return minCard;
}

/* *********************************************************************
Function Name: updateHandPile
Purpose: To get update the player's hand pile after a card is played for a turn
Parameters:
		card, A Card pointer for the played card
Return Value:None
Local Variables: None
Algorithm: 
		1) If card from hand, delete from hand
		2) If card not from hand, delete from meld cards and replace corresponding cards to hand
Assistance Received: None
********************************************************************* */
void Player::updateHandPile(Card* card) {

	if (find(cards_in_hand.begin(), cards_in_hand.end(), card) != cards_in_hand.end()) {
		vector<Card*>::iterator it;
		for (it = cards_in_hand.begin(); it != cards_in_hand.end(); ++it) {
			if (*it == card) {
				turn_card = *it;
				cards_in_hand.erase(it);
				break;
			}
		}
	}
	//if from meld pile
	else {
		turn_card = card;
		replaceCorrespondingCards(card);
	}
}

/* *********************************************************************
Function Name: checkForStar
Purpose: To check if the card needs a star in the meld pile i.e. more than 1 active melds
Parameters:
		card, A Card pointer for a particular card
Return Value: Boolean true if needs a star, false if does not need star
Local Variables: 
		count, an integer count to count the number times the card appears in meld pile
Algorithm:
		1) If card has more than one active meld, check if it occurs multiple times in meld pile
		2) If yes, return true. else, return false.
Assistance Received: None
********************************************************************* */
bool Player::checkForStar(Card* card) {

	int count = 0;

	if (moreThanOneActiveMeld(card)) {		
		vector<vector<Card*>>::iterator it;
		//Check if the card occurs multiple times in the meld pile
		for (it = meld_pile.begin(); it != meld_pile.end(); ++it) {
			vector<Card*> vec = *it;
			for (auto i = 0; i < vec.size(); i++){
				if (vec[i] == card) {
					count += 1;
				}
			}
		}
	}
	if (count >= 2) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: moreThanOneActiveMeld
Purpose: To check if a card is involved in more than one active meld
Parameters:
		card, A Card pointer for a particular card
Return Value: Boolean true if needs a more than 1 meld, false if not
Local Variables:
		activeMelds, an integer count to count the number active melds
		melds, A map where the card's melds map is stored
Algorithm:
		1) Search in the melds map of the card if the map has more than 1 melds
		2) For each card in melds, check if the main card is present in that particular
			card's melds map to ensure that it is an active meld
		3) Count the number of active melds and if it is >=2, return true
Assistance Received: None
********************************************************************* */
bool Player::moreThanOneActiveMeld(Card* card) {
	
	map<string, vector<Card*>> melds = card->getMeldsMap();

	int activeMelds = 0;

	for (const auto &myKey : melds) {
		vector<Card*> vec = myKey.second;
		vector<Card*>::iterator it;
		//Check in each card map to ensure that it is an active meld
		for (it = vec.begin(); it != vec.end(); ++it) {
			if (searchInMeldsMap(card, *it)) {
				activeMelds += 1;
				break;
			}
		}
	}
	if (activeMelds >= 2) {
		return true;
	}
	return false;
}


/* *********************************************************************
Function Name: searchInMeldsMap
Purpose: To check if a card is present in the melds map of secondary card
Parameters:
		mainCard, A Card pointer for card which is searched 
		secondaryCard, A Card pointer whose melds map is searched
Return Value: Boolean true if the card is found in secondary card's melds map
Local Variables:
		melds, A map where the secondary card's melds map is stored
Algorithm: 
	1) Search if the main card is present in secondary card's melds map
	2) Return true if found, false if not
Assistance Received: None
********************************************************************* */ 
bool Player::searchInMeldsMap(Card* mainCard, Card* secondaryCard) {

	map<string, vector<Card*>> melds = secondaryCard->getMeldsMap();

	for (const auto &myKey : melds) {
		vector<Card*> vec = myKey.second;
		vector<Card*>::iterator it;
		for (it = vec.begin(); it != vec.end(); ++it) {
			if ((*it) == mainCard) {
				return true;
			}
		}
	}

	return false;
}

/* *********************************************************************
Function Name: storeHandCards
Purpose: To store cards in hand from cards loaded from file
Parameters:
		cards, String value of cards in the hand pile 
Return Value: None
Local Variables: None
Algorithm:
	1) Get each card using stringstream
	2) Make a new card, set face and suit and push to hand pile
Assistance Received: None
********************************************************************* */
void Player::storeHandCards(string cards) {
	string str;
	stringstream ss(cards);
	while (getline(ss, str, ' ')) {
		if (isalpha(str[0]) || str[0] == '9') {
			Card* card = new Card;
			//0 and 1 are the first and second index which is the face and suit value
			card->setFace(str[0]);
			card->setSuit(str[1]);
			cards_in_hand.push_back(card);
		}
	}

}

/* *********************************************************************
Function Name: storeCapturedCards
Purpose: To store cards in capture pile from cards loaded from file
Parameters:
		cards, String value of cards in the capture  pile
Return Value: None
Local Variables: None
Algorithm:
	1) Get each card using stringstream
	2) Make a new card, set face and suit and push to capture pile
Assistance Received: None
********************************************************************* */
void Player::storeCapturedCards(string cards) {

	string str;
	stringstream ss(cards);
	while (getline(ss, str, ' ')) {
		if (isalpha(str[0]) || str[0] == '9') {
			Card* card = new Card;
			//0 and 1 are the first and second index which is the face and suit value
			card->setFace(str[0]);
			card->setSuit(str[1]);
			capture_pile.push_back(card);
		}
	}
}


/* *********************************************************************
Function Name: updateLoadScores
Purpose: To update player's scores received as string from file
Parameters:
		scores, String value of scores of the player
Return Value: None
Local Variables: None
Algorithm:
	1) Get each number using stringstream
	2)Update game and round score for the player
Assistance Received: None
********************************************************************* */
void Player::updateLoadScores(string scores) {

	//remove all spaces
	string::iterator end_pos = remove(scores.begin(), scores.end(), ' ');
	scores.erase(end_pos, scores.end());

	string str;
	stringstream ss(scores);
	int index = 0;
	while (getline(ss, str, '/')) {
		if (index == 0) {
			game_score = stoi(str);
			index += 1;
		}
		else if (index == 1) {
			round_score = stoi(str);
		}
	}

}


/* *********************************************************************
Function Name: setMeldsFromLoad
Purpose: To set the meld pile received as string loaded from file
Parameters:
		cards, String containing cards in a meld pile
Return Value: None
Local Variables: 
		starPile, a vector of Card pointers of the cards that need a star
		starPileString, a vector of strings that has cards as string if a card needs star
		allMeldsInVec, a vector of vectors containing Card pointers of all meld combinations
		meldsInVec, All meld cards converted from string for each meld combination
Algorithm:
	1) Get melds in string, convert it to cards and push into a vector of Card pointers
	2) For each meld, if the card has a star, search in star pile
	3) If not found in star pile, add to star pile 
	4) Else, Create a card with same name as one similar in star pile, and check if meld present in melds map
	5) If meld not present, add meld for the card
	6) Else, Search for another similar card, and add meld if meld not present
	7) If another similar card not found, add a new card to star pile
	8) Update the map for all cards in melds and add the vector into meld pile
	9) If the card with star has only one active meld, get card with same face and suit and assign 
		one of its meld to self. 
	10) Update meld pile.
Assistance Received: None
********************************************************************* */
void Player::setMeldsFromLoad(string cards) {	

	string str;
	stringstream ss(cards);
	vector<Card*> starPile;
	vector<string> starPileString;
	vector<vector<Card*>> allMeldsInVec;

	while (getline(ss, str, ',')) {
		str = removeSpaceFromFrontAndBack(str);
		string each;
		stringstream ss2(str);
		vector<string> meldsInString;
		while (getline(ss2, each, ' ')) {
			//each has each unique card but in string
			meldsInString.push_back(each);
		}
		vector<Card*> meldsInVec = makeCardsFromString(meldsInString);
		string meldName = getMeldName(meldsInVec);
		for (int i = 0; i < meldsInString.size(); i++) {
			//if has star
			if (meldsInString[i].size() > 2) {
				string cardName = meldsInString[i].substr(0, 2);
				//if found in starpile
				if (searchCard(cardName, starPile)) {
					if (find(starPileString.begin(), starPileString.end(), cardName)==starPileString.end()) {
						starPileString.push_back(cardName);
					}					
					Card* card = getCardWithSameFace(cardName, starPile);
					//meld not present then add meld
					if (!checkMeldNameInMap(meldName, card)) {
						replaceCardWithOriginalCard(card, meldsInVec);
					}
					else {
						//if meld found then need to search in another 
						if (getCountOfSimilarCards(card, starPile) > 1) {
							Card* card = getAnotherCardWithSameFace(cardName, starPile);
							//meld not present then add meld, which original kanda does
							if (!checkMeldNameInMap(meldName, card)) {
								replaceCardWithOriginalCard(card, meldsInVec);
							}
						}
						else {
							Card* card = getCardWithSameFace(cardName, meldsInVec);
							starPile.push_back(card);
						}
					}
				}
				else {
					Card* card = getCardWithSameFace(cardName, meldsInVec);
					starPile.push_back(card);
				}

			}
		}
		//update meld piles of map
		updateCardMeldsMap(meldsInVec);
		//meld_pile.push_back(meldsInVec);
		allMeldsInVec.push_back(meldsInVec);
				
	}

	//get the card which has star but only one meld, find a missing meld and assign it to self
	for (auto i = 0; i < starPileString.size(); i++) {
		Card* oneMeldCard = new Card;
		Card* multipleMeldsCard = new Card;
		if (countCardsWithSameInfo(allMeldsInVec, starPileString[i], oneMeldCard, multipleMeldsCard) > 1) {			
			if (oneMeldCard->getMeldsMap().size() == 1 ) {
				string missingMeld = getMissingMeldName(oneMeldCard, multipleMeldsCard);
				vector<Card*> missingMeldVec = replaceMissingMeld(oneMeldCard, multipleMeldsCard, missingMeld);
				replaceAllMeldsInVec(allMeldsInVec, missingMeldVec);
			}
		}
	}

	for (vector<vector<Card*>>::iterator it = allMeldsInVec.begin(); it != allMeldsInVec.end(); ++it) {
		meld_pile.push_back(*it);
	}

}


/* *********************************************************************
Function Name: replaceAllMeldsInVec
Purpose: To Replace a certain meld in vector containing melds
Parameters:
		allMeldsVec, A vector of vectors where melds are stored
Return Value: None
Local Variables: 
		pos, An integer value that is the position of the searched meld in the 
				vector containing all melds 
Algorithm:
	1) Get the position of the meld 
	2) Delete the meld from vector containing all melds using position and 
		replace the meld by the meld sent in parameter
Assistance Received: None
********************************************************************* */
void Player::replaceAllMeldsInVec(vector<vector<Card*>>& allMeldsVec, vector<Card*> cards) {
	
	int pos = 0;
	for (vector<vector<Card*>>::iterator it = allMeldsVec.begin(); it != allMeldsVec.end(); ++it) {
		vector<Card*> vec = *it;
		string meld = getMeldName(vec);
		if (getMeldName(cards) == meld) {
			break;
		}
		pos += 1;
	}
	
	allMeldsVec.erase(allMeldsVec.begin() + pos);
	allMeldsVec.push_back(cards);

}

/* *********************************************************************
Function Name: replaceMissingMeld
Purpose: To add missing meld in oneMeldCard from multipleMeldsCard 
Parameters:
		oneMeldCard, The card in which the meld with 'meldname' is added 
		multipleMeldscard, The card from which a meld is moved to another card's meld map
		meldName, It is the name of the meld that is being moved
Return Value: A vector of Card Pointers that contains cards in a meld
Local Variables:
		cardMeldsMap = The  melds map of card which has multiple melds
		meldCards = the cards with the meld that is being moved
Algorithm:
	1) Search for the meld and sotre in a vector
	2) Delete the meld from melds map of the card with multiple melds
	3) Put the vector into the map of card with only one meld
	4) Return the vector of cards in meld
Assistance Received: None
********************************************************************* */
vector<Card*> Player::replaceMissingMeld(Card* oneMeldCard, Card* multipleMeldsCard, string meldName) {

	map<string, vector<Card*>> cardsMeldsMap = multipleMeldsCard->getMeldsMap();
	vector<Card*> meldCards;

	for (const auto &myKey : cardsMeldsMap) {
		if (myKey.first == meldName) {
			meldCards = myKey.second;
			break;
		}
	}
	
	//delete the meld from multipleMeldCard's map
	multipleMeldsCard->removeMeld(meldName);

	//delete the meld from all associated cards
	for (vector<Card*>::iterator it = meldCards.begin(); it != meldCards.end(); ++it) {
		(*it)->removeMeld(meldName);
	}	
	
	//put it into oneMeldCard's map i.e. put oneMeldCard into meldCards
	meldCards.push_back(oneMeldCard);
	updateCardMeldsMap(meldCards);

	return meldCards;

}

/* *********************************************************************
Function Name: replaceMissingMeld
Purpose: To get the name of missing meld from one meld card to multiple melds card
Parameters:
		oneMeldCard, The card in which the meld 'meldname' is added
		multipleMeldscard, The card from which a meld is moved to another card's meld map
Return Value: A string value that is the name of meld missing in one card
Local Variables:
		cardMeldsMap = The  melds map of card which has multiple melds
Algorithm:
	1) For each meld inmap of card with multiple melds, check if the meld is 
		present in the map of card with one meld. 
	2) If meld not found, return the name of the meld
Assistance Received: None
********************************************************************* */
string Player::getMissingMeldName(Card* oneMeldCard, Card* multipleMeldsCard) {

	map<string, vector<Card*>> cardsMeldsMap = multipleMeldsCard->getMeldsMap();

	for (const auto &myKey : cardsMeldsMap) {
		if (!checkMeldNameInMap(myKey.first, oneMeldCard)) {
			return myKey.first;
		}
	}

	return "None";
}


/* *********************************************************************
Function Name: countCardsWithSameInfo
Purpose: To get the name of missing meld from one meld card to multiple melds card
Parameters:
		cards, A vector with vectors containing Card pointers 
		cardWithSingleMeld, The card in which the meld 'meldname' is added
		cardWithMultipleMelds, The card from which a meld is moved to another card's meld map
		cardName, The face of the card and suit in string
Return Value: An integer value that is the count of the card with name cardName in the vector
				containing vector with Card pointers. 
Local Variables:
		singleCard, A card storing the pointer with the card having the name and suit
						as the string cardName
Algorithm:
	1) For each vector in the vector of vectors cards, search for a card with face and suit 
		same as the string cardName. 
	2) Access the cards melds map and count the number of melds
	3) If the number of melds is less than equal to 1, assign the card to cardWithSingleMeld
	4) If the number of melds is greater than 1, assign the card to card with multiple melds
	5) Return the count of the number of same faced cards
Assistance Received: None
********************************************************************* */
int Player::countCardsWithSameInfo(vector<vector<Card*>> cards, string cardName, Card*& cardWithSingleMeld, Card*& cardWithMultipleMelds) {

	
	int mainCount=0;
	for (vector<vector<Card*>>::iterator it = cards.begin(); it != cards.end(); ++it) {
		vector<Card*> vec = *it;
		if (searchCard(cardName, vec)) {
			mainCount += 1;
			Card* singleCard = getCardWithSameFace(cardName, vec);
			map<string, vector<Card*>> cardsMeldsMap = singleCard->getMeldsMap();
			int count = 0;
			for (const auto &myKey : cardsMeldsMap) {
				count += 1;
			}
			//if less then one equal to 1 meld present 
			if (count <= 1) {
				cardWithSingleMeld = singleCard;
			}
			//if more than 1 meld present
			else {
				cardWithMultipleMelds = singleCard;
			}
		}
	}
	return mainCount;
}


/* *********************************************************************
Function Name: replaceCardWithOriginalCard
Purpose: To replace the duplicate card with an original card
Parameters:
		card, The card which is being added to a vector
		cards, The vector, containing Card pointers, in which a card is being replaced
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::replaceCardWithOriginalCard(Card* card, vector<Card*>& cards) {

	vector<Card*>::iterator it;
	char face = card->getFace();
	char suit = card->getSuit();
	for (it = cards.begin(); it != cards.end(); ++it) {
		if ((*it)->getSuit() == suit && (*it)->getFace() == face) {
			*it = card;
		}
	}

}

/* *********************************************************************
Function Name: getCountOfSimilarCards
Purpose: To get the count with same face and suit in a vector
Parameters:
		card, The card which is being counted
		cards, The vector where the number of cards are counted
Return Value: the integer value of the count of similar cards
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
int Player::getCountOfSimilarCards(Card* card, vector<Card*> cards) {

	char cardFace = card->getFace();
	char cardSuit = card->getSuit();
	vector<Card*> sameCards;
	vector<Card*>::iterator it;

	int count = 0;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (cardFace == (*it)->getFace() && cardSuit == (*it)->getSuit()) {
			count += 1;
		}
	}

	return count;

}


/* *********************************************************************
Function Name: getCardWithSameFace
Purpose: To get the card with face and suit as in string cardName
Parameters:
		cardName, The name of the card i.e. the face and the suite together
		cards, The vector where the card is searched
Return Value: A Card pointer of the card found
Local Variables: None
Algorithm: 
		1) Search for a card with name as the string cardName and return it
Assistance Received: None
********************************************************************* */
Card* Player::getCardWithSameFace(string cardName, vector<Card*> cards) {

	Card* finalCard = new Card;

	char cardFace = cardName[0];
	char cardSuit = cardName[1];
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (cardFace == (*it)->getFace() && cardSuit == (*it)->getSuit()) {
			return (*it);
		}
	}

}

/* *********************************************************************
Function Name: getAnotherCardWithSameFace
Purpose: To get the second card with face and suit as in string cardName
Parameters:
		cardName, The name of the card i.e. the face and the suite together
		cards, The vector where the card is searched
Return Value: A Card pointer of the card found
Local Variables: None
Algorithm:
		1) Search for a card with name as the string cardName and return 
			the card after second occurence
Assistance Received: None
********************************************************************* */
Card* Player::getAnotherCardWithSameFace(string cardName, vector<Card*> cards) {

	char cardFace = cardName[0];
	char cardSuit = cardName[1];
	vector<Card*> sameCards;
	vector<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it) {
		if (cardFace == (*it)->getFace() && cardSuit == (*it)->getSuit()) {
			sameCards.push_back(*it);
		}
	}
	//1 is being used because it is card found on second occurence
	//as there are only 2 cards of similar attributes
	return sameCards[1];
}


/* *********************************************************************
Function Name: checkMeldNameInMap
Purpose: To get the second card with face and suit as in string cardName
Parameters:
		meldName, The name of the meld to search
		card,The Card pointer to the card whose map is being searched
Return Value: Bool true if card found, false if otherwise
Local Variables: None
Algorithm:
		1) Search for a meld with the name meldName in the map of the card
			and return a boolean
Assistance Received: None
********************************************************************* */
bool Player::checkMeldNameInMap(string meldName, Card* card) {

	map<string, vector<Card*>> cardsMeldsMap = card->getMeldsMap();
	for (const auto &myKey : cardsMeldsMap) {
		if (meldName == myKey.first) {
			return true;
		}
	}

	return false;
}


/* *********************************************************************
Function Name: makeCardsFromString
Purpose: Make the elements of the string as cards
Parameters:
		strCards, A vector of string having the cards face and suit
Return Value: A vector of Card pointers of the newly created cards
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
vector<Card*> Player::makeCardsFromString(vector<string> strCards) {

	vector<Card*> cards;
	vector<string>::iterator it;

	for (it = strCards.begin(); it != strCards.end(); ++it) {

		Card* card = new Card;
		card->setFace((*it)[0]);
		card->setSuit((*it)[1]);
		cards.push_back(card);
	}
	return cards;
}


/* *********************************************************************
Function Name: removeSpaceFromFrontAndBack
Purpose: Removes the space from the front and back of the string
Parameters:
		str, a constant string str passed by reference, in which the spaces 
			are being removed
Return Value: A string with the spaces being removed
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
string Player::removeSpaceFromFrontAndBack(const string& str){

	const char* space = " \t\v\r\n";
	size_t start = str.find_first_not_of(space);
	size_t end = str.find_last_not_of(space);
	if (start == end) {
		return "";
	}
	else {
		return str.substr(start, end - start + 1);
	}

}

/* *********************************************************************
Function Name: updateCardMeldsMap
Purpose: Updates the meld map of all cards in a meld
Parameters:
		cards, A vector containing card pointers of cards in melds
Return Value: None
Local Variables: 
		meldName, The name of the melds to add into the melds map of cards
		cardsInMeld, The cards in the meld
Algorithm: 
		1) If the meld is dix, set the card itself in map with key meldName
		2) If other melds, add all other cards in a melds to a card's meld map under the key meldName
Assistance Received: None
********************************************************************* */
void Player::updateCardMeldsMap(vector<Card*> cards) {

	vector<Card*>::iterator it;
	string meldName = getMeldName(cards);
	//because there is only one card in the meld and it is self
	if (meldName == "dix") {
		vector<Card*> cardsInMeld;
		cardsInMeld.push_back(cards[0]);
		cards[0]->setMeldInMap(meldName, cardsInMeld);
	}
	else {
		for (it = cards.begin(); it != cards.end(); ++it) {
			vector<Card*> cardsInMeld;
			//For each card, add all other cards in the map
			for (vector<Card*>::iterator innerIt = cards.begin(); innerIt != cards.end(); ++innerIt) {
				if (cards.size() > 1) {
					if (*it != *innerIt) {
						cardsInMeld.push_back(*innerIt);
					}
				}
				else {
					cardsInMeld.push_back(*innerIt);
				}
			}
			(*it)->setMeldInMap(meldName, cardsInMeld);
		}
	}
}

/* *********************************************************************
Function Name: clearAllCards
Purpose: To clear all the cards a player has
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Player::clearAllCards() {

	capture_pile.clear();
	meld_pile.clear();
	cards_in_hand.clear();
	allPossibleMelds.clear();
	availableCardsForSelection.clear();
}

/* *********************************************************************
Function Name: getAllCards
Purpose: To get all cards a player has
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
vector<Card*> Player::getAllCards() {

	vector<Card*> allCards;
	updateAvailableCardsForSelection();

	allCards.insert(allCards.end(), availableCardsForSelection.begin(), availableCardsForSelection.end());
	allCards.insert(allCards.end(), capture_pile.begin(), capture_pile.end());

	return allCards;
}