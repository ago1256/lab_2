#pragma once

#include "errors.h"
#include<stdio.h>
#include <stdexcept>

template <class T>
class Linked_list {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
        Node(T data, Node* next) : data(data), next(next) {}
    };

    Node* root;
    int size;

public:
    Linked_list();
    Linked_list(T* items, int count);
    Linked_list(const Linked_list<T>& list);
    ~Linked_list();

    T get_first() const;
    T get_last() const;
    T get(int index) const;
    Linked_list<T>* get_sub_list(int start_index, int end_index) const;
    int get_length() const;

    void append(T item);
    void prepend(T item);
    void insert_at(T item, int index);
    void remove(int index);
    void print_list();
    Linked_list<T>* concat(Linked_list<T>* list);
};

template <class T>
Linked_list<T>::Linked_list() {
    root = nullptr;
    size = 0;
}

template <class T>
Linked_list<T>::Linked_list(T* items, int count) {
    if (count < 0) {
        throw Errors::negative_count();
    }

    if (count == 0) {
        root = nullptr;
        size = 0;
        return;
    }

    size = count;
    root = new Node{items[0], nullptr};
    Node* current = root;

    for (int i = 1; i < count; i++) {
        Node* new_node = new Node{items[i], nullptr};
        current->next = new_node;
        current = new_node;
    }
}

template <class T>
Linked_list<T>::Linked_list(const Linked_list<T>& list) {
    if (list.root == nullptr) {
        root = nullptr;
        size = 0;
        return;
    }

    root = new Node{list.root->data, nullptr};
    Node* current_this = root;
    Node* current_other = list.root->next;

    while (current_other != nullptr) {
        current_this->next = new Node{current_other->data, nullptr};
        current_this = current_this->next;
        current_other = current_other->next;
    }

    size = list.size;
}

template <class T>
Linked_list<T>::~Linked_list() {
    Node* current = root;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }    
}

template <class T>
T Linked_list<T>::get_first() const {
    if (root == nullptr) {
        throw Errors::empty_list();
    }
    return root->data;
}

template <class T>
T Linked_list<T>::get_last() const {
    if (root == nullptr) {
        throw Errors::empty_list();
    }

    Node* current = root;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current->data;
}

template <class T>
T Linked_list<T>::get(int index) const {
    if (root == nullptr) {
        throw Errors::empty_list();
    }

    if (index < 0 || index >= size) {
        throw Errors::index_out_of_range();
    }

    Node* current = root;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <class T>
Linked_list<T>* Linked_list<T>::get_sub_list(int start_index, int end_index) const {
    if (start_index < 0 || end_index >= size || start_index > end_index) {
        throw Errors::invalid_indices();
    }

    Linked_list<T>* sub_list = new Linked_list<T>();
    Node* current = root;

    for (int i = 0; i < start_index; i++) {
        current = current->next;
    }

    sub_list->append(current->data);

    for (int i = start_index + 1; i <= end_index; i++) {
        current = current->next;
        sub_list->append(current->data);
    }

    return sub_list;
}

template <class T>
int Linked_list<T>::get_length() const {
    return size;
}

template <class T>
void Linked_list<T>::append(T item) {
    Node* new_node = new Node{item, nullptr};  
    if (root == nullptr) {
        root = new_node;
    } else {
        Node* current = root;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    size++;
}

template <class T>
void Linked_list<T>::prepend(T item) {
    Node* new_node = new Node{item, root};
    root = new_node;
    size++;
}

template <class T>
void Linked_list<T>::insert_at(T item, int index) {
    if (index > size || index < 0) {
        throw Errors::index_out_of_range();
    }

    if (index == 0) {
        prepend(item);
        return;
    }

    Node* current = root;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node* new_node = new Node{item, current->next};
    current->next = new_node;
    size++;
}

template <class T>
void Linked_list<T>::remove(int index) {
    if (size == 0) return;
    
    if (index < 0 || index >= size) {
        throw Errors::index_out_of_range();
    }

    if (index == 0) {
        Node* temp = root;
        root = root->next;
        delete temp;
    } else {
        Node* current = root;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
    size--;
}
template <class T>
void Linked_list<T>::print_list(){
    Node* curr = root;
    while(curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

template <class T>
Linked_list<T>* Linked_list<T>::concat(Linked_list<T>* list) {
    if (list == nullptr) {
        throw Errors::null_list();
    }

    Linked_list<T>* result = new Linked_list<T>(*this);
    Node* current = list->root;
    while (current != nullptr) {
        result->append(current->data);
        current = current->next;
    }
    return result;  
};