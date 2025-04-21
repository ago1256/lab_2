#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>
#include<sstream>
#include <memory>
#include <type_traits>
#include "array_sequence.h"
#include "list_sequence.h"
#include "immut_array_sequence.h"
#include "immut_list_sequence.h"
#include "sequence.h"
#include"errors.h"

inline int error_input(int min, int max) {
    std::cout << " " << min << "-" << max << ":\n";
    int value;
    while (true) {
        if (!(std::cin >> value)) {
            errors_detection(Error::INVALID_ARGUMENT);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (value < min || value > max) {
            errors_detection(Error::INVALID_INDEX);
            continue;
        }
        return value;
    }
}
  

template<typename T>
T get_input(const std::string& prompt) {
    T value;
    std::cout << prompt;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw Error(Error::INVALID_ARGUMENT);
    }
    return value;
}


class Seq_wrapper_operations {
public:
    virtual ~Seq_wrapper_operations() = default;   
    virtual void print() const = 0;
    virtual void append_to_seq() = 0;
    virtual void prepend_to_seq() = 0;
    virtual void insert_at_seq() = 0;
    virtual void remove_at_seq() = 0;
    virtual std::shared_ptr<Seq_wrapper_operations> get_sub_sequence() const = 0;
    virtual std::shared_ptr<Seq_wrapper_operations> concat_sequences(const std::shared_ptr<Seq_wrapper_operations>& other) const = 0;
    virtual void create_seq() = 0;
};


template<typename T>
class Seq_wrapper : public Seq_wrapper_operations {
    std::shared_ptr<Sequence<T>> sequence;
    int type;

public:
    Seq_wrapper(int type) {
        switch(type){
        case 1: sequence = std::make_shared<Array_sequence<T>>(); break;
        case 2: sequence = std::make_shared<List_sequence<T>>(); break;
        case 3: sequence = std::make_shared<Immut_array_sequence<T>>(); break;
        case 4: sequence = std::make_shared<Immut_list_sequence<T>>(); break;
        }
    }

    void print() const override {
        sequence->print_seq();
        }
    
    void append_to_seq() override {
        T value = get_input<T>("Введите значение для добавления в конец: ");
        sequence->append(value);
        std::cout << "Значение добавлено\n";
    }

    void prepend_to_seq() override {
        T value = get_input<T>("Введите значение для добавления в начало: ");
        sequence->prepend(value);
        std::cout << "Значение добавлено\n";
    }

    void insert_at_seq() override {
        std::cout << "Введите индекс из диапазона ";
        int index = error_input(0, sequence->get_length() - 1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        T value = get_input<T>("Введите значение: ");
        sequence->insert_at(value, index);
        std::cout << "Значение добавлено\n";
    }

    void remove_at_seq() override {
        if (sequence->get_length() == 0) {
            throw Error(Error::EMPTY_SEQ);
        }
        std::cout << "Введите индекс из диапазона ";
        int index = error_input(0, sequence->get_length() - 1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        sequence->remove(index);
        std::cout << "Значение удалено\n";
    }

    std::shared_ptr<Seq_wrapper_operations> get_sub_sequence() const override {
        if (sequence->get_length() == 0) {
            throw Error(Error::EMPTY_SEQ);
        }
        std::cout << "Введите начальный индекс из диапазона";
        int start_index = error_input(0, sequence->get_length()-1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите конечный индекс из диапазона";
        int end_index = error_input(0, sequence->get_length()-1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        auto sub_seq = sequence->get_sub_sequence(start_index, end_index);
        sub_seq->print_seq();
        auto res = std::make_shared<Seq_wrapper<T>>(type);
        res->sequence = std::shared_ptr<Sequence<T>>(sub_seq);
        return res;
    }

    std::shared_ptr<Seq_wrapper_operations> concat_sequences(const std::shared_ptr<Seq_wrapper_operations>& other) const override {
        auto other_seq = dynamic_cast<Seq_wrapper<T>*>(other.get());
        if (!other_seq) {
            throw Error(Error::INCOMPATIBLE_TYPES);
        }
        
        auto concat_seq = sequence->concat(other_seq->sequence.get());
        concat_seq->print_seq();
        auto res = std::make_shared<Seq_wrapper<T>>(type);
        res->sequence = std::shared_ptr<Sequence<T>>(concat_seq);
        return res;
    }

    void create_seq() override {
        std::cout << "Введите значения через пробел (Enter для завершения):\n";
        if(std::cin.peek() == '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        T value;
        while (iss >> value) {
            sequence->append(value);
        }
    }
};


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