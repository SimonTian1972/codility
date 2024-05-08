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



int solution(int A, int B, int K) {
    // Implement your solution here
    int numA = A / K;
    int numB = B / K;
    // how about numA itself
    int ret = numB - numA;
    if (A % K == 0) { // should include A itself
        ret = ret + 1;
    }
    return ret;
}




