#pragma once
#include"sequence.h"
#include<stdio.h>


enum class Seq_type { INT, DOUBLE, STRING };

enum class Seq_kind {
    ARRAY,
    LINKED_LIST,
    IMMUT_ARRAY,
    IMMUT_LINKED_LIST
};


struct Any_sequence {
    void* ptr;//указатель на последовательность
    Seq_type type; //тип данных (INT, DOUBLE, STRING)
    Seq_kind seq_kind;//вид последовательности
};

template <typename T>
void convert_sequence(Any_sequence& any_seq, Sequence<T>*& result_seq) {
    switch (any_seq.seq_kind) {
        case Seq_kind::ARRAY:
            result_seq = static_cast<Array_sequence<T>*>(any_seq.ptr);
            break;
        case Seq_kind::LINKED_LIST:
            result_seq = static_cast<List_sequence<T>*>(any_seq.ptr);
            break;
        case Seq_kind::IMMUT_ARRAY:
            result_seq = static_cast<Immut_array_sequence<T>*>(any_seq.ptr);
            break;
        case Seq_kind::IMMUT_LINKED_LIST:
            result_seq = static_cast<Immut_list_sequence<T>*>(any_seq.ptr);
            break;
        default:
            throw std::runtime_error("Неизвестный тип последовательности");
    }
}