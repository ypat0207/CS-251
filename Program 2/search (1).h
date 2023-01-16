/*
  Project 2 - Search
  Name: Yash Patel
  CS 251 Fall 2022
*/

#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
using namespace std;

string cleanToken(string s) {
  while (!s.empty() && ispunct(s[0])) {
    s = s.substr(1);
  }
  while (!s.empty() &&
         (ispunct(s[s.length() - 1]) || isdigit(s[s.length() - 1]))) {
    s = s.substr(0, s.length() - 1);
  }
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  return s;
}

set<string> gatherTokens(string text) {
  set<string> tokens;
  stringstream check1(text);
  string intermediate;
  string ans;

  while (getline(check1, intermediate, ' ')) {
    ans = cleanToken(intermediate);
    if (!ans.empty()) {
      tokens.insert(ans);
    }
  }

  return tokens;
}

int buildIndex(string filename, map<string, set<string>> &index) {
  // TODO:  Write this function.
  ifstream input;
  input.open(filename);
  if (!input.is_open()) {
    cout << "Error: unable to open '" << filename << endl;
  }

  while (!input.eof()) {
    string firstLine;
    string secondLine;

    getline(input, firstLine);
    getline(input, secondLine);
  }

  input.close();

  return 0;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
set<string> findQueryMatches(map<string, set<string>> &index, string sentence) {
  set<string> result;

  // TODO:  Write this function.

  return result; // TODO:  update this.
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string filename) {

  // TODO:  Write this function.
}
