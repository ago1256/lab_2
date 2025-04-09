#ifndef SEQUENCE_H
#define SEQUENCE_H

template <class T>
class Sequence{
public:
    //virtual Sequence();
    //virtual ~Sequence();

    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get_index(int ind) const = 0;
    virtual Sequence<T>* get_sub_sequence(int start_ind, int end_ind) const = 0;
    virtual int get_length() const = 0;

    virtual Sequence<T>* append(const T& item) = 0;
    virtual Sequence<T>* prepend(const T& item) = 0;
    virtual Sequence<T>* insert_at(const T& item, int ind) = 0;
    virtual Sequence<T>* concat(const Sequence<T>* seq) const = 0;


    virtual Sequence<T>* clone() const = 0;
    //virtual Sequence<T>* instance() = 0;
    virtual void print_seq() = 0;
};

#endif 