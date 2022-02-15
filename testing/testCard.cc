#include "Card.h"

#include <vector>

using namespace std;

int main() {
	vector<Card> cards;
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
	
	cout << cards.size() << "\n";
	
	for (size_t i = 0; i < 52; i++) {
		cout << cards[i] << "\n";
	}

	return 0;
}