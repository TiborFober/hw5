#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    string curr,
    string floating,
    const set<string>& dict,
    set<string>& results,
    size_t index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    wordleHelper(in, floating, dict, results, 0);
    return results;
}

// Define any helper functions here
void wordleHelper(
    string curr,
    string floating,
    const set<string>& dict,
    set<string>& results,
    size_t index)
{
    size_t dashes = 0;

    for(size_t i = index; i < curr.length(); ++i)
    {
      if(curr[i] == '-')
      {
        dashes++; // count dashes
      }
    }

    if(floating.length() > dashes)
    {
      return;
    }

    if(dashes == 0)
    {
      if(dict.find(curr) != dict.end() && (floating.size() == 0))
      {
        results.insert(curr);
      }
      return;
    }

    if(curr[index] != '-')
    {
      wordleHelper(curr, floating, dict, results, index + 1);
      return;
    }

    // place floating characters instead of alphabet at current position
    for(size_t i = 0; i < floating.length(); ++i)
    {
      char c = floating[i];
      string remainFloat = floating;
      remainFloat.erase(i,1);

      string newCurr = curr;
      newCurr[index] = c;

      wordleHelper(newCurr, remainFloat, dict, results, index + 1);
    }

    if(floating.length() < dashes)
    {
      for(char c ='a'; c <= 'z'; ++c)
      {
        if(floating.find(c) != string::npos) continue;

        string newCurr = curr;
        newCurr[index] = c;

        wordleHelper(newCurr, floating, dict, results, index + 1);
      }
    }
}