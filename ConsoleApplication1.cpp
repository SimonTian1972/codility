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


// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;


int solution(vector<int>& A, int X) {
    // Implement your solution here
    map<double, int> myMap; // len, count
    for (auto& item : A) {
        myMap[item]++;
    }
    for (auto& myPair : myMap) {
        myMap[myPair.first] = myPair.second / 2; // 2 fences per length or width
    }

    set<double> mySet;
    for (auto& myPair : myMap) {
        if (myPair.second != 0) {
            mySet.insert(myPair.first);
        }
    }


    long long ret = 0;
    for (auto& item : mySet) {
        double width = item;
        double height = X / width;

        auto valid = mySet.lower_bound(height);
        int start_count = 1;
        int end_count = distance(valid, mySet.end());
        if (width < height) {
            ret += start_count * end_count;
        }
        //cout << "width= " << width << " height= " << height << " end_count= " << end_count << endl;
    }

    if (ret > 1000000000) {
        return -1;
    }
    else {
        return static_cast<int>(ret);
    }
}

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <map>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

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
#include <string>       // std::string
#include <sstream> 
//#include <bits/stdc++.h>
using namespace std;


#include <semaphore>
#include <future>
#include <thread>


#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define cat(x, y) x##y

int main() {
    int var123 = 123;
    int result = cat(cat(1, 2), 3);  // Expands to var123
    printf("%d\n", result);  // Should print 123
    return 0;
}



int inspect_bits(unsigned int number)
{
    int count = 0;
    while (number != 0) {
        if (number & 0x1) {
            count++;
        }
        else {
            count = 0;
        }
        number = number >> 1;
        if (count >= 2) {
            return 1;
        }
    }
    // Waiting to be implemented
    return -1; // wrong !
}


#import <stdio.h>
#import <stdlib.h>
#include <stdbool.h>

typedef struct Video {
    char* name;
    int unique_views;
} Video;

typedef struct Viewer {
    char* username;
    Video* watched_videos;
    int watched_videos_size;
} Viewer;

bool is_equal(char* p1, char* p2) {
    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2) {
            return false;
        }
        p1++;
        p2++;
    }
    if (*p1 == '\0' && *p2 == '\0') {
        return true;
    }
    else {
        return false;
    }
}

int count_views(Viewer** viewers, int viewers_size, char* video_name)
{
    int count = 0;
    // Waiting to be implemented
    for (int v = 0; v < viewers_size; v++) {
        Viewer* viewerP = viewers[v];
        for (int i = 0; i < viewerP->watched_videos_size; i++) {
            Video cur = viewerP->watched_videos[i];
            char* video_cur = cur.name;
            if (is_equal(video_cur, video_name)) {
                count++;
            }
        }
    }
    return count;
}

#ifndef RunTests
int main()
{
    Video videos[] = { {.name = "Soccer", .unique_views = 500},
                       {.name = "Basketball", .unique_views = 1000} };
    Viewer viewer = { .username = "Dave", .watched_videos = videos,
                     .watched_videos_size = 2 };

    Viewer* viewers[] = { &viewer };
    printf("%d", count_views(viewers, 1, "Soccer")); /* should print 1 */
}
#endif


#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

int contains(const Node* root, int value)
{
    if (root == NULL) {
        return 0;
    }

    if (root->value == value) {
        return 1;
    }

    if (contains(root->left, value) == 1 || contains(root->right, value) == 1)
    {
        return 1;
    }
    // Waiting to be implemented
    return 0;
}

#ifndef RunTests
int main()
{
    Node n1 = { .value = 1, .left = NULL, .right = NULL };
    Node n3 = { .value = 3, .left = NULL, .right = NULL };
    Node n2 = { .value = 2, .left = &n1, .right = &n3 };

    printf("%d", contains(&n2, 3));
}
#endif

#include <stdio.h>

typedef struct UserInfo
{
    long long credit_amount;
    char* name;
    float interest;
    int account_number;
    int years_member;
    int id;
    short account_type_code;
    char gender;
    char credit_rating;
} UserInfo;

#ifndef RunTests
int main()
{
    printf("%d", sizeof(UserInfo));
}
#endif



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int cmpfunc(char* p1, char* p2) {
    while (*p1 != '\0' and *p2 != '\0') {
        if (*p1 == *p2) {
            continue;
        }
        else {
            return *p2 - *p1;
        }
    }

    if (*p1 == '\0' && *p2 == '\0') {
        return 0;
    }
    else if (*p1 == '\0') {
        return 1;
    }
    else {
        return -1;
    }
}

void sort_words(char* words[], int count)
{
    // Waiting to be implemented
    qsort(words, count, sizeof(char*), cmpfunc);
    return;
}

#ifndef RunTests
int main()
{
    char* words[] = { "cherry", "orange", "apple" };

    sort_words(words, 3);

    for (int i = 0; i < 3; i++)
    {
        printf("%s ", words[i]);
    }
}
#endif


int cmpfunc(const void* a, const void* b) {
    const char** p1 = (const char**)a;
    const char** p2 = (const char**)b;

    return -strcmp(*p1, *p2);  // negate result of strcmp for descending order
}

void sort_words(char* words[], int count) {
    qsort(words, count, sizeof(char*), cmpfunc);
}

#include <stdlib.h>
#include <stdio.h>

void find_roots(double a, double b, double c, double* root1, double* root2)
{
    // Waiting to be implemented
    double mid = sqrt(b * b - 4 * a * c);
    *root1 = (-b + mid) / 2 / a;
    *root2 = (-b - mid) / 2 / a;
    return;
}

#ifndef RunTests
int main()
{
    double root1, root2;
    find_roots(2, 10, 8, &root1, &root2);
    printf("Roots: %f, %f", root1, root2);
}
#endif




#include <stdio.h>
#include <stdbool.h>
int dir[5] = { 0, -1, 0 ,1, 0 };

bool can_go(int** visit, bool* game_matrix, int rows, int cols, int from_row,
    int from_column, int to_row, int to_column) {

    if (visit[from_row][from_column] != 0) {
        return false;
    }
    visit[from_row][from_column] = 1;

    if ((game_matrix + from_row * cols)[from_column] == false) {
        return false;
    }
    if (from_row == to_row && from_column == to_column) {
        return true;
    }

    if (from_row < 0 || from_row >= rows) {
        return false;
    }
    if (from_column < 0 || from_column >= cols) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        if (can_go(visit, game_matrix, rows, cols, from_row + dir[i],
            from_column + dir[i + 1], to_row, to_column) == true) {
            return true;
        }

    }
    return false;
}


bool can_travel_to(bool* game_matrix, int rows, int cols, int from_row,
    int from_column, int to_row, int to_column)
{
    int** visit = calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; i++) {
        visit[i] = calloc(cols, sizeof(int));
    }
    bool ret = can_go(visit, game_matrix, rows, cols, from_row,
        from_column, to_row, to_column);

    // Write your code here
    for (int i = 0; i < rows; i++) {
        free(visit[i]);
    }
    free(visit);
    return ret;
}

#ifndef RunTests
int main()
{
    bool game_matrix[6][6] = {
        {false, true,  true,  false, false, false},
        {true,  true,  true,  false, false, false},
        {true,  true,  true,  true,  true,  true},
        {false, true,  true,  false, true,  true},
        {false, true,  true,  true,  false, true},
        {false, false, false, false, false, false},
    };

    printf("%d\n", can_travel_to((bool*)game_matrix, 6, 6, 3, 2, 2, 2)); // true, Valid move
    printf("%d\n", can_travel_to((bool*)game_matrix, 6, 6, 3, 2, 3, 4)); // false, Can't travel through land
    printf("%d\n", can_travel_to((bool*)game_matrix, 6, 6, 3, 2, 6, 2)); // false, Out of bounds
}
#endif

