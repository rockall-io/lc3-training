#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint16_t MEMORY[65536];

uint16_t R0;
uint16_t R1;
uint16_t R2;
uint16_t R3;
uint16_t R4;
uint16_t R5;
uint16_t R6;
uint16_t R7;
uint16_t PC = 0x3000;

int main(arg) {
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("prog.lc3", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if(line"LD")
    }
    return 0;
}