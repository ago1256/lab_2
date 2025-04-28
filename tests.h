#pragma once
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
#include"sequence_operations.h"


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

void test_immut_array_sequence();
void test_immut_list_sequence();

void test_map();
void test_where();
void test_reduce();

void test_cycle_beginning(); 
void test_cycle_middle();
void test_cycle_end();
void test_empty_list();
void test_no_cycle();
void test_single_element_with_cycle();

