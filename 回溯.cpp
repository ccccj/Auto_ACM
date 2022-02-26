//
//  main.cpp
//  回溯
//
//  Created by admin on 18/5/8.
//  Copyright © 2018年 Amon. All rights reserved.
//
The magic apple tree

Time Limit: 3000/1000 MS (Java/Others)    Memory Limit: 65535/32768 K (Java/Others)
Total Submission(s): 1579    Accepted Submission(s): 351


Problem Description
Sailormoon girls all like eating many kinds of fruit, such as banana, grape, apple and so on.
One day, when they was walking on a orchard, they found a magic apple tree.The magic apple tree have many nodes,but there is only one root. Each notes has its label. It is labeled from 1.On the first day,only each leaf nodes(has no children nodes) have apples. Any other nodes have no apples. The number of apples that each leaf nodes have is just the label of this node.When all the immediate children of a node each has apples,this node will grow some apple on the next day. If a node has K immediate children node,the number of apple that this node grow on next day is just the number of apples that the (K + 1) / 2th smaller node has.The Xth smaller node means there are X – 1 nodes’ number of apples is less than this node’s number of apple.
Now you task is to calculate the number of apples that the root has at last.


Input
There are multiple test cases.
Each case contains a positive integer N, it means this tree has N nodes, labeled 1, 2, ... N(0 < N <= 20000).
The following N lines describe the children of all nodes in order of their labels. The (X + 1)th line in each test case starts with a number p (0 <= p <N), it means the Xth node has p immediate children nodes.then followed by p positive integer, means the label of immediate child node


Output
Print the number of apples that the root grow at last.


Sample Input
7
2 2 3
2 5 4
2 6 7
0
0
0
0

12
3 2 3 4
0
2 5 6
3 7 8 9
3 10 11 12
0
0
0
0
0
0
0


Sample Output
4
6


#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    int lable;
    int apple;
};

vector<vector<node>> v;

bool cmp(struct node a, struct node b) {
    return a.apple < b.apple;
}

void dfs(int now, int fa, int ch) {
    int k = (int)v[now].size();
    k = (k + 1) / 2;
    for (int j = 0; j < v[now].size(); ++j) {
        if (v[now][j].apple == 0) {
            dfs(v[now][j].lable, now, j);
        }
    }
    sort(v[now].begin(), v[now].end(), cmp);
    if (fa == -1) {
        cout << v[now][k - 1].apple + 1 << endl;
    } else {
        v[fa][ch].apple = v[now][k - 1].apple;
    }
}

int main() {
    
    int n;
    while (~scanf("%d", &n)) {
        v.clear();
        v.resize(n * 100 + 5);
        for (int i = 0; i < n; ++i) {
            int num, a;
            cin >> num;
            v[i].resize(num);
            for (int j = 0; j < num; ++j) {
                scanf("%d", &a);
                --a;
                v[i][j].lable = a;
                v[i][j].apple = 0;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < v[i].size(); ++j) {
                if (v[v[i][j].lable].size() == 0) {
                    v[i][j].apple = v[i][j].lable;
                }
            }
        }
        if (n == 1) {
            cout << 1 << endl;
        } else {
            dfs(0, -1, 0);
        }
    }
    return 0;
}





/*
生日蛋糕
Time Limit: 1000MS		Memory Limit: 10000K
Total Submissions: 21927		Accepted: 7804
Description

7月17日是Mr.W的生日，ACM-THU为此要制作一个体积为Nπ的M层生日蛋糕，每层都是一个圆柱体。
设从下往上数第i(1 <= i <= M)层蛋糕是半径为Ri, 高度为Hi的圆柱。当i < M时，要求Ri > Ri+1且Hi > Hi+1。
由于要在蛋糕上抹奶油，为尽可能节约经费，我们希望蛋糕外表面（最下一层的下底面除外）的面积Q最小。
令Q = Sπ
请编程对给出的N和M，找出蛋糕的制作方案（适当的Ri和Hi的值），使S最小。
（除Q外，以上所有数据皆为正整数）
Input

有两行，第一行为N（N <= 10000），表示待制作的蛋糕的体积为Nπ；第二行为M(M <= 20)，表示蛋糕的层数为M。
Output

仅一行，是一个正整数S（若无解则S = 0）。
Sample Input

100
2
Sample Output

68
Hint

圆柱公式
体积V = πR2H
侧面积A' = 2πRH
底面积A = πR2

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

int min_S = 0xffff;
int n, m; // 体积为 n pi， 层数为 m

// 上一个半径，上一个高度，剩余的体积为 sumn pi，剩余的层数
void dfs(int lastr, int lasth, int sumn, int summ, int S) {
    
    if (summ == 0) {
        if (sumn == 0 && min_S > S) min_S = S;
        return;
    }
    
    if (sumn < 0 || summ < 0) return;
    
    if (summ * (lasth - 1 ) * (lastr - 1) * (lastr - 1) < sumn || S > min_S) return;
    
    for (int r = lastr - 1; r >= summ; --r) {
        if (summ == m) S += r * r;
        if (2 * sumn / r + S >= min_S) return;
        
        for (int h = min(lasth - 1, sumn / r / r); h >= summ ; --h) {
            if (S + 2 * r * h >= min_S) continue;

            dfs(r, h, sumn - h * r * r, summ - 1, S + 2 * r * h);
        }
        if (summ == m) {
            S -= r * r;
        }
    }
}

int main() {
    
    while (~scanf("%d%d", &n, &m)) {
        min_S = 0x7fffffff;
        dfs(101, 10001, n, m, 0);
        if (min_S == 0x7fffffff) {
            min_S = 0;
        }
        cout << min_S << endl;
    }
    return 0;
}


蜘蛛牌

Time Limit: 10000/5000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
Total Submission(s): 5202    Accepted Submission(s): 2215


Problem Description
蜘蛛牌是windows xp操作系统自带的一款纸牌游戏，游戏规则是这样的：只能将牌拖到比她大一的牌上面（A最小，K最大），如果拖动的牌上有按顺序排好的牌时，那么这些牌也跟着一起移动，游戏的目的是将所有的牌按同一花色从小到大排好，为了简单起见，我们的游戏只有同一花色的10张牌，从A到10，且随机的在一行上展开，编号从1到10，把第i号上的牌移到第j号牌上，移动距离为abs(i-j)，现在你要做的是求出完成游戏的最小移动距离。


Input
第一个输入数据是T，表示数据的组数。
每组数据有一行，10个输入数据，数据的范围是[1,10]，分别表示A到10，我们保证每组数据都是合法的。


Output
对应每组数据输出最小移动距离。


Sample Input
1
1 2 3 4 5 6 7 8 9 10


Sample Output
9

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

struct card {
    int max;
    int min;
} v[15];

int vis[15];
int sum, ret;

void dfs(int t) {
    if (sum >= ret) return;
    
    if (t == 9) {
        ret = sum;
        return;
    }
    
    for (int i = 0; i < 10; ++i) {
        if (vis[i] == 0 && v[i].max != 10) {
            vis[i] = 1;
            int j = 0;
            for (; j < 10; ++j)
                if (vis[j] == 0 && v[i].max + 1 == v[j].min) break;
        
            sum += abs(j - i);
            int f = v[j].min;
            v[j].min = v[i].min;
            dfs(t + 1);
            v[j].min = f;
            sum -= abs(j - i);
            vis[i] = 0;
            
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        sum = 0, ret = 0xffff;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < 10; ++i) {
            scanf("%d", &v[i].max);
            v[i].min = v[i].max;
        }
        dfs(0);
        cout << ret << endl;
    }
    return 0;
}



Prime Ring Problem

Time Limit: 4000/2000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
Total Submission(s): 61874    Accepted Submission(s): 26682


Problem Description
A ring is compose of n circles as shown in diagram. Put natural number 1, 2, ..., n into each circle separately, and the sum of numbers in two adjacent circles should be a prime.

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


连连看

Time Limit: 20000/10000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
Total Submission(s): 40333    Accepted Submission(s): 9970


Problem Description
“连连看”相信很多人都玩过。没玩过也没关系，下面我给大家介绍一下游戏规则：在一个棋盘中，放了很多的棋子。如果某两个相同的棋子，可以通过一条线连起来（这条线不能经过其它棋子），而且线的转折次数不超过两次，那么这两个棋子就可以在棋盘上消去。不好意思，由于我以前没有玩过连连看，咨询了同学的意见，连线不能从外面绕过去的，但事实上这是错的。现在已经酿成大祸，就只能将错就错了，连线不能从外围绕过。
玩家鼠标先后点击两块棋子，试图将他们消去，然后游戏的后台判断这两个方格能不能消去。现在你的任务就是写这个后台程序。


Input
输入数据有多组。每组数据的第一行有两个正整数n,m(0<n<=1000,0<m<1000)，分别表示棋盘的行数与列数。在接下来的n行中，每行有m个非负整数描述棋盘的方格分布。0表示这个位置没有棋子，正整数表示棋子的类型。接下来的一行是一个正整数q(0<q<50)，表示下面有q次询问。在接下来的q行里，每行有四个正整数x1,y1,x2,y2,表示询问第x1行y1列的棋子与第x2行y2列的棋子能不能消去。n=0,m=0时，输入结束。
注意：询问之间无先后关系，都是针对当前状态的！


Output
每一组输入数据对应一行输出。如果能消去则输出"YES",不能则输出"NO"。


Sample Input
3 4
1 2 3 4
0 0 0 0
4 3 2 1
4
1 1 3 4
1 1 2 4
1 1 3 3
2 1 2 4
3 4
0 1 4 3
0 2 4 1
0 0 0 0
2
1 1 2 4
1 3 2 3
0 0


Sample Output
YES
NO
NO
NO
NO
YES

int map[1010][1010];
int n, m;

int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
bool vis[1010][1010];
int x2, y2;

bool canstay(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m && vis[x][y] == 0)
        if (map[x][y] == 0 || (x == x2 && y == y2)) return 1;
    return 0;
}

int flag = 0;

void dfs(int x1, int y1, int t, int d) {
    if (flag || t > 2) return;
    
    if (x1 == x2 && y1 == y2) {
        flag = 1;
        return;
    }
    if (t == 2 && x1 != x2 && y1 != y2) return;
    
    vis[x1][y1] = 1;
    
    for (int i = 0; i < 4; ++i) {
        int a = x1 + dir[i][0], b = y1 + dir[i][1];
        if (canstay(a, b)) {
            if (d != -1 && i != d) dfs(a, b, t + 1, i);
            else dfs(a, b, t, i);
            
            //if (flag) return;
        }
    }
    vis[x1][y1] = 0;
}

int main() {
    
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                scanf("%d", &map[i][j]);
        
        int q, x1, y1;
        cin >> q;
        while (q--) {
            flag = 0;
            memset(vis, 0, sizeof(vis));
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            
            --x1, --y1, --x2, --y2;
            
            if (map[x1][y1] == map[x2][y2] && map[x1][y1]) {
                dfs(x1, y1, 0, -1);
            }
            
            if (flag) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}


Fire Net

Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
Total Submission(s): 13973    Accepted Submission(s): 8542


Problem Description
Suppose that we have a square city with straight streets. A map of a city is a square board with n rows and n columns, each representing a street or a piece of wall.

A blockhouse is a small castle that has four openings through which to shoot. The four openings are facing North, East, South, and West, respectively. There will be one machine gun shooting through each opening.

Here we assume that a bullet is so powerful that it can run across any distance and destroy a blockhouse on its way. On the other hand, a wall is so strongly built that can stop the bullets.

The goal is to place as many blockhouses in a city as possible so that no two can destroy each other. A configuration of blockhouses is legal provided that no two blockhouses are on the same horizontal row or vertical column in a map unless there is at least one wall separating them. In this problem we will consider small square cities (at most 4x4) that contain walls through which bullets cannot run through.

The following image shows five pictures of the same board. The first picture is the empty board, the second and third pictures show legal configurations, and the fourth and fifth pictures show illegal configurations. For this board, the maximum number of blockhouses in a legal configuration is 5; the second picture shows one way to do it, but there are several other ways.



Your task is to write a program that, given a description of a map, calculates the maximum number of blockhouses that can be placed in the city in a legal configuration.


Input
The input file contains one or more map descriptions, followed by a line containing the number 0 that signals the end of the file. Each map description begins with a line containing a positive integer n that is the size of the city; n will be at most 4. The next n lines each describe one row of the map, with a '.' indicating an open space and an uppercase 'X' indicating a wall. There are no spaces in the input file.


Output
For each test case, output one line containing the maximum number of blockhouses that can be placed in the city in a legal configuration.


Sample Input
4
.X..
....
XX..
....
2
XX
.X
3
.X.
X.X
.X.
3
...
.XX
.XX
4
....
....
....
....
0


Sample Output
5
1
5
2
4

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

int n, sum, ret;
char map[5][5];

bool canstay(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n && map[x][y] == '.') {
        for (int i = x - 1; i >= 0; --i) {
            if (map[i][y] == 'X') break;
            if (map[i][y] == '*') return 0;
        }
        for (int i = x + 1; i < n; ++i) {
            if (map[i][y] == 'X') break;
            if (map[i][y] == '*') return 0;
            
        }
        for (int j = y - 1; j >= 0; --j) {
            if (map[x][j] == 'X') break;
            if (map[x][j] == '*') return 0;
            
        }
        for (int j = y + 1; j < n; ++j) {
            if (map[x][j] == 'X') break;
            if (map[x][j] == '*') return 0;
        }
        return 1;
    }
    return 0;
}

int tmp = 0;
int flag;

void dfs(int x, int y) {
    map[x][y] = '*';
    ++tmp;
    if (tmp > ret) ret = tmp;
    
    if (ret == sum) {
        flag = 1;
        return;
    }
    
    for (int i = x; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == x && j <= y) continue;
            if (canstay(i, j)) {
                dfs(i, j);
                if (flag) {
                    return;
                }
            }
            
        }
    }
    
    map[x][y] = '.';
    --tmp;
}

int main() {
    while (~scanf("%d", &n) && n) {
        flag = 0;
        sum = 0, ret = 0, tmp = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
        }

        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (map[i][j] == '.') {
                    ++sum;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (map[i][j] == '.') {
                    dfs(i, j);
                    if (flag) goto f;
                }
            }
        }
    f:
        cout << ret << endl;
        
        
    }
    
    return 0;
}


Tempter of the Bone

Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
Total Submission(s): 140811    Accepted Submission(s): 37596


Problem Description
The doggie found a bone in an ancient maze, which fascinated him a lot. However, when he picked it up, the maze began to shake, and the doggie could feel the ground sinking. He realized that the bone was a trap, and he tried desperately to get out of this maze.

The maze was a rectangle with sizes N by M. There was a door in the maze. At the beginning, the door was closed and it would open at the T-th second for a short period of time (less than 1 second). Therefore the doggie had to arrive at the door on exactly the T-th second. In every second, he could move one block to one of the upper, lower, left and right neighboring blocks. Once he entered a block, the ground of this block would start to sink and disappear in the next second. He could not stay at one block for more than one second, nor could he move into a visited block. Can the poor doggie survive? Please help him.


Input
The input consists of multiple test cases. The first line of each test case contains three integers N, M, and T (1 < N, M < 7; 0 < T < 50), which denote the sizes of the maze and the time at which the door will open, respectively. The next N lines give the maze layout, with each line containing M characters. A character is one of the following:

'X': a block of wall, which the doggie cannot enter;
'S': the start point of the doggie;
'D': the Door; or
'.': an empty block.

The input is terminated with three 0's. This test case is not to be processed.


Output
For each test case, print in one line "YES" if the doggie can survive, or "NO" otherwise.


Sample Input
4 4 5
S.X.
..X.
..XD
....
3 4 5
S.X.
..X.
...D
0 0 0


Sample Output
NO
YES

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

int n, m, t;
char map[10][10];
bool vis[10][10];
bool att[8][8];


int flag = 0;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct point {
    int x, y;
} s, d;

bool canstay(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m && vis[x][y] == 0 && map[x][y] != 'X') {
        return 1;
    }
    return 0;
}

void dfs(int x, int y, int ti) {
    if (ti == 0) {
        if (x == d.x && y == d.y) flag = 1;
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int a = x + dir[i][0], b = y + dir[i][1];
        
        if (abs(a - d.x) + abs(b - d.y) > ti) continue;
        
        if (canstay(a, b)) {
            vis[a][b] = 1;
            dfs(a, b, ti - 1);
            if (flag) return;
            
            vis[a][b] = 0;
        }
    }
}

void init() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            att[i][j] = (i + j) % 2;
}

int main() {
    
    init();
    
    while (~scanf("%d%d%d", &n, &m, &t) && (n + m + t)) {
        memset(vis, 0, sizeof(vis));
        flag = 0;
        
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'S') {
                    s.x = i, s.y = j;
                } else if (map[i][j] == 'D') {
                    d.x = i, d.y = j;
                }
            }
        }
        if (abs(s.x - d.x) + abs(s.y - d.y) > t
            || (att[s.x][s.y] + att[d.x][d.y] + t) % 2 != 0) {
            cout << "NO" << endl;
            continue;
        }
        vis[s.x][s.y] = 1;
        dfs(s.x, s.y, t);
        
        if (flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}



放苹果
Time Limit: 1000MS		Memory Limit: 10000K
Total Submissions: 36493		Accepted: 22481
Description

把M个同样的苹果放在N个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？（用K表示）5，1，1和1，5，1 是同一种分法。
Input

第一行是测试数据的数目t（0 <= t <= 20）。以下每行均包含二个整数M和N，以空格分开。1<=M，N<=10。
Output

对输入的每组数据M和N，用一行输出相应的K。
Sample Input

1
7 3
Sample Output

8

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int m, n;
int ret;

void dfs(int last, int summ, int sumn) { // 上一个盘子放的个数，剩余的m 剩余的n
    if (summ - last < 0) {
        return;
    }
    if (sumn == 1) {
        ++ret;
        return;
    }
    for (int i = last; i <= summ; ++i) {
        dfs(i, summ - i, sumn - 1);
    }
}
// 0 0 7
// 0 1 6
// 0 2 5
//
int main() {
    int T;
    cin >> T;
    while (T--) {
        ret = 0;
        cin >> m >> n;
        dfs(0, m, n);
        cout << ret << endl;
    }
    return 0;
}



Oil Deposits

Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
Total Submission(s): 39613    Accepted Submission(s): 22988


Problem Description
The GeoSurvComp geologic survey company is responsible for detecting underground oil deposits. GeoSurvComp works with one large rectangular region of land at a time, and creates a grid that divides the land into numerous square plots. It then analyzes each plot separately, using sensing equipment to determine whether or not the plot contains oil. A plot containing oil is called a pocket. If two pockets are adjacent, then they are part of the same oil deposit. Oil deposits can be quite large and may contain numerous pockets. Your job is to determine how many different oil deposits are contained in a grid.


Input
The input file contains one or more grids. Each grid begins with a line containing m and n, the number of rows and columns in the grid, separated by a single space. If m = 0 it signals the end of the input; otherwise 1 <= m <= 100 and 1 <= n <= 100. Following this are m lines of n characters each (not counting the end-of-line characters). Each character corresponds to one plot, and is either `*', representing the absence of oil, or `@', representing an oil pocket.


Output
For each grid, output the number of distinct oil deposits. Two different pockets are part of the same oil deposit if they are adjacent horizontally, vertically, or diagonally. An oil deposit will not contain more than 100 pockets.


Sample Input
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0


Sample Output
0
1
2
2

char map[110][110];
int ret;
int m, n;


bool canstay(int i, int j) {
    if (i >= 0 && i < m && j >= 0 && j < n && map[i][j] == '@') {
        return 1;
    }
    return 0;
}

int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};


void dfs(int i, int j) {

    map[i][j] = '*';
    for (int a = 0; a < 8; ++a) {
        int x = i + dir[a][0], y = j + dir[a][1];
        if (canstay(x, y)) dfs(x, y);
    }
}


int main() {
    
    
    while (~scanf("%d%d", &m, &n) && (m && n)) {
        
        
        ret = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%s", map[i]);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (map[i][j] == '@') {
                    ret++;
                    dfs(i, j);
                }
            }
        }
        cout << ret << endl;
    }
    
    return 0;
}


符号三角形

Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
Total Submission(s): 2624    Accepted Submission(s): 1277


Problem Description
符号三角形的 第1行有n个由“+”和”-“组成的符号 ，以后每行符号比上行少1个，2个同号下面是”+“，2个异 号下面是”-“ 。计算有多少个不同的符号三角形，使其所含”+“ 和”-“ 的个数相同 。 n=7时的1个符号三角形如下:
+ + - + - + +
+ - - - - +
- + + + -
- + + -
- + -
- -
+


Input
每行1个正整数n <=24,n=0退出.


Output
n和符号三角形的个数.


Sample Input
15
16
19
20
0


Sample Output
15 1896
16 5160
19 32757
20 59984

int ret = 0;
int n;
vector<int> v;

bool isvalid() {
    int sum = 0;
    int arr[25][25];
    int m = 0;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        arr[0][m] = *it;
        if (arr[0][m++] == 1) ++sum;
        else --sum;
    }
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < n - i; ++j)
            if (arr[i - 1][j] == arr[i - 1][j + 1]) {
                arr[i][j] = 1;
                ++sum;
            } else {
                arr[i][j] = 0;
                --sum;
            }
        
    if (sum == 0) return 1;
    return 0;
}

void dfs(int j) {
    if (v.size() == n) {
        if (isvalid()) ++ret;
        return;
    }
    
    for (int i = 0; i <= 1; ++i) {
        v.push_back(i);
        dfs(j + 1);
        v.pop_back();
    }
}

int main() {
    
    int arr[25] = {0, 0, 0, 4, 6, 0, 0, 12, 40, 0, 0, 171, 410, 0, 0, 1896, 5160, 0, 0, 32757, 59984, 0, 0, 431095, 822229
};
//    memset(arr, 0, sizeof(arr));
//    for (n = 1; n <= 24; ++n) {
//        ret = 0;
//        dfs(0);
//        arr[n] = ret;
//        cout << arr[n] << endl;
//    }

    
    while (~scanf("%d", &n) && n != 0) {
        cout << n << ' ';
        cout << arr[n] << endl;
    }
    
    return 0;
}


Sudoku Killer

Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
Total Submission(s): 9580    Accepted Submission(s): 2873


Problem Description
自从2006年3月10日至11日的首届数独世界锦标赛以后，数独这项游戏越来越受到人们的喜爱和重视。
据说，在2008北京奥运会上，会将数独列为一个单独的项目进行比赛，冠军将有可能获得的一份巨大的奖品———HDU免费七日游外加lcy亲笔签名以及同hdu acm team合影留念的机会。
所以全球人民前仆后继，为了奖品日夜训练茶饭不思。当然也包括初学者linle，不过他太笨了又没有多少耐性，只能做做最最基本的数独题，不过他还是想得到那些奖品，你能帮帮他吗？你只要把答案告诉他就可以，不用教他是怎么做的。

数独游戏的规则是这样的：在一个9x9的方格中，你需要把数字1-9填写到空格当中，并且使方格的每一行和每一列中都包含1-9这九个数字。同时还要保证，空格中用粗线划分成9个3x3的方格也同时包含1-9这九个数字。比如有这样一个题，大家可以仔细观察一下，在这里面每行、每列，以及每个3x3的方格都包含1-9这九个数字。

例题：


答案：



Input
本题包含多组测试，每组之间由一个空行隔开。每组测试会给你一个 9*9 的矩阵，同一行相邻的两个元素用一个空格分开。其中1-9代表该位置的已经填好的数，问号（?）表示需要你填的数。


Output
对于每组测试，请输出它的解，同一行相邻的两个数用一个空格分开。两组解之间要一个空行。
对于每组测试数据保证它有且只有一个解。


Sample Input
7 1 2 ? 6 ? 3 5 8
? 6 5 2 ? 7 1 ? 4
? ? 8 5 1 3 6 7 2
9 2 4 ? 5 6 ? 3 7
5 ? 6 ? ? ? 2 4 1
1 ? 3 7 2 ? 9 ? 5
? ? 1 9 7 5 4 8 6
6 ? 7 8 3 ? 5 1 9
8 5 9 ? 4 ? ? 2 3


Sample Output
7 1 2 4 6 9 3 5 8
3 6 5 2 8 7 1 9 4
4 9 8 5 1 3 6 7 2
9 2 4 1 5 6 8 3 7
5 7 6 3 9 8 2 4 1
1 8 3 7 2 4 9 6 5
2 3 1 9 7 5 4 8 6
6 4 7 8 3 2 5 1 9
8 5 9 6 4 1 7 2 3

#include <iostream>
#include <cstdio>
using namespace std;
int sum = 0;
char map[9][9];

bool canstay(int i, int j, char k) {
    if (i < 0 || j >= 9) {
        return 0;
    }
    for (int x = 0; x < 9; ++x) {
        if (x == i) continue;
        if (map[x][j] == k) return 0;
    }
    for (int y = 0; y < 9; ++y) {
        if (y == j) continue;
        if (map[i][y] == k) return 0;
    }
    if (i >= 0 && i <= 2) {
        if (j >= 0 && j <= 2)
            for (int x = 0; x <= 2; ++x)
                for (int y = 0; y <= 2; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
        
        if (j >= 3 && j <= 5)
            for (int x = 0; x <= 2; ++x)
                for (int y = 3; y <= 5; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
        
        if (j >= 6 && j <= 8)
            for (int x = 0; x <= 2; ++x)
                for (int y = 6; y <= 8; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
    }
    if (i >= 3 && i <= 5) {
        if (j >= 0 && j <= 2)
            for (int x = 3; x <= 5; ++x)
                for (int y = 0; y <= 2; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
        
        if (j >= 3 && j <= 5)
            for (int x = 3; x <= 5; ++x)
                for (int y = 3; y <= 5; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
        
        if (j >= 6 && j <= 8)
            for (int x = 3; x <= 5; ++x)
                for (int y = 6; y <= 8; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
    }
    if (i >= 6 && i <= 8) {
        if (j >= 0 && j <= 2)
            for (int x = 6; x <= 8; ++x)
                for (int y = 0; y <= 2; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
        
        if (j >= 3 && j <= 5)
            for (int x = 6; x <= 8; ++x)
                for (int y = 3; y <= 5; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
        
        if (j >= 6 && j <= 8)
            for (int x = 6; x <= 8; ++x)
                for (int y = 6; y <= 8; ++y) {
                    if (x == i && y == j) continue;
                    if (map[x][y] == k) return 0;
                }
    }
    return 1;
}

int flag = 0;

void dfs(int i, int j) {
    if (sum == 0) {
        flag = 1;
        return;
    }
    if (map[i][j] == '?') {
        for (char k = '1'; k <= '9'; ++k) {
            if (canstay(i, j, k)) {
                map[i][j] = k;
                --sum;
                if (j == 8) {
                    dfs(i + 1, 0);
                } else {
                    dfs(i, j + 1);
                }
                if (flag) {
                    return;
                }
                map[i][j] = '?';
                ++sum;
            }
        }
    } else {
        if (j == 8) {
            dfs(i + 1, 0);
        } else {
            dfs(i, j + 1);
        }
        if (flag) {
            return;
        }
    }
}

int main() {
    
    
    char ch;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            scanf("%c%c", &map[i][j], &ch);
            if (map[i][j] == '?') {
                ++sum;
            }
        }
    }
    dfs(0, 0);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 8; ++j) {
            printf("%c ", map[i][j]);
        }
        cout << map[i][8] << endl;
    }

    while (~scanf("%c", &ch)) {
        cout << endl;
        flag = 0, sum = 0;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                scanf("%c%c", &map[i][j], &ch);
                if (map[i][j] == '?') {
                    ++sum;
                }
            }
        }
        dfs(0, 0);
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 8; ++j) {
                printf("%c ", map[i][j]);
            }
            cout << map[i][8] << endl;
        }
    }
    return 0;
}


N皇后问题

Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
Total Submission(s): 30397    Accepted Submission(s): 13239


Problem Description
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
// 重点：打表

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
*/

