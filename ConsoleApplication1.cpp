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
#include <string>
#include <sstream>
using namespace std;



int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    vector<int> leftH(N, 0);
    vector<int> rightH(N, 0);
    int high = A[0];
    for (int i = 1; i < N; i++) {
        leftH[i] = high;
        high = max(high, A[i]);
    }
    high = A[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        rightH[i] = high;
        high = max(high, A[i]);
    }

    int deep = 0;
    for (int i = 1; i <= N - 2; i++) {
        int curDeep = min(leftH[i] - A[i], rightH[i] - A[i]);
        deep = max(deep, curDeep);
    }
    return deep;
}
