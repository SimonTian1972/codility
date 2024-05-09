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

int solution(vector<int>& A, vector<int>& B) {
    // Implement your solution here
    const int len = A.size();
    stack<int> myStack;
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (B[i] == 1) { // push to stack donw stream
            myStack.push(A[i]);
        }
        else { // up stream
            if (myStack.empty()) {
                count++;
            }
            else {
                while (myStack.empty() == false) {
                    int top = myStack.top();
                    if (top > A[i]) {
                        break;
                    }
                    else {
                        myStack.pop();
                    }
                }
                if (myStack.empty()) {
                    count++;
                }
            }
        }
    }
    return count + myStack.size();
}
