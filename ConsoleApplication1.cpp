#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;


// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <vector>
#include <string>

using namespace std;



int solution1(vector<int>& A) {
    // Implement your solution here
    int count = 0;
    const int N = A.size();
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (abs(i - j) <= A[i] + A[j]) {
                count++;
            }
        }
    }
    return count;
}


int solution(vector<int>& A) {
    // Implement your solution here
    int count = 0;
    vector<vector<int>> sortSec;
    for (int i = 0; i < A.size(); i++) {
        sortSec.push_back({i - A[i], i + A[i] });
    }
    sort(sortSec.begin(), sortSec.end());
    auto it = sortSec.begin();
    for (int i = 0; i < sortSec.size(); i++) {
        int end = sortSec[i][1];
        auto next = upper_bound(it + i, sortSec.end(), vector<int>{end, 0});

        int temp = distance(next, it + i);
        count = count + (temp - 1);
    }
    return count;
}

int solution(vector<int>& A) {

    using segment = std::pair<int, int>;
    const auto MAX_INTERSECTIONS = 10000000;
    int intersections = 0;

    size_t v_size = A.size();

    // create an array of pairs, each containing the start and end indices of a disk
    vector<segment> segments;
    // reserve the memory for all the pairs to avoid of many allocations
    segments.reserve(v_size);

    // Add the pairs to the array
    for (size_t i = 0; i < v_size; ++i) {
        int radius = A[i];
        // If radius of the circle is bigger than distance to the origin of the coordinate axis or
        // the radius is bigger than length of the given array
        // add this segment to the first point or to the last point.
        // We do this to avoid of scanning from MIN_INT to MAX_INT
        // because the task defines the range started from 0 to end of the given array.
        // We don't need to work outside of this range
        int begin = max(0, static_cast<int>(i) - radius);
        int end = min(v_size - 1, i + radius);
        segments.emplace_back(begin, end);
    }

    // sort the array by the first entry of each pair: the disk start indices
    sort(segments.begin(), segments.end());

    for (size_t i = 0; i < v_size; ++i) {
        // for each disk in order of the *starting* position of the disk, not the centre
        // find the end position of that disk from the array of tuples
        auto disk_end = segments[i].second;
        // find the index of the rightmost value less than or equal to the interval-end
        // this finds the number of disks that have started before disk i ends
        auto it = upper_bound(segments.begin(), segments.end(), make_pair(disk_end, 0),
            [](segment lhs, segment rhs) -> bool { return lhs.first < rhs.first; });

        auto count = distance(segments.begin(), it);

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




