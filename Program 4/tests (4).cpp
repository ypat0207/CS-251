#include <gtest/gtest.h>
#include "mymap.h"
using namespace std;

// netid: rshah268
// Copy and Clear Stress Test
TEST(mymap, Copy) {
    
    // Create two mymaps m1 and m2
    mymap<int, int> m1;
    mymap<int, int> m2;
    int n = 10000;

    for(int  i = 0; i < n; i++) {

        // Generate two random numbers
        int key = randomInteger(0, 100000);
        int val = randomInteger(0, 100000);

        // Insert them in map1
        m1.put(key, val);

        // Insert different elements in map2
        if(i % 2) {
            m2.put(val, key);
        }
    }

    // At this point they must be unequal
    ASSERT_NE(m1.Size(), m2.Size());

    // Set map2 equals to map1
    m2 = m1;

    // Both should be the same size and contain the same elements
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());

    // Clear map1
    m1.clear();

    // Now they are unequal again
    ASSERT_NE(m1.Size(), m2.Size());
    // Map1 must be empty
    ASSERT_EQ(m1.Size(), 0);
}

//Test for operator[] on already balanced tree.
//netid: lsasu2
TEST(mymap, operatorBrackets){
    mymap<int, string> test;
    map<int, string> omap;
    int n= 10;
    int arr[] = {40, 25, 60, 18, 35, 80, 30, 38, 50, 70};

    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap.emplace(arr[i], value);
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

    //Value not in map
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[i*1000], "");
        ASSERT_EQ(test.Size(), n+i+1);
    }

    //Duplicate values
    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap[arr[i]] = value;
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

}
//tkoope2
//Copy Operator test <int, int>
TEST(Operator, IICopyP) {
 mymap<int, int> m;
 mymap<int, int> m2;

 //Populate 1 and 2
 int key, value, high, low, modOp;
 int arrSize = rand() % 100;

 string mOriginal, m2Original;

 //Populate m
 high = 500;
 low = 1;
 modOp = (high - (low + 1)) + low;
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  value = rand() % modOp;
  m.put(key, value);
 }

 //Populate m2
 high = 1000; 
 low = 500;
 modOp = (high - (low + 1)) + low;
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  value = rand() % modOp;
  m2.put(key, value);
 }

 m = m2;

 EXPECT_EQ(m.Size(), m2.Size()) << "IIEquals; size difference\n";
 EXPECT_NE(mOriginal, m.toString()) << "m should not still equal original\n";
 EXPECT_EQ(m2.toString(), m.toString()) << "toString() !=\n" << "M:\n" << m.toString() << "\nM2:\n" << m2.toString() << endl;;
}
// netid: msiddi73
// Testing Put with random int key (Testing Size and toString)
TEST(Put, randomIntInt){

    map<int, int> m;
    mymap <int, int> mymap;
    stringstream s;

    int randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;
    
    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){
                
            randomKey = randomInteger(0, 100);
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();
        
    }

}

// netid: msiddi73
// Testing put with random char key (Testing Size and toString)
TEST(Put, randomCharInt){

    map<char, int> m;
    mymap <char, int> mymap;
    stringstream s;

    char randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;
    

    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){
                
            randomKey = randomInteger(65, 90); // get uppercase characthers
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();
        
    }

}
