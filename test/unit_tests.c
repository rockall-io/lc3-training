#include "munit.h"

extern MunitSuite instruction_suite;
extern MunitSuite program_suite;

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
	int failed = 0;
	failed += munit_suite_main(&instruction_suite, NULL, argc, argv);
	failed += munit_suite_main(&program_suite, NULL, argc, argv);
	return failed;
}