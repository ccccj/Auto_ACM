//
//  main.cpp
//  网络流
//
//  Created by admin on 18/8/23.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 8010, inf = 0x3fffffff;
char table[maxn][maxn];
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1}, num[maxn][maxn], n, m, cnt;
int p[maxn * maxn], pre[maxn * maxn], dis[maxn * maxn], vis[maxn * maxn];
vector<int> v[maxn];

struct node {
    int to, f, cost; // f代表还能流过多少
} Map[maxn * maxn];

bool canstay(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m) return 1;
    return 0;
}

void insert(int x, int y, int f, int cost) {
    Map[cnt] = {y, f, cost};
    v[x].push_back(cnt++);
    Map[cnt] = {x, -f, cost};
    v[y].push_back(cnt++);
}
/*
20 20
@*#*@*@#*##*@*#*###*
*#*@*@*@@***@#@**@@*
@@*@#**#@@##*#@*@##@
#*##*@#*****@@**@#@*
*#***@*#*@@#@*@#*@*@
**@##@@##**@@@*@**#*
**##@@*@*#**@*@**@**
********************
#**@*@#@@#**#@@@*#@@
*#*@*#**@*@@@#@#@**@
#@#@*@##@#*@@@@@#@**
********************
*@****#@@*#@@@#*@@##
#*#*##*#@##@#*#@*@##
@*@@#*@@#@**#*##*##@
@#****@@#@@**@@@##**
**###*******##*####*
*****#**##**#@#***##
####**#****##**#****
********************
*/

void init(int s, int e) {
    memset(pre, -1, sizeof(pre)); // 记录前驱边
    memset(p, -1, sizeof(p)); // 记录前驱结点
    memset(vis, 0, sizeof(vis)); // 标记结点是否在队列中
    for (int i = s; i <= e; ++i) {
        dis[i] = inf;
    }
    dis[s] = 0;
}

bool spfa(int s, int e) {
    init(s, e);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            int y = Map[c].to;
            if (Map[c].f > 0
                && Map[c].cost + dis[now] < dis[y]) {
                dis[y] = Map[c].cost + dis[now];
                p[y] = now;
                pre[y] = c;
                if (vis[y] == 0) {
                    vis[y] = 1;
                    q.push(y);
                }
            }
        }
    }
    return dis[e] != inf;
}

int min_cost_flow(int s, int e) {
    int cost = 0;
    int flow = 0; // 这里不需要
    while (spfa(s, e)) {
        int f = inf;
        for (int u = e; u != s; u = p[u]){
            f = min(f, Map[pre[u]].f);
        }
        flow += f; // 更新最大流
        cost += dis[e] * f; // 更新最小费用
        
        for (int u = e; u != s; u = p[u]){
            Map[pre[u]].f -= f;
            Map[pre[u]^1].f += f;
        }
    }
    return cost;
}

int main() {
    
    while (~scanf("%d%d", &n, &m)) {
        memset(num, -1, sizeof(num));
        int now = 0, s = 0, e = n * m + 1;
        v[s].clear();
        v[e].clear();
        init(s, e);
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s", table[i]);
            for (int j = 0; j < m; ++j) {
                num[i][j] = ++now;
                v[num[i][j]].clear();
                if (table[i][j] == '@') {
                    insert(s, num[i][j], 1, 0);
                } else if (table[i][j] == '#') {
                    insert(num[i][j], e, 1, 0);
                }
            }
            
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < 4; ++k) {
                    int x = dir[k][0] + i, y = dir[k][1] + j;
                    if (canstay(x, y)) {
                        insert(num[i][j], num[x][y], inf, 1);
                    }
                }
            }
        }
        printf("%d\n", min_cost_flow(s, e));
    }
    return 0;
}

/*
// spfa 最小费用最大流算法
// 每次选择费用最小的边（类似于求最短路算法）
// 反复用spfa算法做源到汇的最短路进行增广, 边权值为边上单位费用。
// 反向边上的单位费用是负的。
// 直到无法增广, 即为找到最小费用最大流。
// 成立原因 : 每次增广时, 每增加1个流量, 所增加的费用都是最小的
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int inf = 0x3fffffff, maxn = 10010;
struct node {
    int to, f, cost; // f代表还能流过多少
} Map[maxn * 10];

vector<int> v[maxn];
// p 为前驱结点，p为前驱边
int cnt, p[maxn], pre[maxn], dis[maxn], vis[maxn], n, m;

void insert(int x, int y, int cost, int f) {
    Map[cnt].to = y;
    Map[cnt].f = f;
    Map[cnt].cost = cost;
    v[x].push_back(cnt);
    ++cnt;
}

void init(int s, int e) {
    memset(pre, -1, sizeof(pre)); // 记录前驱边
    memset(p, -1, sizeof(p)); // 记录前驱结点
    memset(vis, 0, sizeof(vis)); // 标记结点是否在队列中
    for (int i = s; i <= e; ++i) {
        dis[i] = inf;
    }
    dis[s] = 0;
}

bool spfa(int s, int e) {
    init(s, e);
    
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            int y = Map[c].to;
            if (Map[c].f > 0
                && Map[c].cost + dis[now] < dis[y]) {
                dis[y] = Map[c].cost + dis[now];
                p[y] = now;
                pre[y] = c;
                if (vis[y] == 0) {
                    vis[y] = 1;
                    q.push(y);
                }
            }
        }
    }
    return dis[e] != inf;
}

int min_cost_flow(int s, int e) {
    int cost = 0;
    // int flow = 0; // 这里不需要
    while (spfa(s, e)) {
        int f = inf;
        for (int u = e; u != s; u = p[u]){
            f = min(f, Map[pre[u]].f);
        }
        // flow += f; // 更新最大流
        cost += dis[e] * f; // 更新最小费用
        
        for (int u = e; u != s; u = p[u]){
            Map[pre[u]].f -= f;
            Map[pre[u]^1].f += f;
        }
    }
    return cost;
}

int main() {
    int x, y, z;
    //freopen("/Users/admin/Desktop/test2.in", "r", stdin);
    while (cin >> n >> m) {
        for (int i = 0; i <= n + 1; ++i) {
            v[i].clear();
        }
        cnt = 0;
        int s = 0, e = n + 1;
        insert(s, 1, 0, 2);
        insert(1, s, 0, 0);
        for (int i = 0; i < m; ++i) {
            // 要建四条边的啊...因为是双向的
            cin >> x >> y >> z;
            insert(x, y, z, 1);
            insert(y, x, z, 1);
            insert(x, y, -z, 0);
            insert(y, x, -z, 0); // 负边权
        }
        insert(n, e, 0, 2);
        insert(e, n, 0, 0);
        
        printf("%d\n", min_cost_flow(s, e));
    }
    return 0;
}



// 最大费用最大流
Problem F: 奇迹暖暖
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 3  Solved: 3
[Submit][Status][Web Board][Creator:qianyouyou][Edit] [TestData]
Description
梅拉抢走了绫罗的设计图，暖暖决定帮绫罗抢过来。于是梅拉和暖暖开始了搭配比赛。梅拉和暖暖各有n套衣服。由于暖暖是天才服装搭配师，且自带主角光环，又怎会输呢，（废话，输了你怎么通关啊）只不过暖暖为了让梅拉输的心服口服，决定狠狠虐梅拉一把。针对梅拉的n套衣服，暖暖的每套衣服i得分都比梅拉的任意一套衣服j得分高出score(ij)，0<=score(ij)<100000。然而每比完一场，他们之后的比赛都不能再用这套的衣服了。所以对于n场比赛，求出暖暖最高能比梅拉高多少分？（至少为0）
Input
首行输入n(n<=300)

接下来n行，第i行表示暖暖的第i套衣服，每行n个数，第j个数表示暖暖第i套衣服比梅拉第j套衣服的分高多少分。

0<=score(ij)<100000

Output
输出一个整数，即最高高出多少分
Sample Input
2
100 5
20 23
Sample Output
123

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int maxn = 100010, inf = 0x3fffffff;
struct node {
    int to, f, cost; // f代表还能流过多少
} Map[maxn * 100];

vector<int> v[maxn];
// p 为前驱结点，p为前驱边
int cnt, p[maxn], pre[maxn], dis[maxn], vis[maxn], n;

void insert(int x, int y, int cost, int f) {
    Map[cnt].to = y;
    Map[cnt].f = f;
    Map[cnt].cost = cost;
    v[x].push_back(cnt);
    ++cnt;
}

void init(int s, int e) {
    memset(pre, -1, sizeof(pre)); // 记录前驱边
    memset(p, -1, sizeof(p)); // 记录前驱结点
    memset(vis, 0, sizeof(vis)); // 标记结点是否在队列中
    for (int i = s; i <= e; ++i) {
        dis[i] = -inf;
    }
    dis[s] = 0;
}

bool spfa(int s, int e) {
    init(s, e);
    
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            int y = Map[c].to;
            if (Map[c].f > 0
                && Map[c].cost + dis[now] > dis[y]) {
                dis[y] = Map[c].cost + dis[now];
                p[y] = now;
                pre[y] = c;
                if (vis[y] == 0) {
                    vis[y] = 1;
                    q.push(y);
                }
            }
        }
    }
    return dis[e] != -inf;
}

int min_cost_flow(int s, int e) {
    int cost = 0;
    // int flow = 0; // 这里不需要
    while (spfa(s, e)) {
        int f = inf;
        for (int u = e; u != s; u = p[u]){
            f = min(f, Map[pre[u]].f);
        }
        // flow += f; // 更新最大流
        cost += dis[e] * f; // 更新最小费用
        
        for (int u = e; u != s; u = p[u]){
            Map[pre[u]].f -= f;
            Map[pre[u]^1].f += f;
        }
    }
    return cost;
}

int main() {
    int x;
    freopen("/Users/admin/Desktop/test-2.in", "r", stdin);
    while (cin >> n) {
        for (int i = 0; i <= n * n + 1; ++i) {
            v[i].clear();
        }
        cnt = 0;
        int s = 0, e = n * n + 1;
        for (int i = 1; i <= n; ++i) {
            insert(s, i, 0, 1);
            insert(i, s, 0, 0);
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> x;
                insert(i, j + n, x, 1);
                insert(j + n, i, -x, 0);
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            insert(n + i, e, 0, 1);
            insert(e, n + i, 0, 0);
        }
        printf("%d\n", min_cost_flow(s, e));
    }
    return 0;
}


// E
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 100010, inf = 0x3fffffff;

int cnt;
struct node {
    int to, now, f;
} Map[maxn * 2];

int depth[maxn];
vector<int> v[maxn];

void insert(int x, int y, int f, int now) {
    Map[cnt].to = y;
    Map[cnt].now = now;
    Map[cnt].f = f;
    v[x].push_back(cnt);
    ++cnt;
    // 由于之后用到Map[now^1]，所以cnt必须从0开始
    // 0-1对应 2-3对应...
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    // 判断有无增广路
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            if (depth[Map[c].to] == 0 && Map[c].f - Map[c].now > 0) {
                depth[Map[c].to] = depth[now] + 1;
                q.push(Map[c].to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int flow) {
    if (now == e) {
        return flow;
    }
    for (int i = 0; i < v[now].size(); ++i) {
        int c = v[now][i];
        if (depth[Map[c].to] == depth[now] + 1
            && Map[c].f - Map[c].now > 0) {
            int d = dfs(Map[c].to, e, min(flow, Map[c].f - Map[c].now));
            if (d > 0) {
                Map[c].now += d;
                Map[c^1].now -= d;
                return d; // 找到增广路
            }
        }
    }
    return 0; // 不存在增广路
}

int dinic(int s, int e) {
    int ans = 0;
    while (bfs(s, e)) {
        while (int d = dfs(s, e, inf)) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, m, e;
    while (cin >> n >> m >> e) {
        cnt = 0;
        for (int i = 0; i <= n + m + 1; ++i) {
            v[i].clear();
        }
        int start = 0, a, b, end = n + m + 1;
        for (int i = 1; i <= n; ++i) {
            insert(start, i, 1, 0);
            insert(i, start, 1, 1);
        }
        for (int i = n + 1; i <= n + m; ++i) {
            insert(i, end, 1, 0);
            insert(end, i, 1, 1);
        }
        for (int i = 0; i < e; ++i) {
            cin >> a >> b;
            b += n;
            
            insert(a, b, 1, 0);
            insert(b, a, 1, 1);
        }
        printf("%d\n", dinic(start, end));
    }
    return 0;
}


// 默写的模板~~
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 2010, inf = 0x3fffffff;

int cnt;
struct node {
    int to, now, f;
} Map[maxn * 2];

int depth[maxn];
vector<int> v[maxn];

void insert(int x, int y, int f, int now) {
    Map[cnt].to = y;
    Map[cnt].now = now;
    Map[cnt].f = f;
    v[x].push_back(cnt);
    ++cnt;
    // 由于之后用到Map[now^1]，所以cnt必须从0开始
    // 0-1对应 2-3对应...
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    // 判断有无增广路
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            if (depth[Map[c].to] == 0 && Map[c].f - Map[c].now > 0) {
                depth[Map[c].to] = depth[now] + 1;
                q.push(Map[c].to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int flow) {
    if (now == e) {
        return flow;
    }
    for (int i = 0; i < v[now].size(); ++i) {
        int c = v[now][i];
        if (depth[Map[c].to] == depth[now] + 1
            && Map[c].f - Map[c].now > 0) {
            int d = dfs(Map[c].to, e, min(flow, Map[c].f - Map[c].now));
            if (d > 0) {
                Map[c].now += d;
                Map[c^1].now -= d;
                return d; // 找到增广路
            }
        }
    }
    return 0; // 不存在增广路
}

int dinic(int s, int e) {
    int ans = 0;
    while (bfs(s, e)) {
        while (int d = dfs(s, e, inf)) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, m, a, b, f;
    while (cin >> n >> m) {
        cnt = 0;
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> f;
            insert(a, b, f, 0);
            insert(b, a, f, f);
        }
        printf("%d\n", dinic(1, n));
    }
    return 0;
}


// 网络流最小割
Problem G: 巨人也疯狂
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 4  Solved: 4
[Submit][Status][Web Board][Creator:qianyouyou][Edit] [TestData]
Description
人类发现巨人控制吃人的神经是由一些神经元和一些神经通道组成的，每个神经通道两端各有一个神经元，且这个通道是单向的。吃人信号从脑部神经元S发出到控制吃人的神经元T，S、T之间是一个有向无环图。人类想把某些神经通道切断达到S的信号无法传到T（由于神经元太小不容易砍掉，所以考虑神经元），每个神经通道由于位置不同也有砍断所需的力量。人类想知道如何花最小的力气而使S的信号传不到T。
Input
首行输入两个数，n，m，（n，m<1000）。n代表包括s，t在内共有n个节点，1为s，n为t。

接下来m行，每行3个数，a，b，c，表示a到b的神经通路需要花费c力气。

Output
输出最小的力气。
Sample Input
7 8
1 2 2
1 3 2
2 4 2
2 5 2
3 5 2
4 6 2
6 7 2
5 7 2
Sample Output
4

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 0x3fffffff;

struct node {
    int to, now, f; // 流向哪、当前流量、最大流量
} Map[2010];

int cnt, depth[2010]; // 结点个数 和 每个节点深度

vector<int> v[1010];

void insert(int x, int y, int f, int now) {
    Map[cnt].to = y;
    Map[cnt].f = f;
    Map[cnt].now = now;
    v[x].push_back(cnt);
    ++cnt;
}

int bfs(int s, int e) {
    // 判断有无增广路
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        
        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            if (Map[c].f - Map[c].now > 0 && depth[Map[c].to] == 0) {
                depth[Map[c].to] = depth[now] + 1;
                q.push(Map[c].to);
            }
        }
    }
    return depth[e] != 0; // 若depth[e] == 0 说明没有增广路，返回0
}

// s : 当前结点
// flow : 当前流量
int dfs(int now, int flow, int e) {
    if (now == e) {
        // 当已经到达汇点，直接返回
        return flow;
    }
    for (int i = 0; i < v[now].size(); ++i) {
        int c = v[now][i];
        if (depth[now] + 1 == depth[Map[c].to]
            && Map[c].f - Map[c].now > 0) {
            // 下一个节点在下一层，并且有流量
            int d = dfs(Map[c].to, min(flow, Map[c].f - Map[c].now), e);
            if (d > 0) {
                // 有增广路
                Map[c].now += d;
                Map[c^1].now -= d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int e) {
    int ans = 0;
    while (bfs(s, e)) { // 只要还有增广路
        while (int d = dfs(s, inf, e)) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, m, a, b, f;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
        }
        cnt = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &f);
            insert(a, b, f, 0);
            insert(b, a, f, f);
        }
        printf("%d\n", dinic(1, n));
    }
    return 0;
}


// 网络流最大流裸题
Problem C: 进击的巨人
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 3  Solved: 3
[Submit][Status][Web Board][Creator:qianyouyou][Edit] [TestData]
Description
那一年，巨人发起了第一轮进击，s城破，埃尔文团长带领众居民计划逃往较安全的t城。从s城到t城之间共有m坐城市，某些城市之间构成单向通路。由s城到t城恰构成一个有向无环图。然而每条路上都有限定的最大人流量。埃尔文团长想知道每一次最多有多少居民能到达t城。
Input
首行输入两个数n，m（n，m<=100），n0为s城，nn为t城。s城到t城之间的城用n1——nn表示。m表示单项通道数。

接下来m行，每行三个数a，b，c，代表a到b的最大人流量是c。c<1000。

Output
输出最多有多少人到t
Sample Input
6 14
0 2 5
0 1 10
1 2 6
0 3 5
3 1 2
1 5 3
5 2 3
5 4 3
3 5 3
3 4 4
3 6 5
2 6 6
4 6 10
2 4 4
Sample Output
18

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 0x3fffffff;

struct node {
    int to, now, f; // 流向哪、当前流量、最大流量
} Map[2010];

int cnt, depth[2010]; // 结点个数 和 每个节点深度

vector<int> v[1010];

void insert(int x, int y, int f, int now) {
    Map[cnt].to = y;
    Map[cnt].f = f;
    Map[cnt].now = now;
    v[x].push_back(cnt);
    ++cnt;
}

int bfs(int s, int e) {
    // 判断有无增广路
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        
        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            if (Map[c].f - Map[c].now > 0 && depth[Map[c].to] == 0) {
                depth[Map[c].to] = depth[now] + 1;
                q.push(Map[c].to);
            }
        }
    }
    return depth[e] != 0; // 若depth[e] == 0 说明没有增广路，返回0
}

// s : 当前结点
// flow : 当前流量
int dfs(int now, int flow, int e) {
    if (now == e) {
        // 当已经到达汇点，直接返回
        return flow;
    }
    for (int i = 0; i < v[now].size(); ++i) {
        int c = v[now][i];
        if (depth[now] + 1 == depth[Map[c].to]
            && Map[c].f - Map[c].now > 0) {
            // 下一个节点在下一层，并且有流量
            int d = dfs(Map[c].to, min(flow, Map[c].f - Map[c].now), e);
            if (d > 0) {
                // 有增广路
                Map[c].now += d;
                Map[c^1].now -= d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int e) {
    int ans = 0;
    while (bfs(s, e)) { // 只要还有增广路
        while (int d = dfs(s, inf, e)) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, m, a, b, f;
    while (cin >> n >> m) {
        for (int i = 0; i <= n; ++i) {
            v[i].clear();
        }
        cnt = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &f);
            insert(a, b, f, 0);
            insert(b, a, f, f);
        }
        printf("%d\n", dinic(0, n));
    }
    return 0;
}


// 网络流最大流裸题
// hdu 1532 也可过
Problem B: 海上钢琴师
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 7  Solved: 4
[Submit][Status][Web Board][Creator:qianyouyou][Edit] [TestData]
Description
宁愿一生孤独，不愿随波逐流。海上钢琴师毅然留在了船上，与大海为伴，此生再不上岸。

然而，他的音乐却已名扬四海。为了将他的钢琴声可以传播到陆地以便欣赏，人们决定在陆地与钢琴师所在的船之间的n-2座岛屿上建立声音保留设备。每当声音传到该设备处时，以该设备为起点可以将声音信号发送到其他与该设备有信号连接的设备那里。信号传播是单向的，且是有限的。当该设备将一部分信号传给其他设备时，该设备所拥有的总信号要减去相应传出去的信号，所保留的信号可以继续传给其他的设备。船上也有该设备，由于岛屿与船的位置不同，所以钢琴声传到设备的声音有限。设备与设备之间的传播分贝也有限。陆地的总接收设备与某些岛屿上的设备有信号连接，请问陆地最多能收到多少分贝的钢琴声。

Input
第一行输入两个数m，n。m代表共有m对设备建立了单向连接。n代表包括船和陆地在内共有n个设备。编号1为船，编号n为陆地，其他为岛屿（n<=100，m<=1000）

接下来m行，每行三个数a，b，c，代表a->b，即a的信号可以传到b信号，最大可以通过该信号传送c分贝。c<=2000

Output
输出陆地上最大可以收到多少分贝声音。（海上钢琴声不超过10000分贝）
Sample Input
5 4
1 2 100
1 3 50
2 3 2
3 4 60
2 4 99
Sample Output
150

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 0x3fffffff;

struct node {
    int to, now, f; // 流向哪、当前流量、最大流量
} Map[2010];

int cnt, depth[2010]; // 结点个数 和 每个节点深度

vector<int> v[1010];

void insert(int x, int y, int f, int now) {
    Map[cnt].to = y;
    Map[cnt].f = f;
    Map[cnt].now = now;
    v[x].push_back(cnt);
    ++cnt;
}

// 算法步骤如下:
// STEP1 : 建造原网络G的一个分层网络L。
// STEP2 : 用增广路算法计算L的最大流F, 若在L中找不到增广路, 算法结束。
// SETP3 : 根据 F 更新G中的流f, 转STEP1

// 分层网络的构造算法:
// STEP1 : 标号源节点s,M[s]=0。
// STEP2 : 调用广度优先遍历算法,执行一步遍历操作, 当前遍历的弧e=v1v2,令r=G.u(e)-G.f(e)。 若r>0,则
// (1) 若M[v2]还没有遍历,则M[v2]=M[v1]+1,且将 弧e加入到L中,容量L.u(e)=r。
// (2) 若M[v2]已经遍历且M[v2]=M[v1]+1,则将边e 加入到L中,容量L.u(e)=r。
// (3) 否则L.u(e)=0。
// 否则L.u(e)=0。 重复本步直至G遍历完。其中的G.u(e)、G.f(e)、L.u(e) 分别表示图G中弧e的容量上界和当前流量,图L中弧e 的容量上界。
int bfs(int s, int e) {
    // 判断有无增广路
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < v[now].size(); ++i) {
            int c = v[now][i];
            if (Map[c].f - Map[c].now > 0 && depth[Map[c].to] == 0) {
                depth[Map[c].to] = depth[now] + 1;
                q.push(Map[c].to);
            }
        }
    }
    return depth[e] != 0; // 若depth[e] == 0 说明没有增广路，返回0
}

// s : 当前结点
// flow : 当前流量
int dfs(int now, int flow, int e) {
    if (now == e) {
        // 当已经到达汇点，直接返回
        return flow;
    }
    for (int i = 0; i < v[now].size(); ++i) {
        int c = v[now][i];
        if (depth[now] + 1 == depth[Map[c].to]
            && Map[c].f - Map[c].now > 0) {
            // 下一个节点在下一层，并且有流量
            int d = dfs(Map[c].to, min(flow, Map[c].f - Map[c].now), e);
            if (d > 0) {
                // 有增广路
                Map[c].now += d;
                Map[c^1].now -= d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int e) {
    int ans = 0;
    while (bfs(s, e)) { // 只要还有增广路
        while (int d = dfs(s, inf, e)) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, m, a, b, f;
    while (cin >> m >> n) {
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
        }
        cnt = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &f);
            insert(a, b, f, 0);
            insert(b, a, f, f);
        }
        printf("%d\n", dinic(1, n));
    }
    return 0;
}


Problem A: 赛马
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 22  Solved: 3
[Submit][Status][Web Board][Creator:qianyouyou][Edit] [TestData]
Description
古有田忌赛马戏齐王，今有悠悠赛马虐渣渣。悠悠和他的小老弟渣渣每人有n匹马，每匹马都有一个评分，分数越高速度越快。现在渣渣不甘于当小老弟，随着赛马曲的想起，渣渣决定挑战悠悠，规则同田忌赛马。每胜一局得1分，每负一局减一分，赵神做裁判，悠悠为了捍卫自己的王者地位，决定出老千，问了赵神关于渣渣的赛马顺序，请问悠悠最高能得多少分。
Input
文件有多组测试样例，遇0为止。

首行一个整数n，n<=1000;

第2行n个整数表示悠悠每匹马的分数。

第2行n个整数表示渣渣每匹马的分数。0<=分数<500;

Output
输出悠悠最高分。
Sample Input
3
192 173 71
195 177 74
2
10 10
10 10
2
220 219
222 218
0
Sample Output
1
0
0
// 贪心
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
LL tianji[1010], qiwang[1010];

int main(int argc, const char * argv[]) {
    int n;
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            cin >> tianji[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> qiwang[i];
        }
        // 从小到大排序
        sort(tianji, tianji + n);
        sort(qiwang, qiwang + n);
        LL sum = 0;
        int min1 = 0, min2 = 0, max1 = n - 1, max2 = n - 1, cnt = 0;
        while (cnt++ < n) {
            if (tianji[max1] > qiwang[max2]) {
                // tianji最快若大于qiwang最快，则比较
                ++sum;
                --max1, --max2;
            } else if (tianji[max1] < tianji[max2]) {
                // 若小于，则所有马都慢于qiwang最快马，用最慢马消耗
                --sum;
                ++min1;
                --max2;
            } else {
                // 若两者最快马等于，比较最慢马
                if (tianji[min1] > qiwang[min2]) {
                    // 若大于，将两者最慢马比较
                    ++sum;
                    ++min1, ++min2;
                } else {
                    // 其他，将tianji最慢马与qiwang最快马比较
                    if (tianji[min1] < qiwang[max2]) {
                        --sum;
                    }
                    // 若二者也相等，不用减
                    ++min1, --max2;
                }
            }
        }
        cout << sum << endl;
    }
    return 0;
}
*/
