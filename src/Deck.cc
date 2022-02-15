#include "Deck.h"
#include "Card.h"

#include <cstdlib>
#include <algorithm>
#include <time.h>

using namespace std;

Deck::Deck(bool empty, const char *n) {
	log.setDebug(false);
	log.setProgramName("Deck.cc");
	log("Creating Deck Object");
	if (!empty) {
		generate();
	}
	
	name = n;
	log ("Deck '" + name + "' created.");	
}

void Deck::generate() {
	log("Generating a new deck!");
	vector<string> suits;
	suits.push_back("Hearts");
	suits.push_back("Spades");
	suits.push_back("Diamonds");
	suits.push_back("Clubs");
	
	for (size_t j = 0; j < suits.size(); j++) {
		for (size_t i = 1; i < 14; i++) {
			Card c(i, suits[j]);
			cards.push_back(c);
		}
	}
}

void Deck::shuffle() {
	log("Shuffling Deck '" + name + "'");
	srand(time(0));
	random_shuffle(cards.begin(), cards.end());
}

void Deck::sortInOrder() {
	log("Sorting Deck '" + name + "'");
	sort(cards.begin(), cards.end());
}

void Deck::moveTo(Deck &dest, int sourceIndex) {
	log("Moving card '" + cards[sourceIndex].getName() + "' from Deck '" + name + "' to Deck '" + dest.getName() + "'");
	Card temp = cards[sourceIndex];
//	log("Erasing card '" + cards[sourceIndex].getName() + "' from Deck '" + name + "'");
	cards.erase(cards.begin() + sourceIndex);
	dest.cards.push_back(temp);
}

void Deck::print() {
	log("Printing Deck '" + name + "'");
	for (size_t i = 0; i < cards.size(); i++) {
		cout << cards[i] << "\n";
	}
}

string Deck::getName() {
	return name;
}

bool Deck::empty() {
	return cards.empty();
}

int Deck::contains(int rank) {
	log("Searching for '" + to_string(rank) + "'s in Deck '" + name + "'");
	int index = -1;
	for (size_t i = 0; i < cards.size(); i++) {
		if (cards[i].getRank() == rank) {
			log("Found!");
			index = i;
			break;
		}
	}
	return index;
}

Card Deck::getCard(int index) {
	return cards[index];
}

int Deck::size() {
	return cards.size();
}

int Deck::howMany(int num) {
	int count = 0;
	for (size_t i = 0; i < cards.size(); i++) {
		if (cards[i].getRank() == num) {
			count++;
		}
	}
	return count;
}

std::ostream& operator<<(std::ostream &out, Deck &d) {
	d.print();
	return out;
}