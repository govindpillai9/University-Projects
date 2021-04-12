#include "philos.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
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
    return ((pos + 1) % players);
}

int main(void) {
    //initializing variables
    uint8_t num_players = 0;
    int seed = 0;
    int players_with_money = 0;
    uint8_t current_pos = 0;
    int num_rolls = 0;
    int pot = 0;
    int roll = 0;
    int bank[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
    //asking user for random seed
    printf("Random Seed: ");
    scanf("%d", &seed);
    //making sure user input is valid
    if (seed < 1) {
        printf("Pseudorandom seed must be non-negative (");
        printf("%d", seed);
        printf(")\n");
        return 1;
    }
    //asking user for number of players
    printf("How many players? ");
    //making sure user input is valid
    if (scanf("%" SCNu8, &num_players) != 1) {
        fprintf(stderr, "Number of players not defined\n");
        return 1;
    }
    if (num_players < 1 || num_players > 14) {
        printf("Number of players must be from 1 to 14\n");
        return 1;
    }
    srandom(seed);
    //start of while loop that is only broken once only one player has money
    while (1) {
        //checks to see how many players has money
        for (uint8_t i = 0; i < num_players; i++) {
            if (bank[i] > 0) {
                players_with_money++;
            }
        }
        //if only one player has money, break from the loop
        if (players_with_money <= 1) {
            break;
        }
        players_with_money = 0;
        //setting the number of rolls for the player at the current position
        if (bank[current_pos] >= 3) {
            num_rolls = 3;
        } else {
            num_rolls = bank[current_pos];
        }
        if (num_rolls > 0) {
            printf("%s rolls... ", philosophers[current_pos]);
        }
        //for loop that produces each roll for the player at the current position
        for (int j = 0; j < num_rolls; j++) {
            roll = random() % 6;
            //gives one dollar to the player on the left of current position
            //prints the transaction
            if (die[roll] == LEFT) {
                bank[current_pos] -= 1;
                bank[left(current_pos, num_players)] += 1;
                printf("gives $1 to ");
                printf("%s", philosophers[left(current_pos, num_players)]);
                printf(" ");
                //gives one dollar to the player on the right of current position
                //prints the transaction
            } else if (die[roll] == RIGHT) {
                bank[current_pos] -= 1;
                bank[right(current_pos, num_players)] += 1;
                printf("gives $1 to ");
                printf("%s", philosophers[right(current_pos, num_players)]);
                printf(" ");
                //gives one dollar to the pot
                //prints the transaction
            } else if (die[roll] == CENTER) {
                bank[current_pos] -= 1;
                pot++;
                printf("puts $1 in the pot ");
                //does not distribute money
                //prints transaction
            } else if (die[roll] == PASS) {
                printf("gets a pass ");
            }
        }
        if (num_rolls > 0) {
            printf("\n");
        }
        //sets current position to the player on the right of current position
        current_pos = right(current_pos, num_players);
    }
    //finds the name of the winner
    //prints the winner, the pot, and his bank total
    for (int x = 0; x < 14; x++) {
        if (bank[x] > 0) {
            printf(
                "%s wins the $%d pot with $%d left in the bank!\n", philosophers[x], pot, bank[x]);
            break;
        }
    }
}
