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

class Solution {
public:
    // 辅函数
    int lower_bound1(vector<int>& nums, int target) {
        int l = 0, r = nums.size(), mid;
        while (l < r) {
            mid = l + (r - l) / 2;
            if (nums[mid] >= target) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }

    int lower_bound2(vector<int>& nums, int target) {
        const int N = nums.size();
        int s = 0;
        int e = N - 1;
        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (nums[mid] >= target) {
                e = mid - 1;
            }
            else {
                s = mid + 1;
            }
        }
        return s;
    }

    int lower_bound(vector<int>& nums, int target) {
        const int N = nums.size();
        int s = 0;
        int e = N - 1;
        int ret = N;
        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (nums[mid] >= target) {
                ret = mid;
                e = mid - 1;
            }
            else {
                s = mid + 1;
            }
        }
        return ret;
    }

    int upper_bound(vector<int>& nums, int target) {
        const int N = nums.size();
        int s = 0;
        int e = N - 1;
        int ret = N;
        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (nums[mid] > target) {                
                ret = N;
                e = mid - 1;
            }
            else {
                s = mid + 1;
            }
        }
        return s;
    }


    int upper_bound2(vector<int>& nums, int target) {
        const int N = nums.size();
        int s = 0;
        int e = N - 1;
        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (nums[mid] > target) {
                e = mid - 1;
            }
            else {
                s = mid + 1;
            }
        }
        return s;
    }


    int upper_bound1(vector<int>& nums, int target) {
        int l = 0, r = nums.size(), mid;
        while (l < r) {
            mid = l + (r - l) / 2;
            if (nums[mid] > target) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return vector<int>{-1, -1};
        int lower = lower_bound(nums, target);
        int upper = upper_bound(nums, target) - 1; // 这里需要减1位
        if (lower == nums.size() || nums[lower] != target) {
            return vector<int>{-1, -1};
        }
        return vector<int>{lower, upper};
    }

};