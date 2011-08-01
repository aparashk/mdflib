/* gcc test_mdflib.c cunit/libcunit.a -o test_mdflib.exe && test_mdflib.exe */

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/TestDB.h"


int suite1_init_func(void){return CUE_SUCCESS;}
int suite1_cleanup_func(void){return CUE_SUCCESS;}

void test_func1(void)
{

}

CU_TestInfo test_array1[] = {
  { "testname1", test_func1 },
  CU_TEST_INFO_NULL,
};

CU_SuiteInfo suites[] = {
  { "suitename1", suite1_init_func, suite1_cleanup_func, test_array1 },
  CU_SUITE_INFO_NULL,
};

int main()
{
   CU_initialize_registry();
   CU_register_suites(suites);
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
