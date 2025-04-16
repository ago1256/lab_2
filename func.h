#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include<sstream>
#include "array_sequence.h"
#include "list_sequence.h"
#include "immut_array_sequence.h"
#include "immut_list_sequence.h"
#include "sequence.h"
#include "interface.h"
#include"any_sequence.h"
#include"errors.h"


//обработка ввода
int error_input(int min, int max);
template<typename T> T value_typed();

//приведение типов посл-тей 
template<typename F>
void dispatch_by_type(Seq_type type, F&& func);


template <typename T>
void add_sequence(int seq_kind, Seq_type seq_type, std::vector<Any_sequence>& all_sequences);

void create_sequence(std::vector<Any_sequence>& all_sequences);
void prepend_to_seq(std::vector<Any_sequence>& all_sequences);
void append_to_seq(std::vector<Any_sequence>& all_sequences);
void remove_at_seq(std::vector<Any_sequence>& all_sequences);
void insert_at_seq(std::vector<Any_sequence>& all_sequences);
void get_sub_sequence(std::vector<Any_sequence>& all_sequences);
void concat_sequences(std::vector<Any_sequence>& all_sequences);
void print_all(const std::vector<Any_sequence>& all_sequences);
void remove_sequence(std::vector<Any_sequence>& all_sequences);
void clean_up(std::vector<Any_sequence>& all_sequences);


