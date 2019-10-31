//
// Started by pocol and rat on 10/18/2019.
//
#include "at.h"
#include <stdio.h>

#define CR 0x0D
#define LF 0x0A

typedef enum {
    STATE_MACHINE_NOT_READY,
    STATE_MACHINE_READY_OK,
    STATE_MACHINE_READY_WITH_ERROR
}STATE_MACHINE_RETURN_VALUE;

AT_DATA at;
int state;

void reset_fsm(){
    state = 0;
}

int parse(uint8_t ch) {
    static uint32_t string_index = 0; //fancy way to say i & j

    switch (state) {
        case 0:
            if (ch == CR) {
                state = 1;
//                printf("Am citit CR, astept LF\n");
                break;
            } else {
                state = -1;
                break;
            }

        case 1:
            if (ch == LF) {
                state = 2;
//                printf("Am citit LF, astept O sau E sau +\n");
                break;
            } else {
                state = -1;
                break;
            }

        case 2: //after LF, start to distribute
            if (ch == 'O') {
                state = 3;
//                printf("Am citit %c, astept K\n", ch);
                break;
            } else if (ch == 'E') {
                state = 6;
//                printf("Am citit %c, astept R\n", ch);
                break;
            } else if (ch == '+') {
                state = 12;
//                printf("Am citit %c, astept caracter\n", ch);
                break;
            } else {
                state = -1;
                break;
            }

        case 3:
            if (ch == 'K') {
                state = 4;
//                printf("Am citit %c, astept CR\n", ch);
                break;
            } else {
                state = -1;
                break;
            }

        case 4:
            if (ch == CR) {
                state = 5;
//                printf("Am citit CR, astept LF\n");
                break;
            } else {
                state = -1;
                break;
            }

        case 5:
            if (ch == LF) { //final transition for the OK case
                at.ok = true;
//                printf("Tranzitie finala pentru cazul OK, resetez automatul\n");
                reset_fsm();
                return STATE_MACHINE_READY_OK;
            } else {
                state = -1;
                break;
            }

        case 6:
            if (ch == 'R') {
                state = 7;
//                printf("Am citit %c, astept R\n", ch);
                break;
            } else {
                state = -1;
                break;
            }

        case 7:
            if (ch == 'R') {
                state = 8;
//                printf("Am citit %c, astept O\n", ch);
                break;
            } else {
                state = -1;
                break;
            }

        case 8:
            if (ch == 'O') {
                state = 9;
//                printf("Am citit %c, astept R\n", ch);
                break;
            } else {
                state = -1;
                break;
            }

        case 9:
            if (ch == 'R') {
                state = 10;
//                printf("Am citit %c, astept CR\n", ch);
                break;
            } else {
                state = -1;
                break;
            }

        case 10:
            if (ch == CR) {
                state = 11;
//                printf("Am citit CR, astept LF\n");
                break;
            } else {
                state = -1;
                break;
            }

        case 11:
            if (ch == LF) { //final transition for the ERROR case
                at.ok = false;
//                printf("Tranzitie finala pentru cazul ERROR, resetez automatul\n");
                reset_fsm();
                return STATE_MACHINE_READY_WITH_ERROR;
            } else {
                state = -1;
                break;
            }

        case 12:
            if (ch != CR) {
//                printf("Am citit %c, astept citire caracter\n");
                at.str[at.line_count][string_index++] = ch;
                break;
            } else if (string_index != 0) { //verifies if at least one CHAR is read before CR
//                printf("Cazul in care a citit ceva inainte de CR si acum a venit CRu si astept LF\n");
//                printf("Am terminat de citit si pun terminatorul de sir la finalul liniei\n");
                at.str[at.line_count][string_index++] = '\0';
                string_index = 0;
                state = 13;
                break;
            } else {
                state = -1;
                break;
            }

        case 13:
            if (ch == LF) {
//                printf("Am citit LF, astept < + > sau CR \n");
                at.line_count ++; //new line in matrix of commands
                state = 14;
                break;
            } else {
                state = -1;
                break;
            }

        case 14:
            if (ch == '+') { //means that more useful lines are coming and need to return to reading state
//                printf("Am citit %c, astept citire caracter\n", ch);
                state = 12;
                break;
            } else if (ch == CR) {
//                printf("Am citit CR, astept LF\n");
                state = 15;
                break;
            } else {
                state = -1;
                break;
            }

        case 15:
            if (ch == LF) {
                state = 16;
//                printf("Am citit LF, astept O sau E\n");
                break;
            } else {
                state = -1;
                break;
            }

        case 16:
            if (ch == 'O') {
//                printf("Am citit %c, astept K\n", ch);
                state = 3; //returns to a previous transition of states where K<CR><LF> is treated
                break;
            } else if (ch == 'E') {
//                printf("Am citit %c, astept R\n", ch);
                state = 7; //returns to a previous transition of states where RROR<CR><LF> is treated
                break;
            } else {
                state = -1;
                break;
            }
        case -1:
//            printf("Stare de eroare (case = -1), resetez automatul\n", ch);
            reset_fsm();
            at.ok = false;
            return STATE_MACHINE_READY_WITH_ERROR;

    }

    return STATE_MACHINE_NOT_READY; //means that the FSM needs more chars to continue parsing lines

}

void showAT_DATA() {
    int i, j;

    printf("bool: %s\n", at.ok ? "true" : "false");
    printf("line count = %d\n", at.line_count);
    for (i = 0; i < at.line_count; i++) {
        for (j = 0; at.str[i][j] != '\0'; ++j) {
            printf("%c", at.str[i][j]);
        }
        printf("\n");
    }
}
