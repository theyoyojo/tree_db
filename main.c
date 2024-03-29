#include <stdio.h>
#include <argp.h>
#include <lil_test.h>
#include "config.h"
#include "simple_node.h"
#include "data_node.h"
#include "data_type_none.h"
#include "metadata.h"

char help_string[] = "Hello there, user. I am " PACKAGE_STRING " but I do not do much yet" ;

static struct argp argp = { 0, 0, 0, help_string, 0, 0, 0} ;

TEST_SET(simple_node_tests,
	/* TEST_CASE(fake_test_case, */
	/* 	(void)0 ; */
	/* ) ; */
	TEST_CASE(create_simple_node,
		struct node * test = simple_node_create(NULL) ;
		node_kill(&test) ;
	) ;
	TEST_CASE(get_and_set_data,
		struct node * test = simple_node_create(NULL) ;
		ASSERT(simple_node_get_int(test) == 0) ;
		simple_node_set_int(test,4) ;
		ASSERT(simple_node_get_int(test) == 4) ;
		node_kill(&test) ;
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
		node_kill(&test) ;
	) ;
	TEST_CASE(vefify_get_set,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		// TODO
		node_kill(&test) ;
	) ;
	TEST_CASE(make_one_kill_it,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		node_kill_child(test,0,1,false) ;
		node_kill(&test) ;
	) ;
	TEST_CASE(make_two_kill_first,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		node_create_child(test, NULL) ;
		node_kill_child(test,0,1,false) ;
		node_kill(&test) ;
	) ;
	TEST_CASE(make_two_kill_second,
		struct node * test = simple_node_create(NULL) ;
		node_create_child(test, NULL) ;
		node_create_child(test, NULL) ;

		node_kill_child(test,1,1,false) ;
		ASSERT(node_get_child_count(test) == 1) ;

		node_kill(&test) ;
	) ;
	TEST_CASE(make_three_kill_second,
		struct node * test = simple_node_create(NULL) ;
		for (int i = 0; i < 3; ++i) {
			node_create_child(test, NULL) ;
		}

		/* node_print_child_linkage(test, stdout) ; */
		ASSERT(node_get_child_count(test) == 3) ;

		node_kill_child(test,1,1,false) ;
		ASSERT(node_get_child_count(test) == 2) ;
		/* node_print_child_linkage(test, stdout) ; */

		node_kill(&test) ;
	) ;
	TEST_CASE(make_three_kill_third,
		struct node * test = simple_node_create(NULL) ;
		for (int i = 0; i < 3; ++i) {
			node_create_child(test, NULL) ;
		}

		/* node_print_child_linkage(test, stdout) ; */
		ASSERT(node_get_child_count(test) == 3) ;

		node_kill_child(test,2,1,false) ;
		ASSERT(node_get_child_count(test) == 2) ;
		/* node_print_child_linkage(test, stdout) ; */

		node_kill(&test) ;
	) ;
	TEST_CASE(make_three_kill_second_and_third,
		struct node * test = simple_node_create(NULL) ;
		for (int i = 0; i < 3; ++i) {
			node_create_child(test, NULL) ;
		}

		/* node_print_child_linkage(test, stdout) ; */
		ASSERT(node_get_child_count(test) == 3) ;
		node_kill_child(test,1,2, false) ;
		/* printf("killed the children\n") ; */

		ASSERT(node_get_child_count(test) == 1) ;
		/* node_print_child_linkage(test, stdout) ; */

		node_kill(&test) ;
	) ;
	TEST_CASE(make_ten_kill_half,
		struct node * test = simple_node_create(NULL) ;

		for(int i = 0; i < 10; ++i) {
			node_create_child(test, NULL) ;
		}

		ASSERT(test->child_count == 10) ;

		/* node_print_child_linkage(test, stdout) ; */

		node_kill_child(test,2,5, false) ;
		/* printf("children count = %d\n",test->child_count) ; */
		ASSERT(test->child_count == 5) ;

		/* node_print_child_linkage(test, stdout) ; */
		node_kill(&test) ;
	) ;
	/* TEST_CASE(make_a_million_children, */
	/* 	struct node * test = simple_node_create(NULL) ; */

	/* 	for(int i = 0; i < 1000000; ++i) { */
	/* 		node_create_child(test, NULL) ; */
	/* 	} */

	/* 	ASSERT(test->child_count == 1000000) ; */

	/* 	node_kill(&test) ; */
	/* ) ; */
	TEST_CASE(delete_random_few,
		struct node * test = simple_node_create(NULL) ;
		for(int i = 0; i < 10; ++i) {
			node_create_child(test, NULL) ;
		}

		ASSERT(test->child_count == 10) ;
		ASSERT(node_verify_child_count(test)) ;

		node_kill_child(test,3,7,false) ;
		ASSERT(test->child_count == 3) ;
		ASSERT(node_verify_child_count(test)) ;

		node_kill(&test) ;
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
		node_kill_child(test,100,7,false) ;
		ASSERT(node_get_child_count(test) == 993) ;

		ASSERT(node_verify_child_count(test)) ;
		ASSERT(node_verify_sibling_integrity(test)) ;

		/* systematic murder */
		node_kill_all_children(test) ;
		ASSERT(node_get_child_count(test) == 0) ;

		ASSERT(node_verify_child_count(test)) ;
		ASSERT(node_verify_sibling_integrity(test)) ;

		node_kill(&test) ;
	) ;
	TEST_CASE(grandchildren,
		struct node * test = simple_node_create(NULL), * child ;
	
		node_create_child(test,NULL) ;
		child = node_get_child_by_index(test, 0) ;

		simple_node_set_int(child, 9) ;
		ASSERT(simple_node_get_int(child) == 9) ;

		node_kill(&test) ;
	) ;
	TEST_CASE(deep_family,
		struct node * test = simple_node_create(NULL), * child ;
		
		child = test ;
		for (int i = 0; i < 10000; ++i) {
			node_create_child(child, NULL) ;
			child = node_get_child_by_index(child, 0) ;
		}

		node_kill(&test) ;
	) ;
	TEST_CASE(compare,
		struct node * test = simple_node_create(NULL), *first, *second ;
		node_create_child(test, NULL) ;
		node_create_child(test, NULL) ;
		first = node_get_child_by_index(test, 0) ;
		second = node_get_child_by_index(test, 1) ;

		ASSERT(first->data_ops.compare(first->data,second->data) == 0) ;

		simple_node_set_int(first, 4) ;
		simple_node_set_int(second, 3) ;
		ASSERT(first->data_ops.compare(first->data,second->data) == 1) ;

		simple_node_set_int(first, 1) ;

		ASSERT(first->data_ops.compare(first->data,second->data) == -2) ;
		simple_node_set_int(second, 1) ;

		ASSERT(first->data_ops.compare(first->data,second->data) == 0) ;

		node_kill(&test) ;
	) ;
	TEST_CASE(pop_child,
		struct node * test = simple_node_create(NULL), * second_child ;
		node_create_child(test, NULL) ;
		node_create_child(test, NULL) ;

		simple_node_set_int(node_get_child_by_index(test, 1), 10) ;

		ASSERT(node_get_child_count(test) == 2) ;

		second_child = node_pop_child_by_index(test, 1) ;

		ASSERT(node_get_child_count(test) == 1) ;
		ASSERT(simple_node_get_int(second_child) == 10) ;

		/* the caller is responsible for the memory of a pop'd node */
		node_kill(&second_child) ;

		node_kill(&test) ;
	) ;
) ;

TEST_SET(data_node_basic_and_none,
	TEST_CASE(crud,
		struct node * test = data_node_create_none() ;
		node_kill(&test) ;
	) ;
	TEST_CASE(get_type_default,
		struct node * test = data_node_create_none() ;
		
		char buf[64] ;
		test->data_ops.get_string(test, buf, 64) ;
		/* printf("%s\n", buf) ; */
		ASSERT(!strncmp(buf, data_type_none_get_string_bytes(),
				data_type_none_get_string_length())) ;

		node_kill(&test) ;
	) ;
	TEST_CASE(attempt_set_none,
		struct node * test = data_node_create_none() ;
		int random_constant = 0x420beef ;
		ASSERT(!test->data_ops.set(test,&random_constant,0)) ;

		node_kill(&test) ;
	) ;
	TEST_CASE(data_is_zero,
		struct node * test = data_node_create_none() ;
		ASSERT(test->data_ops.compare(
			test->data_ops.get_bytes(test), (void *)&CONST_NONE) == 0) ;
		node_kill(&test) ;
	) ;
	TEST_CASE(size_is_correct,
		struct node * test = data_node_create_none() ;
		ASSERT(test->data_ops.get_length(test) == sizeof(none_t)) ;
		node_kill(&test) ;
	) ;
	TEST_CASE(get_hash_of_default,
		struct node * test = data_node_create_none() ;
		udid_print_value(test->udid, stdout) ;
		udid_print_table(test->udid, stdout) ;
		node_kill(&test) ;
	) ;
	TEST_CASE(swap,
		struct node * test = data_node_create_none() ;
		struct node * test2 = data_node_create_none() ;

		ASSERT(test->data_ops.swap(test->data, test2->data) == true) ;

		node_kill(&test) ;
		node_kill(&test2) ;
	) ;
) ;

char lorem_ipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam erat leo, hendrerit et orci a, congue accumsan quam. Sed sodales accumsan neque at gravida. Nam molestie ante dapibus purus convallis sollicitudin. Nulla nec leo imperdiet eros feugiat rutrum non non orci. Maecenas eu risus vitae ipsum suscipit vehicula. Nam commodo ipsum a sem semper egestas. Duis vel ante velit. Suspendisse mollis ligula sed tellus tincidunt, at mollis eros tincidunt. Sed ultrices vulputate elit et interdum. Morbi efficitur lacinia metus, sit amet laoreet leo. Etiam fermentum luctus eros." ;

TEST_SET(udid,
	TEST_CASE(random,
		char a[] = "aasdfasdfasdfasajsdkfajslkdfsjdfhalksdjfalsd" ;
		udid_t test ;
		test = udid_calculate(a, sizeof(a)) ;
	) ;
	TEST_CASE(lorem_compare,
		udid_t test, test2 ;
		test = udid_calculate(lorem_ipsum, sizeof(lorem_ipsum)) ;
		test2 = udid_calculate(lorem_ipsum, sizeof(lorem_ipsum)) ;

		ASSERT(udid_compare(test, test2) == true) ;
	) ;
	TEST_CASE(lorem_compare_different,
		udid_t test, test2 ;
		test = udid_calculate(lorem_ipsum, sizeof(lorem_ipsum)) ;
		test2 = udid_calculate(lorem_ipsum, sizeof(lorem_ipsum) - 1) ;

		ASSERT(udid_compare(test, test2) == false) ;
	) ;

	
) ;

TEST_SET(metadata,
	TEST_CASE(set_type,
		metadata_t test ;
		metadata_set_data_type(&test, DATA_TYPE_TEXT) ;
		ASSERT(metadata_get_data_type(test) == DATA_TYPE_TEXT) ;
	) ;
) ;


int main(int argc, char * argv[]) {
	argp_parse(&argp, argc, argv, 0, 0, 0) ;
	
	return 0 ;
}

