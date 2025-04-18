#pragma
#include <stdio.h>
#include<assert.h>
#include"sequence.h"
#include"linked_list.h"
#include"dynamic_array.h"
#include"array_sequence.h"
#include"list_sequence.h"
#include"immut_array_sequence.h"
#include"immut_list_sequence.h"
#include"errors.h"
#include"additional_ops.h"


void test_linked_list_basic();
void test_linked_list_append();
void test_linked_list_prepend();
void test_linked_list_remove();
void test_linked_list_errors();

void test_dynamic_array_basic();
void test_dynamic_array_resize();
void test_dynamic_array_set();
void test_dynamic_array_errors();
   
void test_array_sequence_append();
void test_array_sequence_prepend();
void test_array_sequence_insert();
void test_array_sequence_subsequence();
void  test_array_sequence_remove();
void test_array_sequence_errors();

void test_list_sequence_append();
void test_list_sequence_prepend();
void test_list_sequence_insert();
void test_list_sequence_remove();
void test_list_sequence_subsequence();
void test_list_sequence_concat();
void test_list_sequence_errors();

void test_immut_array_sequence_immutability();
void test_immut_list_sequence_immutability();

void test_map();
void test_where();
void test_reduce();
