/*
	Christian Roccanova
	CS362-400
	Assignment 3
	tests isGameOver()
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
	}
}

int main(int argc, char** argv) 
{
	struct gameState g;
	int i;
	int numSupplyPiles = 25;
	int actual;
	int expected;

	/* initialize supply piles with one card */
	for (i = 0; i < numSupplyPiles; i++)
	{
		g.supplyCount[i] = 1;
	}

	printf("Running tests for isGameOver() function\n");

	//test with supply piles and provinces still having at least 1 card - game should not end
	printf("\nTesting province and supply piles not empty - expect return 0\n");
	expected = 0;
	actual = isGameOver(&g);
	isTrue(actual, expected);
	
	//test with empty stack of province cards - game should end
	printf("\nTesting province pile is empty - expect return 1\n");
	expected = 1;
	g.supplyCount[province] = 0;
	actual = isGameOver(&g);
	isTrue(actual, expected);
	
	//test with 3 empty supply piles - game should end
	printf("\nTesting 3 empty supply piles - expect return 1\n");
	expected = 1;
	g.supplyCount[province] = 1;
	g.supplyCount[adventurer] = 0;
	g.supplyCount[smithy] = 0;
	g.supplyCount[mine] = 0;
	actual = isGameOver(&g);
	printf("Expected: %d	Actual: %d\n", expected, actual);
	isTrue(actual, expected);
	
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