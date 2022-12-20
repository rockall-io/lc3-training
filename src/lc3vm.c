#include "lc3vm.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void handle_add_opcode(uint16_t instruction, Registers registers)
{
    bool is_imm_bit_set = is_bit_at_position_set(instruction, 5);
    if(is_imm_bit_set) {
 
    } else {
        uint16_t dest_register = parse_destination_register(instruction);
        uint16_t src1_register = parse_source_one_register(instruction);
        uint16_t src2_register = parse_source_two_register(instruction);
        printf("%d, %d, %d\n", dest_register, src1_register, src2_register);
    }
}

Memory load_program(char * file_name, Registers * registers) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    Memory memory;
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, fp);
    origin = swap16(origin);
    registers->PC = origin;

    uint16_t value;
    while(fread(&value, sizeof(value), 1, fp) == 1) {
        uint16_t flipped_value = swap16(value);
        memory.memory[registers->PC] = flipped_value;
        registers->PC++;
    }

    registers->PC = origin;
    return memory;
}

bool is_bit_set(uint16_t instruction, uint16_t bit_position) {
    uint16_t shifted = instruction >> (bit_position - 1);
    return shifted & 1;
}

uint16_t parse_pc_offset(uint16_t instruction, uint16_t program_counter) {
    uint16_t offset = instruction & 511;
    return offset + program_counter;
}

uint16_t parse_destination_register(uint16_t instruction) {
    uint16_t destination_register = (instruction >> 9) & 7;
    return destination_register;
}

uint16_t parse_source_one_register(uint16_t instruction) {
    uint16_t source_register = (instruction >> 6) & 7;
    return source_register;
}
uint16_t parse_source_two_register(uint16_t instruction) {
    uint16_t source_register = instruction & 7;
    return source_register;
}

uint16_t parse_opcode(uint16_t instruction) {
    uint16_t opcode = (instruction >> 12);
    return opcode;
}