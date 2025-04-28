#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>
#include<sstream>
#include <memory>
#include <type_traits>
#include "interface.h"
#include "array_sequence.h"
#include "list_sequence.h"
#include "immut_array_sequence.h"
#include "immut_list_sequence.h"
#include "sequence.h"
#include"errors.h"


int error_input(int min, int max) {
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
T get_input() {
    T value;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw Error(Error::INVALID_ARGUMENT);
    }
    return value;
}

template<typename T>
std::vector<T> get_input_array() {
    std::vector<T> arr;
    std::cout << "Введите значения через пробел (Enter для завершения):\n";
    if(std::cin.peek() == '\n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    T value;
    while (iss >> value) {
        arr.push_back(value);
    }
    return arr;
}

class Seq_wrapper_operations {
    public:
        virtual ~Seq_wrapper_operations() = default;   
        virtual void print() const = 0;
        virtual void append_to_seq() = 0;
        virtual void prepend_to_seq() = 0;
        virtual void insert_at_seq() = 0;
        virtual void remove_at_seq() = 0;
        virtual Seq_wrapper_operations* get_sub_sequence() const = 0;
        virtual Seq_wrapper_operations* concat_sequences(Seq_wrapper_operations* other) const = 0;
        virtual void create_seq() = 0;
    };

template<typename T>
class Seq_wrapper : public Seq_wrapper_operations {
    Sequence<T>* sequence;
    int type;

public:
    Seq_wrapper(int type_seq){
        type = type_seq;
        switch(type) {
            case 1: sequence = new Array_sequence<T>(); break;
            case 2: sequence = new List_sequence<T>(); break;
            case 3: sequence = new Immut_array_sequence<T>(); break;
            case 4: sequence = new Immut_list_sequence<T>(); break;
        }
    }

    Seq_wrapper(int type_seq, const std::vector<T>& values)  {
        type = type_seq;
        T* items = new T[values.size()];
        for (size_t i = 0; i < values.size(); ++i) {
            items[i] = values[i];
        }

        switch(type) {
            case 1: 
                sequence = new Array_sequence<T>(items, values.size());
                break;
            case 2: 
                sequence = new List_sequence<T>(items, values.size());
                break;
            case 3: 
                sequence = new Immut_array_sequence<T>(items, values.size());
                break;
            case 4: 
                sequence = new Immut_list_sequence<T>(items, values.size());
                break;
        }

        delete[] items;
    }

    ~Seq_wrapper() {
        delete sequence;
    }

    void print() const override {
        sequence->print_seq();
        switch(type){
            case 1: std::cout << " Изменяемый динамический массив\n"; break;
            case 2: std::cout << " Изменяемый связный список\n"; break;
            case 3: std::cout << " Неизменяемый динамический массив\n"; break;
            case 4: std::cout << " Неизменяемый связный список\n"; break;
        }
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
    
    void append_to_seq() override {
        std::cout << "Введите значение для добавления в конец: ";
        T value = get_input<T>();
        sequence->append(value);
        std::cout << "Значение добавлено\n";
    }

    void prepend_to_seq() override {
        std::cout << "Введите значение для добавления в начало: ";
        T value = get_input<T>();
        sequence->prepend(value);
        std::cout << "Значение добавлено\n";
    }

    void insert_at_seq() override {
        std::cout << "Введите индекс из диапазона ";
        int index = error_input(0, sequence->get_length() - 1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите значение: ";
        T value = get_input<T>();
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

    Seq_wrapper_operations* get_sub_sequence() const override {
        if (sequence->get_length() == 0) {
            throw Error(Error::EMPTY_SEQ);
        }
        std::cout << "Введите начальный индекс из диапазона";
        int start_index = error_input(0, sequence->get_length()-1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите конечный индекс из диапазона";
        int end_index = error_input(0, sequence->get_length()-1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Sequence<T>* sub_seq = sequence->get_sub_sequence(start_index, end_index);
        sub_seq->print_seq();
        Seq_wrapper<T>* res = new Seq_wrapper<T>(type);
        delete res->sequence; 
        res->sequence = sub_seq;
        return res;
    }

    Seq_wrapper_operations* concat_sequences(Seq_wrapper_operations* other) const override {
        Seq_wrapper<T>* other_seq = dynamic_cast<Seq_wrapper<T>*>(other);
        if (!other_seq) {
            throw Error(Error::INCOMPATIBLE_TYPES);
        }
        if (other_seq->sequence->get_length() == 0) {
            throw Error(Error::EMPTY_SEQ);
        }
        Sequence<T>* concat_seq = sequence->concat(other_seq->sequence);
        concat_seq->print_seq();
        Seq_wrapper<T>* res = new Seq_wrapper<T>(type);
        delete res->sequence;
        res->sequence = concat_seq;
        return res;
    }
};



int enter() {
    std::vector<Seq_wrapper_operations*> all_sequences;
    while (true) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("cls"); 
        try {
            std::cout << "Действия:\n";
            std::cout << "1 Добавить новую последовательность\n";
            std::cout << "2 Вывести все последовательности\n";
            std::cout << "3 Добавить элемент в конец последовательности\n";
            std::cout << "4 Добавить элемент в начало последовательности\n";
            std::cout << "5 Добавить элемент в последовательность по индексу\n";
            std::cout << "6 Удалить элемент последовательности по индексу\n";
            std::cout << "7 Получить подпоследовательность\n";
            std::cout << "8 Конкатенация с другой последовательностью\n";
            std::cout << "9 Удалить последовательность по индексу\n";
            std::cout << "10 Выход\n";
            std::cout << "Выберите действие в диапазоне";
            
            int operation_type = error_input(1, 10);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            switch (operation_type) {
                case 1: {
                    std::cout << "Типы последовательностей\n";
                    std::cout << "1 - Изменяемый динамический массив\n";
                    std::cout << "2 - Изменяемый связный список\n";
                    std::cout << "3 - Неизменяемый динамический массив\n";
                    std::cout << "4 - Неизменяемый связный список\n";
                    std::cout << "Введите тип последовательности в диапазоне ";
                    int seq_type = error_input(1, 4);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Тип значений последовательности\n";
                    std::cout << "1 - целое\n";
                    std::cout << "2 - вещественное\n";
                    std::cout << "3 - строка\n";
                    std::cout << "4 - пользователь(имя, фамилия, возраст, телефон)\n";
                    std::cout << "Выберите тип значений последовательности в диапазоне";
                    int data_type = error_input(1, 4);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    Seq_wrapper_operations* new_seq = nullptr;
                    switch (data_type) {
                        case 1: {
                            auto values = get_input_array<int>();
                            new_seq = new Seq_wrapper<int>(seq_type, values);
                            break;
                        }
                        case 2: {
                            auto values = get_input_array<double>();
                            new_seq = new Seq_wrapper<double>(seq_type, values);
                            break;
                        }
                        case 3: {
                            auto values = get_input_array<std::string>();
                            new_seq = new Seq_wrapper<std::string>(seq_type, values);
                            break;
                        }
                        case 4: {
                            auto values = get_input_array<User>();
                            new_seq = new Seq_wrapper<User>(seq_type, values);
                            break;
                        }
                    }       
                    all_sequences.push_back(new_seq);
                    std::cout << "Последовательность добавлена\n";
                    break;
                }
                case 2: {
                    if (all_sequences.empty()) {
                        std::cout << "Массив пуст\n";
                        break;
                    }
                    for (size_t i = 0; i < all_sequences.size(); i++) {
                        all_sequences[i]->print();
                    }
                    break;
                }
                case 3: {
                    std::cout << "Введите индекс последовательности из диапазона";
                    int index = error_input(0, all_sequences.size() - 1);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    all_sequences[index]->append_to_seq();
                    break;
                }
                case 4: {
                    std::cout << "Введите индекс последовательности из диапазона";
                    int index = error_input(0, all_sequences.size() - 1);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    all_sequences[index]->prepend_to_seq();
                    break;
                }
                case 5: {
                    std::cout << "Введите индекс последовательности из диапазона";
                    int index = error_input(0, all_sequences.size() - 1);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    all_sequences[index]->insert_at_seq();
                    break;
                }
                case 6: {
                    std::cout << "Введите индекс последовательности из диапазона";
                    int index = error_input(0, all_sequences.size() - 1);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    all_sequences[index]->remove_at_seq();
                    break;
                }
                case 7: {
                    std::cout << "Введите индекс последовательности из диапазона";
                    int index = error_input(0, all_sequences.size() - 1);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Seq_wrapper_operations* sub_seq = all_sequences[index]->get_sub_sequence();
                    std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
                    int choice = error_input(0, 1);
                    if (choice == 1) {
                        all_sequences.push_back(sub_seq);
                        std::cout << "Подпоследовательность добавлена\n";
                    } else {
                        delete sub_seq; 
                    }
                    break;
                }
                case 8: {
                    std::cout << "Введите индекс 1ой последовательности из диапазона";
                    int index_1 = error_input(0, all_sequences.size()-1);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Введите индекс 2ой последовательности из диапазона";
                    int index_2 = error_input(0, all_sequences.size()-1);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Seq_wrapper_operations* concat_seq = all_sequences[index_1]->concat_sequences(all_sequences[index_2]);
                    std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
                    int choice = error_input(0, 1);
                    if (choice == 1) {
                        all_sequences.push_back(concat_seq);
                        std::cout << "Подпоследовательность добавлена\n";
                    } else {
                        delete concat_seq;
                    }
                    break;
                }
                case 9: {
                    if (all_sequences.empty()) {
                        std::cout << "Массив пуст\n";
                        break;
                    }
                    std::cout << "Введите индекс последовательности из диапазона";
                    int index = error_input(0, all_sequences.size()-1);
                    delete all_sequences[index];
                    all_sequences.erase(all_sequences.begin() + index);
                    std::cout << "Последовательность удалена\n";
                    break;
                }
                case 10: {
                    for (auto seq : all_sequences) {
                        delete seq;
                    }
                    all_sequences.clear();
                    return 0;
                }
                default: {
                    std::cout << "Неизвестная команда\n";
                    break;
                }
            }
        }
        catch(Error er) {
            errors_detection(er);
            continue;
        }
    }
}