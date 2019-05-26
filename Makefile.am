bin_PROGRAMS = tree_db
noinst_HEADERS = simple_node.h	data_node.h MurmurHash3.h udid.h node.h data_type_none.h data_type_number.h data_type_text.h data_type_time.h metadata.h lil_test/src/lil_test.h
tree_db_SOURCES = main.c simple_node.c data_node.c MurmurHash3.c udid.c node.c data_type_none.c data_type_number.c data_type_text.c data_type_time.c metadata.c
tree_db_CFLAGS = -I$(top_srcdir)/lil_test/src --std=gnu11
tree_db_LDFLAGS = -lm
