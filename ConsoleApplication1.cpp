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
    vector<int> plus;
    vector<int> negs;
    for (int num : A) {
        if (num >= 0) {
            plus.push_back(num);
        }
        else {
            negs.push_back(-num);
        }
    }
    sort(plus.begin(), plus.end(), greater<int>());
    sort(negs.begin(), negs.end(), greater<int>());

    int result = INT_MIN;
    if (plus.size() >= 3) {
        result = max(result, plus[0] * plus[1] * plus[2]);
    }

    if (plus.size() >= 1) {
        result = max(result, plus[0] * negs[0] * negs[1]);
    }
}