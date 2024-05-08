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



int solution1(vector<int>& A) {
    // Implement your solution here
    int count = 0;
    const int N = A.size();
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (abs(i - j) <= A[i] + A[j]) {
                count++;
            }
        }
    }
    return count;
}


int solution(vector<int>& A) {
    // Implement your solution here
    int count = 0;
    vector<vector<int>> sortSec;
    for (int i = 0; i < A.size(); i++) {
        sortSec.push_back({i - A[i], i + A[i] });
    }
    sort(sortSec.begin(), sortSec.end());
    auto it = sortSec.begin();
    for (int i = 0; i < sortSec.size(); i++) {
        int end = sortSec[i][1];
        auto next = upper_bound(it + i, sortSec.end(), vector<int>{end, 0});

        int temp = distance(next, it + i);
        count = count + (temp - 1);
    }
    return count;
}




