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
    const string& in,
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
    wordleHelper("", in, floating, dict, results, 0);
    return results;
}

// Define any helper functions here
void wordleHelper(
    string curr,
    const string& in,
    string floating,
    const set<string>& dict,
    set<string>& results,
    size_t index)
{
    if(index == in.size()) // base case 1
    {
        if(floating.empty() && dict.find(curr) != dict.end())
        {
            results.insert(curr);
        }
        return;
    }

    if(in[index] != '-')
    {
        wordleHelper(curr + in[index], in, floating, dict, results, index + 1);
    }
    else
    {
        // try all 26 letters in alphabet
        for(char c = 'a'; c <= 'z'; ++c)
        {
            string newFloating = floating;

            size_t pos = newFloating.find(c);
            if(pos != string::npos)
            {
                newFloating.erase(pos, 1);

            }

            wordleHelper(curr + c, in, newFloating, dict, results, index + 1);
        }
    }
}
