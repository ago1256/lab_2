#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include<sstream>
#include "interface.h"


int enter() {
    std::vector<Any_sequence> all_sequences;
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
                create_sequence(all_sequences); 
                break;
            }
            case 2: {
                print_all(all_sequences); 
                break; 
            }
            case 3: {
                append_to_seq(all_sequences);
                break;
            }
            case 4: {
                prepend_to_seq(all_sequences);
                break;
            }
            case 5: {
                insert_at_seq(all_sequences);
                break;
            }
            case 6: {
                remove_at_seq(all_sequences);
                break;
            }
            case 7: {
                get_sub_sequence(all_sequences);
                break;
            }
            case 8: {
                concat_sequences(all_sequences);
                break;
            }
            case 9: {
                remove_sequence(all_sequences);
                break;
            }
            case 10: {
                clean_up(all_sequences);
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
