#include <stdio.h>
#include <stdlib.h>
#define TAPE_LEN 65536*sizeof(char)

void interpreter(FILE * source)
{
    // pointer - tape of chars in memory
    // cmd - command symbol from file
    char * pointer, cmd;
    // Allocate memory
    pointer = malloc(TAPE_LEN);
    do {
        cmd = (char)getc(source);
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
