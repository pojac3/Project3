//VERY IMPORTANT CLASS THAT TELLS U HOW TO DO A LINKED LIST
/*
 * Point Implementation
 * Array Implementation
 *
 * Project Talk: you have to implement LinkedList. f(x) = 2x^5 - 3x^2 + 10x - 500
 * we will create a class called term that will store the terms of a polynomial. class term has a coefficient and an exponent variable
 * class polynomial has a linkedlist of terms
 */

#include <iostream>
using namespace std;

template <class DT>
class LinkedList {
protected:
    DT* _info;
    LinkedList<DT>* _next;
    int _size;
public:
    LinkedList();
    LinkedList(DT& i, LinkedList<DT>* n);
    virtual ~LinkedList();
    DT& operator[](int pos);
    int size();
    void add(LinkedList<DT>& newOne);
    void add(DT& other);
    void insertAt(int pos, DT& x);
    void remove();
    DT& infoAt(int pos);
    
};

template <class DT>
LinkedList<DT>::LinkedList() {
    _info = NULL;
    _next = NULL;
};

template <class DT>
LinkedList<DT>::LinkedList(DT& i, LinkedList<DT>* n) {
    _info = i;
    _next = n;
};

template <class DT>
LinkedList<DT>::~LinkedList<DT>() {
    if (_info == NULL){
        return;
    }
    else {
        delete _info;
        delete _next;
    }
}

template <class DT>
int LinkedList<DT>::size() {
    if (_info == NULL) return 0;
    return (1+(*_next).size());
};

//ADD ADDS TO THE BEGINNING OF THE LINKEDLIST

template <class DT>
void LinkedList<DT>::add(LinkedList<DT>& newOne) {
    
};

template <class DT>
void LinkedList<DT>::add(DT& other) {
    LinkedList<DT>* temp = new LinkedList<DT>(_info,_next);
    _info = new DT(other);
    _next = temp;
};

template <class DT>
void LinkedList<DT>::insertAt(int pos, DT& x) {
    if (pos == 0) {
        add(x);
    }
    else {
        (*_next).insertAt(pos-1,x);
    }
}

template <class DT>
void LinkedList<DT>::remove() {
    if (_info != NULL) {
        delete _info;
        LinkedList<DT>* temp = _next;
        _info = (*temp)._info;
        _next = (*temp)._next;
        (*temp)._info = NULL;
        (*temp)._next = NULL;
        delete temp;
    }
}

template<class DT>
DT& LinkedList<DT>::infoAt(int pos) {
    if (pos == 0) {
        return *_info;
    }
    else {
        return (*_next).infoAt(pos-1);
    }
}

template <class DT>
DT& LinkedList<DT>::operator[](int pos) {
    return infoAt(pos);
}

int main() {
    LinkedList<int>* one = new LinkedList<int>();
    LinkedList<int>* two = new LinkedList<int>();
    
    return 0;
}
