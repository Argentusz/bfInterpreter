#include <stdio.h>
#include <stdlib.h>
#define TAPE_LEN 256

void interpreter(FILE * source)
{
    // pointer - tape of chars in memory
    // cmd - command symbol from file
    int * pointer, *safety, cmd;
    // Allocate memory
    pointer = safety = (int*)malloc(TAPE_LEN*sizeof(int));
    for(int i = 0; i < TAPE_LEN; i++) {
        *safety = 0;
        safety++;
    }
    do {
        cmd = getc(source);
        switch(cmd) {
            case '>':
                pointer++;
                break;
            case '<':
                pointer--;
                break;
            case '+':
                (*pointer)++;
                break;
            case '-':
                (*pointer)--;
                break;
            case '.':
                putc(*pointer, stdout);
                break;
            case ',':
                *pointer = getc(stdin);
                break;
            default:
                continue;
        }
    } while(cmd != EOF);
}

int main(int argc, char** argv) {
    FILE * source = fopen(argv[1], "r");
    if(argc > 2) {
        fprintf(stderr, "fatal error: Unexpected argument\n");
        exit(2);
    }
    if (source == NULL) {
        fprintf(stderr, "fatal error: Could not open '%s'\n", argv[1]);
        source = fopen("ex.bf", "r");
    }
    interpreter(source);
    return 0;
}
