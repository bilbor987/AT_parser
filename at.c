//
// Created by pocol on 10/18/2019.
//
#include "at.h"

#define CR 0x0A
#define LF 0x0D

AT_DATA at;
uint8_t state;

void reset_fsm(){
    state = 0;
}

uint8_t parse(uint8_t ch) {
    uint32_t line_index = 0, string_index = 0; //fancy way to say i & j

    switch (state){
        case 0:
            if (ch == CR){
                state = 1;
                break;
            }
            else {
                state = -1;
                break;
            }

        case 1:
            if (ch == LF){
                state = 2;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 2: //after LF, start to distribute
            if (ch == 'O'){
                state = 3;
                break;
            }
            else if (ch == 'E'){
                state = 6;
                break;
            }
            else if (ch == '+'){
                //at.str[line_index][string_index++] = ch;
                state = 12;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 3:
            if (ch == 'K'){
                state = 4;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 4:
            if (ch == CR){
                state = 5;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 5:
            if (ch == LF){ //final transition for the OK case
                at.ok = true;
                reset_fsm();
            }
            else{
                state = -1;
                break;
            }

        case 6:
            if (ch == 'R'){
                state = 7;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 7:
            if (ch == 'R'){
                state = 8;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 8:
            if(ch == 'O'){
                state = 9;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 9:
            if (ch == 'R'){
                state = 10;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 10:
            if (ch == CR){
                state = 11;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 11:
            if (ch == LF){ //final transition for the OK case
                at.ok = true;
                reset_fsm();
            }
            else{
                state = -1;
                break;
            }

        case 12:
            if (ch != CR){
                at.str[line_index][string_index++] = ch;
                //break;
            }
            else if (string_index != 0) { //verifies if at least one CHAR is read before CR
                at.str[line_index][string_index++] = '\0';
                state = 13;
                break;
            }
            else {
                state = -1;
                break;
            }

        case 13:
            if(ch == LF){
                state = 14;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 14:
            if(ch == '+'){ //means that more useful lines are coming and need to return to reading state
                state = 12;
                break;
            }
            else if(ch == CR){
                state = 15;
                break;
            }
            else{
                state = -1;
                break;
            }

        case 15:
            if(ch == LF){
                state = 16;
                break;
            }
            else{
                state = -1;
                 break;
            }

        case 16:
            if(ch == 'O'){
                state = 3; //returns to a previous transition of states where K<CR><LF> is treated
                break;
            }

            else if(ch == 'E'){
                state = 7; //returns to a previous transition of states where RROR<CR><LF> is treated
                break;
            }

            else{
                state = -1;
                break;
            }


    }


//#TODO
//treat state -1 state
//maybe use ENUM
//    typedef enum
//    {
//        STATE_MACHINE_NOT_READY,
//        STATE_MACHINE_READY_OK,
//        STATE_MACHINE_READY_WITH_ERROR //state -1 basically and maybe reset_fsm()
//    }STATE_MACHINE_RETURN_VALUE;
//    STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t current_character);

}