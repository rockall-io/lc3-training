#include <stdint.h>
#include <stdbool.h>

typedef struct Registers
{
    uint16_t R0;
    uint16_t R1;
    uint16_t R2;
    uint16_t R3;
    uint16_t R4;
    uint16_t R5;
    uint16_t R6;
    uint16_t R7;
    uint16_t PC;
} Registers;

typedef struct Memory {
    uint16_t memory[65536];
} Memory;

typedef enum Instructions {
    ADD = 1,
    LEA = 14,
    AND = 5,
    NOT = 9,
    BR = 0,
    LD = 2,
    ST = 3,
    JSR = 4,
    LDR = 6,
    STR = 7,
    RTI = 8,
    LDI = 10,
    STI = 11,
    JMP = 12,
    RET = 12,
    TRAP = 15,
} Instructions;

typedef struct VirtualMachine {
    Registers registers;
    Memory memory;
    Instructions instructions;
} VirtualMachine;

void handle_instruction(uint16_t instruction, Registers *registers, Memory *memory);

bool is_bit_set(uint16_t instruction, uint16_t bit_position);

uint16_t parse_pc_offset(uint16_t instruction, uint16_t program_counter);
uint16_t parse_pc_offset_11(uint16_t instruction, uint16_t program_counter);

uint16_t parse_destination_register(uint16_t instruction);
uint16_t parse_source_one_register(uint16_t instruction);
uint16_t parse_source_two_register(uint16_t instruction);
uint16_t parse_base_register(uint16_t instruction);

uint16_t parse_opcode(uint16_t instruction);
uint16_t parse_trapvect_8(uint16_t instruction);

uint16_t get_immediate_value(uint16_t instruction);

Memory load_program(char * file_name, Registers * registers);
void run_program(Memory *memory, Registers *registers);