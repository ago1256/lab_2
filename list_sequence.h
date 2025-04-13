#pragma once

#include"sequence.h"
#include"linked_list.h"
#include <stdexcept>

template <typename T>
class List_sequence : public Sequence<T> {
protected:
    Linked_list<T>* list;

    Sequence<T>* create_from_list(Linked_list<T>* list) const {
        return new List_sequence<T>(*list);
    }

public:
    List_sequence() {
        list = new Linked_list<T>();
    }

    List_sequence(T* items, int count) {
        list = new Linked_list<T>(items, count);
    }

    List_sequence(const List_sequence<T>& other) {
        list = new Linked_list<T>(*other.list);
    }

    List_sequence(const Linked_list<T>& list) {
        this->list = new Linked_list<T>(list);
    }

    ~List_sequence() override {
        delete list;
    }

    T get_first() const override { return list->get_first(); }
    T get_last() const override { return list->get_last(); }
    T get_index(int index) const override { return list->get(index); }
    int get_length() const override { return list->get_length(); }

    Sequence<T>* get_sub_sequence(int start_index, int end_index) const override {
        Linked_list<T>* sub = list->get_sub_list(start_index, end_index);
        return create_from_list(sub);
    }

    Sequence<T>* concat(Sequence<T>* other) const override {
        auto other_list = dynamic_cast<const List_sequence<T>*>(other);
        if (!other_list) throw Errors::incompatible_types();
        Linked_list<T>* result = list->concat(other_list->list);
        return create_from_list(result);
    }

    Sequence<T>* append(T item) override {
        list->append(item);
        return this;
    }

    Sequence<T>* prepend(T item) override {
        list->prepend(item);
        return this;
    }

    Sequence<T>* remove(int index) override {
        list->remove(index);
        return this;
    }

    void print_seq(){
        list->print_list();
    }
    Sequence<T>* insert_at(T item, int index) override {
        list->insert_at(item, index);
        return this;
    }

    Sequence<T>* append_internal(T item) override { return append(item); }
    Sequence<T>* prepend_internal(T item) override { return prepend(item); }
    Sequence<T>* insert_at_internal(T item, int index) override { return insert_at(item, index); }

    Sequence<T>* instance() override { return this; }
    Sequence<T>* clone() const override { return new List_sequence<T>(*this); }
};
