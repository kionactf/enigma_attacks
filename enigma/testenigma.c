#include <stdio.h>
#include <string.h>
#include "enigma.h"

int testsample1() {
    // Enigma Instruction Manual, 1930: http://wiki.franklinheath.co.uk/index.php/Enigma/Sample_Messages
    int reflector = 0; // A
    int wheel_order[3] = {2-1, 1-1, 3-1};
    char ring_setting[3] = {24 + 'A' - 1, 13 + 'A' - 1, 22 + 'A' - 1}; // XMV
    char wheel_pos[3] = {'A', 'B', 'L'};
    char plugboard_pairs[13] = "AMFINVPSTUWZ\0";

    EnigmaParam param;
    char from[91] = "GCDSEAHUGWTQGRKVLFGXUCALXVYMIGMMNMFDXTGNVHVRMMEVOUYFZSLRHDRRXFJWCFHUHMUNZEFRDISIKBGPMYVXUZ\0";
    char to[91];
    char to_expected[91] = "FEINDLIQEINFANTERIEKOLONNEBEOBAQTETXANFANGSUEDAUSGANGBAERWALDEXENDEDREIKMOSTWAERTSNEUSTADT\0";

    if (setparam_ENIGMA_I(&param, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testsample2() {
    // Turing's Treatise, 1940: http://wiki.franklinheath.co.uk/index.php/Enigma/Sample_Messages
    int wheel_order[3] = {3-1, 1-1, 2-1};
    char ring_setting[4] = {26 + 'A' - 1, 17 + 'A' - 1, 16 + 'A' - 1, 13 + 'A' - 1}; // ZQPM
    char wheel_pos[4] = {'J', 'E', 'Z', 'A'};

    EnigmaParam param;
    char from[33] = "QSZVIDVMPNEXACMRWWXUIYOTYNGVVXDZ\0";
    char to[33];
    char to_expected[33] = "DEUTSQETRUPPENSINDJETZTINENGLAND\0";

    if (setparam_ENIGMA_RAILWAY(&param, wheel_order, ring_setting, wheel_pos) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testSwissK() {
    // to_expected is obtained from: https://dencode.com/en/cipher/enigma
    // some public implementation result is not same, but I think dencode is correct (testsample2 correctly decoded)
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[4] = {'Z', 'Y', 'X', 'W'};
    char wheel_pos[4] = {'A', 'B', 'C', 'D'};

    EnigmaParam param;
    char from[79] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    char to[79];
    char to_expected[79] = "ONRKVYAVVQOAXFZAKFPUADNGUTXNFSKPPWGUSZYIEKBTAHDGPJMRPEUMUADJFKHQODHTUWNCKPRWQO\0";

    if (setparam_ENIGMA_SWISSK(&param, wheel_order, ring_setting, wheel_pos) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}


int testsample3() {
    // Operation Barbarossa, 1941: http://wiki.franklinheath.co.uk/index.php/Enigma/Sample_Messages
    int reflector = 1; // B
    int wheel_order[3] = {2-1, 4-1, 5-1};
    char ring_setting[3] = {2 + 'A' - 1, 21 + 'A' - 1, 12 + 'A' - 1}; // BUL
    char wheel_pos[3] = {'B', 'L', 'A'};
    char plugboard_pairs[21] = "AVBSCGDLFUHZINKMOWRX\0";

    EnigmaParam param;
    char from[175] = "EDPUDNRGYSZRCXNUYTPOMRMBOFKTBZREZKMLXLVEFGUEYSIOZVEQMIKUBPMMYLKLTTDEISMDICAGYKUACTCDOMOHWXMUUIAUBSTSLRNBZSZWNRFXWFYSSXJZVIJHIDISHPRKLKAYUPADTXQSPINQMATLPIFSVKDASCTACDPBOPVHJK";
    char to[175];
    char to_expected[175] = "AUFKLXABTEILUNGXVONXKURTINOWAXKURTINOWAXNORDWESTLXSEBEZXSEBEZXUAFFLIEGERSTRASZERIQTUNGXDUBROWKIXDUBROWKIXOPOTSCHKAXOPOTSCHKAXUMXEINSAQTDREINULLXUHRANGETRETENXANGRIFFXINFXRGTX";

    if (setparam_ENIGMA_I(&param, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testsample4() {
    // U-264 (Kapitänleutnant Hartwig Looks), 1942: http://wiki.franklinheath.co.uk/index.php/Enigma/Sample_Messages
    int reflector = 0; // Thin B
    int wheel_order[4] = {1-1, 2-1, 4-1, 1-1}; // beta, 2, 4, 1
    char ring_setting[4] = {1 + 'A' - 1, 1 + 'A' - 1, 1 + 'A' - 1, 22 + 'A' - 1}; // AAAV
    char wheel_pos[4] = {'V', 'J', 'N', 'A'};
    char plugboard_pairs[21] = "ATBLDFGJHMNWOPQYRZVX\0";

    EnigmaParam param;
    char from[233] = "NCZWVUSXPNYMINHZXMQXSFWXWLKJAHSHNMCOCCAKUQPMKCSMHKSEINJUSBLKIOSXCKUBHMLLXCSJUSRRDVKOHULXWCCBGVLIYXEOAHXRHKKFVDREWEZLXOBAFGYUJQUKGRTVUKAMEURBVEKSUHHVOYHABCJWMAKLFKLMYFVNRIZRVVRTKOFDANJMOLBGFFLEOPRGTFLVRHOWOPBEKVWMUQFMPWPARMFHAGKXIIBG\0";
    char to[233];
    char to_expected[233] = "VONVONJLOOKSJHFFTTTEINSEINSDREIZWOYYQNNSNEUNINHALTXXBEIANGRIFFUNTERWASSERGEDRUECKTYWABOSXLETZTERGEGNERSTANDNULACHTDREINULUHRMARQUANTONJOTANEUNACHTSEYHSDREIYZWOZWONULGRADYACHTSMYSTOSSENACHXEKNSVIERMBFAELLTYNNNNNNOOOVIERYSICHTEINSNULL\0";

    if (setparam_ENIGMA_M4(&param, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testsample5() {
    // Scharnhorst (Konteradmiral Erich Bey), 1943: http://wiki.franklinheath.co.uk/index.php/Enigma/Sample_Messages
    int reflector = 0; // B
    int wheel_order[3] = {3-1, 6-1, 8-1};
    char ring_setting[3] = {1 + 'A' - 1, 8 + 'A' - 1, 13 + 'A' - 1}; // AHM
    char wheel_pos[3] = {'U', 'Z', 'V'};
    char plugboard_pairs[21] = "ANEZHKIJLRMQOTPVSWUX\0";

    EnigmaParam param;
    char from[81] = "YKAENZAPMSCHZBFOCUVMRMDPYCOFHADZIZMEFXTHFLOLPZLFGGBOTGOXGRETDWTJIQHLMXVJWKZUASTR\0";
    char to[81];
    char to_expected[81] = "STEUEREJTANAFJORDJANSTANDORTQUAAACCCVIERNEUNNEUNZWOFAHRTZWONULSMXXSCHARNHORSTHCO\0";

    if (setparam_ENIGMA_M3(&param, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testsample6() {
    // Enigma Tripitz, 1944: http://wiki.franklinheath.co.uk/index.php/Enigma/Sample_Messages
    int wheel_order[3] = {6-1, 4-1, 7-1};
    char ring_setting[4] = {6 + 'A' - 1, 17 + 'A' - 1, 3 + 'A' - 1, 20 + 'A' - 1}; // 
    char wheel_pos[4] = {'F', 'Q', 'D', 'C'};

    EnigmaParam param;
    char from[5][26] = {"IRCYPXNVSFERKMKMNJZZZTDBF", "GMFBOJGADLKJSVGJKSGBJQFKU", "FXWVSMWGKOCPKMQKFDDRMRDSQ", "OAOIUGAIRMZZCBQMEFMGZVAOQ", "QWJXNJENOFDBHVK\0"};
    char to[5][26];
    char to_expected[5][26] = {"MOEGLICHERWEISEAUFNAHMEAU", "FTREFFPUNKTNURDURCHZWOZER", "STOERERXMITSPYETEREMHERAN", "SCHLIESSENVONZWOTORPEDOBO", "OTENRECHNENQMFW\0"};

    unsigned int blk;

    if (setparam_ENIGMA_T(&param, wheel_order, ring_setting, wheel_pos) != 0)
        return -1;

    for (blk=0; blk < 5; blk++) {
        enigmaDecrypt_with_inplace_param(&param, from[blk], to[blk]);
        // increment reflector
        param.wheelpos[3].wheelpos = ((param.wheelpos[3].wheelpos - 'A' + 1) % 26) + 'A';
    }
 
    unsigned int i;

    for (blk=0; blk < 5; blk++) {
        if (strlen(from[blk]) != strlen(to[blk]))
            return -1;
        
        for (i=0; i < strlen(to[blk]); i++) {
            if (to[blk][i] != to_expected[blk][i])
                return -1;
        }
    }

    return 0;
}

int testupdoublematchturnover() {
    // check normal procedure for matching turnovers to lefthand 2 rotors (for finding bugs about indicator increment)
    // to_expected is obtained from: https://dencode.com/en/cipher/enigma
    int reflector = 0; // B
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'X', 'Y', 'Z'};
    char wheel_pos[3];
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    wheel_pos[0] = TurnoverSet[TURNOVER_I].turnover[0]; // 'Q'
    wheel_pos[1] = TurnoverSet[TURNOVER_II].turnover[0]; // 'E'
    wheel_pos[2] = 'A';

    EnigmaParam param;
    char from[79] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    char to[79];
    char to_expected[79] = "RPZIVWCOYHAEOWUFPKIIXDIQKRHPLPVENWRNBMJXAWFVIWRRJRFGTJSYNUPCDTGCTJLIJAYSGXRDTN\0";

    if (setparam_ENIGMA_M3(&param, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testtriplematchturnover() {
    // check normal procedure for matching turnoveres to lefthand 3 rotors (for finding bugs about indicator increment)
    // to_expected is obtained from: https://dencode.com/en/cipher/enigma
    int reflector = 0; // B
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'X', 'Y', 'Z'};
    char wheel_pos[3];
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    wheel_pos[0] = TurnoverSet[TURNOVER_I].turnover[0]; // 'Q'
    wheel_pos[1] = TurnoverSet[TURNOVER_II].turnover[0]; // 'E'
    wheel_pos[2] = TurnoverSet[TURNOVER_III].turnover[0]; // 'V'

    EnigmaParam param;
    char from[79] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    char to[79];
    char to_expected[79] = "LORHRQLIDWQRYGPVFBAAOIIAVMRZSLQMHABZAKJWKRKQEMJTNPJFWCUJSUPQQQHMTLSBSGFIRRVZEN\0";

    if (setparam_ENIGMA_M3(&param, reflector, wheel_order, ring_setting, wheel_pos, (char*)plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testDK() {
    // to_expected is obtained from: https://dencode.com/en/cipher/enigma
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[4] = {'Z', 'Y', 'X', 'W'};
    char wheel_pos[4] = {'A', 'B', 'C', 'D'};

    EnigmaParam param;
    char from[79] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    char to[79];
    char to_expected[79] = "MHLOJUPRXEFZPUTOEMJWTUOPTHJJDXOYUPRYLJBLMGGCUNLKCYGVVMTIVBDXFLXGREBLDKOOCNGWVY\0";

    if (setparam_ENIGMA_D_K(&param, wheel_order, ring_setting, wheel_pos) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testNorway() {
    // to_expected is obtained from: https://dencode.com/en/cipher/enigma
    int wheel_order[3] = {1-1, 2-1, 4-1};
    char ring_setting[3] = {'Z', 'Y', 'X'};
    char wheel_pos[3] = {'A', 'B', 'C'};
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    EnigmaParam param;
    char from[79] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    char to[79];
    char to_expected[79] = "DQLNYQAITAZCNYRMBVMFRJEYJJYAZYMZXGDDJOXWDFKAAKMDHFLGOQJOHUOXNUSPERALZCPKYEVZEY\0";

    if (setparam_ENIGMA_NORWAY(&param, wheel_order, ring_setting, wheel_pos, plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int testSonder() {
    // to_expected is obtained from: https://dencode.com/en/cipher/enigma
    int wheel_order[3] = {1-1, 2-1, 3-1};
    char ring_setting[3] = {'Z', 'Y', 'X'};
    char wheel_pos[3] = {'A', 'B', 'C'};
    char plugboard_pairs[21] = "BQCRDIEJKWMTOSPXUZGH\0";

    EnigmaParam param;
    char from[79] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    char to[79];
    char to_expected[79] = "LVOMMLCYUNQRDCFIAPALGNZKWVYLKPIBFMLHAQAQGLDSTGRJVCJYQZVMJIMQEWCJFTVONCGXSSYYXD\0";

    if (setparam_ENIGMA_SONDER(&param, wheel_order, ring_setting, wheel_pos, plugboard_pairs) != 0)
        return -1;

    enigmaDecrypt(&param, from, to);

    unsigned int i;

    if (strlen(from) != strlen(to))
        return -1;

    for (i=0; i < strlen(to); i++) {
        if (to[i] != to_expected[i])
            return -1;
    }

    return 0;
}

int main () {
    unsigned int i;

    typedef struct testcase__ {
        int (*func)();
        char testname[32];
    } TestCase;

    TestCase testcases[] = {
        {testsample1, "testsample1\0"},
        {testsample2, "testsample2\0"},
        {testsample3, "testsample3\0"},
        {testsample4, "testsample4\0"},
        {testsample5, "testsample5\0"},
        {testsample6, "testsample6\0"},
        {testupdoublematchturnover, "test_up_double_match_turnover\0"},
        {testtriplematchturnover, "test_triple_match_turnover\0"},
        {testSwissK, "testSwissK\0"},
        {testDK, "testDK\0"},
        {testNorway, "testNorway\0"},
        {testSonder, "testSonder\0"},
    };

    static const unsigned int testcasenum = 12;

    for (i=0; i < testcasenum; i++) {
        if (testcases[i].func() == 0) {
            printf("%s passed.\n", testcases[i].testname);
        } else {
            printf("%s failed.\n", testcases[i].testname);
        }
    }

    return 0;
}
