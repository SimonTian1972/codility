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

int minSum(vector<int>& A, int first, int nextPos) {
    int len = nextPos - first + 1;
    vector<int> dp(len, 0);
    for (int i = first; i <= nextPos; i++) {
        int idx = i - first;
        int maxCur = INT_MIN;
        for (int step = 1; step <= 6; step++) {
            int prev = 0;
            if (idx - step >= 0) {
                prev = dp[idx - step];
            }
            maxCur = max(maxCur, prev + A[i]);
        }
        dp[idx] = maxCur;
    }
    return dp[len - 1] - A[nextPos];// do not count nextPos value
}

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    int idx = 0;
    int sum = 0;
    while (idx < N) {
        if (idx == 0 || idx == N - 1 || A[idx] >= 0) {
            sum = sum + A[idx];
            idx++;
            continue;
        }
        else { // A[idx] < 0
            int nextPos = idx;
            while (A[nextPos] < 0 && nextPos != N - 1) {
                nextPos++;
            }
            int temp = minSum(A, idx, nextPos);
            sum = sum + temp;
            idx = nextPos;
        }
    }
    return sum;
}