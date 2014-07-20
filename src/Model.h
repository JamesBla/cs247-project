#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <fstream>

#include "Subject.h"

class Player;
class Card;

class Model : public Subject{
public:
	Model();
	virtual ~Model();

	enum State { NONE, ROUND_STARTED, IN_PROGRESS, 		
	ROUND_ENDED, GAME_ENDED, RESET_VIEW, BAD_SAVEFILE}; // current state of the game

														// ACCESORS:
	static const Card* sevenOfSpades();					// accessor for 7 of Spades
	Card* getCard(Card*) const;						// returns equivalent Card in deck
	bool beenPlayed(Card*) const;						// TRUE iff Card(r,s) has been played
	std::vector<Player*> getWinners() const;			// gets the Winners
	State getState() const;								// gets the State
	Player* getFirstPlayer() const;						// gets First Player
	Player* getCurrentPlayer() const;					// gets Current Player
	Player* getPlayer(int) const;						// gets specified Player
	int getPlayerScore(int) const;						// gets score for specified player
	int getPlayerCurrentRoundScore(int) const;			// gets current round score for player
	int getPlayerDiscardedCount(int) const;				// gets discard count for player
	std::vector<Card*> getDiscardedCards(int) const;	// returns discards for player
	std::vector<Card*> getLegalPlays(Player*);			// returns legal plays for player
	std::vector<Card*> getDeck() const;					// returns the Deck
	int getSeed() const;								// returns the seed	
	char getPlayerType(int) const;						// returns type of player

														// MUTATORS
	void initializePlayers();							// initializes players with types
	void initializeDeck();								// initializes unshuffled deck
	void shuffle();										// shuffles the deck
	void deal();										// gives 13 Card* to each player
	void putCardOnTable(Card*);							// gets _playedCards[suit][rank] to true
	void computerizePlayer(int);						// turns humanplayer into computerplayer
	void updateScoreAndEndGame();						// updates the score and ends the game iff score >= 80
	bool playTurn(Card*);								// plays a turn with Card*
	void advanceCurrentPlayer();						// go to next player
	void setState(State state);							// sets model state enum
	void setCurrentPlayer(int);							// sets the currentPlayer
	void setSeed(int);									// sets the seed
	void setPlayerType(int, char);						// sets playerType
	void cleanUp();										// deallocate and reset values
	void clearCardsOnTable();							// clears the table
	void deleteCardsAndPlayers();						// deallocate
	void exportModel(std::ofstream&);					// export gamesave
	void importModel(std::ifstream&);					// import gamesave

private:
	static const Card SEVEN_OF_SPADES;					
	std::vector<Player*> _players;						
	std::vector<Card*> _deck;
	int _firstPlayer;
	int _curPlayer;
	bool _playedCards[4][13];
	State _state;
	int _seed;
	char _playerTypes[4];

	std::string MichaelRonHash(std::string input);		// hash function
	static const std::string _key;						// key for hash function
	static const std::string _fileFormatSignature;		// file-format cookie
};

#endif