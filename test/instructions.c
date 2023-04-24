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
  handle_add_opcode(add, &registers);
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
  uint16_t add = 0b0001000010100000;
  Registers registers;
  registers.R2 = 3;
  handle_add_opcode(add, &registers);
  munit_assert_int(registers.R0, ==, 5);
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
  uint16_t instruction = 0b1000000100010000;
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
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

MunitSuite instruction_suite = {
  "instructions/",
  test_suite_tests,
  NULL,
  MUNIT_SUITE_OPTION_NONE
};