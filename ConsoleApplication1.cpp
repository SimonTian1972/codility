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
    const int N = A.size();
    int minPos = -1;
    double minVal = INT_MAX;
    vector<int> sums(N, 0);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum = sum + A[i];
        sums[i] = sum;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double temp = static_cast<double>(sums[j] - sums[i] +A[i]) / (j - i + 1);
            if (temp < minVal) {
                minVal = temp;
                minPos = i;
            }
        }
    }
    return minPos;
}



int solution(vector<int>& A) {
    // Implement your solution here
    const int N = A.size();
    int minPos = -1;
    double minVal = INT_MAX;
    vector<int> sums(N, 0);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum = sum + A[i];
        sums[i] = sum;
    }
    for (int i = 0; i < N; i++) {        
        if (i > 0 && A[i-1] < minVal) {
            continue;
        }
        for (int j = i + 1; j < N; j++) {
            double temp = static_cast<double>(sums[j] - sums[i] + A[i]) / (j - i + 1);
            if (temp < minVal) {
                minVal = temp;
                minPos = i;
            }
        }
    }
    return minPos;
}


(1) There must be some slices, with length of two or three, having the minimal average value among all the slices.
(2) And all the longer slices with minimal average are built up with these 2 - element and /or 3 - element small slices.

Firstly we will prove the statement(1).In all the following discussion, we assume the slices have two or more element.In every array, there must be at lease one slice, to say S, having the Minimal Average(MA).And PLEASE PAY ATTENTION, the following proof is done with the S, which HAS the global minimal average.

If the length of S is two or three, it follows our conclusion.
If the length of S is odd, we could divide it into a 3 - element sub - slice and some 2 - element sub - slice.For example, for the slice[1, 2, 3, 4, 5], we could get a 3 - element sub - slice[1, 2, 3] and a 2 - element sub - slice[4, 5].Or differently we could get[1, 2] and [3, 4, 5].But the split does not matter in the following prove.
If the sub - slices have different averages, some of them will have smaller average than MA.But it conflicts with the condition that, the MA is known as the global minimal average for all slices.By this contradictory, it’s proved that all the sub - slices MUST have the same average.
If all the sub - slices have the same average, the average of them must be MA.So all these sub - slices have overall minimal average and length of two or three.
If the length of S is even, we could divide it into some 2 - element sub - slice.For the slice[1, 2, 3, 4], the only possible split is[1, 2] and [3, 4].Then, similar with the previous case, all these 2 - element sub - slices have the global minimal average.
And in the construction in step b, we have already proven the statement(2).

UPDATE 03 - 13 - 2014: We are NOT proving that, 4 - or -more - element slices cannot have the global minimal average.We just proved that, there MUST be some 2 - element and /or 3 - element slices, having the global minimal average.In other words, we are NOT SURE whether there are some 4 - or -more - element slices holding global minimal average.But we are ONE HUNDRED PERCENT SURE about the 2 - element and /or 3 - element slices.

    UPDATE 03 - 02 - 2015 : There is another excellent discussion in the comments by Kim.Thanks!

    UPDATE 03 - 14 - 2016 : If you had any question about the statement “If the sub - slices have different averages, some of them will have smaller average than MA”, please read this commentand this comment.Thanks!

    Solution to Min - Avg - Two - Slice by codilityPython
    def solution(A) :
    min_avg_value = (A[0] + A[1]) / 2.0   # The mininal average
    min_avg_pos = 0     # The begin position of the first
    # slice with mininal average
    for index in xrange(0, len(A) - 2) :
        # Try the next 2 - element slice
        if (A[index] + A[index + 1]) / 2.0 < min_avg_value:
min_avg_value = (A[index] + A[index + 1]) / 2.0
min_avg_pos = index
# Try the next 3 - element slice
if (A[index] + A[index + 1] + A[index + 2]) / 3.0 < min_avg_value:
min_avg_value = (A[index] + A[index + 1] + A[index + 2]) / 3.0
min_avg_pos = index
# Try the last 2 - element slice
if (A[-1] + A[-2]) / 2.0 < min_avg_value:
min_avg_value = (A[-1] + A[-2]) / 2.0
min_avg_pos = len(A) - 2
return min_avg_pos



