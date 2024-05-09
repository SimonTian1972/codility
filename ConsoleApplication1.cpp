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




def solution(A) :
    A_len = len(A)    # The length of array A
    # Get the sum of maximum subarray, which ends this position
    # Method: http://en.wikipedia.org/wiki/Maximum_subarray_problem
max_ending_here = [0] * A_len
max_ending_here_temp = 0
for index in range(1, A_len - 2) :
    max_ending_here_temp = max(0, A[index] + max_ending_here_temp)
    max_ending_here[index] = max_ending_here_temp
    # Get the sum of maximum subarray, which begins this position
    # The same method.But we travel from the tail to the head
    max_beginning_here = [0] * A_len
    max_beginning_here_temp = 0
    for index in range(A_len - 2, 1, -1) :
        max_beginning_here_temp = max(0, A[index] + max_beginning_here_temp)
        max_beginning_here[index] = max_beginning_here_temp
        # Connect two subarray for a double_slice.If the first subarray
        # ends at position i, the second subarray starts at position i + 2.
        # Then we compare each double slice to get the one with the
        # greatest sum.
        max_double_slice = 0
        for index in range(0, A_len - 2) :
            max_double_slice = max(max_double_slice,
                max_ending_here[index] + max_beginning_here[index + 2])
            return max_double_slice