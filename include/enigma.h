#ifndef __ENIGMA_H_
#define __ENIGMA_H_

typedef struct wheel__{
    char wheel[26+1];
} Wheel;

typedef struct wheelpos__{
    char wheelpos;
} WheelPos;

typedef struct wheelring__{
    char wheelring;
} WheelRing;

//#define MAXTURNOVERNUM (2)
#define MAXTURNOVERNUM (5)

typedef struct turnover__{
    char turnover[MAXTURNOVERNUM+1];
} Turnover;

// stable parameters on initial setting
typedef struct param__{
    Wheel wheel[6]; // wheel(walzenlage): (entry wheel(ETW,Eintritswalze), rotor(walze), reflector(UKW,umkehrwalze)): entry, rotor-1, rotor-2, rotor-3, reflector (or thin-rotor, thin-reflector)
    WheelPos wheelpos[4]; // rotor-1, rotor-2, rotor-3, reflector
    WheelRing wheelring[4]; // rotor-1, rotor-2, rotor-3, reflector
    Wheel plugboard; // plugboard(steckerbrett)
    Turnover turnover[3]; // turnover: rotor-1, rotor-2, rotor-3
    int reflectorsetflag; // settable position and ring for reflector
    int thinflag; // settable thin reflector and thin rotor
} EnigmaParam;

// variable setting on encrypting/decrypting
typedef struct cursetting__ {
    int indicator[4];
    int prevturnoverflag[3];// turnover is for only rotor-1,2,3
} CurSetting;


// refer(for naming): https://www.cryptomuseum.com/crypto/enigma/wiring.htm (some wiring seems to be wrong)
typedef enum rotorenum__{
    ROTOR_I, ROTOR_II, ROTOR_III, ROTOR_IV, ROTOR_V, ROTOR_VI, ROTOR_VII, ROTOR_VIII,
    ROTOR_BETA, ROTOR_GAMMA,
    ROTOR_RAILWAY_I, ROTOR_RAILWAY_II, ROTOR_RAILWAY_III,
    ROTOR_SWISSK_I, ROTOR_SWISSK_II, ROTOR_SWISSK_III,
    ROTOR_D_K_I, ROTOR_D_K_II, ROTOR_D_K_III,
    ROTOR_NORWAY_I, ROTOR_NORWAY_II, ROTOR_NORWAY_III, ROTOR_NORWAY_IV, ROTOR_NORWAY_V,
    ROTOR_SONDER_I, ROTOR_SONDER_II, ROTOR_SONDER_III,
    ROTOR_T_I, ROTOR_T_II, ROTOR_T_III, ROTOR_T_IV, ROTOR_T_V, ROTOR_T_VI, ROTOR_T_VII, ROTOR_T_VIII,
} RotorEnum;

// refer: https://de.wikipedia.org/wiki/Enigma-Walzen
static const Wheel RotorSet[] = {
    {"EKMFLGDQVZNTOWYHXUSPAIBRCJ"},
    {"AJDKSIRUXBLHWTMCQGZNPYFVOE"},
    {"BDFHJLCPRTXVZNYEIWGAKMUSQO"},
    {"ESOVPZJAYQUIRHXLNFTGKDCMWB"},
    {"VZBRGITYUPSDNHLXAWMJQOFECK"},
    {"JPGVOUMFYQBENHZRDKASXLICTW"},
    {"NZJHGRCXMYSWBOUFAIVLPEKQDT"},
    {"FKQHTLXOCBJSPDZRAMEWNIUYGV"},

    {"LEYJVCNIXWPBQMDRTAKZGFUHOS"},
    {"FSOKANUERHMBTIYCWLQPZXVGJD"},

    {"JGDQOXUSCAMIFRVTPNEWKBLZYH"},
    {"NTZPSFBOKMWRCJDIVLAEYUXHGQ"},
    {"JVIUBHTCDYAKEQZPOSGXNRMWFL"},

    {"PEZUOHXSCVFMTBGLRINQJWAYDK"},
    {"ZOUESYDKFWPCIQXHMVBLGNJRAT"},
    {"EHRVXGAOBQUSIMZFLYNWKTPDJC"},

    {"LPGSZMHAEOQKVXRFYBUTNICJDW"},
    {"SLVGBTFXJQOHEWIRZYAMKPCNDU"},
    {"CJGDPSHKTURAWZXFMYNQOBVLIE"},

    {"WTOKASUYVRBXJHQCPZEFMDINLG"},
    {"GJLPUBSWEMCTQVHXAOFZDRKYNI"},
    {"JWFMHNBPUSDYTIXVZGRQLAOEKC"},
    {"FGZJMVXEPBWSHQTLIUDYKCNRAO"},
    {"HEJXQOTZBVFDASCILWPGYNMURK"},

    {"VEOSIRZUJDQCKGWYPNXAFLTHMB"},
    {"UEMOATQLSHPKCYFWJZBGVXINDR"}, // some pages says "...DNR", but it seems wrong
    {"TZHXMBSIPNURJFDKEQVCWGLAOY"},

    {"KPTYUELOCVGRFQDANJMBSWHZXI"},
    {"UPHZLWEQMTDJXCAKSOIGVBYFNR"},
    {"QUDLYRFEKONVZAXWHMGPJBSICT"},
    {"CIWTBKXNRESPFLYDAGVHQUOJZM"},
    {"UAXGISNJBVERDYLFZWTPCKOHMQ"},
    {"XFUZGALVHCNYSEWQTDMRBKPIOJ"},
    {"BJVFTXPLNAYOZIKWGDQERUCHSM"},
    {"YMTPNZHWKODAJXELUQVGCBISFR"},
};

typedef enum reflectorenum__ {
    REFLECTOR_A, REFLECTOR_B, REFLECTOR_C,
    REFLECTOR_B_THIN, REFLECTOR_C_THIN,
    UKW_RAILWAY,
    UKW_D_K,
    UKW_NORWAY,
    UKW_SONDER,
    UKW_T,
} ReflectorEnum;

static const Wheel ReflectorSet[] = {
    {"EJMZALYXVBWFCRQUONTSPIKHGD"},
    {"YRUHQSLDPXNGOKMIEBFZCWVJAT"},
    {"FVPJIAOYEDRZXWGCTKUQSBNMHL"},

    {"ENKQAUYWJICOPBLMDXZVFTHRGS"},
    {"RDOBJNTKVEHMLFCWZAXGYIPSUQ"},

    {"QYHOGNECVPUZTFDJAXWMKISRBL"},

    {"IMETCGFRAYSQBZXWLHKDVUPOJN"},

    {"MOWJYPUXNDSRAIBFVLKZGQCHET"},

    {"CIAGSNDRBYTPZFULVHEKOQXWJM"},

    {"GEKPBTAUMOCNILJDXZYFHWVQSR"},
};

static const int UKW_SWISSK = UKW_D_K;

typedef enum etwenum__{
    ETW,
    ETW_KEYBOARD,
    ETW_T,
} ETWEnum;

static const Wheel ETWSet[] = {
    {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    
    {"QWERTZUIOASDFGHJKPYXCVBNML"},

    {"KZROUQHYAIGBLWVSTDXFPNMCJE"},
};

static const int ETW_D_K = ETW_KEYBOARD;
static const int ETW_RAILWAY = ETW_KEYBOARD;
static const int ETW_SWISSK = ETW_KEYBOARD;

typedef enum turnoverenum__{
    TURNOVER_I, TURNOVER_II, TURNOVER_III, TURNOVER_IV, TURNOVER_V, TURNOVER_VI, TURNOVER_VII, TURNOVER_VIII,
    TURNOVER_D_K_I, TURNOVER_D_K_II, TURNOVER_D_K_III,
    TURNOVER_T_I, TURNOVER_T_II, TURNOVER_T_III, TURNOVER_T_IV, TURNOVER_T_V, TURNOVER_T_VI, TURNOVER_T_VII, TURNOVER_T_VIII,
} TurnoverEnum;

static const Turnover TurnoverSet[] = {
    {"QQQQQ"}, {"EEEEE"}, {"VVVVV"}, {"JJJJJ"}, {"ZZZZZ"}, {"ZMMMM"}, {"ZMMMM"}, {"ZMMMM"},
    {"YYYYY"}, {"EEEEE"}, {"NNNNN"},
    {"EKQWZ"}, {"FLRWZ"}, {"EKQWZ"}, {"FLRWZ"}, {"CFKRY"}, {"EIMQX"}, {"CFKRY"}, {"EIMQX"}
};

static const int TURNOVER_SWISSK_I = TURNOVER_D_K_I;
static const int TURNOVER_SWISSK_II = TURNOVER_D_K_II;
static const int TURNOVER_SWISSK_III = TURNOVER_D_K_III;

static const int TURNOVER_RAILWAY_I = TURNOVER_D_K_III; // reversed
static const int TURNOVER_RAILWAY_II = TURNOVER_D_K_II;
static const int TURNOVER_RAILWAY_III = TURNOVER_D_K_I;

static const int TURNOVER_NORWAY_I = TURNOVER_I;
static const int TURNOVER_NORWAY_II = TURNOVER_II;
static const int TURNOVER_NORWAY_III = TURNOVER_III;
static const int TURNOVER_NORWAY_IV = TURNOVER_IV;
static const int TURNOVER_NORWAY_V = TURNOVER_V;

static const int TURNOVER_SONDER_I = TURNOVER_I;
static const int TURNOVER_SONDER_II = TURNOVER_II;
static const int TURNOVER_SONDER_III = TURNOVER_III;


static const Wheel IDENTITY_WHEEL = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};


// parameter setting for each model
int setparam_ENIGMA_I(EnigmaParam*, int, int[3], char[3], char[3], char*);/* param, reflector, wheel_order, ring_setting, wheel_pos, plugboard_pairs */
int setparam_ENIGMA_M3(EnigmaParam*, int, int[3], char[3], char[3], char*);
int setparam_ENIGMA_M4(EnigmaParam*, int, int[4], char[4], char[4], char*);
int setparam_ENIGMA_RAILWAY(EnigmaParam*, int[3], char[4], char[4]); // reflector fixed, add reflector pos/ring setting, no plugboard
int setparam_ENIGMA_SWISSK(EnigmaParam*, int[3], char[4], char[4]); // reflector fixed, add reflector pos/ring setting, no plugboard
int setparam_ENIGMA_D_K(EnigmaParam*, int[3], char[4], char[4]); // reflector fixed, add reflector pos/ring setting, no plugboard
int setparam_ENIGMA_NORWAY(EnigmaParam*, int[3], char[3], char[3], char*); // reflector fixed
int setparam_ENIGMA_SONDER(EnigmaParam*, int[3], char[3], char[3], char*); // reflector fixed
int setparam_ENIGMA_T(EnigmaParam*, int[3], char[4], char[4]); // reflector fixed, add reflector pos/ring setting, no plugboard

// simulate Enigma on oneshot (not changing param after encryption)
int enigmaEncrypt(EnigmaParam*, char*, char*);/* param, from, to */
int enigmaDecrypt(EnigmaParam*, char*, char*);/* param, from, to */

// simulate Enigma with inplace (rotor setting is changed after encryption)
int enigmaEncrypt_with_inplace_param(EnigmaParam*, char*, char*);/* param, from, to */
int enigmaDecrypt_with_inplace_param(EnigmaParam*, char*, char*);/* param, from, to */

void printEnigmaParam(EnigmaParam*);
int copyEnigmaParam(EnigmaParam*, EnigmaParam*);/* to, from */


#endif /* __ENIGMA_H_ */
