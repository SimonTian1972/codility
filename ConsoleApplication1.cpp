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

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    sort(A.begin(), A.end());
    int ret = INT_MAX;
    for (int i = 0; i < N - 1; i++) {
        int target = -A[i];
        auto it = lower_bound(A.begin()+i, A.end(), target);
        if (it != A.end()) {
            ret = min(ret, abs(*it - target));
        }
        if (it != A.begin() + i) {
            auto pv = std::prev(it, 1);
            ret = min(ret, abs(*pv - target));
        }
    }
    return ret;
}

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    if (N == 1) {
        return 2 * A[0];
    }
    sort(A.begin(), A.end());
    int ret = INT_MAX;
    for (int i = 0; i < N - 1; i++) {
        int target = -A[i];
        auto it = lower_bound(A.begin() + i, A.end(), target);
        if (it != A.end()) {
            ret = min(ret, abs(*it - target));
        }
        if (it != A.begin() + i) {
            auto pv = std::prev(it, 1);
            ret = min(ret, abs(*pv - target));
        }
    }
    return ret;
}

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    if (N == 1) {
        return 2 * A[0];
    }
    sort(A.begin(), A.end());
    int ret = INT_MAX;
    for (int i = 0; i < N - 1; i++) {
        int target = -A[i];
        auto it = lower_bound(A.begin() + i, A.end(), target);
        if (it != A.end()) {
            ret = min(ret, abs(*it - target));
        }
        if (it != A.begin() + i) {
            auto pv = std::prev(it, 1);
            ret = min(ret, abs(*pv - target));
        }
    }
    return ret;
}




int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    if (N == 1) {
        return 2 * abs(A[0]);
    }
    sort(A.begin(), A.end());
    int ret = INT_MAX;
    for (int i = 0; i < N - 1; i++) {
        int target = -A[i];
        auto it = lower_bound(A.begin() + i, A.end(), target);
        if (it != A.end()) {
            ret = min(ret, abs(*it - target));
        }
        if (it != A.begin() + i) {
            auto pv = std::prev(it, 1);
            ret = min(ret, abs(*pv - target));
        }
    }
    return ret;
}


