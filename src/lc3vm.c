#include "lc3vm.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

uint16_t get_value_from_register(Registers *registers, uint16_t register_number)
{
    switch (register_number)
    {
    case 0:
        return registers->R0;
    case 1:
        return registers->R1;
    case 2:
        return registers->R2;
    case 3:
        return registers->R3;
    case 4:
        return registers->R4;
    case 5:
        return registers->R5;
    case 6:
        return registers->R6;
    case 7:
        return registers->R7;
    }
}

void set_register(Registers *registers, uint16_t register_number, uint16_t value)
{
    switch (register_number)
    {
    case 0:
        registers->R0 = value;
        break;
    case 1:
        registers->R1 = value;
        break;
    case 2:
        registers->R2 = value;
        break;
    case 3:
        registers->R3 = value;
        break;
    case 4:
        registers->R4 = value;
        break;
    case 5:
        registers->R5 = value;
        break;
    case 6:
        registers->R6 = value;
        break;
    case 7:
        registers->R7 = value;
        break;
    case 8:
        registers->PC = value;
        break;
    }
}

void handle_instruction(uint16_t instruction, Registers *registers, Memory *memory)
{
    uint16_t opcode = parse_opcode(instruction);
    if (opcode == ADD)
    {
        bool is_imm_bit_set = is_bit_set(instruction, 5);
        if (is_imm_bit_set)
        {
            uint16_t dest_register = parse_destination_register(instruction);
            uint16_t src1_register = parse_source_one_register(instruction);
            uint16_t src1_value = get_value_from_register(registers, src1_register);
            uint16_t immediate_value = get_immediate_value(instruction);
            set_register(registers, dest_register, (src1_value + immediate_value));
        }
        else
        {
            uint16_t dest_register = parse_destination_register(instruction);
            uint16_t src1_register = parse_source_one_register(instruction);
            uint16_t src2_register = parse_source_two_register(instruction);
            uint16_t src1_value = get_value_from_register(registers, src1_register);
            uint16_t src2_value = get_value_from_register(registers, src2_register);
            set_register(registers, dest_register, (src1_value + src2_value));
        }
    }
    else if (opcode == LEA)
    {
        uint16_t dest_register = parse_destination_register(instruction);

    } else if (opcode == AND)
    {
        bool is_imm_bit_set = is_bit_set(instruction, 5);
        if (is_imm_bit_set)
        {
            uint16_t dest_register = parse_destination_register(instruction);
            uint16_t src1_register = parse_source_one_register(instruction);
            uint16_t src1_value = get_value_from_register(registers, src1_register);
            uint16_t immediate_value = get_immediate_value(instruction);
            set_register(registers, dest_register, (src1_value & immediate_value));
        }
        else
        {
            uint16_t dest_register = parse_destination_register(instruction);
            uint16_t src1_register = parse_source_one_register(instruction);
            uint16_t src2_register = parse_source_two_register(instruction);
            uint16_t src1_value = get_value_from_register(registers, src1_register);
            uint16_t src2_value = get_value_from_register(registers, src2_register);
            set_register(registers, dest_register, (src1_value & src2_value));
        }
    } else if (opcode == NOT)
    {
        uint16_t dest_register = parse_destination_register(instruction);
        uint16_t src1_register = parse_source_one_register(instruction);
        uint16_t src1_value = get_value_from_register(registers, src1_register);
        uint16_t notted_value = ~src1_value;
        set_register(registers, dest_register, notted_value);
    } else if (opcode == RET)
    {
        set_register(registers, 8, registers->R7);    
    } else if (opcode == LD)
    {
        uint16_t dest_register = parse_destination_register(instruction);
        uint16_t pcoffset9 = parse_pc_offset(instruction, registers->PC);
        set_register(registers, dest_register, memory->memory[pcoffset9]);
    }
}

Memory load_program(char *file_name, Registers *registers)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Memory memory;
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, fp);
    origin = swap16(origin);
    registers->PC = origin;

    uint16_t value;
    while (fread(&value, sizeof(value), 1, fp) == 1)
    {
        uint16_t flipped_value = swap16(value);
        memory.memory[registers->PC] = flipped_value;
        registers->PC++;
    }

    registers->PC = origin;
    return memory;
}

bool is_bit_set(uint16_t instruction, uint16_t bit_position)
{
    uint16_t shifted = instruction >> bit_position;
    return shifted & 1;
}

uint16_t parse_pc_offset(uint16_t instruction, uint16_t program_counter)
{
    uint16_t offset = instruction & 511;
    return offset + program_counter;
}

uint16_t parse_destination_register(uint16_t instruction)
{
    uint16_t destination_register = (instruction >> 9) & 7;
    return destination_register;
}

uint16_t parse_source_one_register(uint16_t instruction)
{
    uint16_t source_register = (instruction >> 6) & 7;
    return source_register;
}
uint16_t parse_source_two_register(uint16_t instruction)
{
    uint16_t source_register = instruction & 7;
    return source_register;
}

uint16_t parse_opcode(uint16_t instruction)
{
    uint16_t opcode = (instruction >> 12);
    return opcode;
}

uint16_t get_immediate_value(uint16_t instruction)
{
    uint16_t value = (instruction & 31);
    return value;
}