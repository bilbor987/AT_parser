#include <stdio.h>
#include "at.h"

FILE *inFile;

int main(int argc, char* argv[]) {
    int i, ret;
    char c;

    printf("argc = %d\n", argc);
    printf("%s\t", argv[0]);
    if( argc >= 2 ){
        printf("\nThe arguments supplied are:\n");
        for(i = 1; i < argc; i++){
            printf("%s\t", argv[i]);
        }
        printf("\n");

        inFile = fopen(argv[1], "rb");

        while (!feof(inFile)) {
            c = fgetc(inFile);
            printf("Am citit din fisier %c\n", c);

            ret = parse(c);
           // printf("Parse returned %d\n", ret);
        }
    }
    else{
        printf("\nargument list is empty.\n");
    }

//#TODO
//add a config for CLion to simulate read with command line args
//implement file read to test code
//new line to commit again hehe


    //parse('s');
    return 0;
}