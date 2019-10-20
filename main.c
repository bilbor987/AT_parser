#include <stdio.h>
#include "at.h"

int main(int argc, char* argv[]) {
    int i;

    printf("argc = %d\n", argc);
    printf("%s\t", argv[0]);
    if( argc >= 2 ){
        printf("\nThe arguments supplied are:\n");
        for(i = 1; i < argc; i++){
            printf("%s\t", argv[i]);
        }
    }
    else{
        printf("\nargument list is empty.\n");
    }

    //parse('s');
    return 0;
}