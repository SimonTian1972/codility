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

#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int>& A) {
    const auto MAX_INTERSECTIONS = 10000000;
    int intersections = 0;
    int v_size = A.size();

    // create a vector of vectors, each containing two integers representing a segment
    vector<vector<int>> segments;
    // reserve the memory for all the vectors to avoid many allocations
    segments.reserve(v_size);

    // Add the pairs to the array
    for (int i = 0; i < v_size; ++i) {
        int radius = A[i];
        int begin = max(0, static_cast<int>(i) - radius);
        int end = min(v_size - 1, i + radius);
        segments.push_back({ begin, end });
    }

    // sort the array by the first entry of each pair: the disk start indices
    sort(segments.begin(), segments.end());

    for (int i = 0; i < v_size; ++i) {
        // for each disk in order of the *starting* position of the disk, not the centre
        // find the end position of that disk from the array of vectors
        int disk_end = segments[i][1];
        // find the index of the rightmost value less than or equal to the interval-end
        // this finds the number of disks that have started before disk i ends
        //auto it = upper_bound(segments.begin(), segments.end(), vector<int>{disk_end, INT_MAX});

        auto it = upper_bound(segments.begin(), segments.end(), disk_end,
            [](const int lhs, const vector<int>& rhs) -> bool { return lhs < rhs[0]; });

        int count = distance(segments.begin(), it);
        cout << "count= " << count << endl;

        // subtract current position to exclude previous matches
        // for disk i, i disks that start to the left have already been dealt with
        // subtract i from count to prevent double counting
        // subtract one more to prevent counting the disk itself
        count -= (i + 1);
        intersections += count;
        if (intersections > MAX_INTERSECTIONS) {
            return -1;
        }
    }
    return intersections;
}

int main() {
    vector<int> A = { 1, 5, 2, 1, 4, 0 };
    cout << "Result: " << solution(A) << endl;
    return 0;
}
