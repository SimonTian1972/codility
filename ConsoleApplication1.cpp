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

/*
N is an integer within the range [0..30,000];
each element of arrays A and B is an integer within the range [0..1,000,000,000];
A[I] ≤ B[I], for each I (0 ≤ I < N);
B[K] ≤ B[K + 1], for each K (0 ≤ K < N − 1).
*/

int solution(vector<int>& A, vector<int>& B) {
    // Implement your solution here
    const int N = A.size();
    int cur = 0;
    int count = 0;
    while (cur < N) {
        int end = B[cur];
        count++;
        int next = cur + 1;
        while (next < N && A[next] <= end) {
            next++;
        }
        cur = next;
    }
    return count;
}
