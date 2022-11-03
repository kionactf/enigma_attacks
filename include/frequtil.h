#ifndef __FREQUTIL_H_
#define __FREQUTIL_H_

typedef struct freqfuncs__ {
    char language[2+1];
    int (*initialize)();
    int (*finalize)();
    double (*IOCScore)(char*);
    double (*bigramIOCScore)(char*);
    double (*bigramScore)(char*);
    double (*trigramScore)(char*);
    double (*quadgramScore)(char*);
    double (*sinkovScore)(char*);
    double (*sinkovbigramScore)(char*);
} Freqfuncs;

extern double* monogramtable;
extern double* bigramtable;
extern double* trigramtable;
extern double* quadgramtable;

extern double* monogramlogtable;
extern double* bigramlogtable;
extern double* trigramlogtable;
extern double* quadgramlogtable;

int initializeEnglishFreq();
int finalizeEnglishFreq();

int initializeGermanSpecialFreq();
int finalizeGermanSpecialFreq();

double IOCScore(char*);
double bigramIOCScore(char*);
double bigramScore(char*);
double trigramScore(char*);
double quadgramScore(char*);
double sinkovScore(char*);
double sinkovbigramScore(char*);

int rankBasedScoreTable(unsigned int*, unsigned int, double*, unsigned int);

static double nullScore(char* str) {
    return 0.0 * strlen(str);
}

static const Freqfuncs EnglishFreqfuncs = {
    {"en"},
    initializeEnglishFreq,
    finalizeEnglishFreq,
    IOCScore,
    bigramIOCScore,
    bigramScore,
    trigramScore,
    quadgramScore,
    sinkovScore,
    sinkovbigramScore,
};

static const Freqfuncs GermanSpecialFreqfuncs = {
    {"du"},
    initializeGermanSpecialFreq,
    finalizeGermanSpecialFreq,
    IOCScore,
    bigramIOCScore,
    bigramScore,
    trigramScore,
    nullScore,
    sinkovScore,
    sinkovbigramScore,
};

#endif /* __FREQUTIL_H_ */
