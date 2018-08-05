/*
	Christian Roccanova
	CS362-400
	Assignment 3
	Tests getCost() function
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

	//card costs in order: curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map
	int cardCost[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	int expected;
	int	actual;
	
	printf("Running tests for getCost() function\n");

	//tests getCost for all cards present
	for (int i = 0; i < 27; i++) 
	{
		printf("\nTesting card# %d\n", i);
		actual = getCost(i);
		expected = cardCost[i];		
		printf("Expected: %d	Actual: %d\n", expected, actual);
		isTrue(expected, actual);
	}


	//test with non-existent card - should return -1
	printf("\nTesting invalid card\n");
	actual = getCost(28);
	expected = -1;
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