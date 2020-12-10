/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/
#include "Round.h"


/* *********************************************************************
Function Name: Round
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Round::Round()
{
	round_number = 0;
	current_deck = {};
	current_players = {};

	 trump_card = NULL;
	 trump_suite = trump_card->getSuit();
	 all_cards = {};
}

/* *********************************************************************
Function Name: Round
Purpose: To initialize all member variables of the class.
Parameters: 
		players, a vector with all player pointers of the game
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Round::Round(vector<Player*> players) {
	current_players = players;
	round_number = 0;
}

/* *********************************************************************
Function Name: ~Round
Purpose: To delete all static cards and players created.
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Delete all cards used in the game 
		2) Delete all players in the game
Assistance Received: None
********************************************************************* */
Round::~Round()
{	
	for (vector<Card*>::iterator it = all_cards.begin(); it != all_cards.end(); ++it) {
		delete (*it);
	}
	
	for (vector<Player*>::iterator it = current_players.begin(); it != current_players.end(); ++it) {
		delete (*it);
	}
}

/* *********************************************************************
Function Name: setAllCards
Purpose: To add a cards vector into allcards vector which stores all cards
Parameters: 
		cards, a vector of Card pointers 
Return Value: None
Local Variables: None
Algorithm: 
		1) Insert the cards vector received from the parameter at the 
			end of vector containing all cards 
Assistance Received: None
********************************************************************* */
void Round::setAllCards(vector<Card*> cards) {
	all_cards.insert(all_cards.end(), cards.begin(), cards.end());
}

/* *********************************************************************
Function Name: getTrumpCard
Purpose: To return pointer to the trump card of the round
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Card* Round::getTrumpCard() {
	return trump_card;
}

/* *********************************************************************
Function Name: distributeCards
Purpose: To distribute cards to players
Parameters: None
Return Value: None
Local Variables: 
		deck, a newly created deck for the round
Algorithm: 
		1) Create a new deck and store it into current_deck
		2) Distribute 4 cards at a time from current deck to players until 
			both players have 12 cards
		3) Set the next card from current deck as trump card
		4) Update hand pile and trump card for both players
Assistance Received: None
********************************************************************* */
void Round::distributeCards() {

	Deck deck;
	current_deck = deck.getNewDeck();
	all_cards = current_deck;

	int currReceiver = 1;
	Card* currCard;

	for (int i = 0; i < 6; i++) {
		if (1 == currReceiver) {
			for (int i = 0; i < 4; i++) {
				currCard = current_deck.back();
				current_players[0]->addCardToHand(currCard);
				current_deck.pop_back();
			}
			currReceiver = 2;
		}
		else if (2 == currReceiver) {
			for (int i = 0; i < 4; i++) {
				currCard = current_deck.back();
				current_players[1]->addCardToHand(currCard);
				current_deck.pop_back();
			}
			currReceiver = 1;
		}
	}

	currCard = current_deck.back();
	trump_card = currCard;
	trump_suite = trump_card->getSuit();
	current_deck.pop_back();

	vector<Player*>::iterator playerIt;
	for (playerIt = current_players.begin(); playerIt != current_players.end(); ++playerIt) {
		(*playerIt)->setTrumpCard(trump_card);
		(*playerIt)->updateAvailableCardsForSelection();
	}
}


/* *********************************************************************
Function Name: printCurrentDeck
Purpose: To print the current stock pile
Parameters: None
Return Value: None
Local Variables:
Algorithm:
		1) Print all cards from stock pile which is current_deck using 
			vector iterator
Assistance Received: None
********************************************************************* */
void Round::printCurrentDeck() {
	vector<Card*>::reverse_iterator it;
	for (it = current_deck.rbegin(); it != current_deck.rend(); ++it) {
		cout << (*it)->getFace() << (*it)->getSuit() << " ";
	}
	cout << endl;
}


/* *********************************************************************
Function Name: startRound
Purpose: To start a round and play until one player runs out of playable card
Parameters: None
Return Value: None
Local Variables:
Algorithm:
		1) Call new turn until one player runs out of playable cards
Assistance Received: None
********************************************************************* */
void Round::startRound() {

	//while both players have cards in their hand
	while ((current_players[0]->getAvailableCardsSize() > 0) && (current_players[1]->getAvailableCardsSize() > 0)) {
		newTurn();
	}
}

/* *********************************************************************
Function Name: newTurn
Purpose: To start a round and play until one player runs out of playable card
Parameters: None
Return Value: None
Local Variables:
		playersPlayed, an integer value that stores how many players have played a turn
		turnCard, a card pointer that stores the card played by each player in the turn
Algorithm:
		1) Among current players, find the leader
		2) Show the dashboard and let the leader play and return a lead card
		3) If the player has selected save, call the saveGame function
		4) If game has not been saved, get the chase card from the chasing player
		5) Select a turn winner and ask the winner to show meld
		6) Validate the meld and if invalid, ask to enter valid meld 
		7) If meld is valid, update the meld information in teach card's melds map
		8) For the player showing meld, update the meld_pile 
		9) Evaluate points of the turn and add to the winning player
		10) Assign next card from the stock pile to leader followed by chaser
		11) If stock is empty, assign trump card to the player picking a card
Assistance Received: None
********************************************************************* */
void Round::newTurn() {

	int playersPlayed = 0;
	Card* turnCard = new Card;
	vector<Player*>::iterator it = current_players.begin();
	

	//Assigns leader for first turn so that leader starts first move 
	for (it; it != current_players.end(); ++it) {
		if ((*it)->isLeader()) {
			break;
		}
	}
	showDashboard(*it);
	//until both players show a card each
	while (it != current_players.end() && (size_t)playersPlayed < current_players.size()) {
		turnCard = (*it)->play(turnCard);
		playersPlayed += 1;
		if ((*it)->getSaveGame()) {
			saveGame(*it);
			(*it)->setSaveGame(false);			
			system("pause");
			exit(1);
		}
		it++;
		if (it == current_players.end()) {
			it = current_players.begin();
		}

	}	

	selectTurnWinner();	
	for (it = current_players.begin(); it != current_players.end(); ++it) {
		if ((*it)->isLeader()) {
			cout << (*it)->getName() << " is the winner" << endl;
			break;
		}
	}

	meldAgain:
	//ask for melds and show melds from the winner
	vector<Card*> leaderMelds = (*it)->showMeld();
	if (leaderMelds.size() == 0) {
		//do nothing
	}
	else if ((*it)->validateMeld(leaderMelds, (*it)->getMeldName(leaderMelds)) && (*it)->atLeastOneNewCard(leaderMelds) && (*it)->getMeldName(leaderMelds)!="invalid" && (*it)->getMeldName(leaderMelds) != "" ) {
		//if meld is valid, update meld tables for cards and meld pile for the player
		(*it)->setCardSelectedForMeld(leaderMelds);
		(*it)->updateCardMeldsMap(leaderMelds);
		(*it)->updateMeldPile(leaderMelds);
		cout << (*it)->getMeldName(leaderMelds) << " meld shown which is worth " << (*it)->getMeldPoints((*it)->getMeldName(leaderMelds)) << " points." << endl;		
	}
	else {
		cout << "---Meld invalid. Please try again!!!---" << endl;
		goto meldAgain;
	}

	//Assign points of the turn to the winning player
	int leaderPoints = (*it)->getMeldPoints((*it)->getMeldName(leaderMelds));
	(*it)->addRoundScore(leaderPoints);
	
	//Both players pick a card from stock, leader followed by chaser
	for (it; it != current_players.end(); ++it) {
		if (current_deck.size() > 0) {
			if ((*it)->isLeader()) {
				pickCard(*it);
			}
		}
	}

	for (it=current_players.begin(); it != current_players.end(); ++it) {
		if (current_deck.size() > 0) {
			if (!((*it)->isLeader())) {
				pickCard(*it);
			}
		}
		//If stock is empty, trump card is picked
		else if(trump_card != NULL){
			(*it)->addCardToHand(trump_card);
		}
	}
}


//Selects turn winner and assigns leader for next turn
/* *********************************************************************
Function Name: selectTurnWinner
Purpose: To get winner of the turn and assign leader to next turn
Parameters: None
Return Value: None
Local Variables:
		leadCard, lead card for the turn
		chaseCard, chase card for the turn
Algorithm:
		1) Get the lead card and chase card for the turn from each player
		2) use turnWinnerCard helper functon to know which card is a winner
		3) if chase card is a winner, assign chasing player as leader, else leader stays leader 
		4) Add both chase and lead card to capture pile of the winner
		5) Add round score that includes scores for both lead and chase cards added
Assistance Received: None
********************************************************************* */
void Round::selectTurnWinner() {

	Card* leadCard = new Card;
	Card* chaseCard = new Card;
	vector<Player*>::iterator it = current_players.begin();


	//Assigns leader for first turn so that leader starts first move 
	for (it; it != current_players.end(); ++it) {
		if ((*it)->isLeader()) { leadCard = (*it)->getTurnCard(); }
		else { chaseCard = (*it)->getTurnCard(); }
	}

	//If chasing player is a winner
	if (turnWinnerCard(leadCard, chaseCard) == "chase") {
		for (it = current_players.begin(); it != current_players.end(); ++it) {
			if ((*it)->isLeader()) { (*it)->setLeader(false); }
			else {
				(*it)->setLeader(true);
				//Update capture pile
				(*it)->addCardToCapturePile(leadCard);
				(*it)->addCardToCapturePile(chaseCard);
				//Update points
				(*it)->addRoundScore(leadCard->getPointsWorth() + chaseCard->getPointsWorth());
			}
		}
	}
	//if leader is winner, add cards to leader's capture pile
	else {
		for (it = current_players.begin(); it != current_players.end(); ++it) {
			if ((*it)->isLeader()) { 
				(*it)->addCardToCapturePile(leadCard);
				(*it)->addCardToCapturePile(chaseCard);
				//Update scores
				(*it)->addRoundScore(leadCard->getPointsWorth() + chaseCard->getPointsWorth());
				break;
			}
		}
		
	}

}


/* *********************************************************************
Function Name: turnWinnerCard
Purpose: To get the winner among two cards
Parameters: None
Return Value: string value 'chase' if chase card is winner, otherwise 'lead' returned
Local Variables:
		leadCard, lead card pointer for the turn
		chaseCard, chase card pointer for the turn
Algorithm:
		1) If lead card and chase card are of trump suit, if both are same cards, return lead 
		2) If both are not same cards, use helper function to get precedence for both cards
		3) Return the card which hs greater precedence
		4) If lead card is not trump suit, f chase card is of trump suit, return chase
		5) If both same suit, if same cards, lead wins
		6) If not same cards, card with greater precedence wins
		
Assistance Received: None
********************************************************************* */
string Round::turnWinnerCard(Card* leadCard, Card* chaseCard) {

	//If lead card is trump suit
	if (leadCard->getSuit() == trump_suite) { 
		//If chase card also trump suit
		if (chaseCard->getSuit() == trump_suite) {
			//If same cards
			if (leadCard->getFace() == chaseCard->getFace()) {
				return "lead";
			}
			else {
				//If both trump and not same, greater card wins
				if (getCardPrecedence(leadCard->getFace()) > getCardPrecedence(chaseCard->getFace())) {
					return "lead";
				}
				else {
					return "chase";
				}
			}
		}
		else {
		}
	}
	//Lead card not trump suit
	else {
		if (chaseCard->getSuit() == trump_suite) {
			return "chase";
		}
		//both not trump but same suit
		else if(leadCard->getSuit() == chaseCard->getSuit()){
			//If same cards lead wins
			if (leadCard->getFace() == chaseCard->getFace()) {
				return "lead";
			}
			//if not same cards
			else {
				//If both same suit and not same, greater card wins
				if (getCardPrecedence(leadCard->getFace()) > getCardPrecedence(chaseCard->getFace())) {
					return "lead";
				}
				else {
					return "chase";
				}
			}
		}
	}

	return "lead";

}


/* *********************************************************************
Function Name: getCardPrecedence
Purpose: To return integer value as precedence of card
Parameters: 
		cardFace, the face of the card as a character
Return Value: Integer value by precedence of the card
Local Variables: None
Algorithm: 
		1) Return an integer value by precedence i.e. if the card has higher 
			precedence, return higher integer
Assistance Received: None
********************************************************************* */
const int Round::getCardPrecedence(char cardFace) {
	if ('9' == cardFace) { return 1; }
	else if('J' == cardFace) { return 2; }
	else if ('Q' == cardFace) { return 3; }
	else if ('K' == cardFace) { return 4; }
	else if ('X' == cardFace) { return 5; }
	else if ('A' == cardFace) { return 6; }

	return -1;
}

/* *********************************************************************
Function Name: showDashboard
Purpose: To show dashboard before each turn 
Parameters:
		player, Player pointer of the current player
Return Value: None
Local Variables:None
Algorithm:
		1) Print Round number 
		2) For each player, print the score, hand pile, capture pile and meld pile
		3) Print the trump card and stock pile
		4) Print the leader for next turn as Next Player
Assistance Received: None
********************************************************************* */
void Round::showDashboard(Player* player) {
	cout << "----------------------------------------------" << endl;
	cout << "Round: " << round_number << endl << endl;
	vector<Player*>::iterator it = current_players.begin();
	for (it = current_players.begin(); it != current_players.end(); ++it) {
		cout << (*it)->getName() << ":" << endl;
		cout << "\tScore: " << (*it)->getGameScore() << "/" << (*it)->getRoundScore() << endl;
		cout << "\tHand: ";
		(*it)->printCards((*it)->getHandPile());
		cout << "\tCapture Pile: ";
		(*it)->printCards((*it)->getCapturePile());
		cout << "\tMelds: ";
		(*it)->printMeldPile();
		cout << endl << endl;
	}

	cout << "Trump card: ";
	if (current_deck.size() > 0) {
		cout << trump_card->getFace() << trump_card->getSuit() << endl;
	}
	else {
		cout << trump_suite << endl;
	}
	cout << "Stock: ";

	printCurrentDeck();
	cout << endl;

	cout << "Next player: " << (player)->getName() << endl;
}

/* *********************************************************************
Function Name: setRoundNumber
Purpose: To set the round number
Parameters:
		roundNumber, the number of current round
Return Value: None
Local Variables:None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Round::setRoundNumber(int roundNumber) {
	round_number = roundNumber;
}

/* *********************************************************************
Function Name: pickCard
Purpose: To pick a card from stock pile
Parameters:
		player, Player pointer to the current player
Return Value: None
Local Variables:None
Algorithm: 
		1) Add the next card from stock pile to the player's hand pile
		2) Remove the card from stock pile
Assistance Received: None
********************************************************************* */
void Round::pickCard(Player* player) {
	
	if (!current_deck.empty()) {
		player->addCardToHand(current_deck.back());
		current_deck.pop_back();
	}	
	
}

/* *********************************************************************
Function Name: saveGame
Purpose: To save all details of a game to a .txt file
Parameters:
		player, Player pointer of the current player
Return Value: None
Local Variables:None
Algorithm:
		1) Ask for a filename and validate
		2) In the file, open the file and write the details 
		3) Write Round number
		4) For each player, write the score, hand pile, capture pile and meld pile
		5) Write the trump card and stock pile
		6) Write the leader for next turn as Next Player
Assistance Received: None
********************************************************************* */
void Round::saveGame(Player* player) {

	string fileName;
	cin.ignore();
	do {		
		cout << "Please enter the name of the file that you want to save(.txt): \n";
		getline(cin, fileName);
		cin.clear();
	} while (fileName.size() == 0);

	ofstream outfile(fileName);
	if (outfile.is_open()) {
		outfile << "Round: " << round_number << '\n';
		vector<Player*>::iterator it = current_players.begin();
		for (it = current_players.begin(); it != current_players.end(); ++it) {
			outfile << (*it)->getName() << ":\n";
			outfile << "     Score: " << (*it)->getGameScore() << "/"  << (*it)->getRoundScore() << '\n';
			outfile << "     Hand: ";
			(*it)->printCardsToFile((*it)->getHandPile(), outfile);
			outfile << "\n     Capture Pile: ";
			(*it)->printCardsToFile((*it)->getCapturePile(), outfile);
			outfile << "\n     Melds: ";
			(*it)->printMeldCardsToFile(outfile);
			outfile << "\n\n";
		}		
		outfile << "Trump Card: " << trump_card->getFace() << trump_card->getSuit() << '\n';

		//Write stock pile
		outfile << "Stock: ";
		vector<Card*>::reverse_iterator it2;
		for (it2 = current_deck.rbegin(); it2 != current_deck.rend(); ++it2) {
			outfile << (*it2)->getFace() << (*it2)->getSuit() << " ";
		}
		outfile << "\n\n";
		outfile << "Next player: " << player->getName() << '\n';
		outfile.close();
	}
	cout << "Saved in file " << fileName << "."<<  endl;
}

/* *********************************************************************
Function Name: setLoadTrumpCard
Purpose: To set trump card received from load file
Parameters:
		card, string value as the trump card or trump suit
Return Value: None
Local Variables:None
Algorithm:
		1) Remove all spaces from the string and store only characters
		2)If the string has two characters, update trump card
		3) If the string has only one character, update trump suit
		4) Update trump card and suit for both players
Assistance Received: None
********************************************************************* */
void Round::setLoadTrumpCard(string card) {

	
	string::iterator end_pos = remove(card.begin(), card.end(), ' ');
	card.erase(end_pos, card.end());


	if (card.length() == 2) {
		Card* c = new Card;
		c->setFace(card[0]);
		c->setSuit(card[1]);
		trump_card = c;
		for (int i = 0; i < 2; i++) {
			current_players[i]->setTrumpCard(trump_card);
			all_cards.push_back(trump_card);
			current_players[i]->setTrumpSuit(trump_card->getSuit());
		}
		trump_suite = trump_card->getSuit();
	}
	else {
		trump_suite = card[0];
		for (int i = 0; i < 2; i++) {
			current_players[i]->setTrumpSuit(trump_suite);
		}
	}
	   
}

/* *********************************************************************
Function Name: updateStockFromLoad
Purpose: To set stock pile received from load file
Parameters:
		cards, stock pile cards as a string
Return Value: None
Local Variables:None
Algorithm:
		1) Remove all spaces from the string and store only characters
		2) Set the face and suit of cards from the string members seperated
			by space and ad into current deck
		3) Reverse the current deck because card is popped from back every time
Assistance Received: None
********************************************************************* */
void Round::updateStockFromLoad(string cards) {

	string str;
	stringstream ss(cards);
	while (getline(ss, str, ' ')) {
		if (isalpha(str[0]) || str[0] == '9') {
			Card* card = new Card;
			card->setFace(str[0]);
			card->setSuit(str[1]);
			current_deck.push_back(card);
		}
	}

	//reverse because card is popped from back everytime a card is picked from stock
	reverse(current_deck.begin(),current_deck.end());
	//Insert into all cards to delete all cards at the end of the round
	all_cards.insert(all_cards.begin(), current_deck.begin(), current_deck.end());
}

/* *********************************************************************
Function Name: getWinner
Purpose: To get a winner for the round
Parameters: None
Return Value: None
Local Variables:None
Algorithm:
		1) Evaluate scores for both players and return winner's index on current players 
		2) If scores tied, return -1
Assistance Received: None
********************************************************************* */
const int Round::getWinner() {

	if (current_players[0]->getRoundScore() > current_players[1]->getRoundScore()) {
		return 0;
	}
	else if(current_players[0]->getRoundScore() < current_players[1]->getRoundScore()) {
		return  1;
	}
	else {
		return -1;
	}

}
