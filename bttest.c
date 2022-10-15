#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "btree.h"
#include "btree.c"

int init_suite(void) { 

return 0; 
}

int clean_suite(void) { 
	
return 0;
}

void btInit_deInit(void)
{
	node_t *bt = (node_t*) calloc(1, sizeof(node_t));
	
	deInitBT(bt);
}

int main()
{	
	
	if ( CUE_SUCCESS != CU_initialize_registry() )
		return CU_get_error();
 
	CU_basic_set_mode(CU_BRM_VERBOSE);
 
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("bt_test_suite", init_suite, clean_suite);
	
	if (NULL == pSuite) {
  		CU_cleanup_registry();
  		return CU_get_error();
	}

	if (( NULL == CU_add_test(pSuite, "init_deInit", btInit_deInit ))) {
			
  		CU_cleanup_registry();
  		return CU_get_error();
	}
	
  	CU_basic_run_tests();
   	CU_basic_show_failures(CU_get_failure_list());
	printf("\n");
	CU_cleanup_registry();
	
return CU_get_error();

}