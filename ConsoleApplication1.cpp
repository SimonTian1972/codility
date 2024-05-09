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


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

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



#include <vector>
#include <algorithm>

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
    unordered_map<int, vector<int>> myMap; // num, count
    for (int i = 0; i < A.size(); i++) {
        myMap[A[i]].push_back(i);
    }

    int largest = 0;
    int idx = -1;
    for (auto myPair : myMap) {
        if (myPair.second.size() > largest) {
            largest = myPair.second.size();
            idx = myPair.second[0];
        }
    }

    const int N = A.size();
    if (largest > N / 2) {
        return idx;
    }
    else {
        return -1;
    }
}

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
    unordered_map<int, vector<int>> myMap; // num, count
    for (unsigned int i = 0; i < A.size(); i++) {
        myMap[A[i]].push_back(i);
    }

    unsigned int largest = 0;
    int idx = -1;
    for (auto myPair : myMap) {
        if (myPair.second.size() > largest) {
            largest = myPair.second.size();
            idx = myPair.second[0];
        }
    }

    const unsigned int N = A.size();
    if (largest > N / 2) {
        return idx;
    }
    else {
        return -1;
    }
}

