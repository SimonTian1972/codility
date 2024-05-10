#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <iostream>
using namespace std;

// you can use includes, for example:
// #include <algorithm>
int solution(vector<int>& A, vector<int>& B, vector<int>& C) {
    // Implement your solution here
    set<vector<int>> myPlank;
    const int N = A.size();
    for (int i = 0; i < N; i++) {
        myPlank.insert(vector<int>{A[i], B[i]});
    }

    const int cN = C.size();
    for (int i = 0; i < cN; i++) {
        auto itEnd = upper_bound(myPlank.begin(), myPlank.end(), vector<int>{C[i], 0},
            [](vector<int>left, vector<int>right) {
                return left[0] < right[0];
            });
        vector<vector<int>> toRemove;
        for (auto it = myPlank.begin(); it != myPlank.end() && it != itEnd; it++) {
            // save item to remove
            int end = (*it)[1];
            if (end >= C[i]) {
                toRemove.push_back(vector<int>{(*it)[0], (*it)[1]});
            }
        }
        // remove items
        for (auto item : toRemove) {
            myPlank.erase(item);
        }
        if (myPlank.empty()) {
            return i+1; // number of nails
        }
    }
    return -1;
}

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

// you can use includes, for example:
// #include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <iostream>
using namespace std;

int solution(vector<int>& A, vector<int>& B, vector<int>& C) {
    // Implement your solution here
    set<vector<int>> myPlank;
    const int N = A.size();
    for (int i = 0; i < N; i++) {
        myPlank.insert(vector<int>{A[i], B[i]});
    }

    const int cN = C.size();
    for (int i = 0; i < cN; i++) {
        auto itEnd = upper_bound(myPlank.begin(), myPlank.end(), vector<int>{C[i], 0},
            [](vector<int>left, vector<int>right) {
                return left[0] < right[0];
            });
        vector<vector<int>> toRemove;
        for (auto it = myPlank.begin(); it != myPlank.end() && it != itEnd; it++) {
            // save item to remove
            int end = (*it)[1];
            if (end >= C[i]) {
                toRemove.push_back(vector<int>{(*it)[0], (*it)[1]});
            }
        }
        // remove items
        for (auto item : toRemove) {
            myPlank.erase(item);
        }
        if (myPlank.empty()) {
            return i + 1; // number of nails
        }
    }
    return -1;
}