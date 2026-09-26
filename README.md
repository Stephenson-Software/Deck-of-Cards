# Deck-of-Cards
Represents a 52-card deck with C++. Allows for creation of empty decks and movement. Has some other functionality as well.

## API overview

Include `Card.h` and/or `Deck.h` from `src/` and link against `src/Card.cc` and `src/Deck.cc` (the CMake build below packages these as the `deck_of_cards` library).

### `Card` (`src/Card.h`)

A single card: a rank from 1 (Ace) to 13 (King) plus a suit string.

- `Card(int rank, std::string suit)` / `Card(int rank, const char *suit)` — throws `std::runtime_error` if `rank` is not between 1 and 13. The suit is stored as given; it is not validated.
- `getRank()` — the rank, 1–13.
- `getSuit()` — the suit string passed to the constructor.
- `getName()` — the card's name, e.g. `"Ace of Hearts"`, `"Seven of Clubs"`, `"Queen of Spades"`.
- `operator==` — true when rank, suit, and name all match.
- `operator<` — compares **rank only**; suit is ignored.
- `operator<<(std::ostream&, const Card&)` — writes the card's name.

### `Deck` (`src/Deck.h`)

A named, ordered collection of `Card`s.

- `Deck(bool empty, const char *name)` — creates an empty deck when `empty` is `true`; otherwise calls `generate()` to fill it with the 52 standard cards.
- `generate()` — appends the 52 standard cards (Hearts, Spades, Diamonds, Clubs; Ace through King within each suit). Existing cards are not removed first, so calling it on a non-empty deck adds to what is already there.
- `shuffle()` — shuffles the cards randomly (`std::shuffle` with a `std::mt19937` seeded from `std::random_device`).
- `sortInOrder()` — sorts by rank using `Card::operator<`; the relative order of equal-rank cards of different suits is unspecified.
- `moveTo(Deck &dest, int index)` — removes the card at `index` from this deck and appends it to the end of `dest`. Throws `std::out_of_range` if `index` is not a valid position.
- `getCard(int index)` — returns a copy of the card at `index`. Throws `std::out_of_range` if `index` is not a valid position.
- `contains(int rank)` — returns the **index** of the first card with that rank, or `-1` if there is none (not a `bool`).
- `howMany(int rank)` — the number of cards with that rank.
- `size()` — the number of cards.
- `empty()` — `true` when the deck holds no cards.
- `getName()` — the name passed to the constructor.
- `print()` — writes each card's name to `std::cout`, one per line.
- `operator<<(std::ostream&, const Deck&)` — writes each card's name, separated by newlines (no trailing newline).

`testing/testingDeck.cc` shows these calls together: it builds a full deck, shuffles it, and deals seven cards each to two empty decks with `myDeck.moveTo(playerone, 0)` and `myDeck.moveTo(playertwo, 0)`.

## Building and Testing

This project uses CMake as its build system and Catch2 for unit testing. Continuous Integration (CI) automatically runs the test suite on Ubuntu, macOS, and Windows for both Debug and Release builds.

### Prerequisites
- C++17 compatible compiler
- CMake 3.10 or higher

### Building
```bash
mkdir build
cd build
cmake ..
make
```

### Running Tests
```bash
# Run all tests
ctest

# Run individual test suites
./test_card    # Card class tests
./test_deck    # Deck class tests
```

### Running Original Test Programs
```bash
./testCard     # Original Card testing program
./testingDeck  # Original Deck testing program
```

### Continuous Integration

The project includes a GitHub Actions CI pipeline that automatically:
- Builds the project on Ubuntu, macOS, and Windows
- Runs all unit tests in both Debug and Release configurations
- Provides immediate feedback on pull requests and commits

The project includes comprehensive unit tests covering:
- Card construction, operators, and methods
- Deck operations, shuffling, card management, and index validation
- Error handling and edge cases
