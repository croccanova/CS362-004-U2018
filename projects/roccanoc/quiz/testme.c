/*
	Christian Roccanova
	CS362-400
	Random Testing Quiz
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar() 
{
	// selects random characters from ASCII ' ' to ~
	char randChar;
	int min = 32; // ' '
	int max = 126; // ~
	int range = max - min;
	randChar = (rand() % (range + 1)) + min;
	return randChar;
}

void inputString(char randString[]) 
{
	// selects random characters from ASCII a to z
	int min = 97; // a
	int max = 122; // z
	int range = max - min;
	for (int i = 0; i < 5; i++) {
		randString[i] = (rand() % (range + 1)) + min;
	}
	
}

void testme() {
	int tcCount = 0;
	char s[6] = "temps";
	char c;
	int state = 0;
	while (1) {
		tcCount++;
		c = inputChar(); 
		inputString(s);
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' '&& state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' &&
			s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9) {
			printf("error ");
			exit(200);
		}
	}
}


int main(int argc, char *argv[]) {
	srand(time(NULL));
	testme();
	
	return 0;
}