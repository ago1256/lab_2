#pragma once

#include"sequence.h"
#include"dynamic_array.h"
#include "errors.h"
#include <stdexcept>

template <typename T>
class Array_sequence : public Sequence<T> {
protected:
    Dynamic_array<T>* items;
    int count;
    int capacity;

    Sequence<T>* seq_by_arr(Dynamic_array<T>* array) const;

public:
    Array_sequence();
    Array_sequence(const Dynamic_array<T>& array);
    Array_sequence(T* arr, int count_array);
    Array_sequence(const Array_sequence<T>& other);
    ~Array_sequence() override;

    T get_first() const override;
    T get_last() const override;
    T get_index(int index) const override;
    int get_length() const override;
    Sequence<T>* get_sub_sequence(int start_index, int end_index) const override;
    Sequence<T>* concat(const Sequence<T>* other) const override;

    Sequence<T>* append(T item) override;
    Sequence<T>* prepend(T item) override;
    Sequence<T>* insert_at(T item, int index) override;
    Sequence<T>* remove(int ind) override;

    Array_sequence<T>& operator=(const Array_sequence<T>& other);
    void print_seq() const;
    void clear();

    Sequence<T>* instance() override;
    Sequence<T>* clone() const override;
    bool operator==(const Sequence<T>& other) const override;

};

template <typename T>
Sequence<T>* Array_sequence<T>::seq_by_arr(Dynamic_array<T>* array) const {
    return new Array_sequence<T>(*array);
}

template <typename T>
Array_sequence<T>::Array_sequence() {
    capacity = 4;
    count = 0; 
    items = new Dynamic_array<T>(capacity);
}

template <typename T>
Array_sequence<T>::Array_sequence(const Dynamic_array<T>& array) {
    items = new Dynamic_array<T>(array);
    count = array.get_size();
    capacity = count * 2;
}

template <typename T>
Array_sequence<T>::Array_sequence(T* arr, int count_array) {
    count = count_array;
    capacity = count_array * 2;
    items = new Dynamic_array<T>(capacity);
    for (int i = 0; i < count_array; i++) {
        items->set(i, arr[i]);
    }
}

template <typename T>
Array_sequence<T>::Array_sequence(const Array_sequence<T>& other) {
    count = other.count;
    capacity = other.capacity;
    items = new Dynamic_array<T>(*other.items);
}

template <typename T>
Array_sequence<T>::~Array_sequence() {
    delete items;
}

template <typename T>
T Array_sequence<T>::get_first() const {
    if (get_length() == 0) {
        errors_detection(Error::EMPTY_SEQ);
        throw Error(Error::EMPTY_SEQ);
    }
    return items->get(0);
}

template <typename T>
T Array_sequence<T>::get_last() const {
    return items->get(get_length() - 1);
}

template <typename T>
T Array_sequence<T>::get_index(int index) const {
    return items->get(index);
}

template <typename T>
int Array_sequence<T>::get_length() const {
    return count;
}

template <typename T>
Sequence<T>* Array_sequence<T>::get_sub_sequence(int start_index, int end_index) const {
    Dynamic_array<T>* sub = items->get_sub_array(start_index, end_index);
    return seq_by_arr(sub);
}

template <typename T>
Sequence<T>* Array_sequence<T>::concat(const Sequence<T>* other) const {
    auto other_array = dynamic_cast<const Array_sequence<T>*>(other);


    int res_size = count + other_array->count;
    Dynamic_array<T>* result = new Dynamic_array<T>(res_size);
    
    for (int i = 0; i < count; i++) {
        result->set(i, items->get(i));
    }
    for (int j = 0; j < other_array->count; j++) {
        result->set(j + count, other_array->get_index(j));
    }
    
    return seq_by_arr(result);
}

template <typename T>
Sequence<T>* Array_sequence<T>::append(T item) {
    if (get_length() == capacity) {
        capacity *= 2;
        items->resize(capacity);
    }
    items->set(get_length(), item);
    count++;
    return this;
}

template <typename T>
Sequence<T>* Array_sequence<T>::prepend(T item) {
    if (get_length() == capacity) {
        capacity *= 2;
        items->resize(capacity);
    }
    for (int i = get_length(); i > 0; i--) {
        items->set(i, items->get(i - 1));
    }
    items->set(0, item);
    count++;
    return this;
}

template <typename T>
Sequence<T>* Array_sequence<T>::insert_at(T item, int index) {
    if (get_length() == capacity) {
        capacity *= 2;
        items->resize(capacity);
    }
    for (int i = get_length(); i > index; i--) {
        items->set(i, items->get(i - 1));
    }
    items->set(index, item);
    count++;
    return this;
}

template <typename T>
Sequence<T>* Array_sequence<T>::remove(int ind) {
    if (count == 0) {
        errors_detection(Error::EMPTY_SEQ);
        throw Error(Error::EMPTY_SEQ);
    }
    if (count>0){
    items->remove(ind);
    count--;
    return this;
    }
    /////////////////////////////////////////////////////////////////
}

template <typename T>
Array_sequence<T>& Array_sequence<T>::operator=(const Array_sequence<T>& other) {
    if (this != &other) {
        this->clear();
        if (other.count > 0) {
            items = new Dynamic_array<T>(other.capacity);
            capacity = other.capacity;
            count = other.count;
        } else {
            items = nullptr;
            capacity = 0;
            count = 0;
        }
        
        for (int i = 0; i < count; ++i) {
            (*items)[i] = other.items->get(i);
        }
    }
    return *this;
}

template <typename T>
void Array_sequence<T>::print_seq() const {
    items->print_array(count);
}

template <typename T>
void Array_sequence<T>::clear() {
    delete items;
    items = nullptr;
    count = 0;
    capacity = 0;
}

template <typename T>
Sequence<T>* Array_sequence<T>::instance() {
    return this;
}

template <typename T>
Sequence<T>* Array_sequence<T>::clone() const {
    return new Array_sequence<T>(*this);
}

template <typename T>
bool Array_sequence<T>::operator==(const Sequence<T>& other) const {

    if (this->get_length() != other.get_length()) {
        return false;
    }

    for (int i = 0; i < this->get_length(); ++i) {
        if (this->get_index(i) != other.get_index(i)) {
            return false;
        }
    }
    return true;
}
