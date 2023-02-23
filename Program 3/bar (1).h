// bar.h
// TO DO:  add header comment here.  Also add function header comments below.

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    // TO DO:  Define private member variables for this class
    // NOTE: You should not be allocating memory on the heap for this class.
    string name;
    int value;
    string category;
 public:

    // default constructor:
    Bar() {
       name = "";
       value = 0;
       category = "";
        // TO DO:  Write this constructor.
        
    }
    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
        
        // TO DO:  Write this constructor.
        this->value = value;
        this->category = category;
        this->name = name;
    }

    // destructor:
    virtual ~Bar() {
        
        // TO DO:  Write this destructor or leave empty if not needed.
        
    }

    // getName:
	string getName() {

    return this->name;  
	}

    // gets the value
	int getValue() {
    
    return this->value;    
	}

    //gets category
	string getCategory() {
    
    return this->category;
	}

	// operators
    // TO DO:  Write these operators.  This allows you to compare two Bar
    // objects.  Comparison should be based on the Bar's value.  For example:
	bool operator<(const Bar &other) const {
        if (this->value < other.value) {
      return true;
    }
    return false;
	}

	bool operator<=(const Bar &other) const {
        if (this->value <= other.value) {
      return true;
    }
    return false;
  }

	bool operator>(const Bar &other) const {
        if (this->value > other.value) {
      return true;
    }
    return false;
	}

	bool operator>=(const Bar &other) const {
        if (this->value >= other.value) {
      return true;
    }
    return false;
	}
};