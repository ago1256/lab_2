#ifndef IMMUT_ARRAY_SEQUENCE_H
#define IMMUT_ARRAY_SEQUENCE_H
#include"array_sequence.h"

template <class T>
class Immut_array_sequence : public Array_sequence<T> {
public:

Immut_array_sequence() : Array_sequence<T>() {}

Immut_array_sequence(const T* data, int count1) : Array_sequence<T>(data, count1) {}

Immut_array_sequence(const Immut_array_sequence<T>& other) : Array_sequence<T>(other) {}

~Immut_array_sequence() {}
virtual Sequence<T>* append(const T& item) override{
    Immut_array_sequence<T>* copy_seq = new Immut_array_sequence<T>(*this);
    copy_seq->Array_sequence<T>::append(item);
    return copy_seq;

}

virtual Sequence<T>* prepend(const T& item) override{
    Immut_array_sequence<T>* copy_seq = new Immut_array_sequence<T>(*this);
    copy_seq->Array_sequence<T>::prepend(item);
    return copy_seq;

}

virtual Sequence<T>* insert_at(const T& item, int ind) override{
    Immut_array_sequence<T>* copy_seq = new Immut_array_sequence<T>(*this);
    copy_seq->Array_sequence<T>::insert_at(item, ind);
    return copy_seq;

}

virtual Sequence<T>* concat(const Sequence<T>* list) const override{
   Immut_array_sequence<T>* new_seq = new Immut_array_sequence<T>(*this);
    new_seq->Array_sequence<T>::concat(list);
    return new_seq;
}
virtual Sequence<T>* clone() const override{
    return new Immut_array_sequence<T>(*this);
}


};

#endif