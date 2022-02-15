#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "tools\mylogger.h"
#include <vector>

class Deck {
	std::vector<Card> cards;
	MyLogger log;
	std::string name;
  public:
	Deck(bool empty, const char *n);
	
	void generate();
	void shuffle();
	void sortInOrder();
	void moveTo(Deck &dest, int sourceIndex);
	void print();
	std::string getName();
	bool empty();
	int contains(int rank);
	Card getCard(int index);
	int size();
	int howMany(int num);
};

std::ostream& operator<<(std::ostream &out, Deck &d);

#endif