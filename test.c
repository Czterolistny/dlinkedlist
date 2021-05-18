#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <time.h>
#include "dlinklist.c"

DoubleLinkList *dl = NULL;

int init_suite(void) { 
	dl = (DoubleLinkList *) malloc(sizeof(DoubleLinkList));
return 0; 
}

int clean_suite(void) { 
	free(dl);
return 0;
}

void empty_dl_test(void)
{
	init(dl);

	CU_ASSERT_PTR_EQUAL(dl->node, NULL);
	//CU_ASSERT_PTR_EQUAL(dl->node->prev, NULL);
	//CU_ASSERT_PTR_EQUAL(dl->node->next, NULL);
	CU_ASSERT_EQUAL(get_size(dl), 0);
	CU_ASSERT_EQUAL(get_cur_pos(dl), -1);
}

#define ITEM_CNT 2000
void add_item_dl_test(void)
{
	for(int i = 0; i < ITEM_CNT; ++i){
		CU_ASSERT_EQUAL(push_end(dl, i * 10), 0);
		CU_ASSERT_PTR_NOT_EQUAL(dl->node, NULL);
		CU_ASSERT_EQUAL(get_size(dl), i + 1);
		CU_ASSERT_EQUAL(get_cur_pos(dl), 0);
	}
}

void get_item_dl_test(void)
{

	CU_ASSERT_EQUAL(get_cur_val(dl), 0);
	CU_ASSERT_EQUAL(get_cur_pos(dl), 0);
	int val;
	for(int i = 1; i < ITEM_CNT; ++i){
		CU_ASSERT_EQUAL(get_cur_pos(dl), i-1);
		CU_ASSERT_TRUE(get_next_val(dl, &val));
		CU_ASSERT_EQUAL(val, i * 10);
	}
	CU_ASSERT_FALSE(get_next_val(dl, &val));
	CU_ASSERT_EQUAL(get_cur_pos(dl), ITEM_CNT -1);

	for(int i = ITEM_CNT - 1; i > 0; --i){
		CU_ASSERT_TRUE(get_prev_val(dl, &val));
		CU_ASSERT_EQUAL(val, (i - 1) * 10);
		CU_ASSERT_EQUAL(get_cur_pos(dl), i - 1);
	}
	CU_ASSERT_FALSE(get_prev_val(dl, &val));
	CU_ASSERT_EQUAL(get_cur_pos(dl), 0);
	CU_ASSERT_EQUAL(get_size(dl), ITEM_CNT);
}

void set_pos_dl_test(void)
{
	for(int i = 0; i < ITEM_CNT; ++i){
		CU_ASSERT_EQUAL(set_pos(dl, i), 0);
		CU_ASSERT_EQUAL(get_cur_pos(dl), i);
	}
	CU_ASSERT_EQUAL(set_pos(dl, -1), -1);
	CU_ASSERT_EQUAL(set_pos(dl, ITEM_CNT), -1);
	CU_ASSERT_EQUAL(set_pos(dl, 0), 0);
	
	CU_ASSERT_EQUAL(set_pos_end(dl), 0);
	CU_ASSERT_EQUAL(get_cur_val(dl), (ITEM_CNT - 1) * 10);
	CU_ASSERT_EQUAL(set_pos_beg(dl), 0);
	CU_ASSERT_EQUAL(get_cur_val(dl), 0);
}

void random_ins_rem_dl_test(void)
{
	for(int i = 0; i < ITEM_CNT * 2; ++i){
		int idx = rand() % ITEM_CNT; 
		CU_ASSERT_EQUAL(insert_item(dl, idx, ITEM_CNT + 1), 0); 
		CU_ASSERT_EQUAL(get_size(dl), ITEM_CNT + 1);
		CU_ASSERT_EQUAL(find_item(dl, 0, ITEM_CNT + 1), idx);
		CU_ASSERT_EQUAL(remove_item(dl, idx), 0);
		CU_ASSERT_EQUAL(get_size(dl), ITEM_CNT);
		CU_ASSERT_EQUAL(find_item(dl, 0, ITEM_CNT + 1), -1);
	}
}

int main() 
{	
	
	if ( CUE_SUCCESS != CU_initialize_registry() )
		return CU_get_error();
 
	CU_basic_set_mode(CU_BRM_VERBOSE);
 
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("dl_test_suit", init_suite, clean_suite);
	
	if (NULL == pSuite) {
  		CU_cleanup_registry();
  		return CU_get_error();
	}

	if (( NULL == CU_add_test(pSuite, "empty_test", empty_dl_test )) ||
		( NULL == CU_add_test(pSuite, "add_item_test", add_item_dl_test )) ||
		( NULL == CU_add_test(pSuite, "get_item_test", get_item_dl_test )) ||
		( NULL == CU_add_test(pSuite, "set_pos_test", set_pos_dl_test )) ||
		( NULL == CU_add_test(pSuite, "rand_ins_rem_test", random_ins_rem_dl_test ))) {
			
  		CU_cleanup_registry();
  		return CU_get_error();
	}
	
  	CU_basic_run_tests();
   	CU_basic_show_failures(CU_get_failure_list());
	printf("\n");
	CU_cleanup_registry();
	
return CU_get_error();
}
