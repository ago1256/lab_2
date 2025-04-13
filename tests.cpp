#include<stdio.h>
#include<iostream>
#include<assert.h>
#include"tests.h"


void test_linked_list(){
        int arr[] = {10, 20, 30, 40};
        Linked_list<int> list(arr, 4);

        assert(list.get_length() == 4);
        assert(list.get_first() == 10);
        assert(list.get_last() == 40);
        assert(list.get(1) == 20);

        list.append(52);
        list.append(-43);
        list.remove(0);

        assert(list.get_first() == 20);
        assert(list.get_last() == -43);
        assert(list.get(3) == 52);
        list.print_list();
}

void test_dynamic_array(){
        int arr[] = {5, 7, 3, 6};
        Dynamic_array<int> array(arr, 4);

        assert(array.get_size() == 4);
        assert(array.get(0) == 5);
        assert(array.get(3) == 6);

        array.resize(6);
        array.set(4, 25);
        array.set(5, 1);

        assert(array.get_size() == 6);
        assert(array.get(4)  == 25);
        assert(array.get(5)  == 1);
        array.print_array(6);
}

void test_array_sequence(){
        Array_sequence<int> arr_seq; 
        arr_seq.append(1);
        arr_seq.append(3);
        arr_seq.append(4);
        arr_seq.append(9);
        assert(arr_seq.get_length() == 4);
        assert(arr_seq.get_first() == 1);
        assert(arr_seq.get_last() == 9);
        assert(arr_seq.get_index(2) == 4);
        arr_seq.print_seq();

        arr_seq.append(20);
        arr_seq.prepend(10);
        arr_seq.insert_at(55, 3);


        assert(arr_seq.get_length() == 7);
        assert(arr_seq.get_first() == 10);
        assert(arr_seq.get_last() == 20);
        assert(arr_seq.get_index(3) == 55);
        arr_seq.print_seq();

        Sequence<int>* sub_arr_seq = arr_seq.get_sub_sequence(1,4);
        assert(sub_arr_seq->get_length() == 4);
        assert(sub_arr_seq->get_first() == 1);
        sub_arr_seq->print_seq();
        int arr[] = {1,2,3,4};
        Array_sequence<int> arr_seq1(arr, 4); 
        arr_seq1.print_seq();
        arr_seq1.append(34);
        arr_seq1.print_seq();


}

void test_list_sequence(){
        List_sequence<int> list_seq;
        list_seq.append(3);
        list_seq.append(9);
        list_seq.append(1);
        list_seq.append(8);

        assert(list_seq.get_length() == 4);
        assert(list_seq.get_first() == 3);
        assert(list_seq.get_last() == 8);
        assert(list_seq.get_index(1) == 9);
        list_seq.print_seq();

        Sequence<int>* list_sub_seq = list_seq.get_sub_sequence(2,3);
        list_seq.prepend(22);
        list_seq.print_seq();
        list_sub_seq->print_seq();
        assert(list_sub_seq->get_first() == 1);
        assert(list_sub_seq->get_length() == 2);
        assert(list_seq.get_length() == 5);


}

void test_immut_array_sequence(){
        int arr[] = {1, 2, 3, 4};
        Immut_array_sequence<int> arr_seq(arr, 4);

        assert(arr_seq.get_length() == 4);
        assert(arr_seq.get_first() == 1);
        assert(arr_seq.get_last() == 4);
        assert(arr_seq.get_index(2) == 3);
        arr_seq.print_seq();

        Sequence<int>* arr_seq1 = arr_seq.append(5);
        assert(arr_seq1->get_length() == 5);
        assert(arr_seq1->get_last() == 5);
        arr_seq1->print_seq();
        

        assert(arr_seq.get_length() == 4);
        assert(arr_seq.get_last() == 4);

        delete arr_seq1;
        

}

void test_immut_list_sequence() {
        int arr[] = {18, 6, 13, 4};
        Immut_list_sequence<int> list_seq(arr, 4);
        assert(list_seq.get_length() == 4);
        assert(list_seq.get_first() == 18);
        assert(list_seq.get_last() == 4);
        list_seq.print_seq();
        
        /*Sequence<int>* list_seq1 = list_seq.append(5);
        list_seq1->print_seq();
        list_seq.print_seq(); 
        Sequence<int>* list_seq2 = list_seq.prepend(0);
        list_seq2->print_seq(); 
        
        
        delete list_seq1;
        delete list_seq2;*/
    }
int main(){
        test_linked_list();
        test_dynamic_array();
        test_array_sequence();
        test_list_sequence();
        test_immut_array_sequence();
        test_immut_list_sequence();


        return 0;
}