#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include<sstream>
#include "array_sequence.h"
#include "list_sequence.h"
#include "immut_array_sequence.h"
#include "immut_list_sequence.h"
#include "sequence.h"
#include "interface.h"
#include"any_sequence.h"

using namespace std;

int error_input(int min, int max) {
    cout  << " "<< min << "-" << max << ":\n";
    int value;
    while (true) {
        if (!(cin >> value) || value < min || value > max) {
            cout << "Неверно введено значение. Введите значение из диапазона: " << min << "-" << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else { 
            return value;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

template <typename T>
void add_sequence(int type_seq, Seq_type seq_type, vector<Any_sequence>& all_sequences) {
    Sequence<T>* seq = nullptr;
    
    switch (type_seq) {
        case 1: seq = new Array_sequence<T>(); break;
        case 2: seq = new List_sequence<T>(); break;
        case 3: seq = new Immut_array_sequence<T>(); break;
        case 4: seq = new Immut_list_sequence<T>(); break;
    }
    
    cout << "Введите значения через пробел (Enter для завершения): \n";
    string line;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    if (getline(cin, line)) {
        istringstream iss(line);
        T value;
        while (iss >> value) {
            seq = seq->append(value);
        }
    }
    
    add_sequence(seq, seq_type, all_sequences);
    cout << "Последовательность добавлена\n";
}


void remove_at_seq(vector<Any_sequence>& all_sequences){
    cout << "Введите индекс последовательности: ";
    int index = error_input(0, all_sequences.size()-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int seq_length;
    switch (all_sequences[index].type) {
        case Seq_type::INT: 
            seq_length = static_cast<Sequence<int>*>(all_sequences[index].ptr)->get_length();
            break;
        case Seq_type::DOUBLE:
            seq_length = static_cast<Sequence<double>*>(all_sequences[index].ptr)->get_length();
            break;
        case Seq_type::STRING:
            seq_length = static_cast<Sequence<string>*>(all_sequences[index].ptr)->get_length();
            break;
    }
    cout << "Введите индекс для удаления из диапазона ";
    int index_value = error_input(0, seq_length);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (all_sequences[index].type) {
        case Seq_type::INT: {
            auto* seq = static_cast<Sequence<int>*>(all_sequences[index].ptr);
            seq = seq->remove(index_value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::DOUBLE: {
            auto* seq = static_cast<Sequence<double>*>(all_sequences[index].ptr);
            seq = seq->remove(index_value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::STRING: {
            auto* seq = static_cast<Sequence<string>*>(all_sequences[index].ptr);
            cout << "Введите строку: ";
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
    }
}

void insert_at_seq(vector<Any_sequence>& all_sequences){
    cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    int seq_length;
    switch (all_sequences[index].type) {
        case Seq_type::INT: 
            seq_length = static_cast<Sequence<int>*>(all_sequences[index].ptr)->get_length();
            break;
        case Seq_type::DOUBLE:
            seq_length = static_cast<Sequence<double>*>(all_sequences[index].ptr)->get_length();
            break;
        case Seq_type::STRING:
            seq_length = static_cast<Sequence<string>*>(all_sequences[index].ptr)->get_length();
            break;
    }

    cout << "Введите индекс для вставки из диапазона";
    int index_value = error_input(0, seq_length-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (all_sequences[index].type) {
        case Seq_type::INT: {
            auto* seq = static_cast<Sequence<int>*>(all_sequences[index].ptr);
            cout << "Введите целое число: ";
            int value;
            cin >> value;
            seq = seq->insert_at(value, index_value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::DOUBLE: {
            auto* seq = static_cast<Sequence<double>*>(all_sequences[index].ptr);
            cout << "Введите вещественное число: ";
            double value;
            cin >> value;
            seq = seq->insert_at(value, index_value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::STRING: {
            auto* seq = static_cast<Sequence<string>*>(all_sequences[index].ptr);
            cout << "Введите строку: ";
            string value;
            cin >> value;
            seq = seq->insert_at(value, index_value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
    }

    cout << "Значение добавлено\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void prepend_to_seq(vector<Any_sequence>& all_sequences){
    cout << "Введите индекс последовательностииз диапазона";
    int index = error_input(0, all_sequences.size()-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (all_sequences[index].type) {
        case Seq_type::INT: {
            auto* seq = static_cast<Sequence<int>*>(all_sequences[index].ptr);
            cout << "Введите целое число: ";
            int value;
            cin >> value;
            seq = seq->prepend(value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::DOUBLE: {
            auto* seq = static_cast<Sequence<double>*>(all_sequences[index].ptr);
            cout << "Введите вещественное число: ";
            double value;
            cin >> value;
            seq = seq->prepend(value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::STRING: {
            auto* seq = static_cast<Sequence<string>*>(all_sequences[index].ptr);
            cout << "Введите строку: ";
            string value;
            cin >> value;
            seq = seq->prepend(value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
    }

    cout << "Значение добавлено\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void append_to_seq(vector<Any_sequence>& all_sequences){
    cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (all_sequences[index].type) {
        case Seq_type::INT: {
            auto* seq = static_cast<Sequence<int>*>(all_sequences[index].ptr);
            cout << "Введите целое число: ";
            int value;
            cin >> value;
            seq = seq->append(value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::DOUBLE: {
            auto* seq = static_cast<Sequence<double>*>(all_sequences[index].ptr);
            cout << "Введите вещественное число: ";
            double value;
            cin >> value;
            seq = seq->append(value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
        case Seq_type::STRING: {
            auto* seq = static_cast<Sequence<string>*>(all_sequences[index].ptr);
            cout << "Введите строку: ";
            string value;
            cin >> value;
            seq = seq->append(value);
            all_sequences[index].ptr = static_cast<void*>(seq);
            break;
        }
    }

    cout << "Значение добавлено\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void get_sub_sequence(vector<Any_sequence>& all_sequences){
    cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int seq_length;
    switch (all_sequences[index].type) {
        case Seq_type::INT: 
            seq_length = static_cast<Sequence<int>*>(all_sequences[index].ptr)->get_length();
            break;
        case Seq_type::DOUBLE:
            seq_length = static_cast<Sequence<double>*>(all_sequences[index].ptr)->get_length();
            break;
        case Seq_type::STRING:
            seq_length = static_cast<Sequence<string>*>(all_sequences[index].ptr)->get_length();
            break;
    }
    cout << "Введите начальный индекс из диапазона";
    int start_index = error_input(0, seq_length-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Введите конечный индекс из диапазона";
    int end_index = error_input(0, seq_length-1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (all_sequences[index].type) {
        case Seq_type::INT: {
            auto* seq = static_cast<Sequence<int>*>(all_sequences[index].ptr);
            auto* sub_seq = seq->get_sub_sequence(start_index, end_index);
            sub_seq->print_seq();
            
            cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите из диапазона";
            if (error_input(0, 1)) {
                all_sequences.push_back({static_cast<void*>(sub_seq), Seq_type::INT});
                cout << "Подпоследовательность добавлена\n";
            } else {
                delete sub_seq;
            }
            break;
        }
        case Seq_type::DOUBLE: {
            auto* seq = static_cast<Sequence<double>*>(all_sequences[index].ptr);
            auto* sub_seq = seq->get_sub_sequence(start_index, end_index);
            sub_seq->print_seq();
            
            cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет): ";
            if (error_input(0, 1)) {
                all_sequences.push_back({static_cast<void*>(sub_seq), Seq_type::DOUBLE});
                cout << "Подпоследовательность добавлена\n";
            } else {
                delete sub_seq;
            }
            break;
        }
        case Seq_type::STRING: {
            auto* seq = static_cast<Sequence<string>*>(all_sequences[index].ptr);
            auto* sub_seq = seq->get_sub_sequence(start_index, end_index);
            sub_seq->print_seq();
            
            cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
            if (error_input(0, 1)) {
                all_sequences.push_back({static_cast<void*>(sub_seq), Seq_type::STRING});
                cout << "Подпоследовательность добавлена\n";
            } else {
                delete sub_seq;
            }
            break;
        }
    }

}

void concat_sequences(vector<Any_sequence>& all_sequences){
    int index_1, index_2;
    bool equal_types = false;

    while (!equal_types) {
        cout << "Введите индекс 1ой последовательности из диапазона";
        index_1 = error_input(0, all_sequences.size()-1);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Введите индекс 2ой последовательности из диапазона";
        index_2 = error_input(0, all_sequences.size()-1);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (all_sequences[index_1].type != all_sequences[index_2].type) {
            cout << "Введены индексы последовательностей разных типов\n\n";
        } else {
            equal_types = true;
        }
    }
    switch (all_sequences[index_1].type) {
        case Seq_type::INT: {
            auto* seq_1 = static_cast<Sequence<int>*>(all_sequences[index_1].ptr);
            auto* seq_2 = static_cast<Sequence<int>*>(all_sequences[index_2].ptr);
            auto* concat_seq = seq_1->concat(seq_2);
            concat_seq->print_seq();
            
            cout << "Добавить эту получившуюся последовательность в массив? (1-Да, 0-Нет): ";
            if (error_input(0, 1)) {
                all_sequences.push_back({static_cast<void*>(concat_seq), Seq_type::INT});
                cout << "Последовательность добавлена\n";
            } else {
                delete concat_seq;
            }
            break;
        }
        case Seq_type::DOUBLE: {
            auto* seq_1 = static_cast<Sequence<double>*>(all_sequences[index_1].ptr);
            auto* seq_2 = static_cast<Sequence<double>*>(all_sequences[index_2].ptr);
            auto* concat_seq = seq_1->concat(seq_2);
            concat_seq->print_seq();
            
            cout << "Добавить эту получившуюся последовательность в массив? (1-Да, 0-Нет): ";
            if (error_input(0, 1)) {
                all_sequences.push_back({static_cast<void*>(concat_seq), Seq_type::DOUBLE});
                cout << "Последовательность добавлена\n";
            } else {
                delete concat_seq;
            }
            break;
        }
        case Seq_type::STRING: {
            auto* seq_1 = static_cast<Sequence<string>*>(all_sequences[index_1].ptr);
            auto* seq_2 = static_cast<Sequence<string>*>(all_sequences[index_2].ptr);
            auto* concat_seq = seq_1->concat(seq_2);
            concat_seq->print_seq();
            
            cout << "Добавить эту получившуюся последовательность в массив? (1-Да, 0-Нет): ";
            if (error_input(0, 1)) {
                all_sequences.push_back({static_cast<void*>(concat_seq), Seq_type::STRING});
                cout << "Последовательность добавлена\n";
            } else {
                delete concat_seq;
            }
            break;
            }
        }
    }

template <typename T>
void add_sequence(Sequence<T>* seq, Seq_type t, vector<Any_sequence>& all_sequences) {
    all_sequences.push_back({static_cast<void*>(seq), t});
}

void print_all(const vector<Any_sequence>& all_sequences) {
    if (all_sequences.empty()) {
        cout << "Массив пуст\n";
        return;
    }
    for (auto& any_seq : all_sequences) {
        switch (any_seq.type) {
            case Seq_type::INT: {
                auto* seq = static_cast<Sequence<int>*>(any_seq.ptr);
                seq->print_seq();
                break;
            }
            case Seq_type::DOUBLE: {
                auto* seq = static_cast<Sequence<double>*>(any_seq.ptr);
                seq->print_seq();
                break;
            }
            case Seq_type::STRING: {
                auto* seq = static_cast<Sequence<string>*>(any_seq.ptr);
                seq->print_seq();
                break;
            }
        }
    }
}
void remove_sequence(vector<Any_sequence>& all_sequences){
    if (all_sequences.empty()) {
        cout << "Массив  уже пуст\n";
        return;
    }


    cout << "Введите индекс последовательности для удаления: ";
    int index = error_input(0, all_sequences.size()-1);

    switch (all_sequences[index].type) {
        case Seq_type::INT:
            delete static_cast<Sequence<int>*>(all_sequences[index].ptr);
            break;
        case Seq_type::DOUBLE:
            delete static_cast<Sequence<double>*>(all_sequences[index].ptr);
            break;
        case Seq_type::STRING:
            delete static_cast<Sequence<string>*>(all_sequences[index].ptr);
            break;
    }
    all_sequences.erase(all_sequences.begin() + index);
    cout << "Последовательность удалена\n";
}

void clean_up(vector<Any_sequence>& all_sequences) {
    for (auto& any_seq : all_sequences) {
        switch (any_seq.type) {
            case Seq_type::INT: delete static_cast<Sequence<int>*>(any_seq.ptr); break;
            case Seq_type::DOUBLE: delete static_cast<Sequence<double>*>(any_seq.ptr); break;
            case Seq_type::STRING: delete static_cast<Sequence<string>*>(any_seq.ptr); break;
        }
    }
}




int enter(){
    vector<Any_sequence> all_sequences;

    while (1) {
    cout << "Действия:\n";
    cout<<  "1 Добавить новую последовательность\n";
    cout << "2 Вывести все последовательности\n";
    cout << "3 Добавить элемент в конец последовательности\n";
    cout << "4 Добавить элемент в начало последовательности\n";
    cout << "5 Добавить элемент в последовательность по индексу\n";
    cout << "6 Удалить элемент последовательности по индексу\n";
    cout << "7 Получить подпоследовательность\n";
    cout << "8 Конкатенация с другой последовательностью\n";
    cout << "9 Удалить последовательность по индексу\n";
    cout << "10 Выход\n";
    cout << "Выберите действие в диапазоне";
    int operation_type;
    operation_type = error_input(1,10);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    switch (operation_type) {
    case 1:{
        cout << "Типы последовательностей\n";
        cout << "1 - Изменяемый массив\n";
        cout << "2 - Изменяемый связный список\n";
        cout << "3 - Неизменяемый массив\n";
        cout << "4 - Неизменяемый связный список\n";
        cout << "Введите тип последовательности в диапазоне";
        int type_seq = error_input(1,4);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Тип значений последовательности\n";
        cout << "1 - целое\n";
        cout << "2 - вещественное\n";
        cout << "3 - строка\n";
        cout << "Выберите тип значений последовательности в диапазоне";
        int type_value_seq = error_input(1,3);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(type_value_seq) {
            case 1: 
                add_sequence<int>(type_seq, Seq_type::INT, all_sequences);
                break;
            case 2:
                add_sequence<double>(type_seq, Seq_type::DOUBLE, all_sequences);
                break;
            case 3:
                add_sequence<string>(type_seq, Seq_type::STRING, all_sequences);
                break;
        }
        break;
        }
    case 2:{
        print_all(all_sequences); 
        break; 
        }
    case 3:{
        append_to_seq(all_sequences);
        break;
        }
    case 4:{
        prepend_to_seq(all_sequences);
        break;
    }
    case 5:{
        insert_at_seq(all_sequences);
        break;
    }
    case 6:{
        remove_at_seq(all_sequences);
        break;
    }
    case 7:{
        get_sub_sequence(all_sequences);
        break;
    }
    case 8:{
        concat_sequences(all_sequences);
        break;
    }
    case 9:{
        remove_sequence(all_sequences);
        break;
    }
    case 10:{
        return 0;
    }
    }
}
}