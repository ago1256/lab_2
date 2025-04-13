#pragma once

#include"array_sequence.h"
#include "errors.h"
#include <stdexcept>

template <typename T>
class Immut_array_sequence : public Array_sequence<T> {
public:
    using Array_sequence<T>::Array_sequence;

    Sequence<T>* append(T item) override {
        return this->clone()->append_internal(item);
    }

    Sequence<T>* prepend(T item) override {
        return this->clone()->prepend_internal(item);
    }

    Sequence<T>* insert_at(T item, int index) override {
        return this->clone()->insert_at_internal(item, index);
    }

    Sequence<T>* remove(int index) override {
        return this->clone()->remove(index);
    }

    Immut_array_sequence& operator=(const Immut_array_sequence& other) {
        if (this == &other) { 
            return *this;
        }
        if (this->get_length() == 0) {
            Array_sequence<T>::operator=(other);
        } else {
            throw Errors::immutable();
        }
        return *this;
    }


    Sequence<T>* append_internal(T) override { throw Errors::immutable(); }
    Sequence<T>* prepend_internal(T) override { throw Errors::immutable(); }
    Sequence<T>* insert_at_internal(T, int) override { throw Errors::immutable(); }

    Sequence<T>* instance() override { return this->clone(); }
    Sequence<T>* clone() const override {
        return new Immut_array_sequence<T>(*this);
    }
};

