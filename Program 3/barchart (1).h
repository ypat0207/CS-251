// barchart.h
// TO DO:  add header comment here.  Also add function header comments below.

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
/*
 const string RED("\033[1;36m");
 const string PURPLE("\033[1;32m");
 const string BLUE("\033[1;33m");
 const string CYAN("\033[1;31m");
 const string GREEN("\033[1;35m");
 const string GOLD("\033[1;34m");
 const string BLACK("\033[1;37m");
 const string RESET("\033[0m");
 const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};
 */

// Color codes for Replit (dark mode terminal)

const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    // tracks the year the data is being shown
    string frame;
    int capacity;
    int size;
    
 public:
    
    // default constructor:
    BarChart() {
        // initializes variables to default values
        frame = "";
        bars = nullptr;
        capacity = 0;
        size = 0;
    }
    
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
        // updates capacity of array
        bars = new Bar[n]; 
        capacity = n;
        // size is set to 0
        // as no elements have been inserted
        size = 0;
        frame = "";
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
        // TO DO:  Write this constructor.
        this->bars = new Bar[other.size];
        this->size = other.size;
        this->capacity = other.capacity;
        this->frame = other.frame;
        for(int i = 0; i < other.size; i++) {
            this->bars[i] =  other.bars[i];
        }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
        //BarChart bc;
        if(this == &other) {
            return *this;
        }
        // TO DO:  Write this operator.
        delete[] bars;
        this->bars = new Bar[other.size];
        this->size = other.size;
        this->capacity = other.capacity;
        this->frame = other.frame;
        for(int i = 0; i < other.size; i++) {
            this->bars[i] =  other.bars[i];
        }
        return *this;
        //return bc;   // TO DO:  update this, it is only here so code compiles.
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
        
        // TO DO:  Write this operator.
        delete[] bars;
        bars = nullptr;
        capacity = 0;
        size = 0;
        frame = "";
        //bars = new 
    }
    
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
        // TO DO:  Write this destructor.
        if(bars != nullptr) {
            delete[] bars;
            bars = nullptr;
            capacity = 0;
            size = 0;
            frame = "";
        }
    }
    
    // setFrame
    void setFrame(string frame) {
        // TO DO:  Write this destructor.
        this->frame = frame;
    }
    
    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {
        
        return frame; // TO DO:  update this, it is only here so code compiles.
    }

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) {
        
        if(this->size != this->capacity) {
         Bar newBar(name,value,category);
         bars[this->size] = newBar;
         size++;
         return true;
       }
        return false;
  }
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {
        // TO DO:  Write this function.
        return this->size;  // TO DO:  update this, it is only here so code compiles.
    }
  
    Bar& operator[](int i) {
        if(i > size) {
            throw out_of_range("BarChart: i out of bounds");
        }
        // TO DO:  Write this function.
        return bars[i];  // TO DO:  update this, it is only here so code compiles.
    }
    
    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
        // TO DO:  Write this function.
        output << "frame: " << frame << endl;
        sort(bars, bars + size, greater <Bar> ());
        for (int i = 0; i < size; i++) {
            output << bars[i].getName() << " " << bars[i].getValue()
            << " " << bars[i].getCategory() << endl;
        }
    }
    
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60; 
    char space = ' ';
    sort(bars, bars + size, greater <Bar> ());
        if(top > size) {
            top = size;
        }
        int maxValue = bars[0].getValue();
        for (int i = 0; i < top; i++) {
            string color = "";
            int value = bars[i].getValue();
            int lengthOfBar = floor(((double) value / maxValue) * lenMax);
            if(colorMap.find(bars[i].getCategory()) != colorMap.end()) {
                color = colorMap.find(bars[i].getCategory())->second;
            }
            else {
                color = WHITE;
            }
            string barstr = "";
            for(int i = 0; i < lengthOfBar; i++) {
                barstr += BOX;
            }
            output << color << barstr << space << bars[i].getName() << space << bars[i].getValue() << endl;
        }
    }
    
};

