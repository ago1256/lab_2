#ifndef IMMUT_LIST_SEQUENCE_H
#define IMMUT_LIST_SEQUENCE_H
#include"list_sequence.h"


template <class T>
class Immut_list_sequence : public List_sequence<T> {
public:
Immut_list_sequence() : List_sequence<T>() {}

Immut_list_sequence(T* data, int count1) : List_sequence<T>(data, count1) {}

Immut_list_sequence(const Immut_list_sequence<T>& other) : List_sequence<T>(other) {}

~Immut_list_sequence() {}

virtual Sequence<T>* append(const T& item) override{
auto* copy_seq = new Immut_list_sequence<T>(*this);
copy_seq->list->append(item);
return copy_seq;
}


virtual Sequence<T>* prepend(const T& item) override{
Immut_list_sequence<T>* copy_seq = new Immut_list_sequence<T>(*this);
copy_seq->list->prepend(item);
return copy_seq;

}

virtual Sequence<T>* insert_at(const T& item, int ind) override{
Immut_list_sequence<T>* copy_seq = new Immut_list_sequence<T>(*this);
copy_seq->list->insert_at(item, ind);
return copy_seq;

}

virtual Sequence<T>* concat(const Sequence<T>* other_seq) const override {
Immut_list_sequence<T>* new_seq = new Immut_list_sequence<T>(*this);
for (int i = 0; i < other_seq->get_length(); i++) {
    new_seq->list->append(other_seq->get_index(i));
}
return new_seq;
}

virtual Sequence<T>* clone() const override{
return new Immut_list_sequence<T>(*this);
}

};

#endif