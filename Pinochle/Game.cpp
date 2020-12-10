/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#include "Game.h"


/* *********************************************************************
Function Name: Game
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Game::Game()
{
	numberOfRounds = 0;
	current_players = {};
}


/* *********************************************************************
Function Name: ~Game
Purpose: To delete all objects of the class.
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Game::~Game()
{
}


/* *********************************************************************
Function Name: getCurrentPlayers
Purpose: To return a vector with all current players
Parameters: None
Return Value: A vector of Player pointers i.e. vector<Player*> with current players
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
const vector<Player*> Game::getCurrentPlayers() {
	return current_players;
}

/* *********************************************************************
Function Name: createNewGame
Purpose: To create a new game 
Parameters: None
Return Value: None
Local Variables: 
		userInput, an integer inpyut from user for choice to start a game or load one
		human, new human object
		computer, new computer object
		round, new round in a game
		result, a character that is the result from coin toss

Algorithm: 
		1) Ask a user to either start a new game or load a game
		2) For load game selection, call loadgame function
		3) For new game, create 2 players, Human and Computer
		4) Start a new round with two players
		5) Assign a leader according to the coin toss result and human selection
		6) Start the round
Assistance Received: None
********************************************************************* */
void  Game::createNewGame() {
	

	cout << "---------Welcome to Pinochle.---------\n" << endl;

	cout << "1. New Game \n2. Load Game\n" << endl;
	int userInput;
	
	do {
		cin >> userInput;
		cin.clear();
		if ((userInput < 1 || userInput >2) || !cin) {
			cout << "Invalid input!!! Please select an option again: " << endl;
			cin.ignore();
		}
	} while ((userInput < 1 || userInput > 2) || !cin);
	cin.clear();
	if (userInput == 2) {
		//Loadgame kanda
		loadGame();
	}
	else {
		//If new game

		Player* human = new Human;
		Player* computer = new Computer;

		human->setName("Human");
		current_players.push_back(human);
		current_players.push_back(computer);

		Round round(current_players);
		round.distributeCards();


		char input = current_players[0]->tossSelection();
		char result = cointoss();

		cout << endl << "Toss output: " << result << endl;

		if (result == input) {
			cout << current_players[0]->getName() << " wins the toss." << endl;
			current_players[0]->setLeader(true);
		}
		else {
			cout << current_players[1]->getName() << " wins the toss." << endl;
			current_players[1]->setLeader(true);
		}

		numberOfRounds += 1;
		round.setRoundNumber(numberOfRounds);
		round.startRound();
		endOfRound(round);
	}
}

/* *********************************************************************
Function Name: cointoss
Purpose: Toss a coin and return the result
Parameters: None
Return Value: Character H or T according to the toss result
Local Variables: 
		value, the random value generated which is either 1 or 2
Algorithm: 
		1) Generate a random value 1 or 2
		2) Assign head or tails and return the result
Assistance Received: None
********************************************************************* */
char Game::cointoss() {
	int value;
	value = rand() % 2 + 1;
	if (1 == value) {
		return 'h';
	}
	else {
		return 't';
	}
}


/* *********************************************************************
Function Name: loadGame
Purpose: To load a game from saved file
Parameters: None
Return Value: None
Local Variables: 
		 fileName, the name of the file from which game loads
		 line, a string where each line from input file is stored
	     players, a vector of string where player names are stored
		 roundVal, a vector of string where number of rounds is stored
		 hand, a vector of string where cards from hand pile are stored
		 capture, a vector of string where cards from capture pile are stored
		 meld, a vector of string where cards from melds are stored
		 trumpCardVal, a vector of string where trump card is stored
		 stockPile, a vector of string where cards from stock pile are stored
		 score, a vector of string where scores of each player are stored
		 nextPlayer, a string where the next player's name is stored
		 round, newly created round to load a game
Algorithm: 
		1) Ask for a input filename, validate and open the file
		2) Read all lines from the file
		3) For each line, store the line into corresponding vector by 
			looking for matching keyword in the line
		4) Create players according to name in the file
		5) For each player, assign all attributes according to index. E.g. 
			if human is index 1, assign all attributes from index 1 of the corresponding vector
		6) Create a new round, set round number, trump card and stockpile
		7) Assign a leader according to the Next Player value from the file
		8) Start the created round
Assistance Received: None
********************************************************************* */
void Game::loadGame() {

	string line;
	vector<string> players;
	vector<string> roundVal;
	vector<string> hand;
	vector<string> capture;
	vector<string> meld;
	vector<string> trumpCardVal;
	vector<string> stockPile;
	vector<string> score;
	string nextPlayer;

	cin.ignore();

	fileAsk:
	string fileName;
	do {
		cout << "Please enter the name of the file that you load a game from: \n";
		getline(cin, fileName);
		cin.clear();
	} while (fileName.size() == 0);

	ifstream inFile(fileName);
	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			if (line.find("Human") != string::npos || line.find("Computer") != string::npos) {				
				string str;
				stringstream ss(line);
				while (getline(ss, str, ':')) {						
					players.push_back(str);
				}				
			}
			if (line.find("Round") != string::npos) {
				roundVal.push_back(parseValues("Round", line));
			} else if (line.find("Hand") != string::npos) {
				hand.push_back(parseValues("Hand", line));
			}
			else if (line.find("Capture Pile") != string::npos) {
				capture.push_back(parseValues("Capture Pile", line));
			}
			else if (line.find("Melds") != string::npos) {
				meld.push_back(parseValues("Melds", line));
			}
			else if (line.find("Trump Card") != string::npos) {
				trumpCardVal.push_back(parseValues("Trump Card", line));
			}
			else if (line.find("Stock") != string::npos) {
				stockPile.push_back(parseValues("Stock", line));
			}
			else if (line.find("Score") != string::npos) {
				score.push_back(parseValues("Score", line));
			}else if (line.find("Next Player") != string::npos) {
				nextPlayer = parseValues("Next Player", line);
				string::iterator end_pos = remove(nextPlayer.begin(), nextPlayer.end(), ' ');
				nextPlayer.erase(end_pos, nextPlayer.end());
			}

			
		}
		inFile.close();
	}
	else {
		goto fileAsk;
	}

	for (int i = 0; i < 2; i++) {
		Player* player;
		if (players[i] == "Human") {
			player = new Human;
		}
		else {
			player = new Computer;
		}
		//set player attributes for each player
		player->setName(players[i]);
		player->storeHandCards(hand[i]);
		player->storeCapturedCards(capture[i]);
		player->updateLoadScores(score[i]);
		current_players.push_back(player);
	}
	
	//Create a new round and set attrinbutes of a round
	Round round(current_players);
	round.setLoadTrumpCard(trumpCardVal[0]);
	numberOfRounds = stoi(roundVal[0]);
	round.updateStockFromLoad(stockPile[0]);
	
	//Find the next player and set the next player as leader
	for (int i = 0; i < 2; i++) {
		current_players[i]->setMeldsFromLoad(meld[i]);
		if (current_players[i]->getName() == nextPlayer) {
			current_players[i]->setLeader(true);
		}
		current_players[i]->updateAvailableCardsForSelection();
		round.setAllCards(current_players[i]->getAllCards());
	}	

	round.setRoundNumber(numberOfRounds);
	round.startRound();

	endOfRound(round);
}


/* *********************************************************************
Function Name: parse values
Purpose: To get the values from a line according to the key 
Parameters:
		key, a string value in the line whose correspoinding values is needed
		line, a string from which values are returned according to the key
Return Value: A string which is the value from a string e.g. in a string key: value, 
				'value' is returned
Local Variables: 
			vec, a string that stores the value from the string line
Algorithm: 
		1) From each line, use delimeter to seperate key and value
		2) According to the key found, return the value
Assistance Received: None
********************************************************************* */
string Game::parseValues(string key, string line) {

	string vec;

	if (line.find(key) != string::npos) {
		string str;
		stringstream ss(line);
		while (getline(ss, str, ':')) {
			if (str.find(key) == string::npos) {
				vec= (str);
			}
		}
	}

	return vec;
}


/* *********************************************************************
Function Name: anotherRound
Purpose: To create another round if a user wants to play another round.
Parameters: None
Return Value: None
Local Variables: 
		round, newly created round
Algorithm: 
		1) Create a new round with same players as current players
		2) Increase the round number and set round number
		3) Clear the previous scores and cards for both players 
		4) Start the round
Assistance Received: None
********************************************************************* */
void Game::anotherRound() {

	Round round(current_players);
	numberOfRounds += 1;
	round.setRoundNumber(numberOfRounds);
	for (auto i = 0; i < current_players.size(); i++) {
		current_players[i]->clearRoundScore();
		current_players[i]->clearAllCards();
	}
	round.distributeCards();
	round.startRound();

	endOfRound(round);

}


/* *********************************************************************
Function Name: endGame
Purpose: To successfully end a game, display scores and declare winner
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
		1) Get game score for both players and display 
		2) Evaluate the winner from scores of both players and declare winner
Assistance Received: None
********************************************************************* */
void Game::endGame() {

	cout << "Game has ended. \n-----------------------------\n\Final Scores: \n" << endl;

	for (vector<Player*>::iterator it = current_players.begin(); it != current_players.end(); ++it) {
		cout << "   " <<(*it)->getName() << ": " << (*it)->getGameScore() << endl;
	}

	cout << endl;
	if (current_players[0]->getGameScore() > current_players[1]->getGameScore()) {
		cout << current_players[0]->getName() << " is the winner!!!" << endl;
	}
	else {
		cout << current_players[1]->getName() << " is the winner!!!" << endl;
	}

	cout << "-----------------------------\n\n" << endl;
	system("pause");
}


/* *********************************************************************
Function Name: endOfRound
Purpose: To successfully end a round, display round scores, declare winner and 
		proceed to next round or end game according to user's choice
Parameters:
		round, current round in progress that has ended
Return Value: None
Local Variables: 
		winner, the index of winner returned by get winner
		userInput, user's input for new round or end game
Algorithm:
		1) Get the winner index and declare a winner by evaluating the winner
		2) Ask user for options to play new round or end game
		3) Add each user's round score to game score
		4) According to round winner, set leader. If no winner, select leader by toss
		5) Start another round i.e. call anotherRound() function. 
Assistance Received: None
********************************************************************* */
void Game::endOfRound(Round round) {


	cout << "Round " << numberOfRounds << " has ended. " << endl;
	int winner = round.getWinner();

	if (winner != -1) {				
		cout << "\nWinner of this round is " << current_players[winner]->getName() << " with " << current_players[winner]->getRoundScore() << " points. " << endl;
		cout << "Loser of the round is " << current_players[1 - winner]->getName() << " with " << current_players[1 - winner]->getRoundScore() << " points." << endl;
	}
	else {
		cout << "The score is a tie. No player wins. " << endl;
	}	

	cout << "---------------------\n\n" << endl;
	cout << "Please select an option:\n\t1. New Round \n\t2. Quit\n" << endl;
	int userInput;

	do {
		cin >> userInput;
		cin.clear();
		if ((userInput < 1 || userInput >2) || !cin) {
			cout << "Invalid input!!! Please select an option again: " << endl;
			cin.ignore();
		}
	} while ((userInput < 1 || userInput > 2) || !cin);
	cin.clear();

	for (vector<Player*>::iterator it = current_players.begin(); it != current_players.end(); ++it) {
		(*it)->addGameScore((*it)->getRoundScore());
	}

	if (userInput == 1) {//if another round
		//get winner or toss
		if (winner == 0) {
			current_players[0]->setLeader(true);
			current_players[1]->setLeader(false);
		}
		else if (winner == 1) {
			current_players[1]->setLeader(true);
			current_players[0]->setLeader(false);
		}
		else {
			char input;
			int humanIndex = 0;
			if (current_players[0]->getName() == "Human") {
				 input = current_players[0]->tossSelection();
			}
			else {
				input = current_players[1]->tossSelection();
				humanIndex = 1;
			}
			char result = cointoss();

			cout << endl << "Toss output: " << result << endl;

			if (result == input) {
				cout << current_players[humanIndex]->getName() << " wins the toss." << endl;
				current_players[humanIndex]->setLeader(true);
			}
			else {
				cout << current_players[1-humanIndex]->getName() << " wins the toss." << endl;
				current_players[1-humanIndex]->setLeader(true);
			}
		}
		anotherRound();
	}
	else {
		endGame();
	}

}