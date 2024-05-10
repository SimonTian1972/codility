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


#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

int solution(int M, vector<int>& A) {
    unordered_set<int> seen;
    int front = 0, back = 0, total = 0;

    auto resetTable = [&seen]() {
        seen.clear();
    };

    while (front < A.size() && back < A.size()) {
        while (front < A.size() && seen.find(A[front]) == seen.end()) {
            seen.insert(A[front]);
            total += front - back + 1;

            if (total >= 1000000000) {
                return 1000000000;
            }

            front++;
        }

        while (front < A.size() && back < A.size() && A[back] != A[front]) {
            seen.erase(A[back]);
            back++;
        }

        seen.erase(A[back]);
        back++;
    }

    return total;
}


#include <vector>
#include <iostream>

using namespace std;

int solution(int M, vector<int>& A) {
    vector<bool> seen(M + 1, false);
    int front = 0, back = 0, total = 0;

    auto resetTable = [&seen]() {
        fill(seen.begin(), seen.end(), false);
    };

    while (front < A.size() && back < A.size()) {
        while (front < A.size() && !seen[A[front]]) {
            seen[A[front]] = true;
            total += front - back + 1;

            if (total >= 1000000000) {
                return 1000000000;
            }

            front++;
        }

        while (front < A.size() && back < A.size() && A[back] != A[front]) {
            seen[A[back]] = false;
            back++;
        }

        seen[A[back]] = false;
        back++;
    }

    return total;
}

