#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H
#include"sequence.h"
#include"dynamic_array.h"

template <class T>
class Array_sequence: public Sequence<T>{
private:
    Dynamic_array<T>* items;
    int count;
    int capacity;

public:
Array_sequence(){
    count = 0;
    capacity = 2;
    items = new Dynamic_array<T>(capacity);

}

Array_sequence(const T* data, int count1){
    count = count1;
    capacity = count1 * 2;
    items = new Dynamic_array<T>(data, capacity);
}

Array_sequence( const Array_sequence<T> &  array){
    count = array.count;
    capacity = array.capacity;
    items = new Dynamic_array<T>(*array.items);
}

~Array_sequence(){
    delete items;
}

virtual T get_first() const override{
    return items->get(0);
}

virtual T get_last() const override{
    return items->get(count - 1);
}

virtual T get_index(int ind) const override{
    return items->get(ind);
}

virtual Sequence<T>* get_sub_sequence(int start_ind, int end_ind) const override{
 
    /*if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= count) {

    }*/
    int new_count = end_ind - start_ind + 1;
    T* tmp = new T[new_count];
    for (int i = 0; i < new_count; i++) {
        tmp[i] = items->get(start_ind + i);
    }
    Array_sequence<T>* sub_seq = new Array_sequence<T>(tmp, new_count);
    delete[] tmp;
    return sub_seq;
}

virtual int get_length() const override{
    return count;
}

virtual Sequence<T>* append(const T& item) override{
    if(count == capacity){
        int new_capacity = capacity * 2;
        items->resize(new_capacity);
        capacity = new_capacity;
    }
    items->set(count, item);
    count++;
    return this;
}

virtual Sequence<T>* prepend(const T& item) override{
    if(count == capacity){
        int new_capacity = capacity * 2;
        items->resize(new_capacity);
        capacity = new_capacity;
    }
    for(int i = count; i>0; i--){
        items->set(i, items->get(i-1));
    }
    items->set(0, item);
    count++;
    return this;
}

virtual Sequence<T>* insert_at(const T& item, int ind) override{
    if(count == capacity){
        int new_capacity = capacity * 2;
        items->resize(new_capacity);
        capacity = new_capacity;
    }

    for(int i = count; i>ind; i--){
        items->set(i,items->get(i-1));
    }
    items->set(ind, item);
    count++;
    return this;
}

virtual Sequence<T>* concat(const Sequence<T>* list)const override{
    Array_sequence<T>* new_seq = new Array_sequence<T>(*this);
    for(int i=0; i < list->get_length(); i++){
        new_seq->append(list->get_index(i));
    }
    return new_seq;
}


virtual Sequence<T>* clone() const override{
    return new Array_sequence<T>(*this);
}

void print_seq(){
    items->print_array(count);
}
};

#endif
