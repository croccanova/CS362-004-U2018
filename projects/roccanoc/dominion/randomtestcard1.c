/*
	Christian Roccanova
	CS362-400
	Assignment 4
	Random tester for the smithy card
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <time.h>

void randomizeState(struct gameState *state);
int randInt(int min, int max);

// counter for total number of failures
int failCount = 0;

// checks if two values are equivalent
void isTrue(int a, int b)
{
	if (a == b)
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
		failCount++;
	}
}

// randomly initialize game state
void randomizeState(struct gameState *state)
{
	for (int i = 0; i < sizeof(struct gameState); i++) {
		((char*)state)[i] = floor(Random() * 256);
	}

	// randomize player count and selected player
	int numPlayers = randInt(2, MAX_PLAYERS);
	int playerNumber = randInt(0, numPlayers);

	// fill gameState data members
	state->numPlayers = numPlayers;
	state->whoseTurn = playerNumber;
	state->deckCount[playerNumber] = randInt(3, MAX_DECK);
	state->discardCount[playerNumber] = randInt(0, MAX_DECK - state->deckCount[playerNumber]);
	state->handCount[playerNumber] = randInt(0, MAX_DECK - state->deckCount[playerNumber] - state->discardCount[playerNumber]);
	state->playedCardCount = 0;


	// randomize cards in deck, discard pile, and hand
	for (int i = 0; i < state->deckCount[playerNumber]; i++)
	{
		state->deck[playerNumber][i] = randInt(curse, treasure_map);
	}
	for (int i = 0; i < state->discardCount[playerNumber]; i++)
	{
		state->discard[playerNumber][i] = randInt(curse, treasure_map);
	}
	for (int i = 0; i < state->handCount[playerNumber]; i++)
	{
		state->hand[playerNumber][i] = randInt(curse, treasure_map);
	}
}


//returns a random integer within given range
//source: http://c-faq.com/lib/randrange.html
int randInt(int min, int max)
{
	double r = rand();
	return (int)(min + r * (max - min) / (double)RAND_MAX);
}

void smithyTest(struct gameState control, int failCount)
{
	//make copy of gameState to run through the tests
	struct gameState test;
	test = control;

	//initialize cardEffect parameters to random values using randi from randomhelpers
	int c1 = randInt(curse, treasure_map);
	int c2 = randInt(curse, treasure_map);
	int c3 = randInt(curse, treasure_map);
	int playerNum = control.whoseTurn;
	int handPos = randInt(0, control.handCount[playerNum]);
	int bonus = randInt(0, MAX_DECK);
	int actual, expected;

	cardEffect(smithy, c1, c2, c3, &test, handPos, &bonus);

	//test hand count
	printf("\nTest hand count for player A\n");
	expected = control.handCount[playerNum] + 2; //3 cards drawn, 1 card played
	actual = test.handCount[playerNum];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test deck count
	printf("\nTest deck count for player A\n");
	expected = control.deckCount[playerNum] - 3;
	actual = test.deckCount[playerNum];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//Tests to ensure victory cards are unchanged
	printf("\nTesting that victory card piles remain unchanged\n");
	printf("\nTesting province\n");
	actual = test.supplyCount[province];
	expected = control.supplyCount[province];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	printf("\nTesting duchy\n");
	actual = test.supplyCount[duchy];
	expected = control.supplyCount[duchy];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	printf("\nTesting estate\n");
	actual = test.supplyCount[duchy];
	expected = control.supplyCount[duchy];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//Tests to ensure kingdom cards are unchanged
	printf("\nTesting that kingdom card piles remain unchanged\n");
	for (int i = 0; i < treasure_map + 1; i++)
	{
		printf("\nTesting pile# %d\n", i);
		actual = test.supplyCount[i];
		expected = control.supplyCount[i];
		printf("Expected: %d	Actual: %d\n", expected, actual);
		isTrue(expected, actual);
	}

	//Tests to ensure other player is not affected
	printf("\nTesting that there was no effect on other player(s)\n");
	for (int i = 0; i < control.numPlayers; i++) 
	{
		if (i == playerNum) 
		{
			printf("\nSkipping tested player\n");
			continue;
		}
		else
		{
			printf("Testing player #%d\n", i);
			printf("Testing other player's hand count(s)\n");
			actual = test.handCount[i];
			expected = control.handCount[i];
			printf("Expected: %d	Actual: %d\n", expected, actual);
			isTrue(expected, actual);

			printf("\nTesting other player's deck count(s)\n");
			actual = test.deckCount[i];
			expected = control.deckCount[i];
			printf("Expected: %d	Actual: %d\n", expected, actual);
			isTrue(expected, actual);

			printf("\nTesting other player's discard count(s)\n");
			actual = test.discardCount[i];
			expected = control.discardCount[i];
			printf("Expected: %d	Actual: %d\n", expected, actual);
			isTrue(expected, actual);
		}
	}

	if (failCount > 0)
	{
		printf("\nFINAL RESULT: TEST FAILED\n");
		printf("Number of tests failed: %d\n", failCount);
	}
	else
	{
		printf("\nFINAL RESULT: ALL TESTS PASSED\n");
	}
}



int main(int argc, char** argv)
{
	srand(time(NULL));

	printf("Running tests for Smithy card.\n");
	int testCount = 100;
	int totalFails = 0;
	struct gameState g;
	for (int i = 0; i < testCount; i++) 
	{
		failCount = 0;
		randomizeState(&g);
		smithyTest(g, failCount);
		totalFails += failCount;
	}

	if (totalFails > 0) 
	{
		printf("%d Tests Failed over %d runs of test suite.\n", totalFails, testCount);
	}
	else
	{
		printf("All tests passed!\n");
	}

	return 0;
}
