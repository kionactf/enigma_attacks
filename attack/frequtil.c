#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <math.h>

#include "frequtil.h"

double* monogramtable;
double* bigramtable;
double* trigramtable;
double* quadgramtable;

double* monogramlogtable;
double* bigramlogtable;
double* trigramlogtable;
double* quadgramlogtable;

int readFileKeyValueToArray(char* filename, unsigned int (*keytoidx)(char*), unsigned int* valtotal, double** ary, unsigned int arynum) {
    FILE* fp;
    char line[1024];
    char key[1025];
    unsigned int table_idx;
    char* valptr;
    double val;
    unsigned int i;

    if ((fp = fopen(filename, "r")) == NULL) return -1;

    *ary = (double*)calloc(arynum, sizeof(double));
    if (*ary == NULL) {
        fclose(fp);
        return -1;
    }

    *valtotal = 0;
    while (fgets(line, 1024, fp) != NULL) {
        for (i=0; i < 1024; i++) {
            if ((line[i] == '\r') || (line[i] == '\n'))
                break;
            if ((line[i] == '\t') || (line[i] == ' ') || (line[i] == ','))
                break;
            if ((line[i] >= 'a') && (line[i] <= 'z')) {
                key[i] = toupper(line[i]);
                continue;
            }
            if ((line[i] >= 'A') && (line[i] <= 'Z')) {
                key[i] = line[i];
                continue;
            }
            break;
        }
        key[i++] = '\0';
        table_idx = keytoidx(key);

        for (; i < 1024; i++) {
            if ((line[i] == '\r') || (line[i] == '\n'))
                break;
            if ((line[i] != '\t') && (line[i] != ' ') && (line[i] != ','))
                break;
        }

        valptr = line + i;
        val = atof(valptr);
        if (val < 0) return -1;
        (*ary)[table_idx] = val;
        
        *valtotal += val;
    }

    fclose(fp);

    return 0;
}

int createfreqlogtable(double** plainfreqtable, double** logtable, unsigned int freqsum, unsigned int tablenum) {
    unsigned int i;

    *logtable = (double*)malloc(tablenum * sizeof(double));
    if ((*logtable) == NULL)
        return -1;

    for (i=0; i < tablenum; i++) {
        (*plainfreqtable)[i] = (*plainfreqtable)[i] / (double)freqsum;
        (*logtable)[i] = log((double)1.0 + (*plainfreqtable)[i]);
    }

    return 0;
}

int finalizeFreq() {
    if (monogramlogtable != NULL) {
        free(monogramlogtable);
        monogramlogtable = NULL;
    }
    if (monogramtable != NULL) {
        free(monogramtable);
        monogramtable = NULL;
    }

    if (bigramlogtable != NULL) {
        free(bigramlogtable);
        bigramlogtable = NULL;
    }
    if (bigramtable != NULL) {
        free(bigramtable);
        bigramtable = NULL;
    }

    if (trigramlogtable != NULL) {
        free(trigramlogtable);
        trigramlogtable = NULL;
    }
    if (trigramtable != NULL) {
        free(trigramtable);
        trigramtable = NULL;
    }

    if (quadgramlogtable != NULL) {
        free(quadgramlogtable);
        quadgramlogtable = NULL;
    }
    if (quadgramtable != NULL) {
        free(quadgramtable);
        quadgramtable = NULL;
    }

    return 0;
}


/** English **/

unsigned int keytomonogramidx(char* key) {
    return (unsigned int)(key[0] - 'A');
}

int initializeEnglishMonogram() {
    unsigned int freqsum;

    char filename[1024] = "freqdb/english_monograms.txt\0";

    if (readFileKeyValueToArray(filename, keytomonogramidx, &freqsum, &monogramtable, 26) != 0)
        return -1;
    if (createfreqlogtable(&monogramtable, &monogramlogtable, freqsum, 26) != 0)
        return -1;

    return 0;
}

unsigned int keytobigramidx(char* key) {
    return (unsigned int)((key[0] - 'A') * 26 + (key[1] - 'A'));
}

int initializeEnglishBigram() {
    unsigned int freqsum;

    char filename[1024] = "freqdb/english_bigrams.txt\0";

    if (readFileKeyValueToArray(filename, keytobigramidx, &freqsum, &bigramtable, 26 * 26) != 0)
        return -1;
    if (createfreqlogtable(&bigramtable, &bigramlogtable, freqsum, 26 * 26) != 0)
        return -1;

    return 0;
}

unsigned int keytotrigramidx(char* key) {
    return (unsigned int)((key[0] - 'A') * (26 * 26) + (key[1] - 'A') * 26 + (key[2] - 'A'));
}

int initializeEnglishTrigram() {
    unsigned int freqsum;

    char filename[1024] = "freqdb/english_trigrams.txt\0";

    if (readFileKeyValueToArray(filename, keytotrigramidx, &freqsum, &trigramtable, 26 * 26 * 26) != 0)
        return -1;
    if (createfreqlogtable(&trigramtable, &trigramlogtable, freqsum, 26 * 26 * 26) != 0)
        return -1;

    return 0;
}

unsigned int keytoquadgramidx(char* key) {
    return (unsigned int)((key[0] - 'A') * (26 * 26 * 26) + (key[1] - 'A') * (26 * 26) + (key[2] - 'A') * 26 + (key[3] - 'A'));
}

int initializeEnglishQuadgram() {
    unsigned int freqsum;

    char filename[1024] = "freqdb/english_quadgrams.txt\0";

    if (readFileKeyValueToArray(filename, keytoquadgramidx, &freqsum, &quadgramtable, 26 * 26 * 26 * 26) != 0)
        return -1;
    if (createfreqlogtable(&quadgramtable, &quadgramlogtable, freqsum, 26 * 26 * 26 * 26) != 0)
        return -1;

    return 0;
}

int initializeEnglishFreq() {
    if (
        (initializeEnglishMonogram() != 0) || 
        (initializeEnglishBigram() != 0) || 
        (initializeEnglishTrigram() != 0) || 
        (initializeEnglishQuadgram() != 0)
    )
        return -1;
    
    return 0;
}

int finalizeEnglishFreq() {
    return finalizeFreq();
}



/** German special **/


int initializeGermanSpecialBigram() {
    unsigned int freqsum;

    char filename[1024] = "freqdb/german_special_bigrams.txt\0";

    if (readFileKeyValueToArray(filename, keytobigramidx, &freqsum, &bigramtable, 26 * 26) != 0)
        return -1;
    if (createfreqlogtable(&bigramtable, &bigramlogtable, freqsum, 26 * 26) != 0)
        return -1;

    return 0;
}

int initializeGermanSpecialTrigram() {
    unsigned int freqsum;

    char filename[1024] = "freqdb/german_special_trigrams.txt\0";

    if (readFileKeyValueToArray(filename, keytotrigramidx, &freqsum, &trigramtable, 26 * 26 * 26) != 0)
        return -1;
    if (createfreqlogtable(&trigramtable, &trigramlogtable, freqsum, 26 * 26 * 26) != 0)
        return -1;

    return 0;
}

int initializeGermanSpecialMonogram_from_Bigramtable() {
    unsigned int i;

    if (bigramtable == NULL)
        return -1;

    monogramtable = (double*)calloc(26, sizeof(double));
    if (monogramtable == NULL)
        return -1;

    for (i=0; i < 26; i++)
        monogramtable[i] = (double)0.0;

    for (i=0; i < 26 * 26; i++) {
        monogramtable[i % 26] += bigramtable[i];
        monogramtable[i / 26] += bigramtable[i];
    }

    for (i=0; i < 26; i++)
        monogramtable[i] /= 2;

    return 0;
}

int initializeGermanSpecialFreq() {
    if ((initializeGermanSpecialBigram() != 0) || (initializeGermanSpecialTrigram() != 0))
        return -1;
    if (initializeGermanSpecialMonogram_from_Bigramtable() != 0)
        return -1;
    // not generate quadgramtable

    return 0;
}

int finalizeGermanSpecialFreq() {
    return finalizeFreq();
}


/** general score computation **/

double IOCScore(char* text) {
    // calculate Index of Coincidence (neglecting multipling c(the number of letter=26))

    unsigned int i;
    unsigned int counttable[26];
    unsigned int n;
    double ioc;

    for (i=0; i < 26; i++) counttable[i] = 0;

    n = strlen(text);

    // construct count table
    for (i=0; i < n; i++) {
        if ((text[i] >= 'A') && (text[i] <= 'Z'))
            counttable[text[i] - 'A'] += 1;
    }

    ioc = (double)0.0;
    for (i=0; i < 26; i++)
        ioc += ((double)counttable[i]) * ((double)(counttable[i]-1));

    ioc = ioc / (n * (n - 1));

    return ioc;
}

double bigramIOCScore(char* text) {
    unsigned int i;
    unsigned int counttable[26*26];
    unsigned int n;
    double ioc;
    unsigned int idx;

    for (i=0; i < 26 * 26; i++)
        counttable[i] = 0;

    n = strlen(text);

    // construct count table
    for (i=0; i < n-1; i++) {
        if (((text[i] >= 'A') && (text[i] <= 'Z')) && ((text[i+1] >= 'A') && (text[i+1] <= 'Z'))) {
            idx = (text[i] - 'A') * 26 + (text[i+1] - 'A');
            counttable[idx] += 1;
        }
    }

    ioc = (double)0.0;
    for (i=0; i < 26 * 26; i++)
        ioc += ((double)counttable[i]) * ((double)(counttable[i]-1));

    ioc = ioc / ((n - 1) * ((n - 1) - 1));

    return ioc;
}

double bigramScore(char* text) {
    unsigned int i;
    unsigned int n;
    unsigned int table_idx;
    double score;

    score = (double)0.0;

    n = strlen(text);

    for (i=0; i < n - 1; i++) {
        if (((text[i] >= 'A') && (text[i] <= 'Z')) && ((text[i+1] >= 'A') && (text[i+1] <= 'Z'))) {
            table_idx = (text[i] - 'A') * 26 + (text[i+1] - 'A');
            score += bigramlogtable[table_idx];
        }
    }

    return score;
}

double trigramScore(char* text) {
    unsigned int i;
    unsigned int n;
    unsigned int table_idx;
    double score;

    score = (double)0.0;

    n = strlen(text);

    for (i=0; i < n - 2; i++) {
        if (((text[i] >= 'A') && (text[i] <= 'Z')) && ((text[i+1] >= 'A') && (text[i+1] <= 'Z')) && ((text[i+2] >= 'A') && (text[i+2] <= 'Z'))) {
            table_idx = (text[i] - 'A') * (26 * 26) + (text[i+1] - 'A') * 26 + (text[i+2] - 'A');
            score += trigramlogtable[table_idx];
        }
    }

    return score;
}

double quadgramScore(char* text) {
    unsigned int i;
    unsigned int n;
    unsigned int table_idx;
    double score;

    score = (double)0.0;

    n = strlen(text);

    for (i=0; i < n - 3; i++) {
        if (((text[i] >= 'A') && (text[i] <= 'Z')) && ((text[i+1] >= 'A') && (text[i+1] <= 'Z')) && ((text[i+2] >= 'A') && (text[i+2] <= 'Z')) && ((text[i+3] >= 'A') & (text[i+3] <= 'Z'))) {
            table_idx = (text[i] - 'A') * (26 * 26 * 26) + (text[i+1] - 'A') * (26 * 26) + (text[i+2] - 'A') * 26 + (text[i+3] - 'A');
            score += quadgramlogtable[table_idx];
        }
    }

    return score;
}

double sinkovScore(char* text) {
    unsigned int i;
    unsigned int counttable[26];
    unsigned int n;
    double score;

    for (i=0; i < 26; i++)
        counttable[i] = 0;

    n = strlen(text);

    for (i=0; i < n; i++) {
        if ((text[i] >= 'A') && (text[i] <= 'Z'))
            counttable[text[i] - 'A'] += 1;
    }

    score = (double)0.0;
    for (i=0; i < 26; i++)
        score += monogramtable[i] * (double)counttable[i];

    score /= n;

    return score;
}

double sinkovbigramScore(char* text) {
    unsigned int i;
    unsigned int counttable[26*26];
    unsigned int n;
    double score;
    unsigned int idx;

    for (i=0; i < 26*26; i++)
        counttable[i] = 0;

    n = strlen(text);

    for (i=0; i < n-1; i++) {
        if (((text[i] >= 'A') && (text[i] <= 'Z')) && ((text[i+1] >= 'A') && (text[i+1] <= 'Z'))) {
            idx = (text[i] - 'A') * 26 + (text[i+1] - 'A');
            counttable[idx] += 1;
        }
    }

    score = (double)0.0;
    for (i=0; i < 26 * 26; i++)
        score += bigramtable[i] * (double)counttable[i];

    score /= (n - 1);

    return score;
}


/* freq ranking */
typedef struct __rankelement {
    unsigned int idx;
    double score;
} RankDict;

int cmpscore(const void* a, const void* b) {
    // for sorting with decreasing order
    return (int)(((((RankDict*)b)->score) - (((RankDict*)a)->score)) > 0);
}

int rankBasedScoreTable(unsigned int* rank, unsigned int maxrank, double* table, unsigned int tablenum) {
    unsigned int i;
    RankDict* rankdictary;

    if (rank == NULL)
        return -1;
    if (table == NULL)
        return -1;

    rankdictary = (RankDict*)calloc(tablenum, sizeof(RankDict));

    for (i=0; i < tablenum; i++) {
        rankdictary[i].idx = i;
        rankdictary[i].score = table[i];
    }

    qsort(rankdictary, tablenum, sizeof(RankDict), cmpscore);

    for (i=0; i < maxrank; i++)
        rank[i] = rankdictary[i].idx;

    if (rankdictary != NULL) {
        free(rankdictary);
        rankdictary = NULL;
    }

    return 0;
}
