//
// Started by pocol and rat on 10/18/2019.
// Pocol Bogdan - Adrian & Rat Alexandru an IV CTI RO
//

#ifndef TD_AT_H
#define TD_AT_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_COUNT 100
#define STR_SIZE 99

typedef struct {
    bool ok; //daca a venit OK sau error
    uint32_t line_count; //need to know how many used lines in str and maybe need to transmit to a higher level this info
    char str[MAX_LINE_COUNT][STR_SIZE + 1]; //+1 for \0 as a word end
} AT_DATA;

extern AT_DATA at;
extern int state;

int parse(uint8_t ch);
void reset_fsm();
void showAT_DATA();


#endif //TD_AT_H
