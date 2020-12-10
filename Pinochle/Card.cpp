/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#include "Card.h"


/* *********************************************************************
Function Name: Card
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Card::Card()
{
	points_worth = 0;
	unique_index = 0;
	at_least_one_meld = false;
}

/* *********************************************************************
Function Name: ~Card
Purpose: To delete all objects of the class.
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Card::~Card()
{
}

/* *********************************************************************
Function Name: getFace
Purpose: To return the character face of the card
Parameters: None
Return Value: The face of the card as a character
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
const char Card::getFace() {
	return face;
}

/* *********************************************************************
Function Name: getSuit
Purpose: To return the character suit of the card
Parameters: None
Return Value: The suit of the card as a character
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
const char Card::getSuit() {
	return suite;
}


/* *********************************************************************
Function Name: getPointsWorth
Purpose: To return the points worth of the card as an integer
Parameters: None
Return Value: The points worth of the card as an integer
Local Variables: None
Algorithm: 
		1) Compare the car's face with all possible characters of cards
		2) Return points worth of the corresponding face
Assistance Received: None
********************************************************************* */
const int Card::getPointsWorth() {

	//Compare the face with possible characters and return points worth
	if ('J' == face) {
		return 2;
	}
	else if ('Q' == face) {
		return 3;
	}
	else if ('K' == face) {
		return 4;
	}
	else if ('X' == face) {
		return 10;
	}
	else if ('A' == face) {
		return 11;
	}
	else {
		return 0;
	}
}


/* *********************************************************************
Function Name: setFace
Purpose: To assign a character value to the card's face
Parameters: 
		str, a character with the card's face value 
Return Value: None
Local Variables: None
Algorithm: 
		1) Assign the face as the character value received from the parameter
Assistance Received: None
********************************************************************* */
void Card::setFace(char str) {
	face = str;
}


/* *********************************************************************
Function Name: setSuit
Purpose: To assign a character value to the card's suit
Parameters:
		str, a character with the card's suit value
Return Value: None
Local Variables: None
Algorithm:
		1) Assign the suit as the character value received from the parameter
Assistance Received: None
********************************************************************* */
void Card::setSuit(char str) {
	suite = str;
}

/* *********************************************************************
Function Name: setPointsWorth
Purpose: To assign a points worth value to the card
Parameters:
		value, an integer with the card's point worth
Return Value: None
Local Variables: None
Algorithm:
		1) Assign the points worth as the integer value received from the parameter
Assistance Received: None
********************************************************************* */
void Card::setPointsWorth(int value) {
	points_worth = value;
}

/* *********************************************************************
Function Name: meldExists
Purpose: To find if a meld exists in the card's melds map 
Parameters:
		meldName, a string with the meld name to be checked in the map
Return Value: Boolean true if the meld is found and false if not
Local Variables: None
Algorithm:
		1) Check if the meld name exists in the melds mao of the card
		2) If exists, return true otherwise return false
Assistance Received: None
********************************************************************* */
bool Card::meldExists(string meldName) {
	
	if (melds.find(meldName) != melds.end()) {
		return true;
	}
	return false;
}


/* *********************************************************************
Function Name: noOldMelds
Purpose: To find if the melds map of the card is empty or not
Parameters:
Return Value: Boolean true if the map is empty and false if not
Local Variables: None
Algorithm:
		1) Check if the melds map is empty
		2) If empty, return true otherwise return false
Assistance Received: None
********************************************************************* */
bool Card::noOldMelds() {
	if (melds.empty()) {
		return true;
	}
	return false;
}


/* *********************************************************************
Function Name: setMeldInMap
Purpose: To add a meld in melds map of the card using the meld's name as key
Parameters:
		meldName, a string with the meld name as key in the map
		cards, a vector containing cards used in the meld
Return Value: None
Local Variables: None
Algorithm:
		1) In the map, add the vector of cards in meld as a value corresponding
			to string meldName as the key
Assistance Received: None
********************************************************************* */
void Card::setMeldInMap(string meldName, vector<Card*> cards) {
	melds[meldName] = cards;
}

/* *********************************************************************
Function Name: printMelds
Purpose: To print the melds map containing all melds the card is involved in
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
		1) Print all the cards in the melds map using map and vector 
			iterators respectively. 
Assistance Received: None
********************************************************************* */
void Card::printMelds() {

	for (map<string, vector<Card*>>::iterator it = melds.begin(); it != melds.end(); ++it) {
		cout << (it)->first << " -> ";
		for (vector<Card*>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2) {
			cout << (*it2)->getFace() << (*it2)->getSuit() << " " << (*it2) << "  ";
		}
		cout << endl;
	}
}

/* *********************************************************************
Function Name: setAtLeaseOneMeld
Purpose: To assign a bolean value to the variable atLeastOneMeld
Parameters:
		selection, a boolean to set in atLeastOneMeld variable
Return Value: None
Local Variables: None
Algorithm:
		1) Assign atLeastOneMeld as the boolean value received from the parameter
Assistance Received: None
********************************************************************* */
void Card::setAtLeastOneMeld(bool selection) {
	at_least_one_meld = selection;
}


/* *********************************************************************
Function Name: getMeldsMap
Purpose: To return the melds map of the card
Parameters: None
Return Value: The melds map of the card as a map of string key and 
				vector of Cards as value		
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
const map<string, vector<Card*>> Card::getMeldsMap() {
	return melds;
}


/* *********************************************************************
Function Name: getUniqueIndex
Purpose: To return the unique index  of the card
Parameters: None
Return Value: The unique index of the card as integer
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
const int Card::getUniqueIndex() {
	return unique_index;
}


/* *********************************************************************
Function Name: setUniqueIndex
Purpose: To assign unique index value to the card
Parameters:
		i, an integer with the card's unique index value
Return Value: None
Local Variables: None
Algorithm:
		1) Assign the unique index as the integer value received from the parameter
Assistance Received: None
********************************************************************* */
void Card::setUniqueIndex(int i) {
	unique_index = i;
}

/* *********************************************************************
Function Name: removeMeld
Purpose: To remove a meld from the card's melds map
Parameters: 
		meldName, as a string which is the key for the meld to remove
Return Value: None
Local Variables: None
Algorithm: 
		1) Erase the meld vector corresponding to the meldName key received 
			from the parameter from melds map
Assistance Received: None
********************************************************************* */
void Card::removeMeld(string meldName) {

	melds.erase(meldName);
}
