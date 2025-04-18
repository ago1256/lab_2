#include<stdio.h>
#include"func.h"


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
T value_typed() {
    T value;
    std::cout << "Введите значение:\n";
    if (!(std::cin >> value)) {
        throw Error(Error::INVALID_ARGUMENT);
    }
    return value;
}


template<typename F>
void dispatch_by_type(Seq_type type, F&& func) {
    static const std::unordered_map<Seq_type, std::function<void()>> type_handlers = {
        {Seq_type::INT,    [&]() { func.template operator()<int>(); }},
        {Seq_type::DOUBLE, [&]() { func.template operator()<double>(); }},
        {Seq_type::STRING, [&]() { func.template operator()<std::string>(); }},
    };

    auto it = type_handlers.find(type);
    if (it != type_handlers.end()) {
        it->second();
    } else {
        throw std::runtime_error("Неизвестный тип данных");
    }
}
template <typename T>
void add_sequence(int seq_kind, Seq_type seq_type, std::vector<Any_sequence>& all_sequences) {
    std::cout << "Введите значения через пробел (Enter для завершения): \n";
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::vector<T> values;
    T value;
    while (iss >> value) {
        values.push_back(value);
    }

    Sequence<T>* seq = nullptr;
    Any_sequence new_seq;
    new_seq.type = seq_type;

    switch (seq_kind) {
        case 1:{
            seq = new Array_sequence<T>(values.data(), values.size()); 
            new_seq.seq_kind = Seq_kind::ARRAY;
            break;
        }
        case 2:{
            seq = new List_sequence<T>(values.data(), values.size()); 
            new_seq.seq_kind = Seq_kind::LINKED_LIST;
            break;
        }
        case 3:{
            seq = new Immut_array_sequence<T>(values.data(), values.size()); 
            new_seq.seq_kind = Seq_kind::IMMUT_ARRAY;
            break;
        }
        case 4:{
             seq = new Immut_list_sequence<T>(values.data(), values.size());
             new_seq.seq_kind = Seq_kind::IMMUT_LINKED_LIST;
            break;
        }
        default: throw Error(Error::INVALID_ARGUMENT);
    }
    new_seq.ptr = static_cast<void*>(seq);
    all_sequences.push_back(new_seq);
    std::cout << "Последовательность добавлена\n";
}
   
void create_sequence(std::vector<Any_sequence>& all_sequences) {
    std::cout << "Типы последовательностей\n";
    std::cout << "1 - Изменяемый массив\n";
    std::cout << "2 - Изменяемый связный список\n";
    std::cout << "3 - Неизменяемый массив\n";
    std::cout << "4 - Неизменяемый связный список\n";
    std::cout << "Введите тип последовательности в диапазоне ";
    int type_seq = error_input(1, 4);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Тип значений последовательности\n";
    std::cout << "1 - целое\n";
    std::cout << "2 - вещественное\n";
    std::cout << "3 - строка\n";
    std::cout << "Выберите тип значений последовательности в диапазоне";
    int type_value_seq = error_input(1, 3);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch(type_value_seq) {
        case 1:
            add_sequence<int>(type_seq, Seq_type::INT, all_sequences);
            break;
        case 2:
            add_sequence<double>(type_seq, Seq_type::DOUBLE, all_sequences);
            break;
        case 3:
            add_sequence<std::string>(type_seq, Seq_type::STRING, all_sequences);
            break;
    }
}


void prepend_to_seq(std::vector<Any_sequence>& all_sequences) {
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size() - 1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (all_sequences[index].seq_kind == Seq_kind::IMMUT_LINKED_LIST || all_sequences[index].seq_kind == Seq_kind::IMMUT_ARRAY){
        throw Error(Error::IMMUT_SEQ);
    }
    auto new_seq = [&]<typename T>() {
        Sequence<T>* seq;
        convert_sequence(all_sequences[index], seq);
        T value = value_typed<T>();
        seq->prepend(value);
        all_sequences[index].ptr = static_cast<void*>(seq);

    };

    dispatch_by_type(all_sequences[index].type, new_seq);

    std::cout << "Значение добавлено\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void append_to_seq(std::vector<Any_sequence>& all_sequences) {
    if (all_sequences.empty()) throw Error(Error::EMPTY_SEQ);
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (all_sequences[index].seq_kind == Seq_kind::IMMUT_LINKED_LIST || all_sequences[index].seq_kind == Seq_kind::IMMUT_ARRAY){
        throw Error(Error::IMMUT_SEQ);
    }

    auto new_seq = [&]<typename T>() {
        Sequence<T>* seq;
        convert_sequence(all_sequences[index], seq);
        T value = value_typed<T>();
        seq->append(value);
        all_sequences[index].ptr = static_cast<void*>(seq);
    };
    dispatch_by_type(all_sequences[index].type, new_seq);
    std::cout << "Значение добавлено\n";
}

void remove_at_seq(std::vector<Any_sequence>& all_sequences) {
    if (all_sequences.empty()) throw Error(Error::EMPTY_SEQ);
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (all_sequences[index].seq_kind == Seq_kind::IMMUT_LINKED_LIST || all_sequences[index].seq_kind == Seq_kind::IMMUT_ARRAY){
        throw Error(Error::IMMUT_SEQ);
    }
    auto new_seq = [&]<typename T>() {
        Sequence<T>* seq;
        convert_sequence(all_sequences[index], seq);
        if (seq->get_length() == 0) {
        throw Error(Error::EMPTY_SEQ);
        }
        std::cout << "Введите индекс для удаления из диапазона";
        int index_value = error_input(0, seq->get_length() - 1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        seq->remove(index_value);
        all_sequences[index].ptr = static_cast<void*>(seq);
    };
    dispatch_by_type(all_sequences[index].type, new_seq);
    std::cout << "Значение добавлено\n";
}

void insert_at_seq(std::vector<Any_sequence>& all_sequences) {
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (all_sequences[index].seq_kind == Seq_kind::IMMUT_LINKED_LIST || all_sequences[index].seq_kind == Seq_kind::IMMUT_ARRAY){
        throw Error(Error::IMMUT_SEQ);
    }
    auto new_seq = [&]<typename T>() {
        Sequence<T>* seq;
        convert_sequence(all_sequences[index], seq);
        std::cout << "Введите индекс из диапазона ";
        int index_value = error_input(0, seq->get_length() - 1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        T value = value_typed<T>();
        seq->insert_at(value, index_value);
        all_sequences[index].ptr = static_cast<void*>(seq);
    };
    dispatch_by_type(all_sequences[index].type, new_seq);
    std::cout << "Значение добавлено\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void get_sub_sequence(std::vector<Any_sequence>& all_sequences) {
    if (all_sequences.empty()) throw Error(Error::EMPTY_SEQ);

    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (all_sequences[index].seq_kind == Seq_kind::IMMUT_LINKED_LIST || all_sequences[index].seq_kind == Seq_kind::IMMUT_ARRAY){
        throw Error(Error::IMMUT_SEQ);
    }
    auto new_seq = [&]<typename T>() {
        Sequence<T>* seq;
        convert_sequence(all_sequences[index], seq);
        if (seq->get_length() == 0) {
        throw Error(Error::EMPTY_SEQ);
        }
        std::cout << "Введите начальный индекс из диапазона";
        int start_index = error_input(0, seq->get_length()-1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите конечный индекс из диапазона";
        int end_index = error_input(0, seq->get_length()-1);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Sequence<T>* sub_seq = seq->get_sub_sequence(start_index, end_index);
        sub_seq->print_seq();
        std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
        int choice = error_input(0, 1);
        if (choice == 1) {
            Any_sequence new_sub_seq;
            new_sub_seq.type = all_sequences[index].type;
            new_sub_seq.seq_kind = all_sequences[index].seq_kind;
            new_sub_seq.ptr = static_cast<void*>(sub_seq);
            all_sequences.push_back(new_sub_seq);
            std::cout << "Подпоследовательность добавлена\n";
        } else {
            delete sub_seq;
        }
    };
    dispatch_by_type(all_sequences[index].type, new_seq);
}
void concat_sequences(std::vector<Any_sequence>& all_sequences) {
    std::cout << "Введите индекс 1ой последовательности из диапазона";
    int index_1 = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите индекс 2ой последовательности из диапазона";
    int index_2 = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (all_sequences[index_1].seq_kind == Seq_kind::IMMUT_LINKED_LIST || all_sequences[index_1].seq_kind == Seq_kind::IMMUT_ARRAY){
        throw Error(Error::IMMUT_SEQ);
    }
    if (all_sequences[index_2].seq_kind == Seq_kind::IMMUT_LINKED_LIST || all_sequences[index_2].seq_kind == Seq_kind::IMMUT_ARRAY){
        throw Error(Error::IMMUT_SEQ);
    }
    if (all_sequences[index_1].type != all_sequences[index_2].type || all_sequences[index_1].seq_kind != all_sequences[index_2].seq_kind) {
            throw Error(Error::INCOMPATIBLE_TYPES);
    }
    auto new_seq = [&]<typename T>() {
        Sequence<T>* seq_1;
        convert_sequence(all_sequences[index_1], seq_1);
        Sequence<T>* seq_2;
        convert_sequence(all_sequences[index_2], seq_2);
        Sequence<T>* concat_seq = seq_1->concat(seq_2);
        concat_seq->print_seq();
        std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
        int choice = error_input(0, 1);
        if (choice == 1) {
            Any_sequence new_concat_seq;
            new_concat_seq.type = all_sequences[index_1].type;
            new_concat_seq.seq_kind = all_sequences[index_1].seq_kind;
            new_concat_seq.ptr = static_cast<void*>(concat_seq);
            all_sequences.push_back(new_concat_seq);
            std::cout << "Последовательность добавлена\n";
        } else {
            delete concat_seq;
        }
    };
    dispatch_by_type(all_sequences[index_1].type, new_seq);
}

void print_all(const std::vector<Any_sequence>& all_sequences) {
    if (all_sequences.empty()) {
        std::cout << "Массив пуст\n";
        return;
    }

    auto new_seq = [](const auto& any_seq) {
        auto printer = [&]<typename T>() {
            const auto* seq = static_cast<const Sequence<T>*>(any_seq.ptr);
            seq->print_seq();
        };
        dispatch_by_type(any_seq.type, printer);
    };
    
    for (const auto& seq : all_sequences) {
        new_seq(seq);
    }
}

void remove_sequence(std::vector<Any_sequence>& all_sequences) {
    if (all_sequences.empty()) {
        std::cout << "Массив уже пуст\n";
        return;
    }
    std::cout << "Введите индекс последовательности для удаления из диапазона";
    int index = error_input(0, all_sequences.size() - 1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto new_seq = [&]<typename T>() {
        Sequence<T>* seq = static_cast<Sequence<T>*>(all_sequences[index].ptr);
        delete seq;
        all_sequences[index].ptr = nullptr;
        all_sequences.erase(all_sequences.begin() + index);
        std::cout << "Последовательность удалена\n";
    };
    dispatch_by_type(all_sequences[index].type, new_seq);
}

void clean_up(std::vector<Any_sequence>& all_sequences) {
    auto clean_seq = [](Any_sequence& any_seq) {
        auto del_seq = [&]<typename T>() {
            Sequence<T>* seq = static_cast<Sequence<T>*>(any_seq.ptr);
            delete seq;
            any_seq.ptr = nullptr;
        };
    };

    for (auto& seq : all_sequences) {
        clean_seq(seq);
    }
    all_sequences.clear();  
}
