/*
	Christian Roccanova
	CS362-400
	Assignment 3
	Tests gainCard()
*/ 

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

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


int main(int argc, char** argv) {
	
	int seed = 1000;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall };	
	struct gameState g;
	int actual;
	int expected;

	printf("Running tests for gainCard() function\n");

	initializeGame(2, k, seed, &g);

	//tests attempt to gain from an empty pile
	printf("\nTesting empty pile\n");
	g.supplyCount[smithy] = 0;
	expected = -1;
	actual = gainCard(smithy, &g, 0, 0);
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);
	g.supplyCount[smithy] = 10;

	//tests that card is discarded when flag is 0
	printf("\nTesting addition of card to discard pile\n");
	expected = g.discardCount[0] + 1;
	gainCard(smithy, &g, 0, 0);
	actual = g.discardCount[0];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test that card is added to the deck when flag is 1
	printf("\nTesting addition of card to deck\n");
	expected = g.deckCount[0] + 1;
	gainCard(smithy, &g, 1, 0);
	actual = g.deckCount[0];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test that card is added to the hand when flag is 2
	printf("\nTesting addition of card to hand\n");
	expected = g.handCount[0] + 1;
	gainCard(smithy, &g, 2, 0);
	actual = g.handCount[0];
	isTrue(expected, actual);

	//tests removal of card from supply count
	printf("\nTesting decrease in card supply\n");
	expected = g.supplyCount[smithy] - 1;
	gainCard(smithy, &g, 0, 0);
	actual = g.supplyCount[smithy];
	isTrue(expected, actual);

	if (failCount > 0)
	{
		printf("\nFINAL RESULT: TEST FAILED\n");
		printf("Number of tests failed: %d\n", failCount);
	}
	else
	{
		printf("\nFINAL RESULT: ALL TESTS PASSED\n");
	}

	return 0;
}
