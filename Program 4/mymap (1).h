// Name: Yash Patel
// Project 5: Mymap
// 
#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
       iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }


        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {
			
			if (curr -> isThreaded) {
                curr = curr -> right;
            } else {
                curr = curr -> right;
                while (curr != nullptr && curr -> left != nullptr) {
                    curr = curr -> left;
                }
            }
            return iterator(curr); // TODO: Update this return.
        }
    };

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
		this -> root = nullptr;
    	this -> size = 0;
    }

	// copies nodes to trees
	void copyNodes(NODE* other) {
		if (other == nullptr) {
       		return;
      	} else {
      		put(other -> key, other -> value);
      		copyNodes(other -> left);
      		other = (other -> isThreaded) ? nullptr : other -> right;
      		copyNodes(other);
      	}
	}

	// deletes node from a tree
	void deleteNodes(NODE* &node) {
		if (node == nullptr) {
			return;
		}
		deleteNodes(node -> left);
		NODE* newNode = (node -> isThreaded) ? nullptr : node -> right;
		deleteNodes(newNode);
		delete node;
	}


    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap  &other) {
		this -> root = nullptr;
		this -> size = 0;
		copyNodes(other.root);
    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap &other) {
		deleteNodes(this -> root);
		this -> size = 0;
		if (other.root == nullptr) {
			return *this;
		}
		this -> root = nullptr;
		copyNodes(other.root);
        return *this;  // TODO: Update this return.
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {
		deleteNodes(root);
		size = 0;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {
		if (size != 0) {
			deleteNodes(root);
		}
    }

	// search for given node in a tree
	NODE* searchNode(NODE* x) {
		NODE* z = root;
    	NODE* notFound = nullptr;

      	while (z != nullptr) {
        	if (z == x) {
          		return z;
       		}
        	if (z -> key < x -> key) {
				z = (z -> isThreaded) ? nullptr : z -> right;
       		} else if (z -> key > x -> key) {
				z = z -> left;
       		}
     	}
     	return notFound;
  	}

	// make a new node w/ given key and val
	NODE* createNode(keyType key, valueType value) {
      	NODE* newNode = new NODE();
      	newNode -> key = key;
      	newNode -> value = value;
      	newNode -> nL = 0;
      	newNode -> nR = 0;
      	newNode -> left = nullptr;
     	newNode -> right = nullptr;
      	newNode -> isThreaded = true;
      	return newNode;
    }

	// search the tree to a given key
	void searchTree(NODE* &cur, NODE* &prev, keyType &key, vector<NODE*> &thruNodes, bool &foundKey, NODE* &foundNode) {
		while (cur != nullptr) {
    		prev = cur;
        	if (cur -> key == key) {
           		foundKey = true;
           		foundNode = cur;
           	return;
        	}
        	if (cur -> key < key) {
				thruNodes.push_back(cur);
          		cur = (cur -> isThreaded) ? nullptr : cur -> right;
        	} else if (cur -> key > key) {
          		thruNodes.push_back(cur);
          		cur = cur -> left;
        	}
      	}
    	return;
    }

	// insert new nodes into tree given key
	void insLoR(NODE* &prev, NODE* &newNode, bool &ins) {
		if (prev == nullptr) {
	        newNode -> isThreaded = true;
	        newNode -> nL = 0;
	        newNode -> nR = 0;
	        newNode -> right = nullptr;
	        this -> root = newNode;
	        ins = true;
	        return;
      } else if (prev -> key > newNode -> key) {
        	newNode -> right = prev;
        	newNode -> isThreaded = true;
        	newNode -> left = nullptr;
        	newNode -> nL = 0;
        	newNode -> nR = 0;
        	prev -> left = newNode;
        	ins = true;
      } else if (prev -> key < newNode -> key) {
        	newNode -> right = prev -> right;
	        prev -> isThreaded = false;
	        newNode -> isThreaded = true;
	        newNode -> nL = 0;
	        newNode -> nR = 0;
	        newNode -> left = nullptr;
	        prev -> right = newNode;
	        ins = true;
      }
	}

	// checks if the thruNodes are balanced
	bool thruNodeBalance(vector<NODE*> &thruNodes, vector<NODE*> &probNodes, int &probLoR) {
    	int ind = 0;
    	for(NODE* &i : thruNodes) {
      	if ((max(i -> nL, i -> nR)) > (2 * min(i -> nL, i -> nR) + 1)) {
       		probNodes.push_back(i);
       		if (ind > 0) {
	        	probNodes.push_back(thruNodes[ind - 1]);
          		if (probNodes[1] -> left == probNodes[0]) {
            		probLoR = 1;
          		} else if (probNodes[1] -> right == probNodes[0]) {
          			probLoR = 2;
          		}
        	}
        return false;
      }
      ind++;
    }
    return true;
    }

	// balances a tree given unordered nodes
	NODE* balanceTree(vector<NODE*> &tree, int left, int right) {
    	int mid = (left + right) / 2;

      	if (left == (mid - 1)) {
        	tree[left] -> isThreaded = true;
        	tree[left] -> right = tree[mid];
        	tree[left] -> left = nullptr;
        	tree[left] -> nL = 0;
        	tree[left] -> nR = 0;
        	tree[mid] -> left = tree[left];
        	tree[mid] -> nL = 1;
      	} else if (left > (mid - 1)) {
        	tree[mid] -> left = nullptr;
        	tree[mid] -> nL = 0;
      	} else if (left < (mid - 1)) {
        	tree[mid] -> left = balanceTree(tree, left, (mid - 1));
        	tree[mid] -> nL = tree[mid] -> left -> nR + tree[mid] -> left -> nL + 1;
      	}

      	if (right == (mid + 1))	{
        	tree[right] -> nR = 0;
        	tree[right] -> nL = 0;
        	tree[right] -> isThreaded = true;
        	tree[right] -> left = nullptr;
        	tree[mid] -> right = tree[right];
        	tree[mid] -> isThreaded = false;
	        tree[mid] -> nR = 1;
      	} else if (right < (mid + 1)) {
        	tree[mid] -> right = nullptr;
        	tree[mid] -> isThreaded = true;
        	tree[mid] -> nR = 0;
      	} else if (right > (mid + 1)) {
        	tree[mid] -> right = balanceTree(tree, (mid + 1), right);
        	tree[mid] -> nR = tree[mid] -> right -> nR + tree[mid] -> right -> nL + 1;
        	tree[mid] -> isThreaded = false;
      	}
      	return tree[mid];
    }

	// compare keys to update node counter
	void nodeComp(NODE* &newNode, vector<NODE*> &thruNodes) {
		for (auto &i : thruNodes) {
			NODE* foundNode = searchNode(i);
			if (newNode -> key < foundNode -> key) {
				foundNode -> nL++;
			} else if (newNode -> key > foundNode -> key) {
				foundNode -> nR++;
			}
		}
	}

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {
		vector<NODE*> thruNodes;
		vector<NODE*> probNodes;
		bool ins =  false; // chaecks if inserted
		bool foundKey = false;
		int probLoR = 0;
		NODE* foundNode = nullptr;
		NODE* cur = this -> root;
		NODE* prev = nullptr;

		searchTree(cur, prev, key, thruNodes, foundKey, foundNode);

		if (foundKey == true) {
			foundNode -> value = value;
			return;
		} else if (foundKey != true) {
			NODE* newNode = createNode(key, value);
			insLoR(prev, newNode, ins);
			if (ins == true) {
				nodeComp(newNode, thruNodes);
				if (thruNodeBalance(thruNodes, probNodes, probLoR) == false) {
					vector<NODE*> needToBal;
					orderedVec(probNodes[0], needToBal);
					int left = 0;
					int right = needToBal.size() - 1;
					NODE* balancedNodes = balanceTree(needToBal, left, right);

					if (probNodes.size() == 1) {
						this -> root = balancedNodes;
					} else if (probNodes.size() == 2) {
						if (probLoR == 1) {
							probNodes[1] -> left = balancedNodes;
						} else if (probLoR == 2) {
							probNodes[1] -> right = balancedNodes;
						}
					}
				}
				size++;
			}
		}
		return;
    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) {
		NODE* cur = root;
		while (cur != nullptr) {
			if (cur -> key == key) {
				return true;
			} else if (cur -> key < key) {
				cur = (cur -> isThreaded) ? nullptr : cur -> right; 
			} else if (cur -> key > key) {
				cur = cur -> left;
			}
		}
        return false;  // TODO: Update this return.
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) {
		NODE* cur = root;
		while (cur != nullptr) {
			if (cur -> key == key) {
				return cur -> value;
			} else if (cur -> key < key) {
				cur = (cur -> isThreaded) ? nullptr : cur -> right;
			} else if (cur -> key > key) {
				cur = cur -> left;
			}
		}
        return valueType();  // TODO: Update this return.
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {
		vector<NODE*> thruNodes;
		vector<NODE*> probNodes;
		bool foundKey = false;
		bool ins = false;
		NODE* cur = root;
		NODE* prev = nullptr;
		NODE* foundNode = nullptr;
		int probLoR = 0;

		searchTree(cur, prev, key, thruNodes, foundKey, foundNode);
		if (foundKey == true) {
			return foundNode -> value;
		} 

		put(key, valueType());
        return valueType();  // TODO: Update this return.
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {
        return this -> size;  // TODO: Update this return.
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() {
		NODE* cur = root;
		NODE* prev = nullptr;
		while (cur != nullptr) {
			prev = cur;
			cur = cur -> left;
		}
        return iterator(prev);  // TODO: Update this return.
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // 
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(nullptr);
    }

	// prints tree in order
	void printTree(NODE* node, ostream &printStr) {
		printTree(node -> left, printStr);
		stringstream ss1;
		string strKey;
		ss1 << node -> key;
		ss1 >> strKey;
		stringstream ss2;
		string strVal;
		ss2 << node -> value;
		ss2 >> strVal;
		printStr << "key: " << strKey << " value: " << strVal << endl;
		node = (node -> isThreaded) ? nullptr : node -> right;
		printTree(node, printStr);
	}
    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() {
		stringstream printStr;
		printTree(this -> root, printStr);
        return printStr.str();  // TODO: Update this return.
    }

	// provides vector of pairs from a tree
	void pairVec(NODE* node, vector<pair<keyType, valueType>> &listTree) {
		pairVec(node -> left, listTree);
		listTree.emplace_back(node -> key, node -> value);
		node = (node -> isThreaded) ? nullptr : node -> right;
		pairVec(node, listTree);
	}

    //
    // toVector:
    //
    // Returns a vector of the entire map in order.
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<pair<keyType, valueType>> toVector() {
      
		vector<pair<keyType, valueType>> listTree;
		pairVec(this -> root, listTree);
		for (auto &i : listTree) {
			cout << "key: " << i.first << " value: " << i.second << endl;
		}
        return listTree;  // TODO: Update this return.
    }

	// puts tree nodes in order
	void orderedVec(NODE* node, vector<NODE*> &listTree) {
		orderedVec(node -> left, listTree);
		listTree.emplace_back(node);
		node = (node -> isThreaded) ? nullptr : node -> right;
		orderedVec(node, listTree);
	}

	void temp(vector<NODE*> &listTree) {
		orderedVec(this -> root, listTree);
		for(auto& i : listTree) {
        	cout << "key: " << i -> key << " value: " << i -> value << endl;
       	}
       	return listTree;
	}
	// puts nodes into strings
	string convToStr(NODE* node) {
		string printStr;
		stringstream ss;
		ss << node -> key;
		string key2;
		ss >> key2;
		printStr = "key: " + key2 + ", nL: " + to_string(node -> nL) + ", nR: " + to_string(node -> nR) + "\n";
		return printStr;
	}
	//updates string with tree
	void updateStr(NODE* other, string &printStr) {
		if (other == nullptr) {
			return;
		} else {
			printStr = printStr + convToStr(other);
			updateStr(other -> left, printStr);
			other = (other -> isThreaded) ? nullptr : other -> right;
			updateSTR(other, printStr);
		}
	}
    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() {
		string printStr;
		updateStr(this -> root, printStr);
        return printStr; 
    }
};
