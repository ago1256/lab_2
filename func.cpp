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
   
void add_sequence(std::vector<Sequence<int>*>& all_sequences) {
    std::cout << "Типы последовательностей\n";
    std::cout << "1 - Изменяемый массив\n";
    std::cout << "2 - Изменяемый связный список\n";
    std::cout << "3 - Неизменяемый массив\n";
    std::cout << "4 - Неизменяемый связный список\n";
    std::cout << "Введите тип последовательности в диапазоне ";
    int type_seq = error_input(1, 4);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите значения через пробел (Enter для завершения): \n";
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::vector<int> values;
    int value;
    while (iss >> value) {
        values.push_back(value);
    }

    Sequence<int>* seq = nullptr;
    
    switch (type_seq) {
        case 1:{
            seq = new Array_sequence<int>(values.data(), values.size()); 
            break;
        }
        case 2:{
            seq = new List_sequence<int>(values.data(), values.size()); 
            break;
        }
        case 3:{
            seq = new Immut_array_sequence<int>(values.data(), values.size()); ;
            break;
        }
        case 4:{
             seq = new Immut_list_sequence<int>(values.data(), values.size());
            break;
        }
        default: throw Error(Error::INVALID_ARGUMENT);
    }
    all_sequences.push_back(seq);
    std::cout << "Последовательность добавлена\n";

}


void prepend_to_seq(std::vector<Sequence<int>*>& all_sequences) {
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size() - 1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int value;
    std::cin >> value;
    all_sequences[index]->prepend(value);
    std::cout << "Значение добавлено\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void append_to_seq(std::vector<Sequence<int>*>& all_sequences) {
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size() - 1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int value;
    std::cin >> value;
    all_sequences[index]->append(value);
    std::cout << "Значение добавлено\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void remove_at_seq(std::vector<Sequence<int>*>& all_sequences) {
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (all_sequences[index]->get_length() == 0) {
    throw Error(Error::EMPTY_SEQ);
    }
    std::cout << "Введите индекс для удаления из диапазона";
    int index_value = error_input(0, all_sequences[index]->get_length() - 1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    all_sequences[index]->remove(index_value);
    std::cout << "Значение добавлено\n";
}

void insert_at_seq(std::vector<Sequence<int>*>& all_sequences) {
    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите индекс из диапазона ";
    int index_value = error_input(0, all_sequences[index]->get_length() - 1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int value;
    std::cin >> value;
    all_sequences[index]->insert_at(value, index_value);
    std::cout << "Значение добавлено\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void get_sub_sequence(std::vector<Sequence<int>*>& all_sequences) {
    if (all_sequences.empty()) throw Error(Error::EMPTY_SEQ);

    std::cout << "Введите индекс последовательности из диапазона";
    int index = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (all_sequences[index]->get_length() == 0) {
        throw Error(Error::EMPTY_SEQ);
        }
    std::cout << "Введите начальный индекс из диапазона";
    int start_index = error_input(0, all_sequences[index]->get_length()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите конечный индекс из диапазона";
    int end_index = error_input(0, all_sequences[index]->get_length()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Sequence<int>* sub_seq = all_sequences[index]->get_sub_sequence(start_index, end_index);
    sub_seq->print_seq();
    std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
    int choice = error_input(0, 1);
    if (choice == 1) {
        all_sequences.push_back(sub_seq);
        std::cout << "Подпоследовательность добавлена\n";
    } else {
        delete sub_seq;
    }
}

void concat_sequences(std::vector<Sequence<int>*>& all_sequences) {
    std::cout << "Введите индекс 1ой последовательности из диапазона";
    int index_1 = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите индекс 2ой последовательности из диапазона";
    int index_2 = error_input(0, all_sequences.size()-1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Sequence<int>* concat_seq = all_sequences[index_1]->concat(all_sequences[index_2]);
    concat_seq->print_seq();
    std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
    int choice = error_input(0, 1);
    if (choice == 1) {
        all_sequences.push_back(concat_seq);
        std::cout << "Последовательность добавлена\n";
    } else {
        delete concat_seq;
    }
}

void print_all(const std::vector<Sequence<int>*>& all_sequences) {
    if (all_sequences.empty()) {
        std::cout << "Массив пуст\n";
        return;
    }
    for (int i = 0; i < all_sequences.size(); i++) {
        all_sequences[i]->print_seq();
    }
}

void remove_sequence(std::vector<Sequence<int>*>& all_sequences) {
    if (all_sequences.empty()) {
        std::cout << "Массив уже пуст\n";
        return;
    }
    std::cout << "Введите индекс последовательности для удаления из диапазона";
    int index = error_input(0, all_sequences.size() - 1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        delete all_sequences[index];
        all_sequences.erase(all_sequences.begin() + index);
        std::cout << "Последовательность удалена";

}

void clean_up(std::vector<Sequence<int>*>& all_sequences){
for (auto *ptr : all_sequences) {
    delete ptr;
}
all_sequences.clear();
}
