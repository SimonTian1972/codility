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

#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

void resetTable(bool* table, int M)
{
    for (int i = 0; i <= M; i++)
    {
        table[i] = false;
    }
}

int solution(int M, vector<int>& A) {
    bool* seen = new bool[M + 1];

    int front = 0;
    int back = 0;
    int total = 0;

    resetTable(seen, M);

    while (front < A.size() && back < A.size())
    {
        // move front foward as far as posiible
        while (front < A.size() && seen[A[front]] == false)
        {
            seen[A[front]] = true;

            // Add the number of toatal sequecnes:
            // (A[back], A[front]), (A[back+1], A[front]), (A[back+2], A[front]) ..., (A[front], A[front])
            total += front - back + 1;

            if (total >= 1000000000)
            {
                return 1000000000;
            }

            // cout<< "+" << front- back + 1 << endl;
            front++;
        }

        // move back to the dupicate value
        while (front < A.size() && back < A.size() && A[back] != A[front])
        {
            seen[A[back]] = false; // reset
            back++;
        }

        // make back to next number
        seen[A[back]] = false;
        back++;

    }
    return total;
}
