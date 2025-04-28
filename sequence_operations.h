#include<iostream>
#include"sequence.h"
#include"array_sequence.h"



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
    Sequence<T>* result = new Array_sequence<T>();
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
