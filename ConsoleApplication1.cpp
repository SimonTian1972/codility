#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <stack>
using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;


int solution(string& S) {
    // Implement your solution here
    set<char> left{ '(','[','{' };
    map<char, char> right;
    right[')'] = '(';
    right[']'] = '[';
    right['}'] = '{';
    stack<char> myStack;
    for (int i = 0; i < S.size(); i++) {
        char cur = S[i];
        if (left.count(cur) == 1) {
            myStack.push(cur);
        }
        else {
            char top = myStack.top();
            if (myStack.size() == 0) {
                return false;
            }
            if (right[cur] == top) {
                myStack.pop();
            }
            else {
                return false;
            }
        }
    }
    if (myStack.empty() == true) {
        return true;
    }
    else {
        return false;
    }

}

