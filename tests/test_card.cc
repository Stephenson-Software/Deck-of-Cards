#include <catch2/catch_test_macros.hpp>
#include "Card.h"
#include <sstream>
#include <stdexcept>

TEST_CASE("Card construction", "[card]") {
    SECTION("Valid card creation with string suit") {
        Card card(1, "Hearts");
        REQUIRE(card.getRank() == 1);
        REQUIRE(card.getSuit() == "Hearts");
        REQUIRE(card.getName() == "Ace of Hearts");
    }
    
    SECTION("Valid card creation with const char* suit") {
        Card card(13, "Spades");
        REQUIRE(card.getRank() == 13);
        REQUIRE(card.getSuit() == "Spades");
        REQUIRE(card.getName() == "King of Spades");
    }
    
    SECTION("Invalid rank throws exception") {
        REQUIRE_THROWS_AS(Card(0, "Hearts"), std::runtime_error);
        REQUIRE_THROWS_AS(Card(14, "Hearts"), std::runtime_error);
        REQUIRE_THROWS_AS(Card(-1, "Hearts"), std::runtime_error);
    }
}

TEST_CASE("Card name generation", "[card]") {
    SECTION("Ace") {
        Card ace(1, "Hearts");
        REQUIRE(ace.getName() == "Ace of Hearts");
    }
    
    SECTION("Number cards") {
        Card two(2, "Diamonds");
        Card ten(10, "Clubs");
        REQUIRE(two.getName() == "Two of Diamonds");
        REQUIRE(ten.getName() == "Ten of Clubs");
    }
    
    SECTION("Face cards") {
        Card jack(11, "Spades");
        Card queen(12, "Hearts");
        Card king(13, "Diamonds");
        REQUIRE(jack.getName() == "Jack of Spades");
        REQUIRE(queen.getName() == "Queen of Hearts");
        REQUIRE(king.getName() == "King of Diamonds");
    }
}

TEST_CASE("Card copy constructor", "[card]") {
    Card original(7, "Hearts");
    Card copy(original);
    
    REQUIRE(copy.getRank() == original.getRank());
    REQUIRE(copy.getSuit() == original.getSuit());
    REQUIRE(copy.getName() == original.getName());
}

TEST_CASE("Card assignment operator", "[card]") {
    Card card1(5, "Clubs");
    Card card2(10, "Spades");
    
    card2 = card1;
    
    REQUIRE(card2.getRank() == card1.getRank());
    REQUIRE(card2.getSuit() == card1.getSuit());
    REQUIRE(card2.getName() == card1.getName());
}

TEST_CASE("Card equality operator", "[card]") {
    Card card1(8, "Hearts");
    Card card2(8, "Hearts");
    Card card3(8, "Diamonds");
    Card card4(9, "Hearts");
    
    REQUIRE(card1 == card2);
    REQUIRE_FALSE(card1 == card3);
    REQUIRE_FALSE(card1 == card4);
}

TEST_CASE("Card less than operator", "[card]") {
    Card low(2, "Hearts");
    Card high(10, "Hearts");
    Card sameLow(2, "Spades");
    
    REQUIRE(low < high);
    REQUIRE_FALSE(high < low);
    REQUIRE_FALSE(low < sameLow);  // Same rank should not be less than
}

TEST_CASE("Card stream output", "[card]") {
    Card card(9, "Diamonds");
    std::ostringstream oss;
    oss << card;
    
    REQUIRE(oss.str() == "Nine of Diamonds");
}