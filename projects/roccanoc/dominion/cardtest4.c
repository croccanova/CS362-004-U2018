/*
	Christian Roccanova
	CS362-400
	Assignment 3
	Tests great hall card
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

int main(int argc, char** argv)
{
	//set arguments for initializeGame and cardEffect
	struct gameState control, test;
	int numPlayers = 2;
	int handPos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
	int seed = 1000;
	int k[] = { adventurer, council_room, feast, gardens, mine,
		outpost, smithy, village, baron, great_hall };
	int expected;
	int actual;
	int playerA = 0;
	int playerB = 1;

	initializeGame(numPlayers, k, seed, &control);

	// copy the game state, test will actually be run while control will be manually modified to represent the expected values
	test = control;

	printf("Running tests for great hall card\n");

	cardEffect(great_hall, choice1, choice2, choice3, &test, handPos, &bonus);

	//test hand count
	printf("\nTesting hand count\n");
	expected = control.handCount[playerA]; //1 cards gained, 1 card played
	actual = test.handCount[playerA];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test deck count
	printf("\nTesting deck count\n"); //deck decreases by 1
	expected = control.deckCount[playerA] - 1;
	actual = test.deckCount[playerA];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test action count
	printf("\nTesting that action count increases\n");
	expected = control.numActions + 1; //1 bonus action gained
	actual = test.numActions;
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
	for (int i = 0; i < 10; i++) 
	{
		printf("\nTesting pile# %d\n", i);
		actual = test.supplyCount[k[i]];
		expected = control.supplyCount[k[i]];
		printf("Expected: %d	Actual: %d\n", expected, actual);
		isTrue(expected, actual);
	}

	//Tests to ensure other player is not affected
	printf("\nTesting that there was no effect on playerB\n");
	printf("\nTesting playerB's hand count\n");
	actual = test.handCount[playerB];
	expected = control.handCount[playerB];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	printf("\nTesting playerB's deck count\n");
	actual = test.deckCount[playerB];
	expected = control.deckCount[playerB];
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	printf("\nTesting playerB's discard count\n");
	actual = test.discardCount[playerB];
	expected = control.discardCount[playerB];
	printf("Expected: %d	Actual: %d\n", expected, actual);
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
