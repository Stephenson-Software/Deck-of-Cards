# Deck-of-Cards
Represents a 52-card deck with C++. Allows for creation of empty decks and movement. Has some other functionality as well.

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
- Card construction, operators, and methods (28 assertions)
- Deck operations, shuffling, and card management (68 assertions)
- Error handling and edge cases
