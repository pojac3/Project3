/**
 * Jacob Courtney, OUID: 113389044
 * Project 3 for Data Structures, C S 2413 at the University of Oklahoma
 */

#include <iostream>
using namespace std;

/**
 * L I N K E D  L I S T =================================================================================================================  L I N K E D  L I S T
 */
template <class DT>
class LinkedList {
protected:
    DT* _info; // the info this linked list is storing
    LinkedList<DT>* _next; // the next LinkedList in the array
    int _size; // the size of the LinkedList, from this LinkedList on
public:
    LinkedList(); // default constructor
    LinkedList(DT& i, LinkedList<DT>* n); // constructor
    virtual ~LinkedList(); //destructor
    DT& operator[](int pos); // square bracket operator
    int size(); // returns the size of the LinkedList
    void add(LinkedList<DT>& newOne); // adds the new LinkedList to the beginning of the list
    void add(DT& other); // adds a new LinkedList with DT& other as the info
    void insertAt(int pos, DT& x); // inserts a new LinkedList at the specified point in the LinkedList
    void remove(); // removes the first element of the LinkedList
    DT& infoAt(int pos); // gets the info at the specified point in the LinkedList
};

//default constructor. sets _info and _next to NULL
template <class DT>
LinkedList<DT>::LinkedList() {
    _info = NULL;
    _next = NULL;
};

//constructor. sets _info to DT& i and sets _next to the specified LinkedList
template <class DT>
LinkedList<DT>::LinkedList(DT& i, LinkedList<DT>* n) {
    _info = i;
    _next = n;
};

//deletes the LinkedList and all next values
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

//returns the size of the LinkedList
template <class DT>
int LinkedList<DT>::size() {
    if (_info == NULL) {
        return 0;
    }
    return (1+(*_next).size());
};

//adds the specified LinkedList element to the beginning of the LinkedList
template <class DT>
void LinkedList<DT>::add(LinkedList<DT>& newOne) {
    LinkedList<DT>* temp = new LinkedList<DT>(_info,_next);
    _info = new DT(newOne.info());
    _next = temp;
                   
};

//adds a new LinkedList element with _info as DT& other to the beginning of the LinkedList
template <class DT>
void LinkedList<DT>::add(DT& other) {
    LinkedList<DT>* temp = new LinkedList<DT>(_info,_next);
    _info = new DT(other);
    _next = temp;
};

//inserts an element at the specified position with info DT& x
template <class DT>
void LinkedList<DT>::insertAt(int pos, DT& x) {
    if (pos == 0) {
        add(x);
    }
    else {
        (*_next).insertAt(pos-1,x);
    }
}

//deletes the LinkedList and then rejoins the pieces
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

//gets the info at the specified position
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

/**
 * T E R M ============================================================================================================================================ T E R M
 */
class Term {
protected:
    int coefficient; // the coefficient of this term
    int exponent; // the exponent of this term
public:
    Term(); //default constructor
    Term(int c, int e); //regular constructor
    virtual ~Term(); //destructor
    int getCoefficient(); // gets the coefficient of this term
    int getExponent(); //gets the exponent of this term
    void setCoefficient(int c); // sets the coefficient of this term
    void setExponent(int e); // sets the exponent of this term
};

//default constructor. sets coefficient and exponent to 0
Term::Term() {
    setCoefficient(0);
    setExponent(0);
};

//constructor. sets coefficient to c and exponent to e
Term::Term(int c, int e) {
    coefficient = c;
    exponent = e;
};

//destructor. this basically just calls the default garbage collector
Term::~Term() {
    
};

//gets the coefficient of this term
int Term::getCoefficient() {
    return coefficient;
}

//gets the exponent of this term
int Term::getExponent() {
    return exponent;
}

//sets the coefficient of this term
void Term::setCoefficient(int c) {
    coefficient = c;
}

//sets the exponent of this term
void Term::setExponent(int e) {
    exponent = e;
}

/**
 * E X P O N E N T ============================================================================================================================ E X P O N E N T
 */

class Polynomial {
protected:
    LinkedList<Term>* myPoly;
public:
    Polynomial();
    virtual ~Polynomial();
    int getDegree();
    int getNumberOfTerms();
    Term getTermAt(int i);
    int getCoefficientAt(int i);
    int getExponentAt(int i);
    bool thereExistsATermWithExponent(int e);
    Term getTermWithExponent(int e);
    int getCoefficientOfTermWithExponent(int e);
};

//default and only constructor. Creates a polynomial with no terms
Polynomial::Polynomial() {
    myPoly = new LinkedList<Term>();
};

//destructor. just calls the default garbage collector for now
Polynomial::~Polynomial() {
    
};

//finds the degree of the polynomial and returns it
int Polynomial::getDegree() {
    int currentDegree = -1;
    for (int i = 0; i < getNumberOfTerms(); i++) {
        if (currentDegree < getExponentAt(i)) {
            currentDegree = getExponentAt(i);
        }
    }
    return currentDegree;
}

//gets the total number of terms in this polynomial
int Polynomial::getNumberOfTerms() {
    return (*myPoly).size();
}

//returns the term at the specified index
Term Polynomial::getTermAt(int i) {
    return (*myPoly).infoAt(i);
}

//returns the coefficient of the term at the specified index
int Polynomial::getCoefficientAt(int i) {
    return (*myPoly).infoAt(i).getCoefficient();
}

//returns the exponenet of the term at the specified index
int Polynomial::getExponentAt(int i) {
    return (*myPoly).infoAt(i).getExponent();
}

//returns true if there is a term with exponent e in this polynomial, false otherwise
bool Polynomial::thereExistsATermWithExponent(int e) {
    bool returnBool = false;
    for (int i = 0; i < (*myPoly).size(); i++) {
        if (getExponentAt(i) == e) {
            returnBool = true;
        }
    }
    return returnBool;
}

//gets the term object with exponent e. if one does not exist, returns a default term
Term Polynomial::getTermWithExponent(int e) {
    for (int i = 0; i < (*myPoly).size(); i++) {
        if (getExponentAt(i) == e) {
            return getTermAt(i);
        }
    }
    return Term();
}

//gets the coefficient of the term with exponent e. if one does not exist, returns 0
int Polynomial::getCoefficientOfTermWithExponent(int e) {
    for (int i = 0; i < (*myPoly).size(); i++) {
        if (getExponentAt(i) == e) {
            return getCoefficientAt(i);
        }
    }
    return 0;
}

/**
 * M A I N  M E T H O D ================================================================================================================== M A I N  M E T H O D
 */
int main() {
    
    return 0;
}
