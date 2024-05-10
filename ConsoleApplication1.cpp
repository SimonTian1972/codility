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
    sort(A.begin(), A.end(), greater<int>());
    int count = 0;
    for (int front = 0; front < N-2; front++) {
        for (int back1 = front + 1; back1 < N - 1; back1++) {
            for (int back2 = back1 + 1; back2 < N; back2++) {
                if (A[back1] + A[back2] > A[front]) {
                    count++;
                }
            }
        }

    }
    return count;
}

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    sort(A.begin(), A.end(), greater<int>());
    int count = 0;
    for (int front = 0; front < N - 2; front++) {
        for (int back1 = front + 1; back1 < N - 1; back1++) {
            // find back2 such back1+back2 <= front
            int target = A[front] - A[back1];
            auto it = find_if(A.begin() + back1 + 1, A.end(), [target](int val) {
                return val < target;
                });
            int temp = distance(A.begin() + back1 + 1, it);
            cout << "temp = " << temp << endl;
            count += temp;
        }
    }
    return count;
}

int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    sort(A.begin(), A.end(), greater<int>());
    int count = 0;
    for (int front = 0; front < N - 2; front++) {
        for (int back1 = front + 1; back1 < N - 1; back1++) {
            // find back2 such back1+back2 <= front
            int target = A[front] - A[back1];
            auto it = find_if(A.begin() + back1 + 1, A.end(), [target](int val) {
                return val <= target;
                });
            int temp = distance(A.begin() + back1 + 1, it);
            //cout << "temp = " << temp << endl;
            count += temp;
        }
    }
    return count;
}
