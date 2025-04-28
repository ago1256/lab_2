#pragma once

#include"list_sequence.h"
#include "errors.h"
#include <stdexcept>

template <typename T>
class Immut_list_sequence : public List_sequence<T> {
    public:
    using List_sequence<T>::List_sequence;

    Sequence<T>* append(T item) override;
    Sequence<T>* prepend(T item) override;
    Sequence<T>* insert_at(T item, int index) override;
    Sequence<T>* remove(int index) override;
    Sequence<T>* concat(const Sequence<T>* other) const override;

    Sequence<T>* instance() override;
    Sequence<T>* clone() const override;
};


template <typename T>
Sequence<T>* Immut_list_sequence<T>::append(T item) {
    auto* copy_seq= new Immut_list_sequence<T>(*this);
    copy_seq->List_sequence<T>::append(item);
    return copy_seq;
}

template <typename T>
Sequence<T>* Immut_list_sequence<T>::prepend(T item) {
    auto* copy_seq= new Immut_list_sequence<T>(*this);
    copy_seq->List_sequence<T>::prepend(item);
    return copy_seq;
}

template <typename T>
Sequence<T>* Immut_list_sequence<T>::insert_at(T item, int ind) {
    auto* copy_seq= new Immut_list_sequence<T>(*this);
    copy_seq->List_sequence<T>::insert_at(item, ind);
    return copy_seq;
}

template <typename T>
Sequence<T>* Immut_list_sequence<T>::concat(const Sequence<T>* other) const{
    auto* new_seq = new Immut_list_sequence<T>(*this);
    new_seq->List_sequence<T>::concat(other);
    return new_seq;
}


template <typename T>
Sequence<T>* Immut_list_sequence<T>::remove(int ind) {
    auto* copy_seq= new Immut_list_sequence<T>(*this);
    copy_seq->List_sequence<T>::remove(ind);
    return copy_seq;
}


template <typename T>
Sequence<T>* Immut_list_sequence<T>::instance() {
     return this->clone(); 
    }

template <typename T>
Sequence<T>* Immut_list_sequence<T>::clone() const {
    return new Immut_list_sequence<T>(*this);
}
