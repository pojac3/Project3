/**
 * Jacob Courtney, OUID: 113389044
 * Project 3 for Data Structures, C S 2413 at the University of Oklahoma
 */

#include <iostream>
using namespace std;

/**
 * L I N K E D  L I S T =================================================================================================================  L I N K E D  L I S T
 * Some algorithms were taken from "Data Structures for C++ by Sridhar Radhakrishnan"
 */

template <class DT>
class LinkedList {
protected:
    DT* _info; // the info this linked list is storing
    LinkedList<DT>* _next; // the next LinkedList in the array
public:
    LinkedList(); // default constructor
    LinkedList(DT& i, LinkedList<DT>* n); // constructor
    LinkedList(const LinkedList<DT>& ll);
    virtual ~LinkedList(); //destructor
    DT& operator[](int pos); // square bracket operator
    int size(); // returns the size of the LinkedList
    void add(LinkedList<DT>& newOne); // adds the new LinkedList to the beginning of the list
    void add(const DT& other); // adds a new LinkedList with DT& other as the info
    void insertAt(int pos, DT& x); // inserts a new LinkedList at the specified point in the LinkedList
    DT remove(); // removes the first element of the LinkedList
    DT removeAt(int pos); //goes to the posth element and removes that element
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
DT LinkedList<DT>::remove() {
    DT temp = *_info;
    delete _info;
    if (_next == NULL) {
        _info = NULL;
    } else {
        LinkedList<DT>* old = _next;
        _info = _next->_info;
        _next = _next->_next;
        old->_info = NULL;
        old->_next = NULL;
        delete old;
    }
    return temp;
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

//coppy constructor
template <class DT>
LinkedList<DT>::LinkedList (const LinkedList<DT>& ll) {
    if (ll._info == NULL) {
        _info = NULL;
    }
    else {
        _info = new DT(*(ll._info));
    }
    if (ll._next == NULL) {
        _next = NULL;
    } else {
        _next = new LinkedList<DT> (*(ll._next));
    }
}

//removes the element at the pos position
template <class DT>
DT LinkedList<DT>::removeAt(int pos) {
    if (pos == 0) {
        return remove();
    } else {
        return _next->removeAt(pos-1);
    }
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
    friend ostream &operator << (ostream& output, Polynomial &M); // << operator
protected:
    LinkedList<Term>* myPoly; //this is the main LinkedList that stores all of the values
public:
    Polynomial(); //default constructor
    virtual ~Polynomial (); //destructor
    int getDegree (); //gets the degree of this polynomial (highest exponent)
    int getNumberOfTerms (); //gets the number of terms in this polynomial
    Term getTermAt (int i); //gets the term at index i
    int getCoefficientAt (int i); //gets the coefficient at index i
    int getExponentAt (int i); //gets the exponent at index i
    bool thereExistsATermWithExponent (int e); //says whether or not there is a term with exponent e
    bool thereExistsATermWithExponentClassic (int e); //says whether or not there is a term with exponent e
    Term getTermWithExponent (int e); //gets the term with exponent e
    int getCoefficientOfTermWithExponent (int e); //gets the coefficient of the term with exponent e
    void setCoefficientOfTermWithExponent(int c, int e); //sets the coefficient of the term with exponent e to the specified value c
    int evaluatePoly (int x); //evaluates the polynomial with value x
    bool addTerm (int c, int e); //adds a term with coefficient c and exponent e to this Polynomial and returns whether or not it was added or already existed
    bool deleteTerm (int e); //deletes the term with exponent e
    Polynomial *addPolynomial (Polynomial& M); //adds this Polynomial to the specified Polynomial and returns the output
    Polynomial *operator+ (Polynomial& M); //overloads the + operator to use the addPolynomial method
    Polynomial *multiplyPolynomial(Polynomial& M); //multiplies this Polynomial and the specified polynomial together and returns the output
    Polynomial *operator* (Polynomial& M); //overloads the * operator to use the multiplyPolynomial method
    void printPolynomial(); //prints this Polynomial in the format (<coefficient, exponent>) + ...
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
    //starts from -1 in case the degree of the Polynomial is 0
    int currentDegree = -1;
    
    //looping through all of the terms
    for (int i = 0; i < getNumberOfTerms(); i++) {
        //checking if the degree of the current term is higher than the last
        if (currentDegree < getExponentAt(i)) {
            //setting the degree to this terms exponent 
            currentDegree = getExponentAt(i);
        }
    }
    return currentDegree;
}

//gets the total number of terms in this polynomial
int Polynomial::getNumberOfTerms() {
    //simply calls the sizs method on myPoly
    return (*myPoly).size();
}

//returns the term at the specified index
Term Polynomial::getTermAt(int i) {
    //simply calls infoAt on myPoly
    return (*myPoly).infoAt(i);
}

//returns the coefficient of the term at the specified index
int Polynomial::getCoefficientAt(int i) {
    //gets the specified index from myPoly, gets the coefficient and returns it
    return (*myPoly).infoAt(i).getCoefficient();
}

//returns the exponenet of the term at the specified index
int Polynomial::getExponentAt(int i) {
    //gets the specified index from myPoly, gets the exponent and returns it
    return (*myPoly).infoAt(i).getExponent();
}

//returns true if there is a term with exponent e in this polynomial, false otherwise
bool Polynomial::thereExistsATermWithExponent(int e) {
    //defaults to false
    bool returnBool = false;
    
    //looping through of the terms in this polynomial
    for (int i = 0; i < (*myPoly).size(); i++) {
        //if the exponent at this index is equal to the specified exponent, returns true
        if ((getExponentAt(i) == e) && getCoefficientOfTermWithExponent(e) != 0) {
            returnBool = true;
        }
    }
    return returnBool;
}

//returns true if there is a term with exponent e in this polynomial, false otherwise
bool Polynomial::thereExistsATermWithExponentClassic(int e) {
    //defaults to false
    bool returnBool = false;
    
    //looping through of the terms in this polynomial
    for (int i = 0; i < (*myPoly).size(); i++) {
        //if the exponent at this index is equal to the specified exponent, returns true
        if ((getExponentAt(i) == e)) {
            returnBool = true;
        }
    }
    return returnBool;
}

//gets the term object with exponent e. if one does not exist, returns a default term
Term Polynomial::getTermWithExponent(int e) {
    //looping through all of the terms in this polynomial
    for (int i = 0; i < (*myPoly).size(); i++) {
        //if this exponent at this index is equal to the specified index, then return the term at this index
        if (getExponentAt(i) == e) {
            return getTermAt(i);
        }
    }
    //otherwise returns a default Term
    return Term();
}

//gets the coefficient of the term with exponent e. if one does not exist, returns 0
int Polynomial::getCoefficientOfTermWithExponent(int e) {
    //looping through all of the terms in this polynomial
    for (int i = 0; i < (*myPoly).size(); i++) {
        //if this exponent at this index is equal to the specified exponent, then returns the coefficient at this index
        if (getExponentAt(i) == e) {
            return getCoefficientAt(i);
        }
    }
    return 0;
}

//sets the coefficient of the term with exponent e to c
void Polynomial::setCoefficientOfTermWithExponent(int c, int e) {
    //looping through all of the terms in this polynomial
    for (int i = 0; i < (*myPoly).size(); i++) {
        //if this exponent at this index is equal to the specified exponent, then set the coefficient at this index
        if (getExponentAt(i) == e) {
            myPoly->infoAt(i).setCoefficient(c);
        }
    }
}

//takes in the variable x and evaluates the polynomial as that variable
int Polynomial::evaluatePoly(int x) {
    //starting total at 0
    int total = 0;
    int c, e, sum;
    //loops through each term and evaluates
    for (int i = 0; i < this->getNumberOfTerms(); i++) {
        c = this->myPoly->infoAt(i).getCoefficient();
        e = this->myPoly->infoAt(i).getExponent();
        sum = x;
        //evaluating the exponent first by looping through and multiplying itself e number of times
        for (int i = 1; i < e; i++) {
            sum *= x;
        }
        //multiplying by the coefficient
        sum *= c;
        //adding to the total
        total += sum;
    }
    
    return total;
}

//adds a term to this polynomial
bool Polynomial::addTerm(int c, int e) {
    //if the term already exists...
    if (thereExistsATermWithExponentClassic(e)) {
        //add c to the coefficient of the term
        this->setCoefficientOfTermWithExponent((getCoefficientOfTermWithExponent(e) + c), e);
        //returns false because a term was not added to this polynomial
        return false;
    } else {
        //if the term doesnt already exist then add the term to myPoly
        this->myPoly->add(Term(c,e));
        //returns true because the term was added
        return true;
    }
}

//deletes the term with the specified coefficient and exponent from this polynomial
bool Polynomial::deleteTerm(int e) {
    if (thereExistsATermWithExponent(e)) {
        this->setCoefficientOfTermWithExponent(0, e);
        return true;
    }
    return false;
}

//adds the specified polynomials together and returns the output
Polynomial* Polynomial::addPolynomial(Polynomial &M) {
    //this is the Polynomial* we will return
    Polynomial* temp = new Polynomial();
    //loop through this Polynomial and add each terms
    for (int i = 0; i < this->getNumberOfTerms(); i++) {
        temp->addTerm(this->getCoefficientAt(i), this->getExponentAt(i));
    }
    //loop through M and add each term. The addTerm method automatically adds each term together that have like exponents
    for (int i = 0; i < M.getNumberOfTerms(); i++) {
        temp->addTerm(M.getCoefficientAt(i), M.getExponentAt(i));
    }
    //returning temp
    return temp;
}

//overloads the + operator; simply uses the addPolynomial function
Polynomial* Polynomial::operator+(Polynomial &M) {
    //simply calls the addPolynomial function
    return this->addPolynomial(M);
}

//multiples the specified polynomials together and returns the output
Polynomial* Polynomial::multiplyPolynomial(Polynomial &M) {
    //this is the Polynomial* we will return
    Polynomial* temp = new Polynomial();
    //loops through this Polynomial
    for (int i = 0; i < this->getNumberOfTerms(); i++) {
        //loops through M
        for (int j = 0; j < M.getNumberOfTerms(); j++) {
            //multiplies the coefficient together and adds the exponents together and adds a term to temp with those values
            temp->addTerm((this->getCoefficientAt(i) * M.getCoefficientAt(j)), (this->getExponentAt(i) + M.getExponentAt(j)));
        }
    }
    //returing temp
    return temp;
}

//overloads the * operator; simply uses the multiplyPolynomial function
Polynomial* Polynomial::operator*(Polynomial &M) {
    //simply calls the multiplyPolynomial function
    return this->multiplyPolynomial(M);
}

//prints the specified polynomial in the format "Polynomial <polynum>: (coefficient, exponent) + ..."
void Polynomial::printPolynomial() {
    //couts the polynomial
    cout << this;
}

//overloads the << operator for Polynomial; uses the following format "Polynomial <polynum>: (coefficient, exponent) + ..."
ostream& operator << (ostream& output, Polynomial &M) {
    bool atFirst = true; //variable to keep track adn check if we are at the first term
    //looping through and printing
    for (int i = M.getDegree(); i > -1; i--) {
        if (M.thereExistsATermWithExponent(i) && M.getCoefficientOfTermWithExponent(i) != 0) {
            if (atFirst) {
                output << "(" << M.getCoefficientOfTermWithExponent(i) << ", " << i << ")";
                atFirst = false;
            }
            else if (!atFirst) {
                output << " + (" << M.getCoefficientOfTermWithExponent(i) << ", " << i << ")";
            }
        }
    }
    //returning the output
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
                cout << "Attempting to insert term with coefficient " << coefficient << " and exponent " << exponent  << " into Polynomial "<< polynum << "..." << endl;
                cout << ((P[polynum-1].addTerm (coefficient, exponent)) ? "Inserted!" : "Not inserted, but added to the term with the same exponent") << endl << endl;
                break;
            case 'D':
                cin >> polynum >> exponent;
                cout << "Attempting to delete term with exponent " << exponent << " from Polynomial " << polynum << "..." << endl;
                cout << ((P[polynum-1].deleteTerm (exponent)) ? "Deleted!" : "Could not find a term with that exponent") << endl << endl;
                break;
            case 'A':
                cin >> i >> j;
                cout << "Adding Polynomial " << i << " [" << P[i-1] << "] and Polynomial " << j << " [" << P[j-1] << "]" << endl;
                cout << *(P[i-1] + P[j-1]) << endl << endl;
                break;
            case 'M':
                cin >> i >> j;
                cout << "Multiplying Polynomial " << i << " [" << P[i-1] << "] and Polynomial " << j << " [" << P[j-1] << "]" << endl;
                cout << *(P[i-1] * P[j-1]) << endl << endl;
                break;
            case 'E':
                cin >> polynum >> value;
                cout << "Evalutating polynomial " << polynum << " with x = " << value << ": " << P[polynum-1] << endl;
                cout << P[polynum-1].evaluatePoly(value) << endl << endl;
                break;
            case 'P':
                cin >> polynum;
                cout << "Polynomial " << polynum << ": " << P[polynum-1] << endl << endl;
                break;
            default:
                cout << "I missed something" << endl << endl;
        }
        cin >> command;
        
    }
    
    
    return 0;
}
