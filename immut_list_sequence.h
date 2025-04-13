#pragma once

#include"list_sequence.h"
#include "errors.h"
#include <stdexcept>

template <typename T>
class Immut_list_sequence : public List_sequence<T> {
public:
    using List_sequence<T>::List_sequence;

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

    Sequence<T>* append_internal(T) override { throw Errors::immutable(); }
    Sequence<T>* prepend_internal(T) override { throw Errors::immutable(); }
    Sequence<T>* insert_at_internal(T, int) override { throw Errors::immutable(); }

    Sequence<T>* instance() override { return this->clone(); }
    Sequence<T>* clone() const override {
        return new Immut_list_sequence<T>(*this);
    }
};

