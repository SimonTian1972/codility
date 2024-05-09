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

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    vector<int> leftLeader(N, -1);
    vector<int> rightLeader(N, -1);
    map<int, int> leftCount; // num, count
    map<int, int> rightCount;

    int largest = 0;
    for (int i = 0; i < N; i++) {
        leftCount[A[i]]++;
        if (leftCount[A[i]] > largest) {
            largest = leftCount[A[i]];
            if (largest > (i + 1) / 2) {
                leftLeader[i] = A[i];
            }
        } else {
            if (largest > (i + 1) / 2) {
                leftLeader[i] = leftLeader[i-1];
            }
        }
    } // leftLeader

    largest = 0;
    for (int i = N - 1; i >= 0; i--) {
        rightCount[A[i]]++;
        if (rightCount[A[i]] > largest) {
            largest = rightCount[A[i]];
            if (largest > (N-i) / 2) {
                rightLeader[i] = A[i];
            }
        } else {
            if (largest > (N-i) / 2) {
                rightLeader[i] = rightLeader[i+1];
            }
        }
    }// rightLeader

    int count = 0;
    for (int i = 0; i < N - 1; i++) {
        int j = i + 1;
        if (leftLeader[i] == rightLeader[j] && leftLeader[i] != -1) {
            count++;
        }
    }
    return count;
}

