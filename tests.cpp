#include<stdio.h>
#include<iostream>
#include<assert.h>
#include"tests.h"
#include<stdexcept>


void test_linked_list_basic() {
        std::cout << "Тест базовых операций Linked_list: ";
        int arr[] = {10, 20, 30, 40};
        Linked_list<int> list(arr, 4);
    
        assert(list.get_length() == 4);
        assert(list.get_first() == 10);
        assert(list.get_last() == 40);
        assert(list.get(1) == 20);
        std::cout << "пройден\n";
 }
    
void test_linked_list_append() {
        std::cout << "Тест добавления в конец Linked_list: ";
        Linked_list<int> list;
        list.append(10);
        list.append(20);

        assert(list.get_length() == 2);
        assert(list.get_last() == 20);
        std::cout << "пройден\n";
}
    
void test_linked_list_prepend() {
        std::cout << "Тест добавления в начало Linked_list: ";
        Linked_list<int> list;
        list.prepend(10);
        list.prepend(20);

        assert(list.get_length() == 2);
        assert(list.get_first() == 20);
        std::cout << "пройден\n";
}

void test_linked_list_remove() {
        std::cout << "Тест удаления из Linked_list: ";
        int arr[] = {10, 20, 30, 40};
        Linked_list<int> list(arr, 4);

        list.remove(1);
        assert(list.get_length() == 3);
        assert(list.get(1) == 30);
        std::cout << "пройден\n";
}


void test_linked_list_errors() {
        std::cout << "Тест обработки ошибок Linked_list: ";
        Linked_list<int> empty_list;
    
        try {
            empty_list.get_first();
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 4); 
        }
    
        try {
            empty_list.get(0);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 4);
        }
    
        try {
            int arr[] = {1, 2, 3};
            Linked_list<int> list(arr, 3);
            list.get(5);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2);
        }
    
        std::cout << "пройден\n";
    }

void test_dynamic_array_basic() {
        std::cout << "Тест базовых операций Dynamic_array: ";
        int arr[] = {5, 7, 3, 6};
        Dynamic_array<int> array(arr, 4);

        assert(array.get_size() == 4);
        assert(array.get(0) == 5);
        assert(array.get(3) == 6);
        std::cout << "пройден\n";
}

void test_dynamic_array_resize() {
        std::cout << "Тест изменения размера Dynamic_array: ";
        Dynamic_array<int> array(3);
        array.resize(5);

        assert(array.get_size() == 5);
        std::cout << "пройден\n";
}

void test_dynamic_array_set() {
        std::cout << "Тест установки значений Dynamic_array: ";
        Dynamic_array<int> array(3);
        array.set(0, 10);
        array.set(1, 20);

        assert(array.get(0) == 10);
        assert(array.get(1) == 20);
        std::cout << "пройден\n";
}


void test_dynamic_array_errors() {
        std::cout << "Тест обработки ошибок Dynamic_array: ";
        Dynamic_array<int> array(3);
    
        try {
            array.get(5);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2); 
        }
    
        try {
            array.set(-1, 10);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2); 
        }
    
        std::cout << "пройден\n";
    }
    

void test_array_sequence_append() {
        std::cout << "Тест добавления в конец Array_sequence: ";
        Array_sequence<int> seq;
        seq.append(1);
        seq.append(2);

        assert(seq.get_length() == 2);
        assert(seq.get_last() == 2);
        std::cout << "пройден\n";
}

void test_array_sequence_prepend() {
        std::cout << "Тест добавления в начало Array_sequence: ";
        Array_sequence<int> seq;
        seq.prepend(1);
        seq.prepend(2);

        assert(seq.get_length() == 2);
        assert(seq.get_first() == 2);
        std::cout << "пройден\n";
}


void test_array_sequence_insert() {
        std::cout << "Тест вставки в Array_sequence: ";
        
        Array_sequence<int> seq;
        Array_sequence<int> expected;

        expected.append(1);
        expected.append(2);
        expected.append(3);
 
        seq.append(1);
        seq.append(3);
        seq.insert_at(2, 1);

        assert(seq == expected);
        assert(seq.get_length() == 3);
        
        std::cout << "пройден\n";
 }
    
void test_array_sequence_remove() {
        std::cout << "Тест удаления из Array_sequence: ";
        
        int arr[] = {4};
        Array_sequence<int> seq(arr, 1);
        Array_sequence<int> expected;
        seq.remove(0);
        assert(seq == expected);
        assert(seq.get_length() == 0);
        
        std::cout << "пройден\n";
}
    
 void test_array_sequence_subsequence() {
        std::cout << "Тест получения подпоследовательности Array_sequence: ";
        
        int arr[] = {1, 2, 3, 4};
        int sub_arr[] = {2, 3};
        Array_sequence<int> seq(arr, 4);
        Array_sequence<int> expected_sub(sub_arr, 2);
        Sequence<int>* sub = seq.get_sub_sequence(1, 2);

        Array_sequence<int>* sub_seq = dynamic_cast<Array_sequence<int>*>(sub);
        assert(sub_seq != nullptr);
        assert(*sub_seq == expected_sub);
        assert(sub->get_length() == 2);
        
        delete sub;
        std::cout << "пройден\n";
}

void test_array_sequence_errors() {
        std::cout << "Тест обработки ошибок Array_sequence: ";
        Array_sequence<int> empty_seq;
    
        try {
            empty_seq.get_first();
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 4);
        }
    
        try {
            empty_seq.get_index(4);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2); 
        }
    
        Array_sequence<int> seq;
        seq.append(1);
        try {
            seq.insert_at(2, 5);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2); 
        }
    
        try {
            seq.remove(5);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2);
        }
        std::cout << "пройден\n";
    }

void test_list_sequence_basic() {
        std::cout << "Тест базовых операций List_sequence: ";
        int arr[] = {5, 7, 3, 6};
        List_sequence<int> seq(arr, 4);
                
        assert(seq.get_length() == 4);
        assert(seq.get_first() == 5);
        assert(seq.get_last() == 6);
        assert(seq.get_index(1) == 7);
        std::cout << "пройден\n";
}

void test_list_sequence_append() {
        std::cout << "Тест добавления в конец List_sequence: ";
        List_sequence<int> seq;
        seq.append(1);
        seq.append(2);
                
        assert(seq.get_length() == 2);
        assert(seq.get_last() == 2);
        std::cout << "пройден\n";
}

void test_list_sequence_prepend() {
        std::cout << "Тест добавления в начало List_sequence: ";
        List_sequence<int> seq;
        seq.prepend(1);
        seq.prepend(2);
                
        assert(seq.get_length() == 2);
        assert(seq.get_first() == 2);
        std::cout << "пройден\n";
}

void test_list_sequence_insert() {
        std::cout << "Тест вставки в List_sequence: ";
        
        List_sequence<int> seq;
        List_sequence<int> expected;
        seq.append(1);
        seq.append(3);
        seq.insert_at(2, 1);
        expected.append(1);
        expected.append(2);
        expected.append(3);
        
        assert(seq == expected);
        assert(seq.get_length() == 3);
        
        std::cout << "пройден\n";
    }
    
    void test_list_sequence_remove() {
        std::cout << "Тест удаления из List_sequence: ";
        
        int arr[] = {1, 2, 3, 4};
        int expected_arr[] = {1, 3, 4};
        List_sequence<int> seq(arr, 4);
        List_sequence<int> expected(expected_arr, 3);
        
        seq.remove(1);
        
        assert(seq == expected);
        assert(seq.get_length() == 3);
        
        std::cout << "пройден\n";
    }
    
    void test_list_sequence_subsequence() {
        std::cout << "Тест получения подпоследовательности List_sequence: ";
        
        int arr[] = {1, 2, 3, 4};
        int sub_arr[] = {2, 3};
        List_sequence<int> seq(arr, 4);
        List_sequence<int> expected_sub(sub_arr, 2);

        Sequence<int>* sub = seq.get_sub_sequence(1, 2);
        List_sequence<int>* sub_seq = dynamic_cast<List_sequence<int>*>(sub);
        assert(sub_seq != nullptr);
        
        assert(*sub_seq == expected_sub);
        assert(sub->get_length() == 2);
        delete sub;
        std::cout << "пройден\n";
}
    
void test_list_sequence_concat() {
        std::cout << "Тест объединения List_sequence: ";
        
        int arr1[] = {1, 2};
        int arr2[] = {3, 4};
        int expected_arr[] = {1, 2, 3, 4};
        List_sequence<int> seq1(arr1, 2);
        List_sequence<int> seq2(arr2, 2);
        List_sequence<int> expected(expected_arr, 4);

        Sequence<int>* result = seq1.concat(&seq2);
        List_sequence<int>* result_seq = dynamic_cast<List_sequence<int>*>(result);
        assert(result_seq != nullptr);
        assert(*result_seq == expected);
        assert(result->get_length() == 4);
        
        delete result;
        std::cout << "пройден\n";
}

void test_list_sequence_errors() {
        std::cout << "Тест обработки ошибок List_sequence: ";
        List_sequence<int> empty_seq;
    
        try {
            empty_seq.get_first();
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 4); 
        }
    
        try {
            empty_seq.get_index(0);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 4); 
        }
    
        List_sequence<int> seq;
        seq.append(1);
        try {
            seq.insert_at(2, 5);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2); 
        }
    
        try {
            seq.remove(5);
            assert(false);
        } catch (Error e) {
            assert(e.get_code() == 2); 
        }
        std::cout << "пройден\n";
}


void test_immut_array_sequence_immutability() {
        std::cout << "Тест неизменяемости Immut_array_sequence: ";
        int arr[] = {1, 2, 3};
        Immut_array_sequence<int> seq(arr, 3);
        assert(seq.get_length() == 3);
        assert(seq.get_first() == 1);

        Sequence<int>* new_seq = seq.append(4);
        assert(new_seq->get_last() == 4);
        assert(seq.get_last() == 3);

        std::cout << "пройден\n";
}

void test_immut_list_sequence_immutability() {
        std::cout << "Тест неизменяемости Immut_list_sequence: ";
        int arr[] = {1, 2, 3};
        Immut_list_sequence<int> seq(arr, 3);
        assert(seq.get_length() == 3);
        assert(seq.get_first() == 1); 
        
        Sequence<int>* new_seq = seq.append(4);
        assert(new_seq->get_last() == 4);
        assert(seq.get_last() == 3);

        std::cout << "пройден\n";
}

int square(const int& x) {
        return x * x;
}

void test_map() {
        std::cout << "Тест map: ";
        int arr[] = {1, 2, 3, 4};
        Array_sequence<int> seq(arr, 4);

        Sequence<int>* squares = map<int, int>(static_cast<Sequence<int>*>(&seq), square);

        assert(squares->get_length() == 4);
        assert(squares->get_index(0) == 1);
        assert(squares->get_index(1) == 4);
        assert(squares->get_index(2) == 9);
        assert(squares->get_index(3) == 16);
        delete squares;
        std::cout << "пройден\n";
}

bool is_even(const int& x) { 
        return x % 2 == 0; 
}

void test_where(){
        std::cout << "Тест where: ";
        int arr[] = {1, 2, 3, 4};
        Array_sequence<int> seq(arr, 4);
        Sequence<int>* evens = where(static_cast<Sequence<int>*>(&seq), is_even); 

        assert(evens->get_length() == 2);
        assert(evens->get_index(0) == 2);
        assert(evens->get_index(1) == 4);
        delete evens;
        std::cout << "пройден\n";
}

int sum(const int& a, const int& b) { 
        return a + b; 
}

void test_reduce(){
        std::cout << "Тест reduce: ";
        int arr[] = {1, 2, 3, 4};
        Array_sequence<int> seq(arr, 4);
        int result = reduce(static_cast<Sequence<int>*>(&seq), sum, 0);
        assert(result == 10);
        std::cout << "пройден\n";
}

int main() {
        test_linked_list_basic();
        test_linked_list_append();
        test_linked_list_prepend();
        test_linked_list_remove();
        test_linked_list_errors();

        test_dynamic_array_basic();
        test_dynamic_array_resize();
        test_dynamic_array_set();
        test_dynamic_array_errors();

        test_array_sequence_append();
        test_array_sequence_prepend();
        test_array_sequence_insert();
        test_array_sequence_subsequence();
        test_array_sequence_remove();
        test_array_sequence_errors();

        test_list_sequence_basic();
        test_list_sequence_append();
        test_list_sequence_prepend();
        test_list_sequence_insert();
        test_list_sequence_remove();
        test_list_sequence_subsequence();
        test_list_sequence_concat();
        test_list_sequence_errors();

        test_immut_array_sequence_immutability();
        test_immut_list_sequence_immutability();

        test_map();
        test_where();
        test_reduce();

        std::cout << "\nВсе тесты пройдены))\n";
        return 0;
}