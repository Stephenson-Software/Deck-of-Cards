#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "helper/mylogger.h"
#include <vector>

class Deck {
	std::vector<Card> cards;
	mutable MyLogger log;
	std::string name;
  public:
	Deck(bool empty, const char *n);
	
	void generate();
	void shuffle();
	void sortInOrder();
	void moveTo(Deck &dest, int sourceIndex);
	void print() const;
	std::string getName() const;
	bool empty() const;
	int contains(int rank) const;
	Card getCard(int index) const;
	int size() const;
	int howMany(int num) const;
};

std::ostream& operator<<(std::ostream &out, const Deck &d);

#endif