#include "lc3vm.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include "munit.h"

static MunitResult
test_add(const MunitParameter params[], void* data) {
  // opcode: 0001
  // dr:      000
  // sr1:     001
  // imm_bit:   0
  // unused:   00
  // sr2:     010
  uint16_t add = 0b0001000001000010;
  Registers registers;
  registers.R1 = 2;
  registers.R2 = 3;
  handle_instruction(add, &registers);
  munit_assert_int(registers.R0, ==, 5);
  return MUNIT_OK;
}

static MunitResult
test_add_imm(const MunitParameter params[], void* data) {
  // opcode: 0001
  // dr:      000
  // sr1:     010
  // imm_bit:   1
  // imm5:  00000
  uint16_t add = 0b0001000010101000;
  Registers registers;
  registers.R2 = 3;
  handle_instruction(add, &registers);
  munit_assert_int(registers.R0, ==, 11);
  return MUNIT_OK;
}

static MunitResult
test_and(const MunitParameter params[], void* data) {
  // opcode: 0101
  // dr:      000
  // sr1:     001
  // imm_bit:   0
  // unused:   00
  // sr2:     010
  uint16_t and = 0b0101000001000010;
  Registers registers;
  registers.R1 = 2; //010
  registers.R2 = 3; //011
  handle_instruction(and, &registers);
  munit_assert_int(registers.R0, ==, 2);
  return MUNIT_OK;
}

static MunitResult
test_and_imm(const MunitParameter params[], void* data) {
  // opcode: 0101
  // dr:      000
  // sr1:     001
  // imm_bit:   1
  // imm:   00110 == 6
  uint16_t and = 0b0101000001100110;
  Registers registers;
  registers.R1 = 2; //010
  handle_instruction(and, &registers);
  munit_assert_int(registers.R0, ==, 2);
  // 2 == 00010 & 6 = 00110 == 00010 i.e 2
  return MUNIT_OK;
}

static MunitResult
test_not(const MunitParameter params[], void* data) {
  // opcode:        1001
  // dr:             001
  // sr:             010
  // notused:     000000
  uint16_t not = 0b1001001010000000;
  Registers registers;
  registers.R2 = 8;
  handle_instruction(not, &registers);
  // 8 = 0000000000000000 NOT 0000000000001000 = 1111111111110111
  munit_assert_int(registers.R1, ==, 65527);
  return MUNIT_OK;
}

static MunitResult
test_ret(const MunitParameter params[], void* data) {
  // opcode:        1100
  // dr:             000
  // sr:             111
  // notused:     000000
  uint16_t ret = 0b1100000111000000;
  Registers registers;
  registers.R7 = 255;
  handle_instruction(ret, &registers);
  munit_assert_int(registers.PC, ==, 255);
  return MUNIT_OK;
}

static MunitResult
test_opcode_parsing(const MunitParameter params[], void* data) {
  uint16_t add = 0b0001000000000000;
  munit_assert_int(parse_opcode(add), ==, 1);
  
  uint16_t and = 0b0101000000000000;
  munit_assert_int(parse_opcode(and), ==, 5);

  return MUNIT_OK;
}

static MunitResult
test_destination_register_parsing(const MunitParameter params[], void* data) {
  uint16_t instruction = 0b1111010000000000;
  munit_assert_int(parse_destination_register(instruction), ==, 2);
  return MUNIT_OK;
}

static MunitResult
test_pc_offset_parsing(const MunitParameter params[], void* data) {
  uint16_t instruction = 0b1111010000000001;
  uint16_t PC = 0x3000;
  munit_assert_int(parse_pc_offset(instruction, PC), ==, 0x3001);
  return MUNIT_OK;
}

static MunitResult
test_is_bit_set(const MunitParameter params[], void* data) {
  uint16_t instruction = 0b1000000100100000;
  munit_assert_true(is_bit_set(instruction, 5));
  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  {(char*) "opcode_parsing", test_opcode_parsing, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*) "destination_register_parsing", test_destination_register_parsing, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*) "pc_offset_parsing", test_pc_offset_parsing, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*) "is_bit_set", test_is_bit_set, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*) "add", test_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}, 
  {(char*) "add_imm", test_add_imm, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}, 
  {(char*) "and", test_and, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}, 
  {(char*) "and_imm", test_and_imm, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}, 
  {(char*) "not", test_not, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*) "ret", test_ret, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

MunitSuite instruction_suite = {
  "instructions/",
  test_suite_tests,
  NULL,
  MUNIT_SUITE_OPTION_NONE
};