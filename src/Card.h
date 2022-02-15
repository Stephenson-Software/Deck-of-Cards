#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
	int rank;
	std::string suit;
	std::string name;
  public:
	// ctor
	Card(int r, const char *s);
	Card(int r, std::string s);
	
	// dtor
	~Card() = default;
	
	// copy constructor
	Card(const Card &other);
	
	// operators
	Card& operator=(const Card &other);
	bool operator==(const Card &other);
	bool operator<(const Card &other);
	
	// methods
	int getRank() const;
	std::string getSuit() const;
	std::string getName() const;
};

std::ostream& operator<<(std::ostream &out, Card &c);

#endif