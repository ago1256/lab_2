#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H
#include"sequence.h"
#include"linked_list.h"

template <class T>
class List_sequence: public Sequence<T>{
protected:
    Linked_list<T>* list;

public:
List_sequence(){
    list = new Linked_list<T>();
}

List_sequence(T* data, int count1){
    list = new Linked_list<T>(data, count1);
}

List_sequence(const Linked_list<T> & list_copy){
    list = new Linked_list<T>(*list_copy);
}

virtual ~List_sequence(){
    delete list;
}

virtual T get_first() const override{
    return list->get_first();
}

virtual T get_last() const override{
    return list->get_last();
}

virtual T get_index(int ind) const override{
    return list->get(ind);
}

virtual Sequence<T>* get_sub_sequence(int start_ind, int end_ind) const override{
    Linked_list<T>* sub_list = list->get_sub_list(start_ind, end_ind);
    List_sequence<T>* sub_seq = new List_sequence<T>();
    //delete sub_seq->list; 
    sub_seq->list = sub_list;
    return sub_seq;
}

virtual int get_length()const override{
    return list->get_length();
}

virtual Sequence<T>* append(const T& item) override{
    list->append(item);
    return this;
}

virtual Sequence<T>* prepend(const T& item) override{
    list->prepend(item);
    return this;
}

virtual Sequence<T>* insert_at(const T& item, int ind) override{
    list->insert_at(item, ind);
    return this;
}

virtual Sequence<T>* concat(const Sequence<T>* list1)const override{
    List_sequence<T>* new_list = new List_sequence<T>(*this);
    for(int i=0; i < list1->get_length(); i++){
        new_list->append(list1->get_index(i));
    }
    return new_list;
} 



virtual Sequence<T>* clone() const override{
    return new List_sequence<T>(*this);
}

void print_seq(){
    list->print_list();
}
};

#endif