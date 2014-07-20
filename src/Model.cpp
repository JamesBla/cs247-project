#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#include "Model.h"
#include "View.h"

#include "Card.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

Card initSevenOfSpades(){
	Card c(SPADE, SEVEN);
	return c;
}

const Card Model::SEVEN_OF_SPADES = initSevenOfSpades();

const Card* Model::sevenOfSpades(){
	return &SEVEN_OF_SPADES;
}

// initializes playerTypes to all human
Model::Model() : _seed(0) {
	for (int i = 0; i < 4; i++) {
		_playerTypes[i] = 'h';
	}
}

// initializes players using playerTypes
void Model::initializePlayers() {
	
	for (int i = 0; i < 4; i++){
		if (_playerTypes[i] == 'h'){
			_players.push_back(new HumanPlayer(this, i+1));
		}
		else{
			_players.push_back(new ComputerPlayer(this, i+1));
		}
	}
}

// initializes unshuffled deck
void Model::initializeDeck(){
	for (int suit = 0; suit < SUIT_COUNT; suit++){
		for (int rank = 0; rank < RANK_COUNT; rank++){
			Card* newCard = new Card(static_cast<Suit>(suit), static_cast<Rank>(rank));
			_deck.push_back(newCard);
		}
	}
}

void Model::shuffle(){
	int n = 52;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = _deck[n];
		_deck[n] = _deck[k];
		_deck[k] = c;
	}
}

// doles out cards to player
void Model::deal(){
	for (int i = 0; i < 52; i++){
		_players[i/13]->addCard(_deck.at(i));

		// possession of seven of spades determine first player
		if (*_deck[i] == SEVEN_OF_SPADES){
			_firstPlayer = i/13;
		}
	}
}

void Model::putCardOnTable(Card* card){
	_playedCards[card->getSuit()][card->getRank()] = true;
}

void Model::computerizePlayer(int playerIndex){
	Player* player = _players.at(playerIndex);
	ComputerPlayer* computerPlayer = new ComputerPlayer(*player);
	delete player;
	_players[playerIndex] = computerPlayer;
}

void Model::updateScoreAndEndGame() {

	// update the score for each player, keeping note
	// of whether a score is >= 80
	int doneGame = false;
	for (int i = 0; i < 4; i++) {
		_players[i]->updateScore();
		if (_players[i]->getScore() >= 80){
			doneGame = true;
		}
	}

	// update scores in view
	notify();

	_state = ROUND_ENDED;

	// display end of round
	notify();

	if (doneGame) {
		_state = GAME_ENDED;

		// if the game is done, notify the view
		notify();
	}
}

bool Model::playTurn(Card *card) {
	return _players[_curPlayer]->playTurn(card, _playedCards);
}

void Model::advanceCurrentPlayer() {

	// go to next player
	_curPlayer = (_curPlayer + 1) % 4;

	// notifies the view for HumanPlayer so as to possible update HandViews et. al.
	if (_playerTypes[_curPlayer] == 'h')
		notify();
}

void Model::setState(State state) {
	_state = state;
	notify();
}

void Model::setCurrentPlayer(int playerIndex) {
	_curPlayer = playerIndex;
}

void Model::setSeed(int seed) {
	_seed = seed;
}

void Model::setPlayerType(int playerIndex, char type) {
	_playerTypes[playerIndex] = type;
}

void Model::cleanUp(){

	// puts the model in the cleanup state
	_state = RESET_VIEW;
	notify();
	_state = NONE;

	// remove cards from table
	clearCardsOnTable();

	// deallocate cards and players
	deleteCardsAndPlayers();

	// clear our deck and player vectors to make
	// room for new pointers
	_deck.clear();
	_players.clear();
}

void Model::clearCardsOnTable(){
	for (int suit = 0; suit < SUIT_COUNT; suit++){
		for (int rank = 0; rank < RANK_COUNT; rank++){
			_playedCards[suit][rank] = false;
		}
	}
}

void Model::deleteCardsAndPlayers() {
	for (vector<Card*>::iterator it = _deck.begin(); it != _deck.end(); it++){
		delete *it;
	}

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++){
		delete *it;
	}
}

Model::~Model(){
	deleteCardsAndPlayers();
}

// returns pointers to the card in the deck equal
// to the target
Card* Model::getCard(Card* target) const {
	for (unsigned int i = 0; i < _deck.size(); i++) {
		if (*target == *(_deck[i])){
			return _deck[i];
		}
	}
	return NULL;
}

// returns true iff card is on the table
bool Model::beenPlayed(Card* c) const{
	return _playedCards[c->getSuit()][c->getRank()];
}

// gets all players with minimum score
vector<Player*> Model::getWinners() const{
	int minScore = 1337;
	vector<Player*> winners;
	for (unsigned int i = 0; i < _players.size(); i++){
		int curScore = _players[i]->getScore();

		if (curScore <= minScore){

			if (curScore < minScore){
				minScore = curScore;
				winners.clear();
			}

			winners.push_back(_players[i]);
		}
	}
	return winners;
}

// get current legal plays for a player
vector<Card*> Model::getLegalPlays(Player* player){
	return player->getLegalPlays(_playedCards);
}

Player* Model::getPlayer(int index) const {
	return _players.at(index);
}

Player* Model::getFirstPlayer() const {
	return getPlayer(_firstPlayer);
}

Model::State Model::getState() const {
	return _state;
}

Player* Model::getCurrentPlayer() const{
	return _players.at(_curPlayer);
}

int Model::getPlayerScore(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getScore();
}

int Model::getPlayerCurrentRoundScore(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getRoundScore();
}

int Model::getPlayerDiscardedCount(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getDiscardedCount();
}

vector<Card*> Model::getDiscardedCards(int playerIndex) const{
	return _players.at(playerIndex)->getDiscarded();
}

vector<Card*> Model::getDeck() const{
	return _deck;
}

int Model::getSeed() const{
	return _seed;
}

char Model::getPlayerType(int playerIndex) const{
	return _playerTypes[playerIndex];
}

const string Model::_key = "MICHAELTU_RONMENG";

// used to verify gamesave file format
const string Model::_fileFormatSignature = "StraightsFormat";

// returns hashed string, also dehashes string.
// since this function is its own inverse
string Model::MichaelRonHash(string input){
	for (int i = 0; i < input.length(); i++){
		input[i] ^= ~(_key[ i% (_key.length()) ]);
	}
	return input;
}

// saves all data in model to a file (hashed output)
void Model::exportModel(ofstream& file) {
	ostringstream oss;

	// append output with file format signature
	oss << _fileFormatSignature << endl;
	oss << _seed << endl;
	oss << _state << endl;
	oss << _firstPlayer << endl;
	oss << _curPlayer << endl;
	for (int i = 0; i < 4; i++) {
		oss << _playerTypes[i] << endl;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			oss << _playedCards[i][j] << endl;
		}
	}
	for (unsigned int i = 0; i < _deck.size(); i++) {
		oss << *(_deck[i]) << endl;
	}
	for (int i = 0; i < 4; i++) {
		oss << "player\n";
		oss << *(_players[i]);
	}
	// hash the string
	file << MichaelRonHash(oss.str());
}

// imports model from hashed file
void Model::importModel(ifstream& file) {
	std::string str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

	istringstream iss;

	// un-hash the string
	iss.str(MichaelRonHash(str));

	string signatureCheck;

	iss >> signatureCheck;

	// if the first token is not our signature,
	// then the savefile is invalid
	if (signatureCheck != _fileFormatSignature){
		setState(Model::BAD_SAVEFILE);
		return;
	}
	
	iss >> _seed;
	
	int state;

	iss >> state;
	_state = static_cast<State>(state);
	iss >> _firstPlayer >> _curPlayer;
	for (int i = 0; i < 4; i++) {
		iss >> _playerTypes[i];
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			iss >> _playedCards[i][j];
		}
	}
	for (int i = 0; i < 52; i++) {
		Card* newCard = new Card(static_cast<Suit>(0), static_cast<Rank>(0));
		iss >> *newCard;
		_deck.push_back(newCard);
	}

	string temp;
	iss >> temp; // hack to skip the first "player" tag
	Card* curCard = new Card(static_cast<Suit>(0), static_cast<Rank>(0));
	for (int i = 0; i < 4; i++){

		int score, roundScore, oldScore, number;
		std::vector<Card*> hand, discards;
		
		iss >> score >> roundScore >> oldScore >> number >> temp;
		
		string sections[] = {"discards", "player"};
		for (int k = 0; k < 2; k++){

			iss >> temp; //first card or "discards"

			while(temp != sections[k] && !iss.eof() && temp.length() > 0){ // while in hand section
				istringstream tempIss;
				tempIss.str(temp);
				tempIss >> *curCard;

				Card* card = getCard(curCard);

				if (k == 0){
					hand.push_back(card);
				}
				else{
					discards.push_back(card);
				}
				iss >> temp;
			}
		}
		
		if (_playerTypes[i] == 'h'){
			_players.push_back(new HumanPlayer(this, score, roundScore, oldScore,
					number, hand, discards));
		}
		else{
			_players.push_back(new ComputerPlayer(this, score, roundScore, oldScore,
					number, hand, discards));
		}

	}
	delete curCard;

	notify();
}
