/* gcc test_mdflib.c mdflib/mdflib.c cunit/libcunit.a -o test_mdflib.exe && test_mdflib.exe */

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/TestDB.h"

#include <stdio.h>

#include "mdflib/mdflib.h"

int binary_fcompare(const char *filename1, const char *filename2)
{
   FILE *file1=NULL, *file2=NULL;
   int c1, c2;

   file1 = fopen(filename1, "rb");
   file2 = fopen(filename2, "rb");
   if( (NULL == file1) || (NULL == file2) )
   {
      return 1;
   }

   do{
      c1 = fgetc(file1);
      c2 = fgetc(file2);
   }while((c1 == c2) && (c1 != EOF) && (c2 != EOF));

   close(file1);
   close(file2);

   if(c1 != c2){
      return 1;
   }

   return 0;
}

int suite1_init_func(void){return CUE_SUCCESS;}
int suite1_cleanup_func(void){return CUE_SUCCESS;}


void test_func1(void)
{
   FILE *file;

   file = mdf_open("test_func1.mdf");
   CU_ASSERT_PTR_NOT_EQUAL_FATAL(NULL, file);
   fclose(file);
   CU_ASSERT_EQUAL(0, binary_fcompare("test_func1.mdf", "test_func1_requested.mdf"));
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
