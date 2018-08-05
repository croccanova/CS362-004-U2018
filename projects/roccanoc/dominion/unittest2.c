/*
	Christian Roccanova
	CS362-400
	Assignment 3
	tests updateCoins()
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
	struct gameState g;
	int numPlayers = 2;
	int seed = 1000;
	int k[] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	int bonus = 0;
	int actual;
	int expected;
		
	//fills arrays with respective treasure cards
	for (int i = 0; i < MAX_HAND; i++) 
	{
		g.hand[0][i] = adventurer;
	}

	initializeGame(numPlayers, k, seed, &g);
	g.handCount[0] = 5;

	printf("Running tests for updateCoins() function\n");
	
	//test hand with 0 coin cards
	printf("Test with 0 coins");	
	for (int i = 0; i < 5; i++)
	{
		g.hand[0][i] = smithy;
	}
	updateCoins(0, &g, bonus);
	expected = 0;
	actual = g.coins;
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test with 5 coppers
	printf("\nTesting with 5 coppers, no bonus - expect 5\n");
	for (int i = 0; i < 5; i++)
	{
		g.hand[0][i] = copper;
	}
	updateCoins(0, &g, bonus);
	actual = g.coins;
	expected = 5;
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test with 5 silver
	printf("\nTesting with 5 silvers, no bonus - expect 10\n");
	for (int i = 0; i < 5; i++)
	{
		g.hand[0][i] = silver;
	}
	updateCoins(0, &g, bonus);
	actual = g.coins;
	expected = 10;
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test with 5 golds
	printf("\nTesting with 5 golds, no bonus - expect 15\n");
	for (int i = 0; i < 5; i++)
	{
		g.hand[0][i] = gold;
	}
	updateCoins(0, &g, bonus);
	actual = g.coins;
	expected = 15;
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(expected, actual);

	//test bonus
	printf("\nTesting 5 golds, +5 bonus - expect 20\n");
	bonus = 5;
	updateCoins(0, &g, bonus);
	actual = g.coins;
	expected = 20;
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