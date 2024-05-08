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

vector<int> solution(string& S, vector<int>& P, vector<int>& Q) {
    int N = S.size();
    int M = P.size();

    // Create prefix sum arrays for each nucleotide type
    vector<int> A(N + 1, 0);
    vector<int> C(N + 1, 0);
    vector<int> G(N + 1, 0);
    vector<int> T(N + 1, 0);

    for (int i = 0; i < N; ++i) {
        A[i + 1] = A[i] + (S[i] == 'A' ? 1 : 0);
        C[i + 1] = C[i] + (S[i] == 'C' ? 1 : 0);
        G[i + 1] = G[i] + (S[i] == 'G' ? 1 : 0);
        T[i + 1] = T[i] + (S[i] == 'T' ? 1 : 0);
    }

    vector<int> result;

    // For each query, find the minimal impact factor
    for (int i = 0; i < M; ++i) {
        int start = P[i];
        int end = Q[i] + 1; // Adding 1 to include the end position
        if (A[end] - A[start] > 0)
            result.push_back(1);
        else if (C[end] - C[start] > 0)
            result.push_back(2);
        else if (G[end] - G[start] > 0)
            result.push_back(3);
        else
            result.push_back(4);
    }

    return result;
}
