#include "Deck.h"

using namespace std;

int main() {
	Deck myDeck(false, "Original");
	
	myDeck.shuffle();
	
	Deck playerone(true, "Player One");
	for (size_t i = 0; i < 7; i++) {
		myDeck.moveTo(playerone, 0);
	}
	
	Deck playertwo(true, "Player Two");
	for (size_t i = 0; i < 7; i++) {
		myDeck.moveTo(playertwo, 0);
	}
	
	cout << myDeck << "\n\n" << playerone << "\n\n" << playertwo;
}