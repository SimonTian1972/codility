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


// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;


int solution(vector<int>& A, int X) {
    // Implement your solution here
    map<double, int> myMap; // len, count
    for (auto& item : A) {
        myMap[item]++;
    }
    for (auto& myPair : myMap) {
        myMap[myPair.first] = myPair.second / 2; // 2 fences per length or width
    }

    set<double> mySet;
    for (auto& myPair : myMap) {
        if (myPair.second != 0) {
            mySet.insert(myPair.first);
        }
    }


    long long ret = 0;
    for (auto& item : mySet) {
        double width = item;
        double height = X / width;

        auto valid = mySet.lower_bound(height);
        int start_count = 1;
        int end_count = distance(valid, mySet.end());
        if (width < height) {
            ret += start_count * end_count;
        }
        //cout << "width= " << width << " height= " << height << " end_count= " << end_count << endl;
    }

    if (ret > 1000000000) {
        return -1;
    }
    else {
        return static_cast<int>(ret);
    }
}

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;


int solution(vector<int>& A, int X) {
    // Implement your solution here
    map<double, int> myMap; // len, count
    for (auto& item : A) {
        myMap[item]++;
    }
    for (auto& myPair : myMap) {
        myMap[myPair.first] = myPair.second / 2; // 2 fences per length or width
    }

    map<double, int> newMap;
    for (auto& myPair : myMap) {
        if (myPair.second != 0) {
            newMap[myPair.first] = myPair.second;
        }
    }


    long long ret = 0;
    for (auto& item : newMap) {
        double width = item.first;
        double height = X / width;

        auto valid = newMap.lower_bound(height);
        int start_count = 1;
        int end_count = distance(valid, newMap.end());
        if (width < height) {
            ret += start_count * end_count;
        }
        if (width == height && item.second > 2) {
            ret++;
        }
        //cout << "width= " << width << " height= " << height << " end_count= " << end_count << endl;
    }

    if (ret > 1000000000) {
        return -1;
    }
    else {
        return static_cast<int>(ret);
    }
}


int solutionRectangleBuilderGreaterArea(vector<int>& A, int X) {
    std::sort(A.begin(), A.end());
    int len = (int)A.size();
    long long ans = 0;
    if (len < 4) return 0;
    vector<int> evenCnt(len, 0);
    for (int i = len - 2, prev = A[len - 1], cnt = 1, sum = 0; i > -2; --i) {
        if (i > -1 && A[i] == prev) ++cnt;
        else {
            if (cnt > 1) ++sum;
            cnt = 1, prev = A[i];
            evenCnt[i + 1] = sum;
        }
    }
    for (int i = 1, prev = A[0], cnt = 1, target; i <= len; ++i) {
        if (i < len && prev == A[i]) ++cnt;
        else {
            if (cnt > 1) {
                target = X / prev + ((0 != X % prev) ? 1 : 0);
                if (prev >= target && cnt > 3)++ans;
                auto itor = std::lower_bound(A.begin() + i, A.end(), target);
                if (A.end() != itor) ans += evenCnt[itor - A.begin()];
            }
            cnt = 1, prev = i < len ? A[i] : 0;
        }
    }
    return ans > 1000000000 ? -1 : static_cast<int>(ans);
}


int solution(vector<int>& A, int X) {
    if (A.size() < 2) { return 0; }

    // reduce double fences to single array
    std::unordered_map<int, int> fenceCnt;
    for (auto const& a : A) {
        if (fenceCnt.find(a) != fenceCnt.end()) { fenceCnt[a]++; }
        else { fenceCnt[a] = 1; }
    }
    vector<int> fence;
    for (auto const& it : fenceCnt) {
        for (int i = 0; i < it.second / 2; i++) {
            fence.push_back(it.first);
        }
    }
    std::sort(fence.begin(), fence.end());

    // count reuseble fence as suffix, e.g., square pen
    int sz = fence.size(); int cntR = 0;
    vector<int> suffixCnt(sz, 0);
    int lastFence = fence[sz - 1];
    for (int i = sz - 2; i >= 0; i--) {
        if (fence[i] == lastFence) { cntR++; }
        suffixCnt[i] = cntR;
        lastFence = fence[i];
    }

    // use BS to find the suitable fence for each
    int ret = 0;
    for (auto it = fence.begin(); it != fence.end(); it++) {
        if ((it != fence.begin()) && (*it == *std::prev(it))) { // skip same length fence
            continue;
        }
        auto lower = std::lower_bound(std::next(it), fence.end(), (X + *it - 1) / *it);
        if (lower != fence.end()) { // can build area larger than X
            int ind = std::distance(fence.begin(), lower);
            ret += sz - ind - suffixCnt[ind];
            if (ret > 1000000000) { ret = -1; break; }
        }
    }
    return ret;
}