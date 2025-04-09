#ifndef LINKED_LIST_H
#define LINKED_LIST_H



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
Linked_list() {
    root = nullptr;
    size = 0;
}

Linked_list(T* items, int count) : Linked_list() {
    if(count > 0) {
        for(int i = 0; i < count; i++) {
            append(items[i]);
        }
    }
}

Linked_list(const Linked_list<T>& list) : Linked_list() {
    Node* curr = list.root;
    while(curr != nullptr) {
        append(curr->data);
        curr = curr->next;
    }
}

~Linked_list() {
    Node* cur = root;
    while(cur != nullptr) {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    root = nullptr;
    size = 0;
}

T get_first() const {
    if(root == nullptr) {
       throw std::out_of_range("пустой список");
    }
    return root->data;
}

T get_last() const {
    if(root == nullptr) {
        throw std::out_of_range("пустой список");
    }
    Node* curr = root;
    while(curr->next != nullptr) {
        curr = curr->next;
    }
    return curr->data;
}

T get(int ind) const {
    if(root == nullptr || ind < 0 || ind >= size) {
        throw std::out_of_range("неверно введен индекс");
    }
    Node* curr = root;
    for(int i = 0; i < ind; i++) {
        curr = curr->next;
    }
    return curr->data;
}

Linked_list<T>* get_sub_list(int start_ind, int end_ind) const {
    if(start_ind < 0 || start_ind >= size || end_ind < 0 || end_ind >= size) {
        throw std::out_of_range("неверно введен индекс");
    }
    Linked_list<T>* sub_list = new Linked_list<T>();
    Node* curr = root;
    for(int i = 0; i < start_ind; i++) {
        curr = curr->next;
    }
    for(int i = start_ind; i <= end_ind; i++) {
        sub_list->append(curr->data);
        curr = curr->next;
    }
    return sub_list;
}

int get_length() const {
    return size;
}

void append(T item) {
    Node* new_node = new Node{item, nullptr};
    if(root == nullptr) {
        root = new_node;
    }
    else {
        Node* curr = root;
        while(curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    size++;
}

void prepend(T item) {
    Node* new_node = new Node{item, root};
    root = new_node;
    size++;
}

void insert_at(T item, int ind) {
    if(ind < 0 || ind >= size) {
        throw std::out_of_range("неверно введен индекс");
    }
    
    if(ind == 0) {
        prepend(item);
    }
    else {
        Node* curr = root;
        for(int i = 0; i < ind-1; i++) {
            curr = curr->next;
        }
        Node* new_node = new Node{item, curr->next};
        curr->next = new_node;
        size++;
    }
}

void remove(int ind) {
    if(ind < 0 || ind >= size) throw std::out_of_range("неверно введен индекс");
    
    if(ind == 0) {
        Node* tmp = root;
        root = root->next;
        delete tmp;
    }
    else {
        Node* curr = root;
        for(int i = 0; i < ind-1; i++) {
            curr = curr->next;
        }
        Node* tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
    }
    size--;
}

Linked_list<T>* concat(Linked_list<T>* list) {
    Linked_list<T>* new_list = new Linked_list<T>(*this);
    Node* curr = list->root;
    while(curr != nullptr) {
        new_list->append(curr->data);
        curr = curr->next;
    }
    return new_list;
}

void print_list() {
    Node* curr = root;
    while(curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

Linked_list<T>& operator=(const Linked_list<T>& list1) {
    if (this != &list1) {
        ~Linked_list();
        Node* curr = list1.root;
        while (curr) {
            this->append(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}
};

#endif