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
    if(index == curr.size()) // base case 1
    {
        if(dict.count(curr) && floating.empty())
        {
            results.insert(curr);
        }
        return;
    }

    if(curr[index] != '-')
    {
        wordleHelper(curr, floating, dict, results, index + 1);
    }

    // place floating characters instead of alphabet at current position
    for(size_t i = 0; i < floating.size(); ++i)
    {
        char c = floating[i];
        string newFloating = floating;
        newFloating.erase(i,1);
        curr[index] = c;
        wordleHelper(curr, newFloating, dict, results, index + 1);
    }

    int remainDashes = count(curr.begin() + index, curr.end(), '-');
    if(remainDashes > floating.size())
    {
        for(char c = 'a'; c <= 'z'; ++c)
        {
            if(floating.find(c) != string::npos) continue;
            curr[index] = c;
            wordleHelper(curr, floating, dict, results, index + 1);
        }
    }
}
