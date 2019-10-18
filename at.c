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
    uint32_t line_index, string_index; //fancy way to say i & j

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


    }

}