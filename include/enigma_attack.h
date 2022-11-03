#ifndef __ENIGMA_ATTACK_H_
#define __ENIGMA_ATTACK_H_

#include "enigma.h"
#include "frequtil.h"

/* hillclimb_plugboard.c */
int initplugboard(EnigmaParam*);
int hillclimbAttackEnigmaPlugboard(EnigmaParam*, EnigmaParam*, char[], Freqfuncs*, unsigned int); /* outputparam, origparam, ciphertext, freqfuncs, maxround */
int hillclimbAttackEnigmaPlugboardSinkov(EnigmaParam*, EnigmaParam*, char[], Freqfuncs*, unsigned int); /* outputparam, origparam, ciphertext, freqfuncs, maxround */
int hillclimbAttackEnigmaPlugboardSinkovWithFewBruteforce(EnigmaParam*, EnigmaParam*, char[], Freqfuncs*, unsigned int); /* outputparam, origparam, ciphertext, freqfuncs, maxround */
int rankingNeighborGivenParam(EnigmaParam[], unsigned int, EnigmaParam*, char[], double (*score)(char*)); /* rankarray, maxrank, origparam, ciphertext, score */

/* bombe_plugboard.c */
int isVaridCrib(char[], char[], unsigned int); /* ciphertext, crib, crib_idx_at_ciphertext */
int bombeAttackEnigmaPlugboard(EnigmaParam*, EnigmaParam*, char[], char[], unsigned int); /* outputparam, origparam, ciphertext, crib, crib_idx_at_ciphertext */

#endif /* __ENIGMA_ATTACK_H_ */
