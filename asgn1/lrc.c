#include <stdio.h>
#include <stdlib.h>
#include "philos.h"
#include <inttypes.h>

//Returns the position of the player to the left of pos
//
//pos: position of the current player
//players: number of current players
static inline uint8_t left(uint8_t pos, uint8_t players) {
	return ((pos + players - 1) % players);
}
//Returns the position of the player to the right of pos
//
//pos: position of the current player
//playersL number of current players
static inline uint8_t right(uint8_t pos, uint8_t players) {
	return((pos + 1) % players);
}
