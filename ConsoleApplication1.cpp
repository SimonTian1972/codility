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

int solution(vector<int>& H) {
    // Implement your solution here
    stack<int> myStack;
    const int N = H.size();
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (myStack.empty()) {
            myStack.push(H[i]);
        }
        else {
            if (myStack.top() < H[i]) {
                myStack.push(H[i]);
            }
            else {
                bool keep = true;
                while (myStack.empty() == false) {
                    int top = myStack.top();
                    if (top > H[i]) {
                        myStack.pop();
                        count++;
                        cout << "top= " << top << "count= " << count << "cur=" << H[i] << endl;
                    }
                    else if (top == H[i]) {
                        myStack.pop();
                        count++;
                        keep = false;
                        cout << "top= " << top << "count= " << count << "cur=" << H[i] << endl;
                        break;
                    }
                    else { // top < H[i]
                        myStack.push(H[i]);
                        break;
                    }
                }
                if (myStack.empty() == true && keep == true) {
                    myStack.push(H[i]);
                }
            }
        }
    }
    cout << "myStack.size()= " << myStack.size() << "count= " << count << endl;
    cout << "top= " << myStack.top() << endl;
    return count + myStack.size();
}