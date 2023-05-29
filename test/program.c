#include "lc3vm.h"

#include <stdbool.h>
#include <stdio.h>
#include "munit.h"

static MunitResult
test_can_load_program(const MunitParameter params[], void* data) {
  char * file_name_to_load = "../programs/2048.obj";
  Registers registers;
  Memory result = load_program(file_name_to_load, &registers);
  uint16_t value_at_origin = result.memory[0x3000];
  uint16_t opcode = parse_opcode(value_at_origin);
  munit_assert_int16(opcode, ==, LD);
  return MUNIT_OK;
}

static MunitResult
test_can_we_step_through_program(const MunitParameter params[], void* data) {
  char * file_name_to_load = "../programs/2048.obj";
  Registers registers;
  Memory memory = load_program(file_name_to_load, &registers);
  munit_assert_int16(registers.PC, ==, 0x3000);
  //run_program(&memory, &registers);
  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  {(char*) "can_load_program", test_can_load_program, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*) "can_we_step_through_program", test_can_we_step_through_program, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

MunitSuite program_suite = {
  "program/",
  test_suite_tests,
  NULL,
  MUNIT_SUITE_OPTION_NONE
};