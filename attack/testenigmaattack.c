#include <stdio.h>
#include <string.h>

#include "enigma.h"
#include "frequtil.h"
#include "enigma_attack.h"

int hillclimbtest1() {
    EnigmaParam encparam, origparam, outputparam;
    char plaintext[465] = "ALICEWASBEGINNINGTOGETVERYTIREDOFSITTINGBYHERSISTERONTHEBANKANDOFHAVINGNOTHINGTODOONCEORTWICESHEHADPEEPEDINTOTHEBOOKHERSISTERWASREADINGBUTITHADNOPICTURESORCONVERSATIONSINITANDWHATISTHEUSEOFABOOKTHOUGHTALICEWITHOUTPICTURESORCONVERSATIONSSOSHEWASCONSIDERINGINHEROWNMINDASWELLASSHECOULDFORTHEHOTDAYMADEHERFEELVERYSLEEPYANDSTUPIDWHETHERTHEPLEASUREOFMAKINGADAISYCHAINWOULDBEWORTHTHETROUBLEOFGETTINGUPANDPICKINGTHEDAISIESWHENSUDDENLYAWHITERABBITWITHPINKEYESRANCLOSEBYHER\0";
    char ciphertext[465];

    int reflector = 0;  // B
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'X', 'Y', 'Z'};
    char wheel_pos[3] = {'A', 'B', 'C'};
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    unsigned int i;

    if (setparam_ENIGMA_M3(&encparam, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;
    enigmaEncrypt(&encparam, plaintext, ciphertext);

    copyEnigmaParam(&origparam, &encparam);
    initplugboard(&origparam);

    if (EnglishFreqfuncs.initialize() != 0)
        return -1;

    if (hillclimbAttackEnigmaPlugboard(&outputparam, &origparam, ciphertext, (Freqfuncs*)&EnglishFreqfuncs, 1) != 0)
        return -1;

#ifdef HILLCLIMBDEBUG
    printf("[encparam]\n");
    printEnigmaParam(&encparam);
    printf("\n[outputparam]\n");
    printEnigmaParam(&outputparam);
    printf("\n");
#endif

    for (i=0; i < 26; i++) {
        if (outputparam.plugboard.wheel[i] != encparam.plugboard.wheel[i])
            return -2;
    }

    if (EnglishFreqfuncs.finalize() != 0)
        return -1;

    return 0;
}

int hillclimbtest_nearestrank_1() {
    EnigmaParam encparam, origparam, outputparam;
    char plaintext[160] = "SOSHEWASCONSIDERINGINHEROWNMINDASWELLASSHECOULDFORTHEHOTDAYMADEHERFEELVERYSLEEPYANDSTUPIDWHETHERTHEPLEASUREOFMAKINGADAISYCHAINWOULDBEWORTHTHETROUBLEOFGETTINGUP\0";
    char ciphertext[160];

    int reflector = 0;  // B
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'X', 'Y', 'Z'};
    char wheel_pos[3] = {'A', 'B', 'C'};
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    unsigned int i;

    if (setparam_ENIGMA_M3(&encparam, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;
    enigmaEncrypt(&encparam, plaintext, ciphertext);

    copyEnigmaParam(&origparam, &encparam);
    initplugboard(&origparam);

    if (EnglishFreqfuncs.initialize() != 0)
        return -1;

    if (hillclimbAttackEnigmaPlugboard(&outputparam, &origparam, ciphertext, (Freqfuncs*)&EnglishFreqfuncs, 2) != 0)
        return -1;

#ifdef HILLCLIMBDEBUG
    printf("[encparam]\n");
    printEnigmaParam(&encparam);
    printf("\n");
#endif

    for (i=0; i < 26; i++) {
        if (outputparam.plugboard.wheel[i] != encparam.plugboard.wheel[i])
            return -2;
    }


    /***
    unsigned int j;
    unsigned int maxrank = 50;
    EnigmaParam rankarray[50];

    if (rankingNeighborGivenParam(rankarray, maxrank, &outputparam, ciphertext, EnglishFreqfuncs.trigramScore) != 0)
        return -1;

    for (i=0; i < maxrank; i++) {
        for (j=0; j < 26; j++) {
            if (rankarray[i].plugboard.wheel[j] != encparam.plugboard.wheel[j])
                break;
        }

        if (j == 26) {
#ifdef HILLCLIMBDEBUG
            printf("MATCHED AT %d\n", i);
#endif
            return 0;
        }
    }
    return -2;
    ***/

    if (EnglishFreqfuncs.finalize() != 0)
        return -1;

    return 0;
}

int hillclimbtest_nearestrank_sinkov_1() {
    EnigmaParam encparam, origparam, outputparam;
    char plaintext[160] = "SOSHEWASCONSIDERINGINHEROWNMINDASWELLASSHECOULDFORTHEHOTDAYMADEHERFEELVERYSLEEPYANDSTUPIDWHETHERTHEPLEASUREOFMAKINGADAISYCHAINWOULDBEWORTHTHETROUBLEOFGETTINGUP\0";
    char ciphertext[160];

    int reflector = 0;  // B
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'X', 'Y', 'Z'};
    char wheel_pos[3] = {'A', 'B', 'C'};
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    unsigned int i;

    if (setparam_ENIGMA_M3(&encparam, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;
    enigmaEncrypt(&encparam, plaintext, ciphertext);

    copyEnigmaParam(&origparam, &encparam);
    initplugboard(&origparam);

    if (EnglishFreqfuncs.initialize() != 0)
        return -1;

    if (hillclimbAttackEnigmaPlugboardSinkov(&outputparam, &origparam, ciphertext, (Freqfuncs*)&EnglishFreqfuncs, 1) != 0)
        return -1;

#ifdef HILLCLIMBDEBUG
    printf("[encparam]\n");
    printEnigmaParam(&encparam);
    printf("\n");
#endif

    for (i=0; i < 26; i++) {
        if (outputparam.plugboard.wheel[i] != encparam.plugboard.wheel[i])
            return -2;
    }

    if (EnglishFreqfuncs.finalize() != 0)
        return -1;

    return 0;
}

int hillclimbtest_sinkov_fewbruteforce_1() {
    EnigmaParam encparam, origparam, outputparam;
    char plaintext[136] = "ALICEWASBEGINNINGTOGETVERYTIREDOFSITTINGBYHERSISTERONTHEBANKANDOFHAVINGNOTHINGTODOONCEORTWICESHEHADPEEPEDINTOTHEBOOKHERSISTERWASREADING\0";
    char ciphertext[136];

    int reflector = 0;  // B
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'X', 'Y', 'Z'};
    char wheel_pos[3] = {'A', 'B', 'C'};
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    unsigned int i;

    if (setparam_ENIGMA_M3(&encparam, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;
    enigmaEncrypt(&encparam, plaintext, ciphertext);

    copyEnigmaParam(&origparam, &encparam);
    initplugboard(&origparam);

    if (EnglishFreqfuncs.initialize() != 0)
        return -1;

    if (hillclimbAttackEnigmaPlugboardSinkovWithFewBruteforce(&outputparam, &origparam, ciphertext, (Freqfuncs*)&EnglishFreqfuncs, 1) != 0)
        return -1;

#ifdef HILLCLIMBDEBUG
    printf("[encparam]\n");
    printEnigmaParam(&encparam);
    printf("\n");
#endif

    for (i=0; i < 26; i++) {
        if (outputparam.plugboard.wheel[i] != encparam.plugboard.wheel[i])
            return -2;
    }

    if (EnglishFreqfuncs.finalize() != 0)
        return -1;

    return 0;
}

int hillclimbtest2() {
    // https://www.bytereef.org/m4-project-first-break.html
    int reflector = 0;  // B_Thin
    int wheel_order[4] = {0, 2-1, 4-1, 1-1};
    char ring_setting[4] = {'A', 'A', 'A', 'V'};
    char wheel_pos[4] = {'V', 'J', 'N', 'A'};
    char plugboard_pairs[21] = "ATBLDFGJHMNWOPQYRZVX\0";

    EnigmaParam encparam, origparam, outputparam;
    char ciphertext[233] = "NCZWVUSXPNYMINHZXMQXSFWXWLKJAHSHNMCOCCAKUQPMKCSMHKSEINJUSBLKIOSXCKUBHMLLXCSJUSRRDVKOHULXWCCBGVLIYXEOAHXRHKKFVDREWEZLXOBAFGYUJQUKGRTVUKAMEURBVEKSUHHVOYHABCJWMAKLFKLMYFVNRIZRVVRTKOFDANJMOLBGFFLEOPRGTFLVRHOWOPBEKVWMUQFMPWPARMFHAGKXIIBG\0";
    char plaintext[233];
    const char plaintext_expected[233] = "VONVONJLOOKSJHFFTTTEINSEINSDREIZWOYYQNNSNEUNINHALTXXBEIANGRIFFUNTERWASSERGEDRUECKTYWABOSXLETZTERGEGNERSTANDNULACHTDREINULUHRMARQUANTONJOTANEUNACHTSEYHSDREIYZWOZWONULGRADYACHTSMYSTOSSENACHXEKNSVIERMBFAELLTYNNNNNNOOOVIERYSICHTEINSNULL\0";

    unsigned int i;

    if (setparam_ENIGMA_M4(&encparam, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;

    copyEnigmaParam(&origparam, &encparam);
    initplugboard(&origparam);

    if (GermanSpecialFreqfuncs.initialize() != 0)
        return -1;

    if (hillclimbAttackEnigmaPlugboard(&outputparam, &origparam, ciphertext, (Freqfuncs*)&GermanSpecialFreqfuncs, 1) != 0)
        return -1;

#ifdef HILLCLIMBDEBUG
    printf("[encparam]\n");
    printEnigmaParam(&encparam);
    printf("\n[outputparam]\n");
    printEnigmaParam(&outputparam);
    printf("\n");
#endif

    for (i=0; i < 26; i++) {
        if (outputparam.plugboard.wheel[i] != encparam.plugboard.wheel[i])
            return -2;
    }

    enigmaDecrypt(&outputparam, ciphertext, plaintext);
    for (i=0; i < strlen(plaintext); i++) {
        if (plaintext[i] != plaintext_expected[i])
            return -3;
    }

    if (GermanSpecialFreqfuncs.finalize() != 0)
        return -1;

    return 0;
}

int bombetest1() {
    EnigmaParam encparam, origparam, outputparam;
    char plaintext[97] = "XXXXXABCDEFGHIJKLMNOPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\0";
    char ciphertext[97];
    char pseudoplaintext[97];

    char crib[16+1] = "ABCDEFGHIJKLMNOP\0";
    unsigned int crib_idx_at_ciphertext = 5;

    int reflector = 0;  // B
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'X', 'Y', 'Z'};
    char wheel_pos[3] = {'A', 'B', 'C'};
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    unsigned int i;

    if (setparam_ENIGMA_M3(&encparam, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;
    enigmaEncrypt(&encparam, plaintext, ciphertext);

    copyEnigmaParam(&origparam, &encparam);
    initplugboard(&origparam);

    if (bombeAttackEnigmaPlugboard(&outputparam, &origparam, ciphertext, crib, crib_idx_at_ciphertext) != 0)
        return -1;

#ifdef BOMBEDEBUG
    printf("[encparam]\n");
    printEnigmaParam(&encparam);
    printf("\n");

    printf("[outputparam]\n");
    printEnigmaParam(&outputparam);
    printf("\n");
#endif

    enigmaDecrypt(&outputparam, ciphertext, pseudoplaintext);

#ifdef BOMBEDEBUG
    printf("[pseudoplaintext]\n");
    printf("%s\n", pseudoplaintext);
#endif

    for (i=0; i < strlen(crib); i++) {
        if (plaintext[crib_idx_at_ciphertext + i] != pseudoplaintext[crib_idx_at_ciphertext + i])
            return -2;
    }

    for (i=0; i < 26; i++) {
        if (outputparam.plugboard.wheel[i] != encparam.plugboard.wheel[i])
            return -3;
    }

    return 0;
}

int main() {
    unsigned int i;

    typedef struct testcase__ {
        int (*func)();
        char testname[64];
    } TestCase;

    TestCase testcases[] = {
        {hillclimbtest1, "hillclimbtest1\0"},
        {hillclimbtest_nearestrank_1, "hillclimbtest_nerestrank_1\0"},
        {hillclimbtest_nearestrank_sinkov_1, "hillclimbtest_nerestrank_sinkov_1\0"},
        {hillclimbtest2, "hillclimbtest2\0"},
        {hillclimbtest_sinkov_fewbruteforce_1, "hillclimbtest_sinkov_fewbruteforce_1\0"},
        {bombetest1, "bombetest1\0"},
    };

    static const unsigned int testcasenum = 6;

    for (i=0; i < testcasenum; i++) {
        if (testcases[i].func() == 0) {
            printf("%s passed.\n", testcases[i].testname);
        } else {
            printf("%s failed.\n", testcases[i].testname);
        }
    }

    return 0;
}
