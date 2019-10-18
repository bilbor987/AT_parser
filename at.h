//
// Created by pocol on 10/18/2019.
//

#ifndef TD_AT_H
#define TD_AT_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_COUNT 1000
#define STR_SIZE 99

typedef struct {
    bool ok;
    uint32_t line_count;
    char str[MAX_LINE_COUNT][STR_SIZE + 1]; //+1 for \0 as a word end
} AT_DATA;

extern AT_DATA at;
uint8_t parse(uint8_t ch);


#endif //TD_AT_H
