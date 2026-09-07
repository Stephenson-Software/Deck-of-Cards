cmake_minimum_required(VERSION 3.10)
project(DeckOfCards)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure proper C++ standard library linkage on all platforms
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/Card.cc
    src/Deck.cc
)

# Create library for reuse in tests
add_library(deck_of_cards ${SOURCES})

# Find or fetch Catch2
find_package(Catch2 3 QUIET)

if(NOT Catch2_FOUND)
    # If Catch2 is not found, download it
    include(FetchContent)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
    )
    FetchContent_MakeAvailable(catch2)
endif()

# Enable testing
enable_testing()

# Test files
add_executable(test_card tests/test_card.cc)
target_link_libraries(test_card deck_of_cards Catch2::Catch2WithMain)

add_executable(test_deck tests/test_deck.cc)
target_link_libraries(test_deck deck_of_cards Catch2::Catch2WithMain)

# Register tests with CTest
add_test(NAME card_tests COMMAND test_card)
add_test(NAME deck_tests COMMAND test_deck)

# Optional: Build existing test programs
add_executable(testCard testing/testCard.cc)
target_link_libraries(testCard deck_of_cards)

add_executable(testingDeck testing/testingDeck.cc)
target_link_libraries(testingDeck deck_of_cards)