#include <stdio.h>
#include <argp.h>
#include <lil_test.h>
#include "config.h"
#include "simple_node.h"
#include "data_node.h"

char help_string[] = "Hello there, user. I am " PACKAGE_STRING " but I do not do much yet" ;

static struct argp argp = { 0, 0, 0, help_string, 0, 0, 0} ;

TEST_SET(simple_node_tests,
	/* TEST_CASE(fake_test_case, */
	/* 	(void)0 ; */
	/* ) ; */
	TEST_CASE(create_simple_node,
		struct node * test = simple_node_create(NULL) ;
		test->kill_self(&test) ;
	) ;
	TEST_CASE(get_and_set_data,
		struct node * test = simple_node_create(NULL) ;
		ASSERT(simple_node_get_data(test) == 0) ;
		simple_node_set_data(test,4) ;
		ASSERT(simple_node_get_data(test) == 4) ;
		test->kill_self(&test) ;
	) ;
	TEST_CASE(add_children,
		struct node * test = simple_node_create(NULL) ;
		ASSERT(test->child_count == 0) ;
		ASSERT(!test->first_child) ;
		node_create_child(test, NULL) ;
		ASSERT(test->child_count == 1) ;
		ASSERT(test->first_child) ;
		node_create_child(test, NULL) ;
		ASSERT(test->child_count == 2) ;
		test->kill_self(&test) ;
	) ;
	TEST_CASE(vefify_get_set,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		// TODO
		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_one_kill_it,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		node_kill_child(test,0,1) ;
		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_two_kill_first,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		node_create_child(test, NULL) ;
		node_kill_child(test,0,1) ;
		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_two_kill_second,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		node_create_child(test, NULL) ;

		node_kill_child(test,1,1) ;
		ASSERT(node_get_child_count(test) == 1) ;

		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_three_kill_second,
		struct node * test = simple_node_create(NULL) ;
		for (int i = 0; i < 3; ++i) {
			node_create_child(test, NULL) ;
		}

		/* node_print_child_linkage(test, stdout) ; */
		ASSERT(node_get_child_count(test) == 3) ;

		node_kill_child(test,1,1) ;
		ASSERT(node_get_child_count(test) == 2) ;
		/* node_print_child_linkage(test, stdout) ; */

		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_three_kill_third,
		struct node * test = simple_node_create(NULL) ;
		for (int i = 0; i < 3; ++i) {
			node_create_child(test, NULL) ;
		}

		/* node_print_child_linkage(test, stdout) ; */
		ASSERT(node_get_child_count(test) == 3) ;

		node_kill_child(test,2,1) ;
		ASSERT(node_get_child_count(test) == 2) ;
		/* node_print_child_linkage(test, stdout) ; */

		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_three_kill_second_and_third,
		struct node * test = simple_node_create(NULL) ;
		for (int i = 0; i < 3; ++i) {
			node_create_child(test, NULL) ;
		}

		/* node_print_child_linkage(test, stdout) ; */
		ASSERT(node_get_child_count(test) == 3) ;
		node_kill_child(test,1,2) ;
		/* printf("killed the children\n") ; */

		ASSERT(node_get_child_count(test) == 1) ;
		/* node_print_child_linkage(test, stdout) ; */

		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_ten_kill_half,
		struct node * test = simple_node_create(NULL) ;

		for(int i = 0; i < 10; ++i) {
			node_create_child(test, NULL) ;
		}

		ASSERT(test->child_count == 10) ;

		/* node_print_child_linkage(test, stdout) ; */

		node_kill_child(test,2,5) ;
		/* printf("children count = %d\n",test->child_count) ; */
		ASSERT(test->child_count == 5) ;

		/* node_print_child_linkage(test, stdout) ; */
		test->kill_self(&test) ;
	) ;
	/* TEST_CASE(make_a_million_children, */
	/* 	struct node * test = simple_node_create(NULL) ; */

	/* 	for(int i = 0; i < 1000000; ++i) { */
	/* 		node_create_child(test, NULL) ; */
	/* 	} */

	/* 	ASSERT(test->child_count == 1000000) ; */

	/* 	test->kill_self(&test) ; */
	/* ) ; */
	TEST_CASE(delete_random_few,
		struct node * test = simple_node_create(NULL) ;
		for(int i = 0; i < 10; ++i) {
			node_create_child(test, NULL) ;
		}

		ASSERT(test->child_count == 10) ;

		/* node_kill_child(test,3,1) ; */
		/* ASSERT(test->child_count == 9) ; */

		test->kill_self(&test) ;
	) ;
	TEST_CASE(mess_with_a_thousand_children,
		struct node * test = simple_node_create(NULL) ;

		for(int i = 0; i < 1000; ++i) {
			node_create_child(test, NULL) ;
		}

		ASSERT(node_get_child_count(test) == 1000) ;

		ASSERT(node_verify_child_count(test)) ;
		ASSERT(node_verify_sibling_integrity(test)) ;

		/* random murder */
		node_kill_child(test,100,7) ;
		ASSERT(node_get_child_count(test) == 993) ;

		ASSERT(node_verify_child_count(test)) ;
		ASSERT(node_verify_sibling_integrity(test)) ;

		/* systematic murder */
		node_kill_all_children(test) ;
		ASSERT(node_get_child_count(test) == 0) ;

		ASSERT(node_verify_child_count(test)) ;
		ASSERT(node_verify_sibling_integrity(test)) ;

		test->kill_self(&test) ;
	) ;
	TEST_CASE(grandchildren,
		struct node * test = simple_node_create(NULL), * child ;
	
		node_create_child(test,NULL) ;
		child = node_get_child_by_index(test, 0) ;

		simple_node_set_data(child, 9) ;
		ASSERT(simple_node_get_data(child) == 9) ;

		test->kill_self(&test) ;
	) ;
	TEST_CASE(deep_family,
		struct node * test = simple_node_create(NULL), * child ;
		
		child = test ;
		for (int i = 0; i < 10000; ++i) {
			node_create_child(child, NULL) ;
			child = node_get_child_by_index(child, 0) ;
		}

		test->kill_self(&test) ;
	) ;
) ;

TEST_SET(data_node_basic,
	TEST_CASE(crud,
		creation_arg_t args = (creation_arg_t){
			.metadata.data = 0,
			.data = 0,
		} ;
		struct node * test = data_node_create(&args) ;

		node_kill(&test) ;
	) ;
) ;


int main(int argc, char * argv[]) {

	argp_parse(&argp, argc, argv, 0, 0, 0) ;
	
	return 0 ;
}

