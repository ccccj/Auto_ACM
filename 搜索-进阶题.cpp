//
//  main.cpp
//  搜索进阶
//
//  Created by admin on 18/8/24.
//  Copyright © 2018年 Amon. All rights reserved.
//
Problem E: 下山
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 43  Solved: 20
[Submit][Status][Web Board][Creator:201506020829][Edit] [TestData]
Description
下面的矩阵可以想象成鸟瞰一座山，矩阵内的数据可以想象成山的高度。
可以从任意一点开始下山。每一步的都可以朝“上下左右”4个方向行走，前提是下一步所在的点比当前所在点的数值小。

例如处在18这个点上，可以向上、向左移动，而不能向右、向下移动。

1  2  3  4 5

16 17 18 19 6

15 24 25 20 7

14 23 22 21 8

13 12 11 10 9

问题是，对于这种的矩阵，请计算出最长的下山路径。
对于上面所给出的矩阵，最长路径为25-24-23-22-21-20-19-18-17-16-15-14-13-12-11-10-9-8-7-6-5-4-3-2-1，应输出结果25。
Input
输入包括多组测试用例。
对于每个用例，第一行包含两个正整数R和C分别代表矩阵的行数和列数。(1 <= RC <= 100)

从第二行开始是一个R行C列矩阵，每点的数值在[010000]内。

Output
输出最长的下山路径的长度。
Sample Input
5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
Sample Output
25

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int n, m, Map[110][110], maxmap[110][110];
bool vis[110][110];

int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int cnt, Max;

bool canstay(int a, int b, int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m
         && Map[x][y] > Map[a][b]) {
        return 1;
    }
    return 0;
}

void dfs(int a, int b) {
    if (maxmap[a][b] != 0) {
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int x = a + dir[i][0], y = b + dir[i][1];
        if (canstay(a, b, x, y)) {
            dfs(x, y);
            maxmap[a][b] = max(maxmap[x][y], maxmap[a][b]);
        }
    }
    maxmap[a][b]++;
}

int main() {
    while (cin >> n >> m) {
        cnt = 1;
        Max = 0;
        memset(maxmap, 0, sizeof(maxmap));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> Map[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                memset(vis, 0, sizeof(vis));
                dfs(i, j);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                Max = max(Max, maxmap[i][j]);
            }
        }
        cout << Max << endl;
        
    }
    return 0;
}

/*
Problem A: division
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 13  Solved: 4
[Submit][Status][Web Board][Creator:201506020829][Edit] [TestData]
Description
Write a program that finds and displays all pairs of 5-digit numbers that between them use the digits 0 through 9 once each such that the first number divided by the second is equal to an integer N where 2 ≤ N ≤ 79. That is

abcde /  ghij = N

where each letter represents a different digit. The first digit of one of the numerals is allowed to be zero.

Input
Each line of the input file consists of a valid integer N. An input of zero is to terminate the program.

Output
Your program have to display ALL qualifying pairs of numerals sorted by increasing numerator (and of course denominator). Your output should be in the following general form:

xxxxx / xxxxx = N

In case there are no pairs of numerals satisfying the condition you must write ‘There are no solutions for N.’. Separate the output for two different values of N by a blank line.

Sample Input
61
62
0
Sample Output
There are no solutions for 61.

79546 / 01283 = 62
94736 / 01528 = 62

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int arr[10], vis[10], n, f, vis1[10];

int judge(int x) {
    for (int i = 0; i < 5; ++i) {
        if (vis[x % 10] == 1 || vis1[x % 10] == 1) {
            return -1;
        } else {
            vis1[x % 10] = 1;
        }
        x /= 10;
    }
    if (x > 0) {
        return -1;
    }
    return 1;
}

int find_num() {
    int x = 0;
    for (int i = 0; i < 5; ++i) {
        x += arr[i] * pow(10, 4 - i);
    }
    if (judge(x * n) != -1) {
        return x * n;
    }
    return -1;
}

void dfs(int now) {
    if (now == 5) {
        int k = find_num();
        if (k != -1) {
            cout << k << " / ";
            for (int i = 0; i < 5; ++i) {
                cout << arr[i];
            }
            printf(" = %d\n", n);
            f = 1;
        }
        memset(vis1, 0, sizeof(vis1));
        return;
    }
    for (int i = 0; i < 10; ++i) {
        if (vis[i] == 0) {
            arr[now] = i;
            vis[i] = 1;
            dfs(now + 1);
            vis[i] = 0;
        }
    }
}

int main() {
    int ca = 0;
    while (cin >> n && n) {
        if (ca++ > 0) {
            cout << endl;
        }
        f = 0;
        memset(vis, 0, sizeof(vis));
        memset(vis1, 0, sizeof(vis1));
        dfs(0);
        if (f == 0) {
            printf("There are no solutions for %d.\n", n);
        }
    }
    return 0;
}


Problem F: N皇后问题
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 35  Solved: 23
[Submit][Status][Web Board][Creator:201506020829][Edit] [TestData]
Description
在N*N的方格棋盘放置了N个皇后，使得它们不相互攻击（即任意2个皇后不允许处在同一排，同一列，也不允许处在与棋盘边框成45角的斜线上。
你的任务是，对于给定的N，求出有多少种合法的放置方法。
Input
共有若干行，每行一个正整数N≤10，表示棋盘和皇后的数量；如果N=0，表示结束。
Output
共有若干行，每行一个正整数，表示对应输入行的皇后的不同放置数量。
Sample Input
1
8
5
0
Sample Output
1
92
10

#include <iostream>
#include <vector>
using namespace std;

struct point {
    int x;
    int y;
};

vector<point> v;

int ret = 0;
int n;

bool isvalid(int x1, int y1, int x2, int y2) {
    if (y1 != y2 && x1 - x2 != y2 - y1 && x1 - x2 != y1 - y2) {
        return 1;
    }
    return 0;
}

bool canstay(int x, int y) {
    vector<point>::iterator i = v.begin();
    for (; i < v.end(); ++i) {
        if (!isvalid(i->x, i->y, x, y)) {
            return 0;
        }
    }
    return 1;
    
}

void dfs(int x, int y) {
    v.push_back({x, y});
    if (x == n - 1) {
        ++ret;
        
        return;
    }
    // 下一行 x+1
    for (int j = 0; j < n; ++j) {
        if (canstay(x + 1, j)) {
            dfs(x + 1, j);
            v.pop_back();
        }
    }
    
}

int sum[11];

int main(int argc, const char * argv[]) {
    
    for (n = 1; n <= 10; ++n) {
        for (int i = 0; i < n; ++i) {
            dfs(0, i);
            v.clear();
        }
        sum[n] = ret;
        ret = 0;
    }
    
    while (~scanf("%d", &n) && n) {
        cout << sum[n] << endl;
    }
    return 0;
}


// G
Problem G: Prime Ring Problem
Time Limit: 2 Sec  Memory Limit: 128 MB
Submit: 4  Solved: 2
[Submit][Status][Web Board][Creator:201506020829][Edit] [TestData]
Description
A ring is compose of n circles as shown in diagram. Put natural number 1 2 ... n into each circle separately and the sum of numbers in two adjacent circles should be a prime.



Note: the number of first circle should always be 1.

Input
n (0 < n < 20).
Output
The output format is shown as sample below. Each row represents a series of circle numbers in the ring beginning from 1 clockwisely and anticlockwisely. The order of numbers must satisfy the above requirements. Print solutions in lexicographical order.

You are to write a program that completes above process.

Print a blank line after each case.
Sample Input
6
8
Sample Output
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2

#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
bool check[50] = {0, 0, 1, 1};
vector<int> v;
int n;

bool vis[25];
bool canstay(int last, int now) {
    if (vis[now] == 0 && check[last + now] == 1) return 1;
    return 0;
}

void dfs(int now, int t) { // 当前这个数，第几个数
    if (t == n && check[now + 1]) {
        cout << 1;
        for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
            cout << ' ' << *it;
        }
        cout << endl;
    }
    for (int i = 2; i <= n; ++i) {
        if (canstay(now, i)) {
            vis[i] = 1;
            v.push_back(i);
            dfs(i, t + 1);
            vis[i] = 0;
            v.pop_back();
        }
    }
}


int main() {
    for (int i = 3; i <= 45; ++i) check[i] = 1;
    
    for (int i = 2; i <= 40; ++i) {
        if (check[i] == 1) {
            for (int j = 2; i * j <= 40; ++j) {
                check[i * j] = 0;
            }
        }
    }
    int ca = 0;
    while (~scanf("%d", &n)) {
        printf("Case %d:\n", ++ca);
        memset(vis, 0, sizeof(vis));
        dfs(1, 1);
        cout << endl;
    }
    return 0;
}
*/
