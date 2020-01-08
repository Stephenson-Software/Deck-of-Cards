#include "Card.h"

using namespace std;

// ctor
Card::Card(int r, const char *s) {
	string temp = s;
	Card(r, temp);
}

Card::Card(int r, string s) {
	
	// rank error checking + assignment
	if (r > 0 && r < 14) {
		rank = r;
	}
	else {
		throw runtime_error("Rank not between 1-13! Rank given: " + to_string(r));
	}
	
	// suit assignment
	suit = s;
	
	// name assignment
	switch(rank) {
		case 1:
			name = "Ace of " + suit;
			break;
		case 2:
			name = "Two of " + suit;
			break;
		case 3:
			name = "Three of " + suit;
			break;
		case 4:
			name = "Four of " + suit;
			break;
		case 5:
			name = "Five of " + suit;
			break;
		case 6:
			name = "Six of " + suit;
			break;
		case 7:
			name = "Seven of " + suit;
			break;
		case 8:
			name = "Eight of " + suit;
			break;
		case 9:
			name = "Nine of " + suit;
			break;
		case 10:
			name = "Ten of " + suit;
			break;
		case 11:
			name = "Jack of " + suit;
			break;
		case 12:
			name = "Queen of " + suit;
			break;
		case 13:
			name = "King of " + suit;
			break;
	}
}

// copy constructor
Card::Card(const Card &other) {
	rank = other.getRank();
	suit = other.getSuit();
	name = other.getName();
}

// operators
Card& Card::operator=(const Card &other) {
	if (this != &other) {
		rank = other.getRank();
		suit = other.getSuit();
		name = other.getName();
	}
	return *this;
}

bool Card::operator==(const Card &other) {
	if ((rank == other.getRank()) && (suit == other.getSuit()) && (name == other.getName())) {
		return true;
	} else {
		return false;
	}
}

bool Card::operator<(const Card &other) {
	return (rank < other.getRank());
}

// methods
int Card::getRank() const {
	return rank;
}
string Card::getSuit() const {
	return suit;
}
string Card::getName() const {
	return name;
}


// non-methods
ostream& operator<<(ostream &out, Card &c) {
	out << c.getName();
	return out;
}