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

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;





int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    long long smallSum = 0;
    vector<long long> leftSum(N, 0);
    for (int i = 0; i < N; i++) {

    }

    vector<long long> rightSum(N, 0); // get rid of two smallest ones
    int smallest = 0;
    int small2nd = 0;
    long long bigSum = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (A[i] < smallest) {
            small2nd = smallest;
            smallest = A[i];
        } else if (A[i] < small2nd) {
            small2nd = A[i];
        }
        bigSum = bigSum + A[i];
        rightSum[i] = bigSum - smallest - small2nd;
    }

    int ret = INT_MIN;
    for (int i = 0; i < N-2; i++) {
        long long temp = leftSum[i];
        temp = temp + rightSum[i + 1];
        if (temp > ret) {
            ret = temp;
        }
    }
    return ret;
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
    const int N = A.size();
    vector<long long> rightSum(N, 0); // get rid of two smallest ones
    int smallest = 0;
    int small2nd = 0;
    long long bigSum = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (A[i] < smallest) {
            small2nd = smallest;
            smallest = A[i];
        }
        else if (A[i] < small2nd) {
            small2nd = A[i];
        }
        bigSum = bigSum + A[i];
        rightSum[i] = bigSum - smallest - small2nd;
    }

    int ret = INT_MIN;
    for (int i = 1; i < N - 2; i++) {
        cout << "righSum= " << rightSum[i + 1] << endl;
        if (rightSum[i + 1] > ret) {
            ret = rightSum[i + 1];
        }
    }
    if (ret == INT_MIN) {
        return 0;
    }
    else {
        return ret;
    }
}
