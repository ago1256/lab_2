#pragma once

#include"array_sequence.h"
#include "errors.h"
#include <stdexcept>

template <typename T>
class Immut_array_sequence : public Array_sequence<T> {
    public:
    using Array_sequence<T>::Array_sequence;

    Sequence<T>* append(T item) override;
    Sequence<T>* prepend(T item) override;
    Sequence<T>* insert_at(T item, int index) override;
    Sequence<T>* remove(int index) override;
    Sequence<T>* concat(const Sequence<T>* other) const override;

    Sequence<T>* instance() override;
    Sequence<T>* clone() const override;
};


template <typename T>
Sequence<T>* Immut_array_sequence<T>::append(T item) {
    auto* copy_seq= new Immut_array_sequence<T>(*this);
    copy_seq->Array_sequence<T>::append(item);
    return copy_seq;
}

template <typename T>
Sequence<T>* Immut_array_sequence<T>::prepend(T item) {
    auto* copy_seq= new Immut_array_sequence<T>(*this);
    copy_seq->Array_sequence<T>::prepend(item);
    return copy_seq;
}

template <typename T>
Sequence<T>* Immut_array_sequence<T>::insert_at(T item, int ind) {
    auto* copy_seq= new Immut_array_sequence<T>(*this);
    copy_seq->Array_sequence<T>::insert_at(item, ind);
    return copy_seq;
}

template <typename T>
Sequence<T>* Immut_array_sequence<T>::concat(const Sequence<T>* other) const{
    auto* new_seq= new Immut_array_sequence<T>(*this);
    new_seq->Array_sequence<T>::concat(other);
    return new_seq;
}


template <typename T>
Sequence<T>* Immut_array_sequence<T>::remove(int ind) {
    auto* copy_seq= new Immut_array_sequence<T>(*this);
    copy_seq->Array_sequence<T>::remove(ind);
    return copy_seq;
}


template <typename T>
Sequence<T>* Immut_array_sequence<T>::instance() {
     return this->clone(); 
    }

template <typename T>
Sequence<T>* Immut_array_sequence<T>::clone() const {
    return new Immut_array_sequence<T>(*this);
}
