#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "enigma.h"
#include "enigma_attack.h"

static const int PLUGBOARD_NOTFOUND_BY_BOMBE = -128;

int isVaridCrib(
    char ciphertext[],
    char crib[],
    unsigned int crib_idx_at_ciphertext
) {
    unsigned int criblen;
    unsigned int ciphertextlen;
    unsigned int i;

    criblen = strlen(crib);
    ciphertextlen = strlen(ciphertext);

    if ((criblen < 2) || (criblen > (ciphertextlen - crib_idx_at_ciphertext)))
        return 0;

    // Enigma encrypt/decrypt each letter to different letter
    for (i=0; i < criblen; i++) {
        if (ciphertext[crib_idx_at_ciphertext + i] == crib[i])
            return 0;
    }

    return 1;
}

typedef struct __connect_element {
    char ch;
    // flag:
    //     0: connect from ciphertext after plugboard to plaintext
    //     1: reversed way
    int flag;
    unsigned int pos;
} connect_element_struct;

typedef struct __connect_struct {
    connect_element_struct node[26];
    unsigned int node_len;
} connect_struct;

typedef union __ring_queue_element {
    char ch;
} ring_queue_element;

void copyRingQueueElement(ring_queue_element* out, ring_queue_element* in) {
    out->ch = in->ch;
}

typedef struct __ring_queue {
    ring_queue_element element[26];
    unsigned int st;
    unsigned int ed;
} ring_queue;

void init_ring_queue(ring_queue* que) {
    que->st = 0;
    que->ed = 0;
}

void put_ring_queue(ring_queue* que, ring_queue_element element) {
    copyRingQueueElement(&(que->element[(que->ed)++]), &element);
    if (que->ed >= 26)
        que->ed = 0;
}

void get_ring_queue(ring_queue* que, ring_queue_element* element) {
    copyRingQueueElement(element, &(que->element[(que->st)++]));
    if (que->st >= 26)
        que->st = 0;
}

int is_empty_ring_queue(ring_queue* que) {
    return que->ed == que->st;
}

typedef struct __connected_graph_info {
    unsigned int idx;
    unsigned int itemnum;
    unsigned int freqmax;
    unsigned int freqch[26];
    unsigned int loopnum;
} connected_graph_info;

int cmp_connected_graph_info(const void* a, const void* b) {
    int retval;
    retval =
        (
            ((connected_graph_info*)b) -> itemnum -
                ((connected_graph_info*)a) -> itemnum) * (26 * 26) +
        (
            ((connected_graph_info*)b) -> loopnum -
                ((connected_graph_info*)a) -> loopnum) * 26 +
        (
            ((connected_graph_info*)b) -> freqmax -
                ((connected_graph_info*)a) -> freqmax);
    return retval;
}

int bombeAttackCoreRecursiveCallInternal(
    char firsttargetch,
    char* curplugboard,
    unsigned int* curplugboardsetflag,
    connect_struct* char_connect_ary,
    char** encrypt_table_no_plugboard,
    char** decrypt_table_no_plugboard
) {
    int plugboardfoundflag;
    ring_queue que;
    ring_queue_element get_que_element, put_que_element;
    connect_element_struct connect_element_val;
    unsigned int i, j;

    plugboardfoundflag = 1;
    init_ring_queue(&que);
    put_que_element.ch = firsttargetch;
    put_ring_queue(&que, put_que_element);

    while (is_empty_ring_queue(&que) != 1) {
        get_ring_queue(&que, &get_que_element);
        for (i=0;
            i < char_connect_ary[get_que_element.ch - 'A'].node_len;
            i++
        ) {
            connect_element_val = char_connect_ary[
                    get_que_element.ch - 'A'
                ].node[i];
            if (connect_element_val.flag == 0) {
                j = decrypt_table_no_plugboard[connect_element_val.pos][
                        curplugboard[get_que_element.ch - 'A'] - 'A'
                    ] - 'A';
            } else {
                j = encrypt_table_no_plugboard[connect_element_val.pos][
                        curplugboard[get_que_element.ch - 'A'] - 'A'
                    ] - 'A';
            }
            if (curplugboardsetflag[j] == 1) {
                if (curplugboard[j] != connect_element_val.ch) {
                    plugboardfoundflag = 0;
                    break;
                }
            } else {
                curplugboard[j] = connect_element_val.ch;
                curplugboard[connect_element_val.ch - 'A'] = 'A' + j;
                curplugboardsetflag[j] = 1;
                curplugboardsetflag[connect_element_val.ch - 'A'] = 1;

                put_que_element.ch = connect_element_val.ch;
                put_ring_queue(&que, put_que_element);
            }
        }
        if (plugboardfoundflag == 0)
            break;
    }
    return plugboardfoundflag;
}

int bombeAttackCoreRecursiveCall(
    char* outputplugboard,
    const char prevplugboard[26],
    const unsigned int prevplugboardsetflag[26],
    unsigned int cnt,
    unsigned int connected_graph_count,
    connect_struct* char_connect_ary,
    int* connected_graph_count_comp_table,
    connected_graph_info* connected_graph_info_ary,
    char** encrypt_table_no_plugboard,
    char** decrypt_table_no_plugboard
) {
    char curplugboard[26], recursiveoutputplugboard[26];
    unsigned int curplugboardsetflag[26];
    unsigned int idx;
    unsigned int i, j, k;
    unsigned int curj;

    if (cnt == connected_graph_count) {
        for (i=0; i < 26; i++)
            outputplugboard[i] = prevplugboard[i];
        return 0;
    }

    // recursive proc
    idx = connected_graph_info_ary[cnt].idx;

    // search already plugged position
    curj = 26;
    for (j=0; j < 26; j++) {
        if (((unsigned int)connected_graph_count_comp_table[j] == idx)) {
            curj = j;
            if (prevplugboardsetflag[j] == 1)
                break;
        }
    }

    // invalid connected_graph_count_comp_table or cnt
    if (curj == 26)
        return -1;

    // already plug set found
    if (j < 26) {
        for (k=0; k < 26; k++) {
            curplugboard[k] = prevplugboard[k];
            curplugboardsetflag[k] = prevplugboardsetflag[k];
        }

        if (bombeAttackCoreRecursiveCallInternal(
            'A'+ j, curplugboard, curplugboardsetflag, char_connect_ary,
            encrypt_table_no_plugboard, decrypt_table_no_plugboard) == 0
        ) {
            return PLUGBOARD_NOTFOUND_BY_BOMBE;
        }

        if (bombeAttackCoreRecursiveCall(
            (char*)recursiveoutputplugboard, curplugboard, curplugboardsetflag,
            cnt + 1, connected_graph_count, char_connect_ary,
            connected_graph_count_comp_table,
            connected_graph_info_ary,
            encrypt_table_no_plugboard, decrypt_table_no_plugboard) == 0
        ) {
            for (i=0; i < 26; i++)
                outputplugboard[i] = recursiveoutputplugboard[i];
            return 0;
        }
    }

    for (i=0; i < 26; i++) {
        if (prevplugboardsetflag[i] == 1)
            continue;

        for (k=0; k < 26; k++) {
            curplugboard[k] = prevplugboard[k];
            curplugboardsetflag[k] = prevplugboardsetflag[k];
        }

        // NOTE: it is possible i == j (not attached plug)
        curplugboard[curj] = 'A' + i;
        curplugboard[i] = 'A' + curj;
        curplugboardsetflag[i] = 1;
        curplugboardsetflag[curj] = 1;

        if (bombeAttackCoreRecursiveCallInternal(
            'A' + curj, curplugboard, curplugboardsetflag, char_connect_ary,
            encrypt_table_no_plugboard, decrypt_table_no_plugboard) == 1
        ) {
            if (bombeAttackCoreRecursiveCall(
                (char*)outputplugboard, curplugboard, curplugboardsetflag,
                cnt + 1, connected_graph_count, char_connect_ary,
                connected_graph_count_comp_table,
                connected_graph_info_ary,
                encrypt_table_no_plugboard, decrypt_table_no_plugboard) == 0
            ) {
                return 0;
            }
        }
    }

    // all candidate exhausted
    return PLUGBOARD_NOTFOUND_BY_BOMBE;
}

int create_encrypt_decrypt_noplugboard_table(
    char*** encrypt_table_no_plugboard, char*** decrypt_table_no_plugboard,
    EnigmaParam* origparam,
    unsigned int criblen, unsigned int crib_idx_at_ciphertext
) {
    EnigmaParam curparam;
    char* pseudociphertext;
    char* pseudoplaintext;

    unsigned int i, j;

    copyEnigmaParam(&curparam, origparam);
    initplugboard(&curparam);

    pseudociphertext = (char*)calloc(
        crib_idx_at_ciphertext + criblen + 1, sizeof(char));
    pseudoplaintext = (char*)calloc(
        crib_idx_at_ciphertext + criblen + 1, sizeof(char));
    *decrypt_table_no_plugboard = (char**)calloc(criblen, sizeof(char*));
    *encrypt_table_no_plugboard = (char**)calloc(criblen, sizeof(char*));

    if (
        (pseudociphertext == NULL) ||
        (pseudoplaintext == NULL) ||
        (*decrypt_table_no_plugboard == NULL) ||
        (*encrypt_table_no_plugboard == NULL)
    ) {
        if (pseudociphertext != NULL)
            free(pseudociphertext);
        if (pseudoplaintext != NULL)
            free(pseudoplaintext);
        if (*decrypt_table_no_plugboard != NULL)
            free(*decrypt_table_no_plugboard);
        if (*encrypt_table_no_plugboard != NULL)
            free(*encrypt_table_no_plugboard);
        return -1;
    }

    for (i=0; i < criblen; i++) {
        (*decrypt_table_no_plugboard)[i] = (char*)malloc(26 * sizeof(char));
        (*encrypt_table_no_plugboard)[i] = (char*)malloc(26 * sizeof(char));
        if ((*decrypt_table_no_plugboard)[i] == NULL)
            return -1;
        if ((*encrypt_table_no_plugboard)[i] == NULL)
            return -1;
    }

    for (i=0; i < 26; i++) {
        for (j=0; j < crib_idx_at_ciphertext; j++)
            pseudociphertext[j] = 'A';  // dummy

        for (j=0; j < criblen; j++)
            pseudociphertext[crib_idx_at_ciphertext + j] = 'A' + i;
        pseudociphertext[crib_idx_at_ciphertext + j] = '\0';

        enigmaDecrypt(&curparam, pseudociphertext, pseudoplaintext);

        for (j=0; j < criblen; j++) {
            (*decrypt_table_no_plugboard)[j][i] =
                pseudoplaintext[crib_idx_at_ciphertext + j];
            // in fact, encrypt_table and decrypt_table is same
            // cause enigma structure.
            // (keep table for confirmation of this fact)
            (*encrypt_table_no_plugboard)[j][
                    (*decrypt_table_no_plugboard)[j][i] - 'A'
                ] = 'A' + i;
        }
    }

    if (pseudoplaintext != NULL) {
        free(pseudoplaintext);
        pseudoplaintext = NULL;
    }
    if (pseudociphertext != NULL) {
        free(pseudociphertext);
        pseudociphertext = NULL;
    }

    return 0;
}

int bombeAttackEnigmaPlugboard(
    EnigmaParam* outputparam,
    EnigmaParam* origparam,
    char ciphertext[],
    char crib[],
    unsigned int crib_idx_at_ciphertext
) {
    unsigned int criblen;

    char** decrypt_table_no_plugboard;
    char** encrypt_table_no_plugboard;

    connect_struct* char_connect_ary;
    char ch_c, ch_p;
    connect_element_struct* con_ele_ptr;

    unsigned int connected_graph_count;
    int connected_graph_count_comp_table[26];
    ring_queue que;
    ring_queue_element que_element;
    char que_element_ch;
    connected_graph_info* connected_graph_info_ary;

    char prevplugboard[26];
    char outputplugboard[26];
    unsigned int prevplugboardsetflag[26];

    int ret;

    unsigned int i, j, cnt;
    int ii;

    if (isVaridCrib(ciphertext, crib, crib_idx_at_ciphertext) == 0)
        return PLUGBOARD_NOTFOUND_BY_BOMBE;

    criblen = strlen(crib);

    if (create_encrypt_decrypt_noplugboard_table(
        &encrypt_table_no_plugboard, &decrypt_table_no_plugboard,
        origparam, criblen, crib_idx_at_ciphertext) != 0
    ) {
        return -1;
    }

    // create bombe/Turing graph
    char_connect_ary = (connect_struct*)calloc(26, sizeof(connect_struct));
    for (i=0; i < 26; i++)
        char_connect_ary[i].node_len = 0;

    for (i=0; i < criblen; i++) {
        ch_c = ciphertext[crib_idx_at_ciphertext + i];
        ch_p = crib[i];

        con_ele_ptr =
            (connect_element_struct*)char_connect_ary[ch_c - 'A'].node +
            char_connect_ary[ch_c - 'A'].node_len;
        con_ele_ptr -> ch = ch_p;
        con_ele_ptr -> flag = 0;
        con_ele_ptr -> pos = i;
        char_connect_ary[ch_c - 'A'].node_len++;

        con_ele_ptr =
            (connect_element_struct*)char_connect_ary[ch_p - 'A'].node +
            char_connect_ary[ch_p - 'A'].node_len;
        con_ele_ptr -> ch = ch_c;
        con_ele_ptr -> flag = 1;
        con_ele_ptr -> pos = i;
        char_connect_ary[ch_p - 'A'].node_len++;
    }

    // grouping each connected subgraph
    for (i=0; i < 26; i++)
        connected_graph_count_comp_table[i] = -1;

    connected_graph_count = 0;
    while (1) {
        for (i=0; i < 26; i++) {
            if (connected_graph_count_comp_table[i] == -1)
                break;
        }

        if (i == 26)
            break;

        init_ring_queue(&que);
        que_element.ch = 'A' + i;
        put_ring_queue(&que, que_element);

        while (is_empty_ring_queue(&que) != 1) {
            get_ring_queue(&que, &que_element);

            que_element_ch = que_element.ch;
            if (connected_graph_count_comp_table[que_element_ch - 'A'] != -1)
                continue;

            connected_graph_count_comp_table[que_element_ch - 'A'] =
                connected_graph_count;
            for (
                i = 0;
                i < char_connect_ary[que_element_ch - 'A'].node_len;
                i++
            ) {
                que_element.ch =
                    char_connect_ary[que_element_ch - 'A'].node[i].ch;
                put_ring_queue(&que, que_element);
            }
        }
        connected_graph_count++;
    }

    // compute statics on each graph for sorting large good graph
    // (for determining plugboard efficiently)
    connected_graph_info_ary = (connected_graph_info*)malloc(
        connected_graph_count * sizeof(connected_graph_info));
    for (cnt=0; cnt < connected_graph_count; cnt++) {
        connected_graph_info_ary[cnt].idx = cnt;
        connected_graph_info_ary[cnt].itemnum = 0;
        for (j=0; j < 26; j++)
            connected_graph_info_ary[cnt].freqch[j] = 0;
        connected_graph_info_ary[cnt].loopnum = 0;
    }

    for (i=0; i < 26; i++) {
        for (j=0; j < char_connect_ary[i].node_len; j++)
            connected_graph_info_ary[
                    connected_graph_count_comp_table[i]
                ].freqch[char_connect_ary[i].node[j].ch - 'A']++;
        connected_graph_info_ary[connected_graph_count_comp_table[i]].itemnum++;
    }

    for (cnt=0; cnt < connected_graph_count; cnt++) {
        connected_graph_info_ary[cnt].freqmax =
            connected_graph_info_ary[cnt].freqch[0];
        for (j=1; j < 26; j++) {
            if (
                connected_graph_info_ary[cnt].freqch[j] >
                    connected_graph_info_ary[cnt].freqmax
            ) {
                connected_graph_info_ary[cnt].freqmax =
                    connected_graph_info_ary[cnt].freqch[j];
            }
        }
    }

    // TODO: implement loopnum computation
    //       (depth-first search, but it might be slow)
    qsort(
        (void*)connected_graph_info_ary,
        (size_t)connected_graph_count,
        sizeof(connected_graph_info),
        cmp_connected_graph_info);

    for (i=0; i < 26; i++) {
        prevplugboard[i] = 'A' + i;
        prevplugboardsetflag[i] = 0;
    }

    if (bombeAttackCoreRecursiveCall(
        (char*)outputplugboard, prevplugboard, prevplugboardsetflag, 0,
        connected_graph_count, char_connect_ary,
        (int*)connected_graph_count_comp_table,
        connected_graph_info_ary,
        encrypt_table_no_plugboard,
        decrypt_table_no_plugboard) != 0
    ) {
        ret = PLUGBOARD_NOTFOUND_BY_BOMBE;
    } else {
        copyEnigmaParam(outputparam, origparam);
        for (i=0; i < 26; i++)
            outputparam->plugboard.wheel[i] = outputplugboard[i];
        ret = 0;
    }

    // clean up

    if (connected_graph_info_ary != NULL)
        free(connected_graph_info_ary);

    if (char_connect_ary != NULL)
        free(char_connect_ary);

    for (ii=criblen - 1; ii >= 0; ii--) {
        if (encrypt_table_no_plugboard[ii] != NULL) {
            free(encrypt_table_no_plugboard[ii]);
            encrypt_table_no_plugboard[ii] = NULL;
        }

        if (decrypt_table_no_plugboard[ii] != NULL) {
            free(decrypt_table_no_plugboard[ii]);
            decrypt_table_no_plugboard[ii] = NULL;
        }
    }

    if (encrypt_table_no_plugboard != NULL) {
        free(encrypt_table_no_plugboard);
        encrypt_table_no_plugboard = NULL;
    }

    if (decrypt_table_no_plugboard != NULL) {
        free(decrypt_table_no_plugboard);
        decrypt_table_no_plugboard = NULL;
    }

    return ret;
}
