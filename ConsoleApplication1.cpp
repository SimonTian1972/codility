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

vector<int> solution(int N, vector<int>& A) {
    // Implement your solution here
    vector<int> result(N, 0);
    int curmaxCount = 0;
    int nextmaxCount = 0;
    for (unsigned int i = 0; i < A.size(); i++) {
        if (A[i] >= 1 && A[i] <= N) {
            int newV = max(curmaxCount + 1, result[A[i] - 1] + 1);
            result[A[i] - 1] = newV;
            nextmaxCount = max(nextmaxCount, result[A[i] - 1]);
        }
        else {
            curmaxCount = nextmaxCount;
        }
    }

    for (unsigned int i = 0; i < result.size(); i++) {
        if (result[i] < curmaxCount) {
            result[i] = curmaxCount;
        }
    }
    return result;
}

