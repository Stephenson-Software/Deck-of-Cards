# Fails if two runs of PROGRAM print exactly the same thing. Deck::shuffle seeds
# its generator once per process, so only a comparison between two processes
# can tell a seed from std::random_device from a fixed one.
#
# Usage: cmake -DPROGRAM=<path to testingDeck> -P two_runs_differ.cmake
#
# The odds of two correct shuffles matching are 1 in 52!, so this does not flake
# in practice. A crash that prints nothing in both runs also fails here.

execute_process(COMMAND "${PROGRAM}" OUTPUT_VARIABLE first)
execute_process(COMMAND "${PROGRAM}" OUTPUT_VARIABLE second)

if(first STREQUAL second)
    message(FATAL_ERROR "Two runs of ${PROGRAM} printed the same output:\n${first}")
endif()
