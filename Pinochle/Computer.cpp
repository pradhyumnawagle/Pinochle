/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#include "Computer.h"


/* *********************************************************************
Function Name: Computer
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Computer::Computer()
{
	name = "Computer";
}


/* *********************************************************************
Function Name: ~Computer
Purpose: To delete all objects of the class
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Computer::~Computer()
{
}


/* *********************************************************************
Function Name: play
Purpose: To play a turn
Parameters: 
		card, A Card pointer that is either an empty card or the lead card
Return Value: A Card pointer
Local Variables: 
		menuItems, The items to print in a menu stored in an integer vector
Algorithm: 
		1) Show the menu and ask for input
		2) Validate the input and check if the player is leader
		3) If leader and if the input is 1, get the lead card from helpLeadCard and update hand pile
		4) If the input is 2, mark the bool save_game as true to save the game
		5) Else,end the game 
		6) If the player is not leader, show the menu and get input
		7) If input is 1, get the chase card from helpChaseCard and update hand pile
Assistance Received: None
********************************************************************* */
Card* Computer::play(Card* card) {

	vector<int> menuItems;
	//If the player is leader
	if (isLeader()) {
		menuItems = { 1,2,4 };
		printMenu(menuItems);
		int input = getPlayerInput(1, 3);
		if (input == 1) {
			updateHandPile(helpLeadCard());
			cout << "The computer chose to play lead card -> " << turn_card->getFace() << turn_card->getSuit() << play_reason << endl;
		}
		else if (input == 2) {
			save_game = true;
		}
		else {
			cout << "\n\nGame ended!!!" << endl;
			system("pause");
			exit(1);
		}
	}
	else {
		//Chase card tactics
		menuItems = { 1,4 };
		printMenu(menuItems);
		int input = getPlayerInput(1,2);
		if (input == 1) {
			updateHandPile(helpChaseCard(card));
			cout << "The computer chose to play chase card -> " << turn_card->getFace() << turn_card->getSuit() << play_reason << endl;
		} else{
			cout << "\n\nGame ended!!!" << endl;
			system("pause");
			exit(1);
		}
	}		

	updateAvailableCardsForSelection();
	return turn_card;
}


/* *********************************************************************
Function Name: showMeld
Purpose: To show a meld 
Parameters: None
Return Value: A vector of Card pointers of cards that form a meld
Local Variables: 
		meldName, The name of meld that the player showed
		meldSelection, A vector of Card pointers of cards that form a meld 
Algorithm: 
		1) Create all possible melds for the player
		2) From the map of all possible melds, show the meld with most points
		3) Return the mvector of cards in the meld
Assistance Received: None
********************************************************************* */
vector<Card*> Computer::showMeld() {

	updateAvailableCardsForSelection();
	createAllPossibleMelds();
	string meldName;

	vector<Card*> meldSelection;	
	
	for (string meld : meldsByPoints) {
		if (allPossibleMelds[meld].size() > 0) {
			meldSelection = allPossibleMelds[meld][0];
			meldName = meld;
			break;
		}
	}

	if (meldSelection.size() > 0) {

		cout << "The computer chose to show " << meldName << " because it is the best possible meld." << endl;
		printCards(meldSelection);
		//system("pause");
	}
	else {
		cout << "No possible meld combinations!!!" << endl;
	}
	return meldSelection;
}
