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

    Sequence<T>* create_from_array(Dynamic_array<T>* array) const {
       return new Array_sequence<T>(*array);
    }

public:
Array_sequence(){
        capacity = 4;
        count = 0; 
        items = new Dynamic_array<T>(capacity);
    }

    Array_sequence(const Dynamic_array<T>& array) {
        items = new Dynamic_array<T>(array);
        count = array.get_size();
        capacity = count * 2;
    }

    Array_sequence(T* arr, int count_array) {
        count = count_array;
        capacity = count_array * 2;
        items = new Dynamic_array<T>(capacity);
        for (int i=0; i<count_array; i++) {
            items->set(i, arr[i]);
        }
    }

    Array_sequence(const Array_sequence<T>& other){
        count = other.count;
        capacity = other.capacity;
        items = new Dynamic_array<T>(*other.items);
    }


    ~Array_sequence() override {
        delete items;
    }

    T get_first() const override {
        if (get_length() == 0) throw Errors::empty_array();
        return items->get(0);
    }

    T get_last() const override {
        if (get_length() == 0) throw Errors::empty_array();
        return items->get(get_length() - 1);
    }

    T get_index(int index) const override {
        return items->get(index);
    }

    int get_length() const override {
        return count;
    }

    Sequence<T>* get_sub_sequence(int start_index, int end_index) const override {
        Dynamic_array<T>* sub = items->get_sub_array(start_index, end_index);
        return create_from_array(sub);
        
    }

    Sequence<T>* concat(Sequence<T>* other) const override {
        auto other_array = dynamic_cast<const Array_sequence<T>*>(other);
        if (!other_array) throw Errors::incompatible_types();

        int res_size = count + other_array->count;
        Dynamic_array<T>* result = new Dynamic_array<T>(res_size);
        
        for (int i = 0; i < count; i++) {
            result->set(i, items->get(i));
        }
        for (int j = 0; j < other_array->count; j++) {
            result->set(j + count, other_array->get_index(j));
        }
        
        return create_from_array(result);
    }

    Sequence<T>* append(T item) override {
        if (get_length() == capacity) {
            capacity *= 2;
            items->resize(capacity);
        }
        items->set(get_length(), item);
        count++;
        return this;
    }

    Sequence<T>* prepend(T item) override {
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

    Sequence<T>* insert_at(T item, int index) override {
        if (index < 0 || index > get_length()) throw Errors::index_out_of_range();
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

    Sequence<T>* remove(int index) override {
        if (index < 0 || index >= count) throw Errors::index_out_of_range();
        for (int i = index; i < count - 1; i++) {
            items->set(i, items->get(i + 1));
        }
        count--;
        return this;
    }
    Array_sequence<T>& operator=(const Array_sequence<T>& other) {
        if (this != &other) {
            this->clear();
            if (other.capacity > 0) {
                items = new Dynamic_array<T>(other.capacity);
                capacity = other.capacity;
            } else {
                items = nullptr;
                capacity = 0;
            }
            count = other.count;
            for (int i = 0; i < count; ++i) {
                (*items)[i] = other.items->get(i);
            }
        }
        return *this;
    }

    void print_seq() override {
        items->print_array(count);
    }

    void clear() {
        delete[] items;
        items = nullptr;
        count = 0;
        capacity = 0;
    }

    Sequence<T>* append_internal(T item) override { return append(item); }
    Sequence<T>* prepend_internal(T item) override { return prepend(item); }
    Sequence<T>* insert_at_internal(T item, int index) override { return insert_at(item, index); }

    Sequence<T>* instance() override { return this; }
    Sequence<T>* clone() const override { return new Array_sequence<T>(*this); }
};
