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
public:
    LinkedList(); // default constructor
    LinkedList(DT& i, LinkedList<DT>* n); // constructor
    virtual ~LinkedList(); //destructor
    DT& operator[](int pos); // square bracket operator
    int size(); // returns the size of the LinkedList
    void add(LinkedList<DT>& newOne); // adds the new LinkedList to the beginning of the list
    void add(const DT& other); // adds a new LinkedList with DT& other as the info
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
    _info = &i;
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
    if (_next == NULL) {
        if (_info == NULL) {
            return 0;
        } else {
            return 1;
        }
    }
    return 1+(*_next).size();
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
void LinkedList<DT>::add(const DT& other) {
    if (_info == NULL) {
        _info = new DT (other);
        
    } else {
        LinkedList<DT>* newOne = new LinkedList<DT>(*new DT(*_info),_next);
        *_info = other;
        _next = newOne;
    }
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
        return _next->infoAt(pos-1);
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
    setCoefficient(c);
    setExponent(e);
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
 * P O L Y N O M I A L ==================================================================================================================== P O L Y N O M I A L
 */

class Polynomial {
    friend ostream &operator << (ostream& output, Polynomial &M);
protected:
    LinkedList<Term>* myPoly;
public:
    Polynomial();
    virtual ~Polynomial ();
    int getDegree ();
    int getNumberOfTerms ();
    Term getTermAt (int i);
    int getCoefficientAt (int i);
    int getExponentAt (int i);
    bool thereExistsATermWithExponent (int e);
    Term getTermWithExponent (int e);
    int getCoefficientOfTermWithExponent (int e);
    int evaluatePoly (int x);
    bool addTerm (int c, int e);
    bool deleteTerm (int e);
    Polynomial *addPolynomial (Polynomial& M);
    Polynomial *operator+ (Polynomial& M);
    Polynomial *multiplyPolynomial(Polynomial& M);
    Polynomial *operator* (Polynomial& M);
    void printPolynomial();
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

//takes in the variable x and evaluates the polynomial as that variable
int Polynomial::evaluatePoly(int x) {
    int sum = 0;
    
    for (int i = 0; i < this->getNumberOfTerms(); i++) {
        sum += ((this->myPoly->infoAt(i).getCoefficient() * x)^this->myPoly->infoAt(i).getExponent());
    }
    
    return sum;
}

//adds a term to this polynomial
bool Polynomial::addTerm(int c, int e) {
    if (thereExistsATermWithExponent(e)) {
        this->getTermWithExponent(e).setCoefficient(getCoefficientOfTermWithExponent(e) + c);
    }
    this->myPoly->add(Term(c,e));
    return true;
}

//deletes the term with the specified coefficient and exponent from this polynomial
bool Polynomial::deleteTerm(int e) {
    return true;
}

//adds the specified polynomials together and returns the output
Polynomial* Polynomial::addPolynomial(Polynomial &M) {
    return nullptr;
}

//overloads the + operator; simply uses the addPolynomial function
Polynomial* Polynomial::operator+(Polynomial &M) {
    return this->addPolynomial(M);
}

//multiples the specified polynomials together and returns the output
Polynomial* Polynomial::multiplyPolynomial(Polynomial &M) {
    return nullptr;
}

//overloads the * operator; simply uses the multiplyPolynomial function
Polynomial* Polynomial::operator*(Polynomial &M) {
    return this->multiplyPolynomial(M);
}

//prints the specified polynomial in the format "Polynomial <polynum>: (coefficient, exponent) + ..."
void Polynomial::printPolynomial() {
    cout << this;
}

//overloads the << operator for Polynomial; uses the following format "Polynomial <polynum>: (coefficient, exponent) + ..."
ostream& operator << (ostream& output, Polynomial &M) {
    output << "(" << M.getCoefficientOfTermWithExponent(0) << ", " << 0 << ")";
    for (int i = 1; i < M.getDegree(); i++) {
        if (M.thereExistsATermWithExponent(i)) {
            output << " + (" << M.getCoefficientOfTermWithExponent(i) << ", " << i << ")";
        }
    }
    return output;
}

/**
 * M A I N  M E T H O D ================================================================================================================== M A I N  M E T H O D
 */
int main() {
    Polynomial P [10];
    char command;
    int polynum, coefficient, exponent, value, i, j;
    
    cin >> command;
    while (!cin.eof()) {
        switch (command) {
            case 'I':
                cin >> polynum >> coefficient >> exponent;
                cout << (P[polynum-1].addTerm (coefficient, exponent)) << endl;
                break;
            case 'D':
                cin >> polynum >> exponent;
                cout << (P[polynum-1].deleteTerm(exponent)) << endl;
                break;
            case 'A':
                cin >> i >> j;
                cout << (P[i-1] + P[j-1]) << endl;
                break;
            case 'M':
                cin >> i >> j;
                cout << (P[i-1] * P[j-1]) << endl;
                break;
            case 'E':
                cin >> polynum >> value;
                cout << P[polynum-1].evaluatePoly(value) << endl;
                break;
            case 'P':
                cin >> polynum;
                cout << P[polynum-1] << endl;
                break;
            default:
                cout << "I missed something" << endl;
        }
        cin >> command;
        
    }
    
    return 0;
}
