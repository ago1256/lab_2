#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include<stdio.h>

template <class T>
class Dynamic_array{
private:
    int size;
    T* data;
public:

Dynamic_array(const T* items, int count) {
    size = count;
    data = new T[size];
    for(int i=0; i<count; i++){
        data[i] = items[i];
    }
}

Dynamic_array(int count) {
    size = count;
    data = new T[size];
}
Dynamic_array(const Dynamic_array<T> & dynamic_array){
    size = dynamic_array.size;
    data = new T[size];
    for(int i=0; i<size; i++){
        data[i] = dynamic_array.data[i]; 
    }
}

~Dynamic_array(){
    delete [] data;
}

T get(int ind) const{
    if(ind<0 || ind>=size){
        throw std::out_of_range("неверно введен индекс");
    }
    return data[ind];
}

int get_size() const{
    return size;
}

void set(int ind, const T& value){
    if(ind<0 || ind>=size){
    throw std::out_of_range("неверно введен индекс");
    }
    data[ind] = value;
}

void resize(int new_size){
    int min_size = (size < new_size) ? size : new_size;
    T* new_data = new T[new_size];
    for(int i=0; i<min_size; i++){
        new_data[i] = data[i];
    }
    for (int i=min_size; i < new_size; i++) {
        new_data[i] = T();
    }
    delete[] data;
    data = new_data;
    size = new_size;
}

void print_array(int count){
    for(int i = 0; i<count; i++){
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}
Dynamic_array<T>& operator=(const Dynamic_array<T>& array1) {
    if (this != &array1) {
        delete[] data;
    }
    size = array1.size;
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = array1.data[i];
        }
    return *this;
}


const T& operator[](int index) const {
    /*if (index < 0 || index >= size) {
        throw std::out_of_range("DynamicArray::operator[] out of range");
    }*/
    return data[index];
}
};



#endif