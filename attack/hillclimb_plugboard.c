#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "enigma.h"
#include "frequtil.h"
#include "enigma_attack.h"

int initplugboard(EnigmaParam* param) {
    // inplace chage for param with IDENTITY_WHEEL plugboard

    unsigned int i;

    for (i=0; i < 26; i++)
        param->plugboard.wheel[i] = IDENTITY_WHEEL.wheel[i];

    return 0;
}

int attachPlugboardTwoIndex(EnigmaParam* curparam, unsigned int i, unsigned int j) {
    // Note: inplace change curparam for plugboard

    unsigned int paired_i, paired_j;

    if (i == j)
        return -1;

    paired_i = curparam->plugboard.wheel[i] - 'A';
    paired_j = curparam->plugboard.wheel[j] - 'A';

    // unplug if already plugged
    curparam->plugboard.wheel[paired_i] = 'A' + paired_i;
    curparam->plugboard.wheel[paired_j] = 'A' + paired_j;

    // plug
    curparam->plugboard.wheel[i] = 'A' + j;
    curparam->plugboard.wheel[j] = 'A' + i;

    return 0;
}

int unplugPlugboardOneIndex(EnigmaParam* curparam, unsigned int i) {
    // Note: inplace change curparam for plugboard
    
    unsigned int paired_i;

    paired_i = curparam->plugboard.wheel[i] - 'A';
    curparam->plugboard.wheel[i] = 'A' + i;
    curparam->plugboard.wheel[paired_i] = 'A' + paired_i;

    return 0;
}

int hillclimbEachScore(EnigmaParam* outputparam, EnigmaParam* origparam, char ciphertext[], double score(char*)) {
    unsigned int i,j;
    EnigmaParam bestparam, curparam, prevparam;
    double bestscore, curscore, prevscore;
    char* plaintext;
    unsigned int plaintextlen;

    plaintextlen = strlen(ciphertext);
    plaintext = (char*)malloc(sizeof(char) * (plaintextlen + 1));

    if (plaintext == NULL)
        return -1;

    // initial param
    copyEnigmaParam(&bestparam, origparam);
    enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
    bestscore = score(plaintext);

    prevscore = bestscore - 0.1;

    while (bestscore > prevscore) {
        prevscore = bestscore;
        copyEnigmaParam(&prevparam, &bestparam);

        // attach plugboard for new pair
        for (i=0; i < 26; i++) {
            for (j=i+1; j < 26; j++) {
                copyEnigmaParam(&curparam, &prevparam);
                attachPlugboardTwoIndex(&curparam, i, j);
                enigmaDecrypt(&curparam, (char*)ciphertext, plaintext);
                curscore = score(plaintext);
    
                if (curscore > bestscore) {
                    copyEnigmaParam(&bestparam, &curparam);
                    bestscore = curscore;
                }
            }
        }

        // unplug some position
        for (i=0; i < 26; i++) {
            if (prevparam.plugboard.wheel[i] != 'A' + (char)i) {
                copyEnigmaParam(&curparam, &prevparam);
                unplugPlugboardOneIndex(&curparam, i);
                enigmaDecrypt(&curparam, (char*)ciphertext, plaintext);
                curscore = score(plaintext);

                if (curscore > bestscore) {
                    copyEnigmaParam(&bestparam, &curparam);
                    bestscore = curscore;
                }
            }
        }
    }

    copyEnigmaParam(outputparam, &bestparam);

    free(plaintext);
    plaintext = NULL;

    return 0;
}

int hillclimbAttackEnigmaPlugboard(EnigmaParam* outputparam, EnigmaParam* origparam, char ciphertext[], Freqfuncs* freqfuncs, unsigned int maxround) {
    /***
     * hill climbing attack based on https://cryptocellar.org/bgac/HillClimbEnigma.pdf
     * assume that origparam is correct except plugboard. (this function changes plugboard only.)
     * (if other parameters are unknown, use bruteforce/randomize method based on IOC.)
     *
     * modified original paper for defeating short message (around 160 characters):
     * - repeatedly round
     * - use bigramIOC
     * 
     * [IOC -> bigramIOC -> bigram](repeat) -> trigram
     ***/

    EnigmaParam bestparam, curparam;
    double bestscore, prevscore;
    char* plaintext;
    unsigned int plaintextlen;
    unsigned int rnd;

    plaintextlen = strlen(ciphertext);
    plaintext = (char*)malloc(sizeof(char) * (plaintextlen + 1));
    if (plaintext == NULL)
        return -1;

    // initialize plugboard
    copyEnigmaParam(&bestparam, origparam);
    initplugboard(&bestparam);
    enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
    bestscore = freqfuncs->trigramScore(plaintext);

    for (rnd=0; rnd < maxround; rnd++) {
        prevscore = bestscore;
    
#ifdef HILLCLIMBDEBUG
        printf("[round]%d\t(prevscore=%lf)\n", rnd, prevscore);
#endif

        // hillclimb based on IOCScore
        copyEnigmaParam(&curparam, &bestparam);
        if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->IOCScore) != 0)
            return -1;
    
#ifdef HILLCLIMBDEBUG
        printf("===== after IOCScore ======\n");
        printEnigmaParam(&bestparam);
        printf("\n");
#endif
    
        // hillclimb based on bigramIOCScore
        copyEnigmaParam(&curparam, &bestparam);
        if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->bigramIOCScore) != 0)
            return -1;
    
#ifdef HILLCLIMBDEBUG
        printf("===== after bigramIOCScore ======\n");
        printEnigmaParam(&bestparam);
        printf("\n");
#endif
    
        // hillclimb based on bigramScore
        copyEnigmaParam(&curparam, &bestparam);
        if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->bigramScore) != 0)
            return -1;
    
#ifdef HILLCLIMBDEBUG
        printf("===== after bigramScore ======\n");
        printEnigmaParam(&bestparam);
        printf("\n");
#endif
   
        // check whether score is improved or not
        enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
        bestscore = freqfuncs->trigramScore(plaintext);
        if (prevscore == bestscore)
            break;
    }

    // finally, hillclimb based on trigramScore
    copyEnigmaParam(&curparam, &bestparam);
    if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->trigramScore) != 0)
        return -1;

#ifdef HILLCLIMBDEBUG
    printf("===== after trigramScore =====\n");
    printEnigmaParam(&bestparam);
    printf("\n");
#endif

    copyEnigmaParam(outputparam, &bestparam);

    if (plaintext != NULL) {
        free(plaintext);
        plaintext = NULL;
    }

    return 0;
}

int hillclimbAttackEnigmaPlugboardSinkov(EnigmaParam* outputparam, EnigmaParam* origparam, char ciphertext[], Freqfuncs* freqfuncs, unsigned int maxround) {
    /***
     * hill climbing attack with using Sinkov score
     * 
     * [sinkov -> sinkov bigram -> bigram](repeat) -> trigram
    ***/
    EnigmaParam bestparam, curparam;
    double bestscore, prevscore;
    char* plaintext;
    unsigned int plaintextlen;
    unsigned int rnd;

    plaintextlen = strlen(ciphertext);
    plaintext = (char*)malloc(sizeof(char) * (plaintextlen + 1));
    if (plaintext == NULL)
        return -1;

    // initialize plugboard
    copyEnigmaParam(&bestparam, origparam);
    initplugboard(&bestparam);
    enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
    bestscore = freqfuncs->trigramScore(plaintext);

    for (rnd=0; rnd < maxround; rnd++) {
        prevscore = bestscore;
    
#ifdef HILLCLIMBDEBUG
        printf("[round]%d\t(prevscore=%lf)\n", rnd, prevscore);
#endif

        // hillclimb based on sinkovScore
        copyEnigmaParam(&curparam, &bestparam);
        if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->sinkovScore) != 0)
            return -1;
    
#ifdef HILLCLIMBDEBUG
        printf("===== after sinkovScore ======\n");
        printEnigmaParam(&bestparam);
        printf("\n");
#endif
   
        // hillclimb based on sinkovbigramScore
        copyEnigmaParam(&curparam, &bestparam);
        if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->sinkovbigramScore) != 0)
            return -1;
    
#ifdef HILLCLIMBDEBUG
        printf("===== after sinkovbigramScore ======\n");
        printEnigmaParam(&bestparam);
        printf("\n");
#endif
    
        // hillclimb based on bigramScore
        copyEnigmaParam(&curparam, &bestparam);
        if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->bigramScore) != 0)
            return -1;
    
#ifdef HILLCLIMBDEBUG
        printf("===== after bigramScore ======\n");
        printEnigmaParam(&bestparam);
        printf("\n");
#endif
    
        // check whether score imprved or not
        enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
        bestscore = freqfuncs->trigramScore(plaintext);
        if (prevscore == bestscore)
            break;
    }

    // finally, hillclimb based on trigramScore
    copyEnigmaParam(&curparam, &bestparam);
    if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->trigramScore) != 0)
        return -1;

#ifdef HILLCLIMBDEBUG
    printf("===== after trigramScore =====\n");
    printEnigmaParam(&bestparam);
    printf("\n");
#endif

    copyEnigmaParam(outputparam, &bestparam);

    if (plaintext != NULL) {
        free(plaintext);
        plaintext = NULL;
    }

    return 0;
}

int hillclimbAttackEnigmaPlugboardSinkovWithFewBruteforce(EnigmaParam* outputparam, EnigmaParam* origparam, char ciphertext[], Freqfuncs* freqfuncs, unsigned int maxround) {
    /***
     * hill climbing attack with Sinkov score
     * with bruteforce: ("E-sticker method" (not only "E", use 5-high monogram score characters))
     * 
     * it might be suitable for short message (so comment out for using trigram score)
    ***/
    EnigmaParam bestouterparam, outerparam, bestparam, curparam;
    double bestouterscore, bestscore, prevscore;
    char* plaintext;
    unsigned int plaintextlen;
    unsigned int i, j;
    unsigned int rank;
    unsigned int rnd;
    unsigned int monogramrank[5];
    int alreadyplugged;

    if (rankBasedScoreTable((unsigned int*)monogramrank, 5, monogramtable, 26) != 0)
        return -1;

    plaintextlen = strlen(ciphertext);
    plaintext = (char*)malloc(sizeof(char) * (plaintextlen + 1));
    if (plaintext == NULL)
        return -1;

    // initialize plugboard
    copyEnigmaParam(&bestouterparam, origparam);
    initplugboard(&bestouterparam);
    enigmaDecrypt(&bestouterparam, (char*)ciphertext, plaintext);
    bestouterscore = freqfuncs->bigramScore(plaintext);

    for (rank=0; rank < 5; rank++) {
        // initialize plugboard
        copyEnigmaParam(&outerparam, &bestouterparam);
        for (i=0; i < 26; i++) {
            alreadyplugged = 0;
            for (j=0; j < rank; j++) {
                if (
                        (monogramrank[j] == i) || 
                        (bestouterparam.plugboard.wheel[monogramrank[j]] == 'A' + (char)i)
                ) {
                    alreadyplugged = 1;
                }
            }
            if (alreadyplugged == 0) 
                outerparam.plugboard.wheel[i] = 'A' + i;
        }

        // plugged for upper rank index
        if (outerparam.plugboard.wheel[monogramrank[rank]] != 'A' + (char)monogramrank[rank])
            continue;
        
        for (j=0; j < 26; j++) {
            copyEnigmaParam(&bestparam, &outerparam);
            bestparam.plugboard.wheel[monogramrank[rank]] = 'A' + j;

            // hillclimb loop
            enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
            bestscore = freqfuncs->bigramScore(plaintext);
            for (rnd=0; rnd < maxround; rnd++) {
                prevscore = bestscore;
#ifdef HILLCLIMBDEBUG
                printf("[round]%d\t(prevscore=%lf)\n", rnd, prevscore);
#endif
        
                // hillclimb based on sinkovScore
                copyEnigmaParam(&curparam, &bestparam);
                if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->sinkovScore) != 0)
                    return -1;
            
#ifdef HILLCLIMBDEBUG
                printf("===== after sinkovScore ======\n");
                printEnigmaParam(&bestparam);
                printf("\n");
#endif
           
                // hillclimb based on sinkovbigramScore        
                copyEnigmaParam(&curparam, &bestparam);
                if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->sinkovbigramScore) != 0)
                    return -1;
            
#ifdef HILLCLIMBDEBUG
                printf("===== after sinkovbigramScore ======\n");
                printEnigmaParam(&bestparam);
                printf("\n");
#endif
            
                // hillclimb based on bigramScore
                copyEnigmaParam(&curparam, &bestparam);
                if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->bigramScore) != 0)
                    return -1;
            
#ifdef HILLCLIMBDEBUG
                printf("===== after bigramScore ======\n");
                printEnigmaParam(&bestparam);
                printf("\n");
#endif
            
                // check whether score imprved or not
                enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
                bestscore = freqfuncs->bigramScore(plaintext);
                if (prevscore == bestscore)
                    break;
            }

            /***            
            // finally, hillclimb based on trigramScore
            copyEnigmaParam(&curparam, &bestparam);
            if (hillclimbEachScore(&bestparam, &curparam, ciphertext, freqfuncs->trigramScore) != 0)
                return -1;
        
#ifdef HILLCLIMBDEBUG
            printf("===== after trigramScore =====\n");
            printEnigmaParam(&bestparam);
            printf("\n");
#endif
            ***/

            enigmaDecrypt(&bestparam, (char*)ciphertext, plaintext);
            bestscore = freqfuncs->bigramScore(plaintext);
            if (bestscore > bestouterscore) {
                copyEnigmaParam(&bestouterparam, &bestparam);
                bestouterscore = bestscore;
            }
        }
    }

    copyEnigmaParam(outputparam, &bestouterparam);

    if (plaintext != NULL) {
        free(plaintext);
        plaintext = NULL;
    }

    return 0;
}


/*** ranking function ***/

static const double NEGINFSCORE = -2e30;

int insertparam(EnigmaParam rankarray[], double scoretable[], EnigmaParam* curparam, double curscore, unsigned int maxrank) {
    unsigned int i;
    int j;

    for (i=0; i < maxrank; i++) {
        if (scoretable[i] <= curscore) {
            for (j=maxrank-2; j >= (int)i; j--) {
                if (scoretable[j] != NEGINFSCORE) {
                    copyEnigmaParam(&(rankarray[j+1]), &(rankarray[j]));
                    scoretable[j+1] = scoretable[j];
                }
            }
            copyEnigmaParam(&(rankarray[i]), curparam);
            scoretable[i] = curscore;

            break;
        }
    }

    return 0;
}


int rankingNeighborGivenParam(EnigmaParam rankarray[], unsigned int maxrank, EnigmaParam* origparam, char ciphertext[], double (*score)(char*)) {
    /***
     * compute score ranking for params of neighbor(one plugboard change) from origparam
     * output: rankarray (array length is maxrank)
    ***/

    unsigned int i, j;
    EnigmaParam curparam;
    unsigned int plaintextlen;
    char* plaintext;
    double curscore;
    double* scoretable;

    plaintextlen = strlen(ciphertext);
    plaintext = (char*)malloc(sizeof(char) * (plaintextlen + 1));
    if (plaintext == NULL)
        return -1;

    scoretable = (double*)malloc(sizeof(double) * maxrank);
    if (scoretable == NULL)
        return -1;

    for (i=0; i < maxrank; i++)
        scoretable[i] = NEGINFSCORE;

    enigmaDecrypt(origparam, (char*)ciphertext, plaintext);
    curscore = score(plaintext);
    insertparam(rankarray, scoretable, origparam, curscore, maxrank);

    for (i=0; i < 26; i++) {
        for (j=i+1; j < 26; j++) {
            if (origparam->plugboard.wheel[i] == 'A' + (char)j)
                continue; // generate same plugboard
            
            copyEnigmaParam(&curparam, origparam);
            attachPlugboardTwoIndex(&curparam, i, j);
            enigmaDecrypt(&curparam, (char*)ciphertext, plaintext);
            curscore = score(plaintext);

            insertparam(rankarray, scoretable, &curparam, curscore, maxrank);
        }
    }

    for (i=0; i < 26; i++) {
        if (origparam->plugboard.wheel[i] == 'A' + (char)j)
            continue;

        copyEnigmaParam(&curparam, origparam);
        unplugPlugboardOneIndex(&curparam, i);
        enigmaDecrypt(&curparam, (char*)ciphertext, plaintext);
        curscore = score(plaintext);

        insertparam(rankarray, scoretable, &curparam, curscore, maxrank);
    }

#ifdef HILLCLIMBDEBUG
    for (i=0; i < maxrank; i++) {
        for (j=0; j < 26; j++)
            printf("%c", rankarray[i].plugboard.wheel[j]);
        printf(" %lf\n", scoretable[i]);
    }
#endif

    free(scoretable);
    scoretable = NULL;

    free(plaintext);
    plaintext = NULL;

    return 0;
}
