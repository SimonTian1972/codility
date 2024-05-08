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
    int ones = 0;
    int sum = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (A[i] == 1) {
            ones++;
        } else {  // zeros
            sum = sum + ones;
        }
    }
    return sum;    
}


