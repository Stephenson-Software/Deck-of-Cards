#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include "Deck.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

TEST_CASE("Deck construction", "[deck]") {
    SECTION("Empty deck creation") {
        Deck emptyDeck(true, "Empty");
        REQUIRE(emptyDeck.empty() == true);
        REQUIRE(emptyDeck.size() == 0);
        REQUIRE(emptyDeck.getName() == "Empty");
    }
    
    SECTION("Full deck creation") {
        Deck fullDeck(false, "Full");
        REQUIRE(fullDeck.empty() == false);
        REQUIRE(fullDeck.size() == 52);
        REQUIRE(fullDeck.getName() == "Full");
    }
}

TEST_CASE("Deck generation", "[deck]") {
    Deck deck(true, "Test");
    REQUIRE(deck.size() == 0);
    
    deck.generate();
    REQUIRE(deck.size() == 52);
    REQUIRE(deck.empty() == false);
    
    // Check that we have all suits and ranks using howMany
    REQUIRE(deck.howMany(1) == 4);  // 4 Aces
    REQUIRE(deck.howMany(13) == 4); // 4 Kings
    REQUIRE(deck.howMany(7) == 4);   // 4 Sevens
    
    // Check that contains returns valid indices
    REQUIRE(deck.contains(1) >= 0);  // Should find an Ace
    REQUIRE(deck.contains(13) >= 0); // Should find a King
}

TEST_CASE("Deck card access", "[deck]") {
    Deck deck(false, "Test");
    
    SECTION("Get card by index") {
        Card firstCard = deck.getCard(0);
        REQUIRE(firstCard.getRank() >= 1);
        REQUIRE(firstCard.getRank() <= 13);
    }
    
    SECTION("Contains rank") {
        // Contains should return a valid index (>= 0) for each rank
        for (int rank = 1; rank <= 13; rank++) {
            REQUIRE(deck.contains(rank) >= 0);
        }
    }
    
    SECTION("How many of specific rank") {
        // A full deck should have 4 of each rank
        for (int rank = 1; rank <= 13; rank++) {
            REQUIRE(deck.howMany(rank) == 4);
        }
    }
}

TEST_CASE("Deck shuffle", "[deck]") {
    Deck deck1(false, "Original");

    // Get initial order
    std::vector<std::string> original_order;
    for (int i = 0; i < deck1.size(); i++) {
        original_order.push_back(deck1.getCard(i).getName());
    }
    
    deck1.shuffle();
    
    // Check that deck still has 52 cards
    REQUIRE(deck1.size() == 52);
    
    // Check that all cards are still present (though order may be different)
    for (int rank = 1; rank <= 13; rank++) {
        REQUIRE(deck1.howMany(rank) == 4);
    }

    // The shuffled deck holds exactly the original 52 cards, each once
    std::vector<std::string> shuffled_order;
    for (int i = 0; i < deck1.size(); i++) {
        shuffled_order.push_back(deck1.getCard(i).getName());
    }
    std::sort(original_order.begin(), original_order.end());
    std::sort(shuffled_order.begin(), shuffled_order.end());
    REQUIRE(shuffled_order == original_order);
}

TEST_CASE("Deck sorting", "[deck]") {
    Deck deck(false, "Test");
    deck.shuffle();  // Shuffle first
    deck.sortInOrder();
    
    // After sorting, verify the order is correct
    REQUIRE(deck.size() == 52);
    
    // First card should be Ace (rank 1)
    Card firstCard = deck.getCard(0);
    REQUIRE(firstCard.getRank() == 1);
    
    // Last card should be King (rank 13)
    Card lastCard = deck.getCard(51);
    REQUIRE(lastCard.getRank() == 13);

    // Every card's rank is at least the rank of the card before it
    for (int i = 1; i < deck.size(); i++) {
        REQUIRE(deck.getCard(i - 1).getRank() <= deck.getCard(i).getRank());
    }
}

TEST_CASE("generate() appends to a non-empty deck instead of replacing it", "[deck]") {
    Deck deck(false, "Test");
    deck.generate();

    REQUIRE(deck.size() == 104);
    REQUIRE(deck.howMany(1) == 8);
    REQUIRE(deck.getCard(51).getName() == "King of Clubs");
    REQUIRE(deck.getCard(52).getName() == "Ace of Hearts");
}

TEST_CASE("Deck move operations", "[deck]") {
    Deck sourceDeck(false, "Source");
    Deck destDeck(true, "Destination");
    
    REQUIRE(sourceDeck.size() == 52);
    REQUIRE(destDeck.size() == 0);
    
    // Move one card
    Card movedCard = sourceDeck.getCard(0);
    sourceDeck.moveTo(destDeck, 0);
    
    REQUIRE(sourceDeck.size() == 51);
    REQUIRE(destDeck.size() == 1);
    
    // Check that the moved card is correct
    Card receivedCard = destDeck.getCard(0);
    REQUIRE(receivedCard.getRank() == movedCard.getRank());
    REQUIRE(receivedCard.getSuit() == movedCard.getSuit());

    // A second move lands at the end of the destination, after the first
    sourceDeck.moveTo(destDeck, 0);
    REQUIRE(destDeck.size() == 2);
    REQUIRE(destDeck.getCard(0).getName() == "Ace of Hearts");
    REQUIRE(destDeck.getCard(1).getName() == "Two of Hearts");
}

TEST_CASE("Deck name operations", "[deck]") {
    Deck deck(true, "TestName");
    REQUIRE(deck.getName() == "TestName");
}

TEST_CASE("Deck stream output", "[deck]") {
    Deck emptyDeck(true, "Empty");
    std::ostringstream oss;
    oss << emptyDeck;
    
    // An empty deck writes nothing
    REQUIRE(oss.str().empty());
    
    // Test with one card
    Deck singleCardDeck(true, "Single");
    singleCardDeck.generate();
    singleCardDeck.moveTo(emptyDeck, 0);  // Move one card to empty deck
    
    oss.str("");  // Clear stream
    oss << emptyDeck;
    REQUIRE(oss.str().length() > 0);
}

TEST_CASE("Deck index validation", "[deck]") {
    Deck deck(false, "Test");
    Deck dest(true, "Dest");

    SECTION("getCard rejects out-of-range indices") {
        REQUIRE_THROWS_AS(deck.getCard(-1), std::out_of_range);
        REQUIRE_THROWS_AS(deck.getCard(52), std::out_of_range);
        REQUIRE_NOTHROW(deck.getCard(0));
        REQUIRE_NOTHROW(deck.getCard(51));
    }

    SECTION("moveTo rejects out-of-range indices and leaves both decks unchanged") {
        REQUIRE_THROWS_AS(deck.moveTo(dest, -1), std::out_of_range);
        REQUIRE_THROWS_AS(deck.moveTo(dest, 52), std::out_of_range);
        REQUIRE(deck.size() == 52);
        REQUIRE(dest.size() == 0);
    }

    SECTION("moveTo on an empty deck throws instead of reading past the end") {
        Deck empty(true, "Empty");
        REQUIRE_THROWS_AS(empty.moveTo(dest, 0), std::out_of_range);
        REQUIRE(dest.size() == 0);
    }

    SECTION("The error message names the rejected index and the deck size") {
        REQUIRE_THROWS_WITH(deck.getCard(52),
            "Index out of range for Deck 'Test' (size 52)! Index given: 52");
        REQUIRE_THROWS_WITH(dest.moveTo(deck, 0),
            "Index out of range for Deck 'Dest' (size 0)! Index given: 0");
    }
}

TEST_CASE("Deck observers are callable on a const Deck", "[deck][const]") {
    const Deck deck(false, "Const");

    REQUIRE(deck.size() == 52);
    REQUIRE_FALSE(deck.empty());
    REQUIRE(deck.getName() == "Const");
    REQUIRE(deck.contains(13) >= 0);
    REQUIRE(deck.howMany(1) == 4);
    REQUIRE(deck.getCard(0).getName() == "Ace of Hearts");

    std::ostringstream oss;
    oss << deck;
    REQUIRE(oss.str().substr(0, 13) == "Ace of Hearts");
}

TEST_CASE("generate() orders cards by suit, then Ace through King", "[deck]") {
    Deck deck(false, "Test");

    REQUIRE(deck.getCard(0).getName() == "Ace of Hearts");
    REQUIRE(deck.getCard(12).getName() == "King of Hearts");
    REQUIRE(deck.getCard(13).getName() == "Ace of Spades");
    REQUIRE(deck.getCard(26).getName() == "Ace of Diamonds");
    REQUIRE(deck.getCard(39).getName() == "Ace of Clubs");
    REQUIRE(deck.getCard(51).getName() == "King of Clubs");
}

TEST_CASE("contains returns the index of the first matching card, or -1", "[deck]") {
    Deck deck(false, "Test");

    REQUIRE(deck.contains(1) == 0);
    REQUIRE(deck.contains(13) == 12);
    REQUIRE(deck.contains(0) == -1);
    REQUIRE(deck.contains(14) == -1);

    SECTION("The next match is found once the first is moved away") {
        Deck dest(true, "Dest");
        deck.moveTo(dest, 0);  // Ace of Hearts
        REQUIRE(deck.contains(1) == 12);  // Ace of Spades
    }

    SECTION("An empty deck contains nothing") {
        Deck empty(true, "Empty");
        REQUIRE(empty.contains(1) == -1);
        REQUIRE(empty.howMany(1) == 0);
    }
}

TEST_CASE("Deck output writes one card name per line", "[deck]") {
    Deck source(false, "Source");
    Deck hand(true, "Hand");
    source.moveTo(hand, 0);  // Ace of Hearts
    source.moveTo(hand, 0);  // Two of Hearts

    SECTION("operator<< separates names with newlines and adds no trailing newline") {
        std::ostringstream oss;
        oss << hand;
        REQUIRE(oss.str() == "Ace of Hearts\nTwo of Hearts");
    }

    SECTION("print() writes each name to std::cout followed by a newline") {
        std::ostringstream captured;
        std::streambuf *original = std::cout.rdbuf(captured.rdbuf());
        hand.print();
        std::cout.rdbuf(original);
        REQUIRE(captured.str() == "Ace of Hearts\nTwo of Hearts\n");
    }
}