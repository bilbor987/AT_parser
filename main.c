//
// Started by pocol and rat on 10/18/2019.
// Pocol Bogdan - Adrian & Rat Alexandru an IV CTI RO
//

#include <stdio.h>
#include "at.h"

#define CR 0x0D
#define LF 0x0A

FILE *inFile;
FILE *outFile; //not used right now

/**
 To use the output file, provide another argument that represents the path to the output file
 */

int main(int argc, char* argv[]) {
    int i, ret;
    char c;

//    printf("argc = %d\n", argc);
//    printf("%s\t", argv[0]);
    if( argc >= 2 ){
//        printf("\nThe arguments supplied are:\n");
//        for(i = 1; i < argc; i++){
//            printf("%s\t", argv[i]);
//        }
//        printf("\n\n\n");

        inFile = fopen(argv[1], "rb");
//        outFile = fopen(argv[2], "w");
        while (!feof(inFile)) {
            c = fgetc(inFile);
//            fprintf(outFile, "Am citit din fisier ");
//            if (c == CR) fprintf(outFile, "CR\n");
//            else if (c == LF) fprintf(outFile, "LF\n");
//            else fprintf(outFile, "%c\n", c);

            ret = parse(c);
//            fprintf(outFile, "Parse returned %d\n\n", ret);
            if (ret != 0) break;
        }

        showAT_DATA();
    }
    else{
        printf("\nargument list is empty.\n");
    }

    return 0;
}