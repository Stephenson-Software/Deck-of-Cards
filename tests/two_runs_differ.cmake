# Fails if two runs of PROGRAM print exactly the same thing. Deck::shuffle seeds
# its generator once per process, so only a comparison between two processes
# can tell a seed from std::random_device from a fixed one.
#
# Usage: cmake -DPROGRAM=<path to testingDeck> -P two_runs_differ.cmake
#
# The seed is one 32-bit value, so two correct runs match about once in 4 billion
# and this does not flake in practice. A crash that prints nothing in both runs
# also fails here.

execute_process(COMMAND "${PROGRAM}" OUTPUT_VARIABLE first)
execute_process(COMMAND "${PROGRAM}" OUTPUT_VARIABLE second)

if(first STREQUAL second)
    message(FATAL_ERROR "Two runs of ${PROGRAM} printed the same output:\n${first}")
endif()
