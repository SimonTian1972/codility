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

#include <iostream>
#include <vector>
#include <iterator>


bool blocksEnough(vector<int>& A, int max, int K)
{
    int block = 1;
    int sum = 0;
    int size = (int)A.size();

    // check if the blocks are enough (less than or equal to K)
    for (int i = 0; i < size; i++)
    {
        if (sum + A[i] <= max)
        {
            sum += A[i];
        }
        else
        {
            // The sum in this block is larger than max, so add a new block to add A[i].
            // cout<< block << ":" << sum << endl;
            block++;
            sum = A[i];
        }

        // If number of blocks is larger than K, return false
        if (block > K)
        {
            return false;
        }
    }

    return true;
}

int solution(int K, int M, vector<int>& A)
{
    int max = 0;
    int min = 0;
    int size = (int)A.size();

    // get the sum of vector, which is set to the upperbound
    vector<int>::iterator it;
    for (it = A.begin(); it != A.end(); it++)
    {
        max += *it;
    }

    // get maximum value in the vector, which is set to the lowerbound
    min = *max_element(A.begin(), A.end());

    // handle special case
    if (K >= size)
    {
        return min;
    }
    else if (K == 1)
    {
        return max;
    }

    // do binary search
    while (min <= max)
    {
        int mid = (min + max) / 2;

        if (blocksEnough(A, mid, K))
        {
            max = mid - 1;
        }
        else
        {
            min = mid + 1;
        }
    }

    return min;
}

