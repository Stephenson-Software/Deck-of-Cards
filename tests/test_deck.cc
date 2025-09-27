#include <catch2/catch_test_macros.hpp>
#include "Deck.h"
#include <sstream>

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
    Deck deck2(false, "Copy");
    
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
}

TEST_CASE("Deck name operations", "[deck]") {
    Deck deck(true, "TestName");
    REQUIRE(deck.getName() == "TestName");
}

TEST_CASE("Deck stream output", "[deck]") {
    Deck emptyDeck(true, "Empty");
    std::ostringstream oss;
    oss << emptyDeck;
    
    // Should not crash with empty deck
    REQUIRE(oss.str().length() >= 0);
    
    // Test with one card
    Deck singleCardDeck(true, "Single");
    singleCardDeck.generate();
    singleCardDeck.moveTo(emptyDeck, 0);  // Move one card to empty deck
    
    oss.str("");  // Clear stream
    oss << emptyDeck;
    REQUIRE(oss.str().length() > 0);
}