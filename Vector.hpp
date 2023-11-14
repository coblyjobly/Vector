#include "Vector.h"

#include <iostream>
using namespace std;

//------------------------------Constructors------------------------------

// Default constructor
template <class T>
Vector<T>::Vector(){
    theSize = 0;
    theCapacity = 0;
    array = nullptr;
}

// Copy Constructor
template <class T>
Vector<T>::Vector(const Vector &rhs):theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{nullptr}
{
    array = new T[theCapacity];
    for( int i = 0; i < theSize; ++i ){
        array[i] = rhs.array[i];
    }
}

// Move Constructor
template <class T>
Vector<T>::Vector(Vector &&rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{rhs.array}{
    rhs.array = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}

// num elements with value of val
template <class T>
Vector<T>::Vector(int num, const T& val){
    theSize = num;
    theCapacity = num;
    array = new T[theCapacity];
    for(int i = 0; i < theSize; ++i){
        array[i] = val;
    }
}

// constructs with elements [start, end)
template <class T>
Vector<T>::Vector(const_iterator start, const_iterator end){
    theSize = 0;
    theCapacity = 0;
    array = nullptr;
    array = new T[theCapacity];
	for (; start != end; ++start) {
		push_back(*start);
	}
}

// Deconstructor
template <class T>
Vector<T>::~Vector(){
    delete [] array;
}


//------------------------------Operators------------------------------\

// index operator
template <class T>
T& Vector<T>::operator[](int index){
     return array[index];
}
template <class T>
const T& Vector<T>::operator[](int index) const{
     return array[index];
}

// copy assignment operator
template <class T>
const Vector<T>& Vector<T>::operator=(const Vector &rhs){
    Vector copy = rhs;
    swap(*this, copy);
    return *this;
}

// move assignment operator
template <class T>
Vector<T>& Vector<T>::operator=(Vector &&rhs){
    swap(theSize, rhs.theSize);
    swap(theCapacity, rhs.theCapacity);
    swap(array, rhs.array);
    return *this;
}

//-----------------------------Functions------------------------------

// at function. safer than operator[]
template <class T>
T& Vector<T>::at(int loc){
    if(loc < 0 || loc >= size()){
        throw out_of_range("Index not in range");
    }
    return array[loc];
}
template <class T>
const T& Vector<T>::at(int loc) const{
    if(loc < 0 || loc > size()){
        throw out_of_range("Index not in range");
    }
    return array[loc];
}

// reference to the first element
template <class T>
T& Vector<T>::front(){
    return array[0];
} 
template <class T>
const T& Vector<T>::front() const{
    return array[0];
}

// reference to the last element
template <class T>
T& Vector<T>::back(){
    return array[theSize-1];
}
template <class T>
const T& Vector<T>::back() const{
    return array[theSize-1];
}

// Accessor Member Functions-----------------------

// number of elements
template <class T>
int Vector<T>::size() const{
    return theSize;
}
// capacity of vector
template <class T>
int Vector<T>::capacity() const{
    return theCapacity;
}
// check if list is empty
template <class T>
bool Vector<T>::empty() const{
    if(theSize == 0){
        return true;
    }
    else{
        return false;
    }
}


// Mutator Member Functions-----------------------

// delete all elements
template <class T>
void Vector<T>::clear(){
    theSize = 0;
}

// insert to the end
template <class T>
void Vector<T>::push_back(const T & val){
    if(theSize == theCapacity){
        doubleCapacity();
    }
    array[theSize++] = val;
}

// delete last element
template <class T>
void Vector<T>::pop_back(){
    --theSize;
}

// resize vector
template <class T>
void Vector<T>::resize(int num, T val){
    if(num > theSize){
        reserve(num * 2);
        for(int i = theSize + 1; i < num-theSize; i++){
            array[i] = val;
        }
    }
    theSize = num;
}

// reserve memory
template <class T>
void Vector<T>::reserve(int newCapacity){
    if(newCapacity < theSize){
        return;
    }
    T *newArray = new T[newCapacity];
    for(int i = 0; i < theSize; ++i){
        newArray[i] = move(array[i]);
    }
    theCapacity = newCapacity;
    swap(array, newArray);
    delete [ ] newArray;
}

// print out all elements. ofc is deliminitor
template <class T>
void Vector<T>::print(ostream& os, char ofc) const{
    for(int i = 0; i < theSize; i++){
        os << array[i] << ofc;
    }
} 


//Iterator Support-----------------------

// iterator to first element
template <class T>
typename Vector<T>::iterator Vector<T>::begin(){
    return &array[0];
}
template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const{
    return &array[0];
}

// end marker iterator
template <class T>
typename Vector<T>::iterator Vector<T>::end(){
    return &array[size()];
}
template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const{
    return &array[size()];
}

// insert val ahead of itr
template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator itr, const T& val){
    Vector<T>::iterator index = itr;
    if(theSize == theCapacity){
        doubleCapacity();
    }
    for (auto itr = end(); itr >= index; --itr){
        *(itr + 1) = *itr;
    }
    *index = val;
    theSize++;
    return index + 1;
}

// erase one element
template <class T>
typename Vector<T>::iterator Vector<T>::erase(iterator itr){
    Vector<T>::iterator index = itr;
    for (itr; itr != end(); itr++){
        *itr = *(itr + 1);
    }
    theSize--;
    return index;
}

// // erase [start, end)
template <class T>
typename Vector<T>::iterator Vector<T>::erase(iterator start, iterator end){
    Vector<T>::iterator index = end;
    for (iterator itr = start; itr != end; ++itr){
        *start = *end;
        start++;
        theSize--;
    }
    return index;
}


//Doubles capacity (private function)-----------------------
template <class T>
void Vector<T>::doubleCapacity(){
    if(theCapacity == 0){
        theCapacity = 1;
    }
    else{
        theCapacity = 2 * theCapacity; 
    }
    reserve(theCapacity);
}


// Operator overloads-----------------------

// overloading comparison operators
template <typename T>
bool operator==(const Vector<T> & lhs, const Vector<T> &rhs){
    if(lhs.size() != rhs.size()){
        return false;
    }
    for(int i = 0; i < lhs.size(); ++i){
        if(lhs[i] != rhs[i]){
            return false;
        }
    }
    return true;
}
template <typename T>
bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs){
    if(lhs.size() != rhs.size()){
            return true;
        }
        for(int i = 0; i < lhs.size(); ++i){
            if(lhs[i] != rhs[i]){
                return true;
            }
        }
    return false;
}

// overloading output operator
template <typename T>
std::ostream & operator<<(ostream &os, const Vector<T> &v){
    v.print(os);
    return os;
}