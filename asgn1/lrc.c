#include <stdio.h>
#include <stdlib.h>
#include "philos.h"
#include <inttypes.h>

//Returns the position of the player to the left of pos
//
//pos: position of the current player
//players: number of current players
/*static inline uint8_t left(uint8_t pos, uint8_t players) {
	return ((pos + players - 1) % players);
}*/
//Returns the position of the player to the right of pos
//
//pos: position of the current player
//playersL number of current players
/*static inline uint8_t right(uint8_t pos, uint8_t players) {
	return((pos + 1) % players);
}*/

int main(void) {
	uint8_t num_players = 0;
	int seed = 0;
	printf("Random Seed: ");
	scanf("%d", &seed);
	if(seed < 1) {	
		printf("Pseudorandom seed must be non-negative (");
		printf("%d",seed);
		printf(")\n");	
		return 1;
	}
	printf("How many players? ");
	if(scanf("%" SCNu8, &num_players) != 1) {
		fprintf(stderr, "Number of players not defined\n");
		return 1;
	}
	if(num_players < 1 || num_players > 14) {
		printf("Number of players must be from 1 to 14\n");
		return 1;
	}
	    	
	       
}
