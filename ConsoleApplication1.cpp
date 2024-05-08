#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;


// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    vector<int> record(1+N, 0);
    for (int i = 0; i < A.size(); i++) {
        if (A[i] > 0 && A[i] <= N) {
            record[A[i]] = 1;
        }
    }

    for (int i = 1; i < record.size(); i++) {
        if (record[i] == 0) {
            return i;
        }
    }
    return N + 1;
}

