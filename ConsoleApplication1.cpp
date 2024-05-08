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

#include <vector>
#include <string>

using namespace std;



int solution(vector<int>& A) {
    // Implement your solution here
    sort(A.begin(), A.end());
    int len = A.size();
    for (int i = 0; i <= len - 3; i++) {
        if (A[i] + A[i + 1] > A[i + 2]) {
            return 1;
        }
    }
    return 0;
}