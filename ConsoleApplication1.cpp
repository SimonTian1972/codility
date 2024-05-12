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

#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(int K, vector<int>& C, vector<int>& D) {
    // Implement your solution here
    const int N = C.size();
    const int M = D.size();
    unordered_map<int, int> cleanMap; // sock_num, count
    int ret = 0;
    for (int s : C) {
        cleanMap[s]++;
        if (cleanMap[s] == 2) {
            cleanMap[s] = 0;
            ret++;
        }
    }
    unordered_map<int, int> dirtyMap;
    for (int s : D) {
        dirtyMap[s]++;
    }

    for (auto& myPair : cleanMap) {
        if (K == 0) {
            break;
        }
        if (myPair.second == 1) {
            if (dirtyMap.find(myPair.first) != dirtyMap.end()) {
                ret++; // more pair
                K--; // wash one
                dirtyMap[myPair.first]--; // dirty one less
            }
        }
    }

    for (auto& myPair : dirtyMap) {
        if (K < 2) {
            break;
        }
        int count = myPair.second / 2;
        count = min(count, K / 2);
        ret = ret + count;
        K = K - 2*count;
    }
    return ret;
}