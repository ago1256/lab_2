#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>
#include<sstream>
#include "interface.h"


int enter() {
    std::vector<std::shared_ptr<Seq_wrapper_operations>> all_sequences;
    while (true) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("cls"); 
        try{
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
                std::cout << "1 - Изменяемый массив\n";
                std::cout << "2 - Изменяемый связный список\n";
                std::cout << "3 - Неизменяемый массив\n";
                std::cout << "4 - Неизменяемый связный список\n";
                std::cout << "Введите тип последовательности в диапазоне ";
                int seq_type = error_input(1, 4);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Тип значений последовательности\n";
                std::cout << "1 - целое\n";
                std::cout << "2 - вещественное\n";
                std::cout << "3 - строка\n";
                std::cout << "Выберите тип значений последовательности в диапазоне";
                int data_type = error_input(1, 3);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            
                std::shared_ptr<Seq_wrapper_operations> new_seq;
                switch (data_type) {
                    case 1: new_seq = std::make_shared<Seq_wrapper<int>>(seq_type); break;
                    case 2: new_seq = std::make_shared<Seq_wrapper<double>>(seq_type); break;
                    case 3: new_seq = std::make_shared<Seq_wrapper<std::string>>(seq_type); break;
                }
                    
                new_seq->create_seq();
                all_sequences.push_back(new_seq);
                std::cout << "Последовательность добавлена\n";
                break;
            }
            case 2: {
                if (all_sequences.empty()) {
                    std::cout << "Массив пуст\n";
                    break;
                }
                for (size_t i = 0; i < all_sequences.size(); i++) {///////////////////++i
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
                std::shared_ptr<Seq_wrapper_operations> sub_seq = all_sequences[index]->get_sub_sequence();
                std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
                int choice = error_input(0, 1);
                if (choice == 1) {
                    all_sequences.push_back(sub_seq);
                    std::cout << "Подпоследовательность добавлена\n";
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
                std::shared_ptr<Seq_wrapper_operations> concat_seq = all_sequences[index_1]->concat_sequences(all_sequences[index_2]);
                std::cout << "Добавить эту подпоследовательность в массив? (1-Да, 0-Нет) выберите в диапазоне";
                int choice = error_input(0, 1);
                if (choice == 1) {
                    all_sequences.push_back(concat_seq);
                    std::cout << "Подпоследовательность добавлена\n";
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
                all_sequences.erase(all_sequences.begin() + index);
                std::cout << "Последовательность удалена\n";
                break;
            }
            case 10: {
                return 0;
            }
            default:{
                std::cout << "Неизвестная команда\n";
                break;
                }
            }
        }
        catch(Error er){
            errors_detection(er);
            continue;
        }
    }
}
