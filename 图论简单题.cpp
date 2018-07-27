//
//  main.cpp
//  0726
//
//  Created by admin on 18/7/26.
//  Copyright © 2018年 Amon. All rights reserved.
/*
// G
Description
有n张牌，每个牌有一个a属性和1个b属性，第i张牌的属性为ai，bi。现在每次从牌中选两张牌i，j，得到一个ai * bj + bi * aj的分数，然后从这两张牌中去掉1张牌。经过n-1次操作之后就剩1张牌了。问经过n-1次操作后得到的最大的分数和是多少。

Input
首行输入n，代表n个点

接下来n行，每一行两个属性ab第i行代表第i张牌，属性为ai，bi。数据范围保持在200以内。

Output
输出最大分数

Sample Input
5
2 4
3 3
1 7
2 5
4 4
Sample Output
108

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

struct node {
    int x, y, l; // 起点 重点 长度
} edge[1010];

int a[1010], b[1010], fa[1010];

bool cmp(node x, node y) {
    return x.l > y.l;
}

int findfa(int x) {
    return fa[x] == x ? x : (fa[x] = findfa(fa[x]));
}

void merge(int i, int j) {
    fa[findfa(i)] = findfa(j);
}

long long int kruskal(int num) {
    int cnt = 0;
    long long int sum = 0;
    for (int i = 0; i < num; ++i) {
        int fx = findfa(edge[i].x);
        int fy = findfa(edge[i].y);
        if (fx != fy) {
            merge(fx, fy);
            ++cnt;
            sum += edge[i].l;
            if (cnt >= num - 1) {
                break;
            }
        }
        
    }
    return sum;
}

int main() {
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
        }
        for (int i = 1; i <= n; ++i) {
            cin >> a[i] >> b[i];
        }
        int num = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j) {
                    edge[num].x = i;
                    edge[num].y = j;
                    edge[num++].l = a[i] * b[j] + a[j] * b[i];
                }
            }
        }
        sort(edge, edge + num, cmp);
        cout << kruskal(num) << endl;
    }
    return 0;
}

// F Floyd算法求环???然而做完感觉完全用不到啊。。。
Description
yoyo得到了一个足球，这个足球与其他的足球一样，表面有 12 个正五边形和 20 个正六边形组成，足球的每个面初始的时候都为白色。现在yoyo把这个足球拆解开来，32个面编号为1~32。
爱画画的yoyo希望将足球的某些面涂为黑色（可能是 0 个），在每次涂色操作中，慢慢只可以将某一些相邻或者联通的面一起涂为黑色（两个面相邻当且仅当他们共用一条边）。例如，yoyo可以在一次涂色操作中将面 1、2、3、4、5 涂为黑色，但是他不可以将面11 和 24 涂为白色，因为面 11 和 24 是不相邻也不联通的。

除了相邻的数，面也相邻外，面 1 和面 13 是相邻的，面 13 和面 17 是相邻的，面 17 和面 32 是相邻的，面 15 和面 32 是相邻的，面 19 和面 32 是相邻的。

求yoyo所需要的最少的涂色次数。

Input
第一行包含一个整数 t，表示有t组测试数据，对于每组测试数据：

输入包含一行，该行包含 32 个整数，每个数的值等于 0 时表示白色，等于 1 时表示黑色。

Output
对于每组测试数据，输出Case c: ans，其中 c 为测试数据编号，ans 为最少的操作次数。

Sample Input
3
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

Sample Output
Case 1: 1
Case 2: 0
Case 3: 2

#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int inf = 0x3f3f3f3f;
int a[40];
int dis[40][40], vis[40];

void dfs(int x) {
    vis[x] = 1;
    a[x] = 0;
    for (int i = 1; i <= 32; ++i) {
        if (i != x && !vis[i] && a[i] == 1 && dis[i][x] == 1) {
            dfs(i);
        }
    }
}

int main() {
    
    int t, Case = 1;
    for (int i = 1; i <= 32; ++i) {
        for (int j = 1; j <= 32; ++j) {
            dis[i][j] = inf;
            if (i == j) {
                dis[i][j] = 0;
            } else if (abs(i - j) == 1) {
                dis[i][j] = 1;
            }
        }
    }
    
    dis[1][13] = 1, dis[13][1] = 1;
    dis[13][17] = 1, dis[17][13] = 1;;
    dis[17][32] = 1, dis[32][17] = 1;
    dis[15][32] = 1, dis[32][15] = 1;
    dis[19][32] = 1, dis[32][19] = 1;
    
    for (int i = 1; i <= 32; ++i) {
        for (int j = 1; j <= 32; ++j) {
            for (int k = 1; k <= 32; ++k) {
                if (i != j && j != k && k != i
                    && dis[i][k] + dis[k][j] <= dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    cin >> t;
    while (t--) {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= 32; ++i) {
            cin >> a[i];
        }
        int cnt = 0;
        for (int i = 1; i <= 32; ++i) {
            if (a[i] == 1) {
                dfs(i);
                ++cnt;
            }
        }
        printf("Case %d: %d\n", Case++, cnt);
    }
    return 0;
}


// E dijkstra 算法变形
Description
假设渣渣灰有一个女朋友，他的女朋友要他陪着一起去公园。由于渣渣灰不喜欢运动，所以他想找一条最短的路到达公园。由于途中会有许多消费点，而每到一个消费点女朋友就要购物，而渣渣灰比较抠，所以假如有多条最短路，则他会选择途中消费点最便宜的。给你n个点，m条无向边，每条边都有长度d和花费p，给你起点s终点t，要求输出起点到终点的最短距离及其花费，如果最短距离有多条路线，则输出花费最少的。

Input
输入nm，点的编号是1~n然后是m行，每行4个数 abdp，表示a和b之间有一条边，且其长度为d，花费为p。最后一行是两个数 st;起点s，终点。n和m为0时输入结束。
(1<n<=1000 0<m<100000 s != t)

Output
输出 一行有两个数， 最短距离及其花费。
Sample Input
3 2
1 2 5 6
2 3 4 5
1 3
0 0

Sample Output
9 11

#include <iostream>
#include <cstring>
#include <cstdio>
 
using namespace std;
 
const int inf = 0x3f3f3f3f;
int n, m;
int road[1010][1010], pay[1010][1010];
int vis[1010], dis[1010], f[1010];

void dijkstra(int s, int e) {
    vis[s] = 1;
    for (int i = 1; i < n; ++i) {
        int minD = inf, k = -1, minP = inf;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && dis[j] < minD) {
                minD = dis[j];
                k = j;
            } else if(!vis[j] && dis[j] == minD) {
                if (minP > f[j]) {
                    minP = f[j];
                    k = j;
                }
            }
        }
        vis[k] = 1;
        
        if (k == e) break;
        if (k == -1) return; // 不通
        
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && dis[k] + road[k][j] < dis[j]) {
                dis[j] = dis[k] + road[k][j];
                f[j] = f[k] + pay[k][j];
            } else if (!vis[j] && dis[k] + road[k][j] == dis[j]) {
                if (f[k] + pay[k][j] < f[j]) {
                    f[j] = f[k] + pay[k][j];
                }
            }
        }
    }
}


int main() {
    
    while (cin >> n >> m && n + m) {
        int a, b, d, p;
        for (int i = 1; i <= n; ++i) {
            fill(road[i] + 1, road[i] + n + 1, inf);
            fill(pay[i] + 1, pay[i] + n + 1, inf);
        }
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> d >> p;
            road[a][b] = min(d, road[a][b]); // 有向
            road[b][a] = min(d, road[b][a]); // 无向
            if (road[a][b] == d) {
                pay[a][b] = p;
                pay[b][a] = p;
            }
        }
        int s, e;
        cin >> s >> e;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; ++i) {
            dis[i] = road[s][i];
            f[i] = pay[s][i];
        }
        dis[s] = 0;
        dijkstra(s, e);
        cout << dis[e] << ' ' << f[e] << endl;
    }
    return 0;
}


// D 记录路径的 dijkstra 算法
Description
你猜怎么样？小Z追到Gakki了！Gakki邀请小Z去她家共进晚餐，小Z喜出望外。小Z的家和Gakki的家隔着几个街区，所以他决定乘坐公交车前往

Gakki家赴约。小Z的家在公交站台的起始站（编号为1），而Gakki家正好在末站（编号为n）。城市中有许多公交站台，有些站台之间可以通过公交

线路互相到达。现在给你n个公交站台和m条不同的公交线路的时间花费，请你帮助小Z分析一下最短的可以从家里来到Gakki身边的路径？

Input
有多组测试样例。
第一行两个正整数n,m(2≤n≤10^5,0≤m≤10^5)，代表站台数与公交线路数量。
接下来m行每行三个正整数a[i],b[i],w[i],代表从公交站a[i]到b[i]需要花费的时间为w[i]。(1≤a[i],b[i]≤n,1≤w[i]≤10^6)
注意：公交线路可能会产生环，并且两个站台之间可能有多条公交线路。

Output
单独一行，输出花费时间最小时小Z经过的公交站台编号，以空格隔开；如果小Z无法到达Gakki的家，则输出-1.

Sample Input
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1

Sample Output
1 4 3 5

#include <iostream>
#include <cstring>
#include <stack>
#include <cstdio>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
int n, m;
int road[1010][1010];
int vis[1010], dis[1010], pre[1010];

bool dijkstra(int s, int e) {
    vis[s] = 1;
    
    for (int i = 1; i < n; ++i) {
        int minD = inf, k = -1;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && dis[j] < minD) {
                minD = dis[j];
                k = j;
            }
        }
        vis[k] = 1;
        
        if (k == e) break;
        if (k == -1) return 0; // 不通
        
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && dis[k] + road[k][j] < dis[j]) {
                dis[j] = dis[k] + road[k][j];
                pre[j] = k;
            }
        }
    }
    return 1;
}

int main() {
    
    while (cin >> n >> m) {
        int a, b, z;
        for (int i = 1; i <= n; ++i) {
            fill(road[i] + 1, road[i] + n + 1, inf);
        }
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> z;
            road[a][b] = min(z, road[a][b]); // 有向
            road[b][a] = min(z, road[b][a]); // 无向
        }
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; ++i) {
            dis[i] = road[1][i];
            pre[i] = 1;
        }
        dis[1] = 0;
        if (dijkstra(1, n) == 0) {
            cout << -1 << endl;
            continue;
        }
        int k = pre[n];
        stack<int> s;
        while (k != 1) {
            s.push(k);
            k = pre[k];
        }
        cout << 1 << ' ';
        while (!s.empty()) {
            cout << s.top() << ' ';
            s.pop();
        }
        cout << n << endl;
    }
    return 0;
}


// C 不记录路径的 dijkstra 算法
Description
渣渣灰因为一句“大家好，我系渣渣辉，系兄弟就来砍我”引得众粉丝纷纷拿两米长的大刀寻找。现有n个据点，编号（1~n），有m条单向路使据点相连。每个据点仅有一个人。这n个人中有k个粉丝。其中渣渣灰在s据点处。请问这k个粉丝到渣渣灰的最短距离是多少
Input
首行输入nmks。(k<=n<=100m<=500)s为渣渣灰所在位置

接下来m行，每行输入xyz，表示从x到y的距离是z，由于是单向边，则y到x的距离不一定是z。

接下来k个数字，表示粉丝所在据点。

Output
对于每一个粉丝，输出对应的最短距离。
Sample Input
3 3 2 1
1 2 1
2 3 1
3 1 1
2 3
Sample Output
2 1

#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;

const int inf = 0x3f3f3f3f;
int n;
int dis[550]; // 存储各个点到源点的最短距离
int road[550][550]; // 两点间直接距离关系
int vis[550];

void dijkstra() {
    // 找 n-1 次
    for (int u = 1; u < n; ++u) {
        int minD = inf, k = -1;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && dis[i] < minD) {
                k = i, minD = dis[i];
            }
        }
        vis[k] = 1;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && dis[k] + road[k][i] < dis[i]) {
                dis[i] = dis[k] + road[k][i];
            }
        }
    }
}

int main() {
    int m, k, s;
    while (cin >> n >> m >> k >> s) {
        for (int i = 1; i <= n; ++i) {
            fill(road[i] + 1, road[i] + n + 1, inf);
        }
        
        int x, y, z;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y >> z;
            road[y][x] = z;
        }
        
        for (int i = 1; i <= n; ++i) {
            dis[i] = road[s][i];
        }
        dis[s] = 0;
        vis[s] = 1;
        dijkstra();
        int e;
        for (int i = 0; i < k - 1; ++i) {
            cin >> e;
            cout << dis[e] << ' ';
        }
        cin >> e;
        cout << dis[e] << endl;
    }
    
    return 0;
}


// B 拓扑排序
Description
有 N 个比赛队（1<=N<=500），编号依次为 1，2，3……N 进行比赛，比赛结束后，裁判委员会要将所有参赛队伍从前往后依次排名，但现在裁判委员会不能直接获得每个队的比赛成绩，只知道每场比赛的结果，即 P1 赢 P2，用 P1，P2 表示，排名时 P1 在 P2之前。现在请你编程序确定排名。

符合条件的排名可能不是唯一的。此时要求输出时编号小的队伍在前。输入数据保证是正确的，即输入数据确保一定能有一个符合要求的排名。

Input
输入有若干组。每组中的第一行为二个数N（1<=N<=500）。M；当中N表示队伍的个数，M表示接着有M行的输入数据。接下来的M行数据中。每行也有两个整数P1。P2表示即P1队赢了P2队。
Output
给出一个符合要求的排名。输出时队伍号之间有空格。最后一名后面没有空格。
Sample Input
4 3
1 4
4 3
2 3
Sample Output
1 2 4 3

#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;
struct node {
    int _to; // 若有权，加一个 int l;
    int _next;
} edge[550];

int num;

int in[550]; // 入度
int ret[550];
int head[550];

void insert(int x, int y) {
    edge[num]._to = y;
    edge[num]._next = head[x];
    head[x] = num++;
}

int main(int argc, const char * argv[]) {
    int n, m;
    while (cin >> n >> m) {
        num = 0;
        memset(head, -1, sizeof(head));
        int x, y;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            insert(x, y);
            ++in[y];
        }
        priority_queue<int, vector<int>, greater<int> > q;
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 0) q.push(i);
        }
        int k = 0;
        while (!q.empty()) {
            int a = q.top();
            ret[k++] = a;
            q.pop();
            for (int now = head[a]; now != -1; now = edge[now]._next) {
                --in[edge[now]._to];
                if (in[edge[now]._to] == 0) {
                    q.push(edge[now]._to);
                }
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            cout << ret[i] << ' ';
        }
        cout << ret[n - 1] << endl;
    }
    return 0;
}


// A 水题
Description
楼梯有n阶台阶，青蛙每次可以跳1~n阶台阶，问青蛙共有多少种上楼梯的方法。
Input
输入仅一行，一个整数n（n<=50）
Output
输出n阶台阶对应上楼梯的方法。
Sample Input
3
Sample Output
4

#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

long long int p(long long int n) {
    long long int sum = 1;
    for (int i = 1; i <= n; ++i) {
        sum *= 2;
    }
    return sum;
}
int main() {
    
    long long int n;
    while (~scanf("%lld", &n)) {
        printf("%lld\n", p(n - 1));
    }
    return 0;
}
*/
