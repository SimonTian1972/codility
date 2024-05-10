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

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    int minPos = -1;
    double minVal = INT_MAX;
    vector<int> sums(N, 0);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum = sum + A[i];
        sums[i] = sum;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double temp = static_cast<double>(sums[j] - sums[i] +A[i]) / (j - i + 1);
            if (temp < minVal) {
                minVal = temp;
                minPos = i;
            }
        }
    }
    return minPos;
}



int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    int minPos = -1;
    double minVal = INT_MAX;
    vector<int> sums(N, 0);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum = sum + A[i];
        sums[i] = sum;
    }
    for (int i = 0; i < N; i++) {        
        if (i > 0 && A[i-1] < minVal) {
            continue;
        }
        for (int j = i + 1; j < N; j++) {
            double temp = static_cast<double>(sums[j] - sums[i] + A[i]) / (j - i + 1);
            if (temp < minVal) {
                minVal = temp;
                minPos = i;
            }
        }
    }
    return minPos;
}



