/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#include "Deck.h"


/* *********************************************************************
Function Name: Deck
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Create a new deck for the round
Assistance Received: None
********************************************************************* */
Deck::Deck()
{
	current_deck = {};
	createDeck();
}


/* *********************************************************************
Function Name: ~Deck
Purpose: To delete all objects of the class.
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Deck::~Deck()
{
}

/* *********************************************************************
Function Name: shuffleDeck
Purpose: To shuffle all cards in a deck
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Shuffle all cards in the current deck using random_shuffle function
Assistance Received: None
********************************************************************* */
void Deck::shuffleDeck() {

	srand(time(NULL));
	random_shuffle(current_deck.begin(), current_deck.end());
}

/* *********************************************************************
Function Name: createDeck
Purpose: To create a new deck of cards
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Generate cards and assign it to current deck
Assistance Received: None
********************************************************************* */
void Deck::createDeck() {

	current_deck = generateCards();
}

/* *********************************************************************
Function Name: printDeck
Purpose: To print all cards from current deck
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Print all cards in current deck using vector<Card*> iterator
Assistance Received: None
********************************************************************* */
void Deck::printDeck() {

	vector<Card*>::iterator it;
	for (it = current_deck.begin(); it != current_deck.end(); ++it) {
		cout << *it << " -> " << (*it)->getFace() << (*it)->getSuit()  << " " << (*it)->getPointsWorth()<< endl;
	}
}


/* *********************************************************************
Function Name: getNewDeck
Purpose: To return a newly created deck 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Create a new deck
		2) SHuffle the deck
		3) return the deck
Assistance Received: None
********************************************************************* */
vector<Card*> Deck::getNewDeck() {
	createDeck();
	shuffleDeck();
	return current_deck;
}

/* *********************************************************************
Function Name: generateCards
Purpose: To generate new cards for a deck
Parameters: None
Return Value: None
Local Variables: 
		cardFaces[], a character array with all possible card faces
		cardSuits[], a character array with all possible suit values
Algorithm: 
		1) Create an array for all possible cards and suits
		2) For each card face, create two cards with each suit
		3) Push the newly created card into the created deck of cards
		4) Return the newly created deck
Assistance Received: None
********************************************************************* */
vector<Card*> Deck::generateCards() {
	char cardFaces[] = { '9', 'J', 'Q', 'K', 'X' , 'A' };
	char cardSuits[] = { 'H', 'S', 'C', 'D' };

	vector<Card*> new_deck;

	//for each card face, create two cards for each suite
	for (char cardFace : cardFaces) {
		for (char cardSuit : cardSuits) {
			Card* card = new Card;
			card->setFace(cardFace);
			card->setSuit(cardSuit);
			new_deck.push_back(card);

			Card* card2 = new Card;
			card2->setFace(cardFace);
			card2->setSuit(cardSuit);
			new_deck.push_back(card2);
		}
	}

	return new_deck;
}
