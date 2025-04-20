#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <utility> 
#include<sstream>
#include "array_sequence.h"
#include "list_sequence.h"
#include "immut_array_sequence.h"
#include "immut_list_sequence.h"
#include "sequence.h"
#include"errors.h"


//обработка ввода
int error_input(int min, int max);

void add_sequence(std::vector<Sequence<int>*>&all_sequences);

void create_sequence(std::vector<Sequence<int>*>& all_sequences);
void prepend_to_seq(std::vector<Sequence<int>*>& all_sequences);
void append_to_seq(std::vector<Sequence<int>*>& all_sequences);
void remove_at_seq(std::vector<Sequence<int>*>& all_sequences);
void insert_at_seq(std::vector<Sequence<int>*>& all_sequences);
void get_sub_sequence(std::vector<Sequence<int>*>& all_sequences);
void concat_sequences(std::vector<Sequence<int>*>& all_sequences);
void print_all(const std::vector<Sequence<int>*>& all_sequences);
void remove_sequence(std::vector<Sequence<int>*>& all_sequences);
void clean_up(std::vector<Sequence<int>*>& all_sequences);


template <class T, class R>
Sequence<R>* map(const Sequence<T>* seq, R (*f)(const T&)) {
    Sequence<R>* result = new Array_sequence<R>();
    for (int i = 0; i < seq->get_length(); i++) {
        R val = f(seq->get_index(i));
        result->append(val);
    }
    return result;
}

template <class T>
Sequence<T>* where(const Sequence<T>* seq, bool (*predicate)(const T&)) {
    Sequence<T>* result = new  Array_sequence<T>();
    for (int i = 0; i < seq->get_length(); i++) {
        T elem = seq->get_index(i);
        if (predicate(elem)) {
            result->append(elem);
        }
    }
    return result;
}

template <class T>
T reduce(const Sequence<T>* seq, T (*f)(const T&, const T&), T start_const) {
    T c = start_const;
    for (int i = seq->get_length()-1; i >= 0; i--) {
        c = f(seq->get_index(i), c);
    }
    return c;
}