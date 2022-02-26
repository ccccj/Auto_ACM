//
//  main.cpp
//  bfs 分支界限
//
//  Created by admin on 18/5/13.
//  Copyright © 2018年 Amon. All rights reserved.
//
/*
Kaitou Kid - The Phantom Thief (2)
题目描述
破解字迷之后，你得知Kid将会在展览开始后T分钟内盗取至少一颗宝石，并离开展馆。整个展馆呈矩形分布，划分为N*M个区域，有唯一的入口和出口（不能从出口进入，同样不能从入口出去）。由某个区域可直接移动至相邻四个区域中的一个，且最快需要一分钟。假设Kid进入放有宝石的区域即可盗取宝石，无需耗时。问至少要封锁几个区域（可以封锁放有宝石的区域，但不能封锁入口和出口）才能保证Kid无法完成任务。

输入
输入的第一行有一个整数C，代表有C组测试数据。每组测试数据的第一行有三个整数N，M，T(2<=N,M<=8,T>0)。接下来N行M列为展馆布置图，其中包括：

'S'：入口
'E'：出口
'J'：放有宝石的区域，至少出现一次
'.'：空白区域
'#'：墙

输出
对每组测试数据，输出至少要封锁的区域数。

样例输入
2
5 5 5
SJJJJ
..##J
.JJJJ
.J...
EJ...
5 5 6
SJJJJ
..##J
.JJJJ
.J...
EJ...
样例输出
0
2

#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int n, m, c;
char map[11][11];
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
bool vis[11][11][2];

struct point {
    int x, y;
    int road;
    int j;
} s, e;

bool canstay(int x, int y, int j) {
    if (x >= 0 && x < n && y >= 0 && y < m
        && map[x][y] != '#' && vis[x][y][j] == 0) {
        vis[x][y][j] = 1;
        return 1;
    }
    return 0;
}

int bfs() {
    memset(vis, 0, sizeof(vis));
    vis[s.x][s.y][s.j] = 1;
    queue<point> q;
    q.push(s);
    while (!q.empty()) {
        point now = q.front();
        if (now.road > c) return -1;
        
        if (map[now.x][now.y] == 'E' && now.j == 1) return 1;
        
        for (int i = 0; i < 4; ++i) {
            int x = now.x + dir[i][0], y = now.y + dir[i][1];
            
            if (map[x][y] == 'J') {
                if (canstay(x, y, 1)) q.push({x, y, now.road + 1, 1});
            } else {
                if (canstay(x, y, now.j))
                    q.push({x, y, now.road + 1, now.j});
            }
        }
        q.pop();
    }
    return -1;
}

bool dfs(int num) {
    if (num == 0) {
        if (bfs() == -1) return 1;
        else return 0;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {

            if (map[i][j] == '.' || map[i][j] == 'J') {
                char ch = map[i][j];
                map[i][j] = '#';
                if (dfs(num - 1) == 1) {
                    return 1;
                }
                map[i][j] = ch;
            }
        }
    }
    return 0;
}


int main() {
    int T;
    cin >> T;
    while (T--) {
        
        cin >> n >> m >> c;
        
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
            for (int j = 0; j < m; ++j)
                if (map[i][j] == 'S') {
                    s.x = i, s.y = j, s.road = 0, s.j = 0;;
                    break;
                } else if (map[i][j] == 'E') {
                    e.x = i, e.y = j;
                    break;
                }
        }

        if (bfs() == -1) {
            cout << 0 << endl;
        } else if (dfs(1) == 1) {
            cout << 1 << endl;
        } else if (dfs(2) == 1) {
            cout << 2 << endl;
        } else if (dfs(3) == 1) {
            cout << 3 << endl;
        } else {
            cout << 4 << endl;
        }
    }
    return 0;
}


Ignatius and the Princess I(BFS)

Problem Description
The Princess has been abducted by the BEelzebub feng5166, our hero Ignatius has to rescue our pretty Princess. Now he gets into feng5166's castle. The castle is a large labyrinth. To make the problem simply, we assume the labyrinth is a N*M two-dimensional array which left-top corner is (0,0) and right-bottom corner is (N-1,M-1). Ignatius enters at (0,0), and the door to feng5166's room is at (N-1,M-1), that is our target. There are some monsters in the castle, if Ignatius meet them, he has to kill them. Here is some rules:

1.Ignatius can only move in four directions(up, down, left, right), one step per second. A step is defined as follow: if current position is (x,y), after a step, Ignatius can only stand on (x-1,y), (x+1,y), (x,y-1) or (x,y+1).
2.The array is marked with some characters and numbers. We define them like this:
. : The place where Ignatius can walk on.
X : The place is a trap, Ignatius should not walk on it.
n : Here is a monster with n HP(1<=n<=9), if Ignatius walk on it, it takes him n seconds to kill the monster.

Your task is to give out the path which costs minimum seconds for Ignatius to reach target position. You may assume that the start position and the target position will never be a trap, and there will never be a monster at the start position.


Input
The input contains several test cases. Each test case starts with a line contains two numbers N and M(2<=N<=100,2<=M<=100) which indicate the size of the labyrinth. Then a N*M two-dimensional array follows, which describe the whole labyrinth. The input is terminated by the end of file. More details in the Sample Input.


Output
For each test case, you should output "God please help our poor hero." if Ignatius can't reach the target position, or you should output "It takes n seconds to reach the target position, let me show you the way."(n is the minimum seconds), and tell our hero the whole path. Output a line contains "FINISH" after each test case. If there are more than one path, any one is OK in this problem. More details in the Sample Output.


Sample Input
5 6 .XX.1. ..X.2. 2...X. ...XX. XXXXX. 5 6 .XX.1. ..X.2. 2...X. ...XX. XXXXX1 5 6 .XX... ..XX1. 2...X. ...XX. XXXXX.


Sample Output
It takes 13 seconds to reach the target position, let me show you the way. 1s:(0,0)->(1,0) 2s:(1,0)->(1,1) 3s:(1,1)->(2,1) 4s:(2,1)->(2,2) 5s:(2,2)->(2,3) 6s:(2,3)->(1,3) 7s:(1,3)->(1,4) 8s:FIGHT AT (1,4) 9s:FIGHT AT (1,4) 10s:(1,4)->(1,5) 11s:(1,5)->(2,5) 12s:(2,5)->(3,5) 13s:(3,5)->(4,5) FINISH It takes 14 seconds to reach the target position, let me show you the way. 1s:(0,0)->(1,0) 2s:(1,0)->(1,1) 3s:(1,1)->(2,1) 4s:(2,1)->(2,2) 5s:(2,2)->(2,3) 6s:(2,3)->(1,3) 7s:(1,3)->(1,4) 8s:FIGHT AT (1,4) 9s:FIGHT AT (1,4) 10s:(1,4)->(1,5) 11s:(1,5)->(2,5) 12s:(2,5)->(3,5) 13s:(3,5)->(4,5) 14s:FIGHT AT (4,5) FINISH God please help our poor hero. FINISH
 

#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int n, m;
char map[110][110];
bool vis[110][110];
unsigned int dis[110][110];
int d[110][110];

struct point {
    int x, y;
    int fight;
    int sum;
    bool operator<(point a) const {
        return sum > a.sum;
    }
};

int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};

bool canstay(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m
        && map[x][y] != 'X' && vis[x][y] == 0) {
        return 1;
    }
    return 0;
}

void printroad(point a) {
    if (a.x == 0 && a.y == 0) return;
    int i = a.x - dir[d[a.x][a.y]][0], j = a.y - dir[d[a.x][a.y]][1];
    int f = 0;
    if (map[a.x][a.y] == '.') f = 1;
    else f = map[a.x][a.y] - '0' + 1;
    
    printroad({i, j, 0, a.sum - f});
    
    if (map[a.x][a.y] == '.') {
        printf("%ds:(%d,%d)->(%d,%d)\n", a.sum, i, j, a.x, a.y);
    } else {
        printf("%ds:(%d,%d)->(%d,%d)\n", a.sum - f + 1, i, j, a.x, a.y);
        for (int k = f - 2; k >= 0; --k) {
            printf("%ds:FIGHT AT (%d,%d)\n", a.sum - k, a.x, a.y);
        }
    }
}

void bfs() {
    vis[0][0] = 1;
    priority_queue<point> q;
    
    q.push({0, 0, 1, 0});
    while (!q.empty()) {
        point now = q.top();
        if (now.x == n - 1 && now.y == m - 1) {
            printf("It takes %d seconds to reach the target position, let me show you the way.\n", now.sum);
            printroad(now);
            cout << "FINISH" << endl;
            return;
        }
        for (int i = 0; i < 4; ++i) {
            int x = now.x + dir[i][0], y = now.y + dir[i][1];
            if (canstay(x, y)) {
                vis[x][y] = 1;
                if (map[x][y] == '.')
                    q.push({x, y, 1, now.sum + 1});
                else q.push({x, y, map[x][y] - '0' + 1,
                    now.sum + map[x][y] - '0' + 1});
                d[x][y] = i;
            }
        }
        q.pop();
    }
    cout << "God please help our poor hero." << endl << "FINISH" << endl;
}

int main() {
    //freopen("/Users/admin/Desktop/test-5.in", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
        }
        memset(dis, -1, sizeof dis);
        bfs();
    }
    return 0;
}



Fire!
题目描述
Joe works in a maze. Unfortunately, portions of the maze have caught on fire, and the owner of the maze neglected to create a fire escape plan. Help Joe escape the maze.

Given Joe’s location in the maze and which squares of the maze are on fire, you must determine whether Joe can exit the maze before the fire reaches him, and how fast he can do it.

Joe and the fire each move one square per minute, vertically or horizontally (not diagonally). The fire spreads all four directions from each square that is on fire. Joe may exit the maze from any square that borders the edge of the maze. Neither Joe nor the fire may enter a square that is occupied by a wall.

输入
The first line of input contains a single integer, the number of test

cases to follow. The first line of each test case contains the two

integers R and C, separated by spaces, with 1 ≤ R, C ≤ 1000. The

following R lines of the test case each contain one row of the maze. Each of these lines contains exactly C characters, and each of these characters is one of:

• #, a wall

• ., a passable square

• J, Joe’s initial position in the maze, which is a passable square • F, a square that is on fire

There will be exactly one J in each test case.

输出
For each test case, output a single line containing ‘IMPOSSIBLE’ if Joe cannot exit the maze before the fire reaches him, or an integer giving the earliest time Joe can safely exit the maze, in minutes.

样例输入
2
4 4
####
#JF#
#..#
#..#
3 3
###
#J.
#.F
样例输出
3
IMPOSSIBLE

#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int n, m;
char map[1010][1010];
bool visf[1010][1010];
bool visj[1010][1010];

unsigned int fire[1010][1010];

struct point {
    int x, y;
    int t;
} s;

int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

bool canstay_fire(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m && visf[x][y] == 0 && map[x][y] != '#') {
        return 1;
    }
    return 0;
}

bool canstay_j(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m && visj[x][y] == 0 && map[x][y] != '#') {
        return 1;
    }
    return 0;
}

void bfs() {
    memset(visj, 0, sizeof(visj));
    visj[s.x][s.y] = 1;
    
    queue<point> q;
    q.push({s.x, s.y, s.t});
    while (!q.empty()) {
        point now = q.front();
        if (now.x == 0 || now.x == n - 1 || now.y == 0 || now.y == m - 1) {
            cout << now.t + 1<< endl;
            return;
        }
        for (int i = 0; i < 4; ++i) {
            int x = now.x + dir[i][0], y = now.y + dir[i][1];
            if (canstay_j(x, y) && now.t + 1 < fire[x][y]) {
                q.push({x, y, now.t + 1});
                visj[x][y] = 1;
            }
        }
        q.pop();
    }
    cout << "IMPOSSIBLE" << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            scanf("%s", map[i]);
        memset(fire, -1, sizeof(fire));
        memset(visf, 0, sizeof(visf));
        
        queue<point> q;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'F') {
                    fire[i][j] = 0;
                    q.push({i, j, 0});
                    visf[i][j] = 1;
                } else if (map[i][j] == 'J') {
                    s.x = i, s.y = j, s.t = 0;
                }
            }
        }
        
        while (!q.empty()) {
            point now = q.front();
            for (int i = 0; i < 4; ++i) {
                int x = now.x + dir[i][0], y = now.y + dir[i][1];
                if (canstay_fire(x, y)) {
                    q.push({x, y, now.t + 1});
                    visf[x][y] = 1;
                    fire[x][y] = now.t + 1;
                }
            }
            q.pop();
        }
        bfs();
    }
    return 0;
}







Find a way
题目描述
Pass a year learning in Hangzhou, yifenfei arrival hometown Ningbo at finally. Leave Ningbo one year, yifenfei have many people to meet. Especially a good friend Merceki.
Yifenfei’s home is at the countryside, but Merceki’s home is in the center of city. So yifenfei made arrangements with Merceki to meet at a KFC. There are many KFC in Ningbo, they want to choose one that let the total time to it be most smallest.
Now give you a Ningbo map, Both yifenfei and Merceki can move up, down ,left, right to the adjacent road by cost 11 minutes.

输入
The input contains multiple test cases.
Each test case include, first two integers n, m. (2<=n,m<=200).
Next n lines, each line included m character.
‘Y’ express yifenfei initial position.
‘M’    express Merceki initial position.
‘#’ forbid road;
‘.’ Road.
‘@’ KCF

输出
For each test case output the minimum total time that both yifenfei and Merceki to arrival one of KFC.You may sure there is always have a KFC that can let them meet.

样例输入
4 4
Y.#@
....
.#..
@..M
4 4
Y.#@
....
.#..
@#.M
5 5
Y..@.
.#...
.#...
@..M.
#...#
样例输出
66
88
66

#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int n, m;
char map[210][210];
bool vis[210][210];
int dis[210][210];
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int mark[210][210];


struct point {
    int x, y;
    int t;
} s, e;

bool canstay(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m
        && map[x][y] != '#' && vis[x][y] == 0) {
        return 1;
    }
    return 0;
}

void bfs(point pt) {
    vis[pt.x][pt.y] = 1;
    queue<point> q;
    q.push(pt);
    while (!q.empty()) {
        point now = q.front();
        if (map[now.x][now.y] == '@') {
            dis[now.x][now.y] += now.t;
            ++mark[now.x][now.y];
        }
        
        for (int i = 0; i < 4; ++i) {
            int x = now.x + dir[i][0], y = now.y + dir[i][1];
            if (canstay(x, y)) {
                vis[x][y] = 1;
                q.push({x, y, now.t + 1});
            }
        }
        q.pop();
    }
}

int main() {
    
    while (~scanf("%d%d", &n, &m)) {
        memset(dis, 0, sizeof(dis));
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; ++i)
            scanf("%s", map[i]);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'Y') s.x = i, s.y = j, s.t = 0;
                else if (map[i][j] == 'M') e.x = i, e.y = j, e.t = 0;
            }
        }
        memset(vis, 0, sizeof(vis));
        vis[e.x][e.y] = 1;
        bfs(s);
        memset(vis, 0, sizeof(vis));
        vis[s.x][s.y] = 1;
        bfs(e);
        
        int tmp = 0x7fffffff;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == '@' && tmp > dis[i][j] && mark[i][j] == 2) {
                    tmp = dis[i][j];
                }
            }
        }
        cout << tmp * 11 << endl;
    }
    return 0;
}



Prime Path
题目描述
The ministers of the cabinet were quite upset by the message from the Chief of Security stating that they would all have to change the four-digit room numbers on their offices.
— It is a matter of security to change such things every now and then, to keep the enemy in the dark.
— But look, I have chosen my number 1033 for good reasons. I am the Prime minister, you know!
— I know, so therefore your new number 8179 is also a prime. You will just have to paste four new digits over the four old ones on your office door.
— No, it’s not that simple. Suppose that I change the first digit to an 8, then the number will read 8033 which is not a prime!
— I see, being the prime minister you cannot stand having a non-prime number on your door even for a few seconds.
— Correct! So I must invent a scheme for going from 1033 to 8179 by a path of prime numbers where only one digit is changed from one prime to the next prime.

Now, the minister of finance, who had been eavesdropping, intervened.
— No unnecessary expenditure, please! I happen to know that the price of a digit is one pound.
— Hmm, in that case I need a computer program to minimize the cost. You don't know some very cheap software gurus, do you?
— In fact, I do. You see, there is this programming contest going on... Help the prime minister to find the cheapest prime path between any two given four-digit primes! The first digit must be nonzero, of course. Here is a solution in the case above.

1033
1733
3733
3739
3779
8779
8179
The cost of this solution is 6 pounds. Note that the digit 1 which got pasted over in step 2 can not be reused in the last step – a new 1 must be purchased.

输入
One line with a positive number: the number of test cases (at most 100). Then for each test case, one line with two numbers separated by a blank. Both numbers are four-digit primes (without leading zeros).

输出
One line for each case, either with a number stating the minimal cost or containing the word Impossible.

样例输入
3
1033 8179
1373 8017
1033 1033
样例输出
6
7
0

#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;

int s, e;
bool vis[10010];
bool prime[10010] = {1, 1, 0, 0};

struct num {
    int k;
    int road;
};

void bfs() {
    queue<num> q;
    q.push({s, 0});
    vis[s] = 1;
    while (!q.empty()) {
        num now = q.front();
        if (now.k == e) {
            cout << now.road << endl;
            return;
        }
        int arr[4] = {now.k % 10, now.k / 10 % 10, now.k / 100 % 10, now.k / 1000};
        
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j <= 3; ++j) {
                if (arr[j] != i) {
                    int key = now.k + (i - arr[j]) * pow(10, j);
                    if (vis[key] == 0 && prime[key] == 0) {
                        vis[key] = 1;
                        q.push({key, now.road + 1});
                    }
                }
            }
        }
        q.pop();
    }
}

void _prime() {
    for (int i = 2; i <= 9999; ++i) {
        if (prime[i] == 0)
            for (int j = i; i * j <= 9999; ++j) prime[i * j] = 1;
    }
    for (int i = 2; i <= 999; ++i) {
        prime[i] = 1;
    }
}

int main() {
    _prime();
    int n;
    while (~scanf("%d", &n)) {
        while (n--) {
            cin >> s >> e;
            memset(vis, 0, sizeof(vis));
            bfs();
        }
    }
    
    return 0;
}



Find The Multiple
Given a positive integer n, write a program to find out a nonzero multiple m of n whose decimal representation contains only the digits 0 and 1. You may assume that n is not greater than 200 and there is a corresponding m containing no more than 100 decimal digits.
Input
The input file may contain multiple test cases. Each line contains a value of n (1 <= n <= 200). A line containing a zero terminates the input.
Output
For each value of n in the input print a line containing the corresponding value of m. The decimal representation of m must not contain more than 100 digits. If there are multiple solutions for a given value of n, any one of them is acceptable.
Sample Input
2
6
19
0
Sample Output
10
100100100100100100
111111111111111111

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int n;
int arr[210][110];
int mod[210];

struct number {
    vector<bool> v;
    int mod;
};

void bfs() {
    queue<number> q;
    vector<bool> v0(1, 1);
    q.push({v0, 1});
    while (!q.empty()) {
        number now = q.front();
        for (int i = 1; i >= 0; --i) {
            now.v.push_back(i);
            int k = now.mod;
            now.mod = (now.mod * 10 % n + i % n) % n;
            
            if (now.mod == 0) {
                arr[n][0] = (int)now.v.size();
                for (int j = 0; j < (int)now.v.size(); ++j)
                    arr[n][j + 1] = now.v[j];
                return;
            }
            
            q.push(now);
            now.v.pop_back();
            now.mod = k;
        }
        q.pop();
    }
}

int main() {
    arr[1][0] = 1;
    arr[1][1] = 1;
    for (n = 2; n <= 200; ++n) {
        if (n % 2 == 0) {
            memcpy(arr[n], arr[n / 2], sizeof(arr[n / 2]));
            arr[n][arr[n][0] + 1] = 0;
            ++arr[n][0];
        } else {
            bfs();
        }
    }
    
    
    while (~scanf("%d", &n) && n) {
        for (int j = 1; j <= arr[n][0]; ++j) {
            printf("%d", arr[n][j]);
        }
        cout << endl;
    }
    return 0;
}


poj 2251
Dungeon Master
Time Limit: 1000MS		Memory Limit: 65536K
Total Submissions: 44733		Accepted: 16841
Description

You are trapped in a 3D dungeon and need to find the quickest way out! The dungeon is composed of unit cubes which may or may not be filled with rock. It takes one minute to move one unit north, south, east, west, up or down. You cannot move diagonally and the maze is surrounded by solid rock on all sides.

Is an escape possible? If yes, how long will it take?
Input

The input consists of a number of dungeons. Each dungeon description starts with a line containing three integers L, R and C (all limited to 30 in size).
L is the number of levels making up the dungeon.
R and C are the number of rows and columns making up the plan of each level.
Then there will follow L blocks of R lines each containing C characters. Each character describes one cell of the dungeon. A cell full of rock is indicated by a '#' and empty cells are represented by a '.'. Your starting position is indicated by 'S' and the exit by the letter 'E'. There's a single blank line after each level. Input is terminated by three zeroes for L, R and C.
Output

Each maze generates one line of output. If it is possible to reach the exit, print a line of the form
Escaped in x minute(s).

where x is replaced by the shortest time it takes to escape.
If it is not possible to escape, print the line
Trapped!
Sample Input

3 4 5
S....
.###.
.##..
###.#

#####
#####
##.##
##...

#####
#####
#.###
####E

1 3 3
S##
#E#
###

0 0 0
Sample Output

Escaped in 11 minute(s).
Trapped!

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

char map[35][35][35];
bool vis[35][35][35];
int l, n, m;

struct point {
    int l, r, c;
    int t;
} s;

int dir[6][3] = {{-1, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

bool canstay(int a, int r, int c) {
    if (a >= 0 && a < l && r >= 0 && r < n && c >= 0 && c < m
        && vis[a][r][c] == 0
        && (map[a][r][c] == '.' || map[a][r][c] == 'E')) {
        return 1;
    }
    return 0;
}

void bfs() {
    queue<point> q;
    q.push(s);
    while (!q.empty()) {
        point now = q.front();
        if (map[now.l][now.r][now.c] == 'E') {
            printf("Escaped in %d minute(s).\n", now.t);
            return;
        }
        
        for (int i = 0; i < 6; ++i) {
            int a = now.l + dir[i][0];
            int r = now.r + dir[i][1];
            int c = now.c + dir[i][2];
            if (canstay(a, r, c)) {
                vis[a][r][c] = 1;
                q.push({a, r, c, now.t + 1});
            }
        }
        q.pop();
    }
    cout << "Trapped!" << endl;
}

int main() {

    while (~scanf("%d%d%d", &l, &n, &m) && l + m + n) {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%s", map[i][j]);
            }
        }
        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    if (map[i][j][k] == 'S') {
                        s.l = i, s.r = j, s.c = k, s.t = 0;
                    }
                }
            }
        }
        bfs();
    }
    return 0;
}


poj 3984
迷宫问题
Time Limit: 1000MS		Memory Limit: 65536K
Total Submissions: 30663		Accepted: 17608
Description

定义一个二维数组：

int maze[5][5] = {
    
    0, 1, 0, 0, 0,
    
    0, 1, 0, 1, 0,
    
    0, 0, 0, 0, 0,
    
    0, 1, 1, 1, 0,
    
    0, 0, 0, 1, 0,
    
};

它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。
Input

一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。
Output

左上角到右下角的最短路径，格式如样例所示。
Sample Input

0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
Sample Output

(0, 0)
(1, 0)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 4)
(4, 4)

#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

int map[6][6];
bool vis[6][6];

int dir[4][2] = {1, 0, -1, 0, 0, -1, 0, 1};

struct point {
    int x, y;
};

void _cout(vector<point> v) {
    for (int i = 0; i < v.size(); ++i) {
        printf("(%d, %d)\n", v[i].x, v[i].y);
    }
}

bool canstay(int x, int y) {
    if (x >= 0 && x < 5 && y >= 0 && y < 5
        && map[x][y] == 0 &&vis[x][y] == 0) {
        return 1;
    }
    return 0;
}

void bfs() {
    queue< vector<point> > q;
    vector<point> start;
    start.push_back({0, 0});
    q.push(start);
    while (!q.empty()) {
        vector<point> now = q.front();
        point now_back = now.back();
        for (int i = 0; i < 4; ++i) {
            int x = now_back.x + dir[i][0];
            int y = now_back.y + dir[i][1];
            if (canstay(x, y)) {
                vis[x][y] = 1;
                point next = {x, y};
                now.push_back(next);
                if (x == 4 && y == 4) {
                    _cout(now);
                    return;
                }
                q.push(now);
                now.pop_back();
            }
        }
        q.pop();
    }
}

int main(int argc, const char * argv[]) {
    
    while (~scanf("%d", &map[0][0])) {
        
        for (int j = 1; j < 5; ++j) scanf("%d", &map[0][j]);
        
        for (int i = 1; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                scanf("%d", &map[i][j]);
        
        memset(vis, 0, sizeof(vis));
        
        bfs();
    }
    return 0;
}
*/
