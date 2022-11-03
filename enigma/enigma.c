#include <stdio.h>
#include <string.h>
#include "enigma.h"

/*** initial parameter setting for enigma ***/

int setplugboard_from_plugboardpairs(EnigmaParam* param, char* plugboard_pairs) {
    unsigned int i, j;

    for (i=0; i < strlen(plugboard_pairs); i++) {
        if ((plugboard_pairs[i] < 'A') || (plugboard_pairs[i] > 'Z'))
            return -1; // invalid plugboard_pairs
        
        for (j=i+1; j < strlen(plugboard_pairs); j++) {
            if (plugboard_pairs[i] == plugboard_pairs[j])
                return -1; // invalid plugboard_pairs
        }
    }

    for (i=0; i < 26; i++)
        param->plugboard.wheel[i] = (char)('A' + i);

    for (i=0; i < strlen(plugboard_pairs); i+=2) {
        param->plugboard.wheel[plugboard_pairs[i]-'A'] = plugboard_pairs[i+1];
        param->plugboard.wheel[plugboard_pairs[i+1]-'A'] = plugboard_pairs[i];
    }

    return 0;
}

int setparam_ENIGMA_I(EnigmaParam* param, int reflector, int wheel_order[3], char ring_settting[3], char wheel_pos[3], char* plugboard_pairs) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_III];
                break;
            case 3:
                param->wheel[(3-i)] = RotorSet[ROTOR_IV];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_IV];
                break;
            case 4:
                param->wheel[(3-i)] = RotorSet[ROTOR_V];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_V];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    switch (reflector) {
        case 0:
            param->wheel[4] = ReflectorSet[REFLECTOR_A];
            break;
        case 1:
            param->wheel[4] = ReflectorSet[REFLECTOR_B];
            break;
        case 2:
            param->wheel[4] = ReflectorSet[REFLECTOR_C];
            break;
        default:
            return -1; // invalid reflector
            break;
    }

    for (i=0; i < 3; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(2-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }
    param->wheelpos[3].wheelpos = 'A'; // fixed reflector

    for (i=0; i < 3; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(2-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }
    param->wheelring[3].wheelring = 'A'; // fixed reflector

    if (setplugboard_from_plugboardpairs(param, plugboard_pairs) != 0)
        return -1;

    param->reflectorsetflag = 0;
    param->thinflag = 0;

    return 0;
}

int setparam_ENIGMA_M3(EnigmaParam* param, int reflector, int wheel_order[3], char ring_settting[3], char wheel_pos[3], char* plugboard_pairs) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_III];
                break;
            case 3:
                param->wheel[(3-i)] = RotorSet[ROTOR_IV];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_IV];
                break;
            case 4:
                param->wheel[(3-i)] = RotorSet[ROTOR_V];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_V];
                break;
            case 5:
                param->wheel[(3-i)] = RotorSet[ROTOR_VI];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_VI];
                break;
            case 6:
                param->wheel[(3-i)] = RotorSet[ROTOR_VII];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_VII];
                break;
            case 7:
                param->wheel[(3-i)] = RotorSet[ROTOR_VIII];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_VIII];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    switch (reflector) {
        case 0:
            param->wheel[4] = ReflectorSet[REFLECTOR_B];
            break;
        case 1:
            param->wheel[4] = ReflectorSet[REFLECTOR_C];
            break;
        default:
            return -1; // invalid reflector
            break;
    }

    for (i=0; i < 3; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(2-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }
    param->wheelpos[3].wheelpos = 'A'; // fixed reflector

    for (i=0; i < 3; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(2-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }
    param->wheelring[3].wheelring = 'A'; // fixed reflector

    if (setplugboard_from_plugboardpairs(param, plugboard_pairs) != 0)
        return -1;

    param->reflectorsetflag = 0;
    param->thinflag = 0;

    return 0;
}

int setparam_ENIGMA_M4_With_Thin(EnigmaParam* param, int reflector, int wheel_order[4], char ring_settting[4], char wheel_pos[4], char* plugboard_pairs) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW];

    switch (wheel_order[0]) {
        case 0:
            param->wheel[(4-0)] = RotorSet[ROTOR_BETA];
            // no turnover
            break;
        case 1:
            param->wheel[(4-0)] = RotorSet[ROTOR_GAMMA];
            // no turnover
            break;
        default:
            return -1; // invalid wheel_order
    }

    for (i=1; i < 4; i++) {
        switch(wheel_order[i]) {
            case 0:
                param->wheel[(4-i)] = RotorSet[ROTOR_I];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_I];
                break;
            case 1:
                param->wheel[(4-i)] = RotorSet[ROTOR_II];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_II];
                break;
            case 2:
                param->wheel[(4-i)] = RotorSet[ROTOR_III];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_III];
                break;
            case 3:
                param->wheel[(4-i)] = RotorSet[ROTOR_IV];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_IV];
                break;
            case 4:
                param->wheel[(4-i)] = RotorSet[ROTOR_V];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_V];
                break;
            case 5:
                param->wheel[(4-i)] = RotorSet[ROTOR_VI];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_VI];
                break;
            case 6:
                param->wheel[(4-i)] = RotorSet[ROTOR_VII];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_VII];
                break;
            case 7:
                param->wheel[(4-i)] = RotorSet[ROTOR_VIII];
                param->turnover[(2-(i-1))] = TurnoverSet[TURNOVER_VIII];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    switch (reflector) {
        case 0:
            param->wheel[5] = ReflectorSet[REFLECTOR_B_THIN];
            break;
        case 1:
            param->wheel[5] = ReflectorSet[REFLECTOR_C_THIN];
            break;
        default:
            return -1; // invalid reflector
            break;
    }

    for (i=0; i < 4; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(3-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }

    for (i=0; i < 4; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(3-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }

    if (setplugboard_from_plugboardpairs(param, plugboard_pairs) != 0)
        return -1;

    param->reflectorsetflag = 0;
    param->thinflag = 1;

    return 0;
}

int setparam_ENIGMA_M4(EnigmaParam* param, int reflector, int wheel_order[4], char ring_settting[4], char wheel_pos[4], char* plugboard_pairs) {
    if (wheel_order[0] < 2) {
        return setparam_ENIGMA_M4_With_Thin(param, reflector, wheel_order, ring_settting, wheel_pos, plugboard_pairs);
    } else {
        /* UFW-D is not implemented */
        return -1;
    }
}

int setparam_ENIGMA_RAILWAY(EnigmaParam* param, int wheel_order[3], char ring_settting[4], char wheel_pos[4]) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW_RAILWAY];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_RAILWAY_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_RAILWAY_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_RAILWAY_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_RAILWAY_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_RAILWAY_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_RAILWAY_III];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    param->wheel[4] = ReflectorSet[UKW_RAILWAY];

    for (i=0; i < 4; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(3-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }

    for (i=0; i < 4; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(3-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }

    param->plugboard = IDENTITY_WHEEL;

    param->reflectorsetflag = 1;
    param->thinflag = 0;

    return 0;
}

int setparam_ENIGMA_SWISSK(EnigmaParam* param, int wheel_order[3], char ring_settting[4], char wheel_pos[4]) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW_SWISSK];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_SWISSK_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_SWISSK_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_SWISSK_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_SWISSK_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_SWISSK_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_SWISSK_III];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    param->wheel[4] = ReflectorSet[UKW_SWISSK];

    for (i=0; i < 4; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(3-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }

    for (i=0; i < 4; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(3-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }

    param->plugboard = IDENTITY_WHEEL;

    param->reflectorsetflag = 1;
    param->thinflag = 0;

    return 0;
}

int setparam_ENIGMA_D_K(EnigmaParam* param, int wheel_order[3], char ring_settting[4], char wheel_pos[4]) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW_D_K];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_D_K_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_D_K_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_D_K_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_D_K_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_D_K_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_D_K_III];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    param->wheel[4] = ReflectorSet[UKW_D_K];

    for (i=0; i < 4; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(3-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }

    for (i=0; i < 4; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(3-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }

    param->plugboard = IDENTITY_WHEEL;

    param->reflectorsetflag = 1;
    param->thinflag = 0;

    return 0;
}

int setparam_ENIGMA_NORWAY(EnigmaParam* param, int wheel_order[3], char ring_settting[3], char wheel_pos[3], char* plugboard_pairs) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_NORWAY_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_NORWAY_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_NORWAY_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_NORWAY_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_NORWAY_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_NORWAY_III];
                break;
            case 3:
                param->wheel[(3-i)] = RotorSet[ROTOR_NORWAY_IV];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_NORWAY_IV];
                break;
            case 4:
                param->wheel[(3-i)] = RotorSet[ROTOR_NORWAY_V];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_NORWAY_V];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    param->wheel[4] = ReflectorSet[UKW_NORWAY];

    for (i=0; i < 3; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(2-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }
    param->wheelpos[3].wheelpos = 'A'; // fixed reflector

    for (i=0; i < 3; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(2-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }
    param->wheelring[3].wheelring = 'A'; // fixed reflector

    if (setplugboard_from_plugboardpairs(param, plugboard_pairs) != 0)
        return -1;

    param->reflectorsetflag = 0;
    param->thinflag = 0;

    return 0;
}

int setparam_ENIGMA_SONDER(EnigmaParam* param, int wheel_order[3], char ring_settting[3], char wheel_pos[3], char* plugboard_pairs) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_SONDER_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_SONDER_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_SONDER_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_SONDER_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_SONDER_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_SONDER_III];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    param->wheel[4] = ReflectorSet[UKW_SONDER];

    for (i=0; i < 3; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(2-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }
    param->wheelpos[3].wheelpos = 'A'; // fixed reflector

    for (i=0; i < 3; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(2-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }
    param->wheelring[3].wheelring = 'A'; // fixed reflector

    if (setplugboard_from_plugboardpairs(param, plugboard_pairs) != 0)
        return -1;

    param->reflectorsetflag = 0;
    param->thinflag = 0;

    return 0;
}

int setparam_ENIGMA_T(EnigmaParam* param, int wheel_order[3], char ring_settting[4], char wheel_pos[4]) {
    unsigned int i;

    param->wheel[0] = ETWSet[ETW_T];
    param->wheel[5] = IDENTITY_WHEEL; // not used last wheel

    for (i=0; i < 3; i++) {
        switch (wheel_order[i]) {
            case 0:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_I];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_I];
                break;
            case 1:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_II];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_II];
                break;
            case 2:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_III];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_III];
                break;
            case 3:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_IV];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_IV];
                break;
            case 4:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_V];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_V];
                break;
            case 5:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_VI];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_VI];
                break;
            case 6:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_VII];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_VII];
                break;
            case 7:
                param->wheel[(3-i)] = RotorSet[ROTOR_T_VIII];
                param->turnover[(2-i)] = TurnoverSet[TURNOVER_T_VIII];
                break;
            default:
                return -1; // invalid wheel_order
                break;
        }
    }

    param->wheel[4] = ReflectorSet[UKW_T];

    for (i=0; i < 4; i++) {
        if ((wheel_pos[i] >= 'A') && (wheel_pos[i] <= 'Z')) {
            param->wheelpos[(3-i)].wheelpos = wheel_pos[i];
        } else {
            return -1; // invalid wheel_pos
        }
    }

    for (i=0; i < 4; i++) {
        if ((ring_settting[i] >= 'A') && (ring_settting[i] <= 'Z')) {
            param->wheelring[(3-i)].wheelring = ring_settting[i];
        } else {
            return -1; // invalid ring_settting
        }
    }

    param->plugboard = IDENTITY_WHEEL;

    param->reflectorsetflag = 1;
    param->thinflag = 0;

    return 0;
}


/*** debug print ***/

void printEnigmaParam(EnigmaParam* param) {
    // print parameters for enigma (order of rotor setting etc. is inputting order(left-to-right).
    // internal order is different(right-to-left))
    
    int i, j;

    if (param->thinflag == 0) {
        printf("reflector=");
        for (i=0; i < 26; i++)
            printf("%c", param->wheel[4].wheel[i]);
        printf("\n");
    } else {
        printf("thin reflector=");
        for (i=0; i < 26; i++)
            printf("%c", param->wheel[5].wheel[i]);
        printf("\n");

        printf("thin rotor=");
        for (i=0; i < 26; i++)
            printf("%c", param->wheel[4].wheel[i]);
        printf("\n");
    }

    printf("(input) rotor1=");
    for (i=0; i < 26; i++)
        printf("%c", param->wheel[3].wheel[i]);
    printf("\n");

    printf("(input) rotor2=");
    for (i=0; i < 26; i++)
        printf("%c", param->wheel[2].wheel[i]);
    printf("\n");

    printf("(input) rotor3=");
    for (i=0; i < 26; i++)
        printf("%c", param->wheel[1].wheel[i]);
    printf("\n");

    printf("etw=");
    for (i=0; i < 26; i++)
        printf("%c", param->wheel[0].wheel[i]);
    printf("\n");

    printf("(input) rotor position=");
    for (i=3; i >= 0; i--) {
        if ((i <=2) || (param->reflectorsetflag == 1) || (param->thinflag == 1)) {
            printf("%c", param->wheelpos[i].wheelpos);
        } else {
            continue;
        }
    }
    printf("\n");

    printf("(input) ring position=");
    for (i=3; i >= 0; i--) {
        if ((i <= 2) || (param->reflectorsetflag == 1) || (param->thinflag == 1)) {
            printf("%c", param->wheelring[i].wheelring);
        } else {
            continue;
        }
    }
    printf("\n");

    printf("plugboard=");
    for (i=0; i < 26; i++)
        printf("%c", param->plugboard.wheel[i]);
    printf("\n");

    printf("(input) turnover=");
    for (i=2; i >= 0; i--) {
        for (j=0; j < 2; j++)
            printf("%c", param->turnover[i].turnover[j]);
        printf(" ");
    }
    printf("\n");
}

void printCurSetting(CurSetting* cursetting) {
    printf("(input) indicator=%c%c%c%c", cursetting->indicator[3]+'A', cursetting->indicator[2]+'A', cursetting->indicator[1]+'A', cursetting->indicator[0]+'A');
    printf("\n");
    printf("(input) prevturnoverflag=%d%d%d", cursetting->prevturnoverflag[2], cursetting->prevturnoverflag[1], cursetting->prevturnoverflag[0]);
    printf("\n");
}


/*** initial encrypt procedure for enigma ***/

int resetCurrentSetting(CurSetting* cursetting, EnigmaParam* param) {
    unsigned int i, j;

    for (i=0; i < 4; i++) {
        cursetting->indicator[i] = param->wheelpos[i].wheelpos - 'A';

        if (i != 3) {
            cursetting->prevturnoverflag[i] = 0;
            for (j=0; j < MAXTURNOVERNUM; j++) {
                cursetting->prevturnoverflag[i] = cursetting->prevturnoverflag[i] || (cursetting->indicator[i] + 'A' == param->turnover[i].turnover[j]);
            }
        }
    }

    return 0;
}

int saveCurrentSetting(EnigmaParam* param, CurSetting* cursetting) {
    unsigned int i;

    for (i=0; i < 4; i++) {
        param->wheelpos[i].wheelpos = cursetting->indicator[i] + 'A';
    }

    return 0;
}

int setInverseWheel(EnigmaParam* param, Wheel inversewheel[]) {
    unsigned int i, j;

    for (i=0; i < 6; i++) {
        for (j=0; j < 26; j++)
            inversewheel[i].wheel[param->wheel[i].wheel[j] - 'A'] = j + 'A';
    }

    return 0;
}

/*** rotor increment (inner encryption procedure) ***/

int incrementIndicator_normal(CurSetting* cursetting, EnigmaParam* param) {
    /***
     * normal rotor incrementation behavior
     * "normal" means most standard Enigma behavior (double stepping)
     * 
     * https://www.cryptomuseum.com/people/hamer/files/double_stepping.pdf
     ***/

    unsigned int i, j;

    // NOTE: not move indicator[3] (reflector or thin-rotor)

    for (i=0; i < 2; i++) {
        if (cursetting->prevturnoverflag[i] == 1) {
            if ((i != 0) && (cursetting->prevturnoverflag[i-1] == 0)) {
                cursetting->indicator[i] += 1;
                if (cursetting->indicator[i] >= 26)
                    cursetting->indicator[i] -= 26;
            }
            cursetting->indicator[i+1] += 1;
            if (cursetting->indicator[i+1] >= 26)
                cursetting->indicator[i+1] -= 26;
        }
    }
    cursetting->indicator[0] += 1;
    if (cursetting->indicator[0] >= 26)
        cursetting->indicator[0] -= 26;


    for (i=0; i < 3; i++) {
        cursetting->prevturnoverflag[i] = 0;
        for (j=0; j < MAXTURNOVERNUM; j++)
            cursetting->prevturnoverflag[i] = cursetting->prevturnoverflag[i] || (cursetting->indicator[i] + 'A' == param->turnover[i].turnover[j]);
    }

    return 0;
}

int incrementIndicator_fastincrement(CurSetting* cursetting, EnigmaParam* param) {
    // NOTE: not move indicator[3] (reflector or thin-rotor)

    unsigned int j;

    cursetting->indicator[0] += 1;
    if (cursetting->indicator[0] >= 26)
        cursetting->indicator[0] -= 26;

    cursetting->prevturnoverflag[0] = 0;
    for (j=0; j < MAXTURNOVERNUM; j++)
        cursetting->prevturnoverflag[0] = cursetting->prevturnoverflag[0] || (cursetting->indicator[0] + 'A' == param->turnover[0].turnover[j]);

    cursetting->prevturnoverflag[1] = 0;
    cursetting->prevturnoverflag[2] = 0;

    if (cursetting->prevturnoverflag[0] == 1) {
        cursetting->indicator[1] += 1;
        if (cursetting->indicator[1] >= 26)
            cursetting->indicator[1] -= 26;

        for (j=0; j < MAXTURNOVERNUM; j++) {
            cursetting->prevturnoverflag[1] = cursetting->prevturnoverflag[1] || (cursetting->indicator[1] + 'A' == param->turnover[1].turnover[j]);
        }

	    if (cursetting->prevturnoverflag[1] == 1) {
            cursetting->indicator[2] += 1;
            if (cursetting->indicator[2] >= 26)
                cursetting->indicator[2] -= 26;
            
            for (j=0; j < MAXTURNOVERNUM; j++) {
                cursetting->prevturnoverflag[2] = cursetting->prevturnoverflag[2] || (cursetting->indicator[2] + 'A' == param->turnover[2].turnover[j]);
            }
        }
    }

    return 0;
}

int incrementIndicator_lateincrement(CurSetting* cursetting, EnigmaParam* param) {
    unsigned int i, j;

    // NOTE: not move indicator[3] (reflector or thin-rotor)

    if (cursetting->prevturnoverflag[0] == 1) {
        cursetting->indicator[1] += 1;
        if (cursetting->indicator[1] >= 26)
            cursetting->indicator[1] -= 26;

        if (cursetting->prevturnoverflag[1] == 1) {
            cursetting->indicator[2] += 1;
            if (cursetting->indicator[2] >= 26)
                cursetting->indicator[2] -= 26;
        }
    }

    cursetting->indicator[0] += 1;
    if (cursetting->indicator[0] >= 26)
        cursetting->indicator[0] -= 26;

    for (i=0; i < 3; i++) {
        cursetting->prevturnoverflag[i] = 0;
        for (j=0; j < MAXTURNOVERNUM; j++)
            cursetting->prevturnoverflag[i] = cursetting->prevturnoverflag[i] || (cursetting->indicator[i] + 'A' == param->turnover[i].turnover[j]);
    }

    return 0;
}


/*** each encryption procedure ***/

char wheelout(char wheel[26], int offset, char ch) {
    // NOTE: assume -25 <= offset <= 25

    int preidx = (ch - 'A') + offset;
    if (preidx < 0) 
        preidx += 26;
    if (preidx >= 26)
        preidx -= 26;

    int postidx = (wheel[preidx] - 'A') - offset;
    if (postidx < 0)
        postidx += 26;
    if (postidx >= 26)
        postidx -= 26;

    return postidx + 'A';
}

char enigmaEachEncrypt(EnigmaParam* param, CurSetting* cursetting, Wheel inversewheel[], char ch) {
    // encrypt one character on current rotor/plugboard etc. setting

    incrementIndicator_normal(cursetting, param);
    
#ifdef DEBUG
    printCurSetting(cursetting);
#endif

#ifdef DEBUG
    printf("(%c) ", ch); //debug
#endif
    ch = wheelout(param->plugboard.wheel, 0, ch);
#ifdef DEBUG
    printf("%c ", ch); //debug
#endif
    ch = inversewheel[0].wheel[ch - 'A']; // ETW
#ifdef DEBUG
    printf("(%c) ", ch); //debug
#endif
    ch = wheelout(param->wheel[1].wheel, cursetting->indicator[0] - (param->wheelring[0].wheelring - 'A'), ch);
#ifdef DEBUG
    printf("[%d %d]", cursetting->indicator[0], param->wheelring[0].wheelring - 'A');
    printf("%c ", ch); //debug
#endif
    ch = wheelout(param->wheel[2].wheel, cursetting->indicator[1] - (param->wheelring[1].wheelring - 'A'), ch);
#ifdef DEBUG
    printf("[%d %d]", cursetting->indicator[1], param->wheelring[1].wheelring - 'A');
    printf("%c ", ch); //debug
#endif
    ch = wheelout(param->wheel[3].wheel, cursetting->indicator[2] - (param->wheelring[2].wheelring - 'A'), ch);
#ifdef DEBUG
    printf("[%d %d]", cursetting->indicator[2], param->wheelring[2].wheelring - 'A');
    printf("%c ", ch); //debug
#endif
    ch = wheelout(param->wheel[4].wheel, cursetting->indicator[3] - (param->wheelring[3].wheelring - 'A'), ch);
#ifdef DEBUG
    printf("[%d %d]", cursetting->indicator[3], param->wheelring[3].wheelring - 'A');
    printf("%c ", ch); //debug
#endif
    if (param->thinflag == 1) {
        ch = wheelout(param->wheel[5].wheel, 0, ch);
#ifdef DEBUG
        printf("<%c> ", ch); //debug
#endif
        ch = wheelout(inversewheel[4].wheel, cursetting->indicator[3] - (param->wheelring[3].wheelring - 'A'), ch);
#ifdef DEBUG
        printf("[%d %d]", cursetting->indicator[3], param->wheelring[3].wheelring - 'A');
        printf("%c ", ch); //debug
#endif
    }
#ifdef DEBUG
    else {
        printf("<%c> ", ch); //debug
    }
#endif
    ch = wheelout(inversewheel[3].wheel, cursetting->indicator[2] - (param->wheelring[2].wheelring - 'A'), ch);
#ifdef DEBUG
    printf("[%d %d]", cursetting->indicator[2], param->wheelring[2].wheelring - 'A');
    printf("%c ", ch); //debug
#endif
    ch = wheelout(inversewheel[2].wheel, cursetting->indicator[1] - (param->wheelring[1].wheelring - 'A'), ch);
#ifdef DEBUG
    printf("[%d %d]", cursetting->indicator[1], param->wheelring[1].wheelring - 'A');
    printf("%c ", ch); //debug
#endif
    ch = wheelout(inversewheel[1].wheel, cursetting->indicator[0] - (param->wheelring[0].wheelring - 'A'), ch);
#ifdef DEBUG
    printf("[%d %d]", cursetting->indicator[0], param->wheelring[0].wheelring - 'A');
    printf("%c ", ch); //debug
#endif
    ch = param->wheel[0].wheel[ch - 'A']; // ETW
#ifdef DEBUG
    printf("(%c) ", ch); //debug
#endif
    ch = wheelout(param->plugboard.wheel, 0, ch);
#ifdef DEBUG
    printf("%c ", ch); //debug
    printf("\n");
#endif

    return ch;
}

int enigmaEncrypt(EnigmaParam* param, char* from, char* to) {
    unsigned int i;
    CurSetting cursetting;
    Wheel inversewheel[6]; // inverse of etw, rotor-1, rotor-2, rotor-3, reflector (or thin-rotor, thin-reflector)

    if (resetCurrentSetting(&cursetting, param) != 0)
        return -1;

    if (setInverseWheel(param, inversewheel) != 0)
        return -1;
    
#ifdef DEBUG
    printEnigmaParam(param);
    printCurSetting(&cursetting);
#endif

    for (i=0; i < strlen(from); i++)
        to[i] = enigmaEachEncrypt(param, &cursetting, inversewheel, from[i]);

    to[i] = '\0';

    return 0;
}

int enigmaEncrypt_with_inplace_param(EnigmaParam* param, char* from, char* to) {
    unsigned int i;
    CurSetting cursetting;
    Wheel inversewheel[6]; // inverse of etw, rotor-1, rotor-2, rotor-3, reflector (or thin-rotor, thin-reflector)

    if (resetCurrentSetting(&cursetting, param) != 0)
        return -1;

    if (setInverseWheel(param, inversewheel) != 0)
        return -1;
    
#ifdef DEBUG
    printEnigmaParam(param);
    printCurSetting(&cursetting);
#endif

    for (i=0; i < strlen(from); i++)
        to[i] = enigmaEachEncrypt(param, &cursetting, inversewheel, from[i]);

    to[i] = '\0';

    // wheel order retantion
    if (saveCurrentSetting(param, &cursetting) != 0)
        return -1;

    return 0;
}

int enigmaDecrypt(EnigmaParam* param, char* from, char* to) {
    // encryption and decryption are same
    return enigmaEncrypt(param, from, to);
}

int enigmaDecrypt_with_inplace_param(EnigmaParam* param, char* from, char* to) {
    return enigmaEncrypt_with_inplace_param(param, from, to);
}


/*** util ***/
int copyEnigmaParam(EnigmaParam* to, EnigmaParam* from) {
    // deep (not pointer, but rewrite each byte) copy for EnigmaParam

    /***
    Wheel wheel[6]; // wheel(walzenlage): (entry wheel(ETW,Eintritswalze), rotor(walze), reflector(UKW,umkehrwalze)): entry, rotor-1, rotor-2, rotor-3, reflector (or thin-rotor, thin-reflector)
    WheelPos wheelpos[4]; // rotor-1, rotor-2, rotor-3, reflector
    WheelRing wheelring[4]; // rotor-1, rotor-2, rotor-3, reflector
    Wheel plugboard; // plugboard(steckerbrett)
    Turnover turnover[3]; // turnover: rotor-1, rotor-2, rotor-3
    int reflectorsetflag; // settable position and ring for reflector
    int thinflag; // settable thin reflector and thin rotor
    ***/
    
    unsigned int i, j;

    for (i=0; i < 6; i++) {
	    for (j=0; j < 26; j++) 
            to->wheel[i].wheel[j] = from->wheel[i].wheel[j];
    }

    for (i=0; i < 4; i++) {
	    to->wheelpos[i].wheelpos = from->wheelpos[i].wheelpos;
	    to->wheelring[i].wheelring = from->wheelring[i].wheelring;
    }

    for (j=0; j < 26; j++) 
        to->plugboard.wheel[j] = from->plugboard.wheel[j];

    for (i=0; i < 3; i++) {
        for (j=0; j < sizeof(Turnover); j++)
            to->turnover[i].turnover[j] =  from->turnover[i].turnover[j];
    }

    to->reflectorsetflag = from->reflectorsetflag;
    to->thinflag = from->thinflag;
    
    return 0;
}
