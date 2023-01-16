//
// STARTER CODE: util.h
//
// Name: Yash Patel
// CS 251 Program 6
//

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <queue>      
#include <vector>         
#include <string>
#include "hashmap.h"
#include "mainprog.h"
#include "bitstream.h"
typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

struct compare
{
    bool operator()(const HuffmanNode *lhs,
        const HuffmanNode *rhs)
    {
        return lhs->count > rhs->count;
    }
};
class GivePriority {
	public:
    bool operator()(const HuffmanNode* temp1, const HuffmanNode* temp2) const {
        return temp1->count > temp2->count;
    }
};

//
// *This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) {
    
    if (node == nullptr) {
        return;
    }

    freeTree(node -> zero);
    freeTree(node -> one);

    delete node;
    
}

//
// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
    
   int value = 0;
    if (isFile == true) {
        ifstream infile(filename);
        char x;
        while (infile.get(x)) {
            if (map.containsKey(x) == false) {
                map.put(x, 1);
            } else {
                value = map.get(x) + 1;
                map.put(x, value);
            }
        }
	} else {
    	for (char x : filename) {
            if (map.containsKey(x) == false) {
                map.put(x, 1);
            } else {
                value = map.get(x) + 1;
                map.put(x, value);
            }
        }
    }
    map.put(PSEUDO_EOF, 1);
    
}

//
// *This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmapF &map) {
    
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, GivePriority> priQue;

    vector<int> allTreeKeys = map.keys();
    for (int i = 0; i < map.size(); i++) {
        HuffmanNode* tempNode = new HuffmanNode();

        tempNode -> character = allTreeKeys.at(i);
        tempNode -> count = map.get(allTreeKeys.at(i));

        priQue.push(tempNode);
    }

    while (priQue.size() > 1) {
        HuffmanNode* firstPop = priQue.top();
        priQue.pop();
        HuffmanNode* secondPop = priQue.top();
        priQue.pop();

        HuffmanNode* newNode = new HuffmanNode();
        newNode -> count = firstPop -> count + secondPop -> count;
        newNode -> character = NOT_A_CHAR;
        newNode -> zero = firstPop;
        newNode -> one = secondPop;

        priQue.push(newNode);
    }

    return priQue.top(); 
}

//
// *Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str,
                       HuffmanNode* prev) {
    
    // TO DO:  Write this function here.
    
}

//
// *This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;
    
    // TO DO:  Write this function here.
    
    return encodingMap;  // TO DO: update this return
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}


//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}

//
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}

//
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
//
string decompress(string filename) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}