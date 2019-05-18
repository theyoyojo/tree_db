#include <stdio.h>
#include <argp.h>
#include <lil_test.h>
#include "config.h"
#include "simple_node.h"

char help_string[] = "Hello there, user. I am " PACKAGE_STRING " but I do not do much yet" ;

static struct argp argp = { 0, 0, 0, help_string, 0, 0, 0} ;

TEST_SET(generic_node_tests,
	TEST_CASE(fake_test_case,
		(void)0 ;
	) ;
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
		ASSERT(test->children_count == 0) ;
		ASSERT(!test->children) ;
		node_create_child(test, NULL) ;
		ASSERT(test->children_count == 1) ;
		ASSERT(test->children) ;
		node_create_child(test, NULL) ;
		ASSERT(test->children_count == 2) ;
		test->kill_self(&test) ;
	) ;
	TEST_CASE(make_ten_kill_half,
		struct node * test = simple_node_create(NULL) ;

		for(int i = 0; i < 10; ++i) {
			node_create_child(test, NULL) ;
		}

		ASSERT(test->children_count == 10) ;

		node_kill_child(test,2,5) ;
		ASSERT(test->children_count == 5) ;

		test->kill_self(&test) ;
	) ;
	/* TEST_CASE(make_a_million_children, */
	/* 	struct node * test = simple_node_create(NULL) ; */

	/* 	for(int i = 0; i < 1000000; ++i) { */
	/* 		node_create_child(test, NULL) ; */
	/* 	} */

	/* 	ASSERT(test->children_count == 1000000) ; */

	/* 	test->kill_self(&test) ; */
	/* ) ; */
	TEST_CASE(delete_random_few,
		struct node * test = simple_node_create(NULL) ;
		for(int i = 0; i < 10; ++i) {
			node_create_child(test, NULL) ;
		}

		ASSERT(test->children_count == 10) ;

		/* node_kill_child(test,3,1) ; */
		/* ASSERT(test->children_count == 9) ; */

		test->kill_self(&test) ;
	) ;
	/* TEST_CASE(mess_with_a_thousand_children, */
	/* 	struct node * test = simple_node_create(NULL) ; */

	/* 	for(int i = 0; i < 1000; ++i) { */
	/* 		node_create_child(test, NULL) ; */
	/* 	} */

	/* 	ASSERT(test->children_count == 1000) ; */

	/* 	/1* random murder *1/ */
	/* 	node_kill_child(test,100,7) ; */
	/* 	ASSERT(test->children_count == 993) ; */

	/* 	/1* systematic murder *1/ */
	/* 	node_kill_all_children(test) ; */
	/* 	ASSERT(test->children_count == 0) ; */


	/* 	test->kill_self(&test) ; */
	/* ) ; */
	TEST_CASE(grandchildren,
		struct node * test = simple_node_create(NULL) ;
	
		node_create_child(test,NULL) ;
		node_create_child(test->children[0],NULL) ;

		simple_node_set_data(test->children[0],9) ;
		ASSERT(simple_node_get_data(test->children[0]) == 9) ;

		test->kill_self(&test) ;
	) ;
	

) ;


int main(int argc, char * argv[]) {

	argp_parse(&argp, argc, argv, 0, 0, 0) ;
	
	return 0 ;
}

