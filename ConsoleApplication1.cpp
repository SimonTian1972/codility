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

bool contains(vector<int> pos, int s, int e) {
    auto lowit = lower_bound(pos.begin(), pos.end(), s);
    if (lowit == pos.end()) {
        return false;
    }

    if (*lowit <= e) {
        return true;
    }  else {
        return false;
    }
}

vector<int> solution(string& S, vector<int>& P, vector<int>& Q) {
 
    // Implement your solution here
    vector<int> charPos[4];
    for (int i = 0; i < S.size(); i++) {
        char cur = S[i];
        if (cur == 'A') {
            charPos[0].push_back(i);
        } else if (cur == 'C') {
            charPos[1].push_back(i);
        } else if (cur == 'G') {
            charPos[2].push_back(i);
        } else if (cur == 'T') {
            charPos[3].push_back(i);
        }
    }

    vector<int> result;
    for (int i = 0; i < P.size(); i++) {
        int s = P[i];
        int e = Q[i];
        int factor = INT_MAX;
        for (int j = 3; j >= 0; j--) {
            if (contains(charPos[j], s, e)) {
                factor = min(factor, j+1); // j+1 is the actual factor 1-4
            }
        }
        result.push_back(factor);
    }
    return result;
}




