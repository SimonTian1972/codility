﻿#include <map>
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



#include <vector>
#include <algorithm>

int solution(std::vector<int>& A) {
    int count = 0;
    std::vector<std::vector<long long>> sortSec;
    for (size_t i = 0; i < A.size(); i++) {
        long long start = static_cast<long long>(i) - static_cast<long long>(A[i]);
        long long end = static_cast<long long>(i) + static_cast<long long>(A[i]);
        sortSec.push_back({ start, end });
    }
    std::sort(sortSec.begin(), sortSec.end());
    auto it = sortSec.begin();
    for (unsigned int i = 0; i < sortSec.size(); i++) {
        long long end = sortSec[i][1];
        auto next = std::upper_bound(it + i, sortSec.end(), std::vector<long long>{end, 0},
            [](const std::vector<long long>& lhs, const std::vector<long long>& rhs) -> bool { return lhs[0] < rhs[0]; });

        int temp = static_cast<int>(std::distance(it + i, next));
        if (temp > 1) {
            count = count + (temp - 1);
        }
    }
    return count;
}