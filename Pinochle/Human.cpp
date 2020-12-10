/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#include "Human.h"


/* *********************************************************************
Function Name: Human
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Human::Human()
{
}

/* *********************************************************************
Function Name: ~Human
Purpose: To delete all objects of the class
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Human::~Human()
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
		3) If leader and if the input is 1, get the lead card from player's input
			and update hand pile
		4) If the input is 2, mark the bool save_game as true to save the game
		5) If the input is 3, Show the help recommendation to the user
		5) Else,end the game
		6) If the player is not leader, show the menu and get input
		7) If input is 1, get the chase card from user's input and play the card
		8) If the menu is 2, show the help recommendation for chase card
Assistance Received: None
********************************************************************* */
Card* Human::play(Card* card) {


	playOption:
	vector<int> menuItems;

	if (isLeader()) {
		menuItems = { 1,2,3,4 };
		printMenu(menuItems);
		int input = getPlayerInput(1, 4);
		if (1 == input) {
			playNewTurn();
		}
		else if (2 == input) {
			//save game here
			save_game = true;
			return turn_card;
		}
		else if (3 == input) {
			//leader help
			Card* lCard = helpLeadCard();
			cout << "I recommend you to present " << lCard->getFace() << lCard->getSuit() << play_reason << endl;
			goto playOption;
		}
		else if (4 == input) {
			cout << "\n\nGame ended!!!" << endl;
			//system("pause");
			exit(1);

		}
	}
	else {
		//If chaser
		menuItems = { 1,3,4 };
		printMenu(menuItems);
		int input = getPlayerInput(1, 3);
		if (input == 1) {
			playNewTurn();
		}
		else if (input == 2) {
			//Show help
			Card* cCard = helpChaseCard(card);
			cout << "I recommend you to present " << cCard->getFace() << cCard->getSuit() << play_reason << endl;
			goto playOption;
		} else{
			cout << "\n\nGame ended!!!" << endl;
			system("pause");
			exit(1);
		}
	}
	
	return turn_card;
}

/* *********************************************************************
Function Name: playNewTurn
Purpose: To play a new turn
Parameters: None
Return Value: None
Local Variables: 
		selectedCard, A vector of integers containing user's input values for the selected card
Algorithm: 
		1) Identify if the player is a leader or a chaser
		2) Update all cards available for selection and get the input selection
		3) If the card is from hand, display the card and erase
		4) If the card is from meld pile, replace corresponding cards to the hand and move the 
			card to capture pile
Assistance Received: None
********************************************************************* */
void Human::playNewTurn() {
	if (isLeader()) { cout << "\nSelect a lead card: "; }
	else { cout << "\nSelect a chase card: "; }

	updateAvailableCardsForSelection();
	printCardsForSelection();
	vector<int> selectedCard = getCardsSelection(1);


	Card* playedCard = availableCardsForSelection[selectedCard[0] - 1];
	vector<Card*>::iterator it;

	//Erase from hand pile if card is selected from hand pile
	int handSize = cards_in_hand.size();
	if (selectedCard[0] <= handSize) {
		for (it = cards_in_hand.begin(); it != cards_in_hand.end(); ++it) {
			if (*it == playedCard) {
				turn_card = *it;
				cards_in_hand.erase(it);
				break;
			}
		}
	}
	else {
		//If card is selected from meld pile
		turn_card = playedCard;
		replaceCorrespondingCards(playedCard);
	}
	updateAvailableCardsForSelection();
	if (isLeader()) { cout << "Lead card: " << turn_card->getFace() << turn_card->getSuit() << endl; }
	else { cout << "Chase card: " << turn_card->getFace() << turn_card->getSuit() << endl; }
}

/* *********************************************************************
Function Name: showMeld
Purpose: To show a meld
Parameters: None
Return Value: A vector of Card pointers of cards that form a meld
Local Variables:
		meldCardsString, the vector of integer inputs that the player enters
		meldSelection, A vector of Card pointers of cards that form a meld
		leaderChoice, Users input in the menu
Algorithm:
		1) Update all cards available for selection and ask for user input
		2) If user asks for help, call the meldHelp() function
		3) Else, get the input and push back into meldSelection
Assistance Received: None
********************************************************************* */
vector<Card*> Human::showMeld() {

	meldHelpOption:
	updateAvailableCardsForSelection();
	printCardsForSelection();
	printMeldMenu();
	int leaderChoice = getPlayerInput(1, 3);
	vector<int> meldCardsString;
	vector<Card*> meldSelection;

	if (leaderChoice == 1) {
		cout << "Please select meld cards" << endl;
		meldCardsString = getCardsSelection(5);

		for (int i = 0; i < meldCardsString.size(); i++) {
			meldSelection.push_back(availableCardsForSelection[meldCardsString[i] - 1]);
		}
		
	}
	else if (leaderChoice == 2) {
		//If player asks for help
		meldHelp();
		goto meldHelpOption;
	} 	
	return meldSelection;

}

/* *********************************************************************
Function Name: meldHelp
Purpose: To recommend a meld to the user
Parameters: None
Return Value: None
Local Variables:
		meldSelection, A vector of Card pointers of cards that form a meld
Algorithm:
		1) Create all possible melds for the player
		2) From all melds, recommend the meld with the highest point
Assistance Received: None
********************************************************************* */
void Human::meldHelp() {

	updateAvailableCardsForSelection();
	createAllPossibleMelds();
	string meldName;

	vector<Card*> meldSelection;

	
	for (string meld : meldsByPoints) {
		if (allPossibleMelds[meld].size() > 0) {
			//[o] has the meld with highest precedence
			meldSelection = allPossibleMelds[meld][0];
			meldName = meld;
			break;
		}
	}

	if (meldSelection.size() > 0) {
		cout << "I recommend you to present ";
		vector<Card*>::iterator it;
		for (it = meldSelection.begin(); it != meldSelection.end(); ++it) {
			cout << (*it)->getFace() << (*it)->getSuit() << " ";
		}
		cout << " as " << meldName << " to earn " << getMeldPoints(meldName) << " points." << endl;
	}
	else {
		cout << "No possible meld combinations!!!" << endl;
	}

}
