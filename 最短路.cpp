//
//  main.cpp
//  最短路
//
//  Created by admin on 18/10/1.
//  Copyright © 2018年 Amon. All rights reserved.
//
// hdu 3360
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 110;
const LL inf = 0x3f3f3f3f3f3f;
LL floyd[maxn][maxn], Map[maxn][maxn];

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main() {
    int n, m, x, y, d;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; ++i) {
            fill(floyd[i], floyd[i] + n + 1, inf);
            fill(Map[i], Map[i] + n + 1, inf);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            floyd[x][y] = floyd[y][x] = Map[y][x] = Map[x][y] = min(Map[x][y], d);
        }
        LL Min = inf;
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    Min = min(Min, Map[i][k] + Map[k][j] + floyd[i][j]);
                }
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
                }
            }
        }
        if (Min == inf) {
            printf("It's impossible.\n");
        } else {
            printf("%lld\n", Min);
        }
    }
    return 0;
}

/*
// hdu 4370
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int maxn = 310, inf = 0x3fffffff;
int vis[maxn], dis[maxn], d[maxn][maxn], n;

void spfa(int choose) {
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    if (choose == 0) {
        q.push(1);
        dis[1] = 0;
    } else {
        for (int i = 1; i <= n; ++i) {
            if (i != choose) {
                dis[i] = d[choose][i];
                q.push(i);
            }
        }
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = 1; i <= n; ++i) {
            if (dis[i] > dis[now] + d[now][i]) {
                dis[i] = dis[now] + d[now][i];
                if (vis[i] == 0) {
                    vis[1] = 1;
                    q.push(i);
                }
            }
        }
    }
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &d[i][j]);
            }
        }
        spfa(0);
        int Min = dis[n], k = 0;
        spfa(1);
        k = dis[1];
        spfa(n);
        k += dis[n];
        printf("%d\n", min(Min, k));
        
    }
    return 0;
}


// poj 3169
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1010, inf = 0x3fffffff;
LL dis[maxn];
int n, cnt;
bool vis[maxn];
struct edge {
    int to;
    LL d;
};
vector<edge> v[maxn];

void insert(int x, int y, LL d) {
    v[x].push_back({y, d});
}

int spfa() {
    fill(dis, dis + maxn, inf);
    queue<int> q;
    dis[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        int len = (int)v[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now][i].to;
            if (dis[to] > dis[now] + v[now][i].d) {
                dis[to] = dis[now] + v[now][i].d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
                if (to == n) {
                    ++cnt;
                }
                if (cnt > n) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int m, k, x, y, d;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &d);
        insert(x, y, d);
    }
    for (int i = 0; i < k; ++i) {
        scanf("%d%d%d", &x, &y, &d);
        insert(y, x, -d);
    }
    if (spfa()) {
        printf("-1\n"); // 找不到路
    } else {
        if (dis[n] == inf) {
            printf("-2\n"); // 走不到，无限远
        } else {
            printf("%lld\n", dis[n]);
        }
    }
    return 0;
}


// poj 3159 差分约束
#include <cstdio>
#include <stack>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn = 3e4 + 10, maxm = 2e5 + 10, inf = 0x3fffffff;
int head[maxn], dis[maxn], vis[maxn], cnt;
struct Edge {
    int to, d, next;
} edge[maxm];

void init() {
    cnt = 0;
    memset(head, -1, sizeof(head));
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
}

void insert(int x, int y, int d) {
    edge[cnt] = {y, d, head[x]};
    head[x] = cnt++;
}

void spfa() {
    stack<int> s;
    s.push(1);
    dis[1] = 0;
    while (!s.empty()) {
        int now = s.top();
        s.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next) {
            int to = edge[i].to, d = edge[i].d;
            if (dis[to] > dis[now] + d) {
                dis[to] = dis[now] + d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    s.push(to);
                }
            }
        }
    }
}

int main() {
    init();
    int n, m, x, y, d;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, d);
        }
        spfa();
        printf("%d\n", dis[n]);
    }
    return 0;
}


// poj 1062
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int maxn = 110;
int dis[maxn], vis[maxn], m;

struct edge {
    int to, d;
};

struct node {
    int value, level;
    struct tmp {
        int num, w;
    };
    vector<tmp> k;
} peo[maxn];

vector<edge> v[maxn];

void insert(int x, int y, int d) {
    v[x].push_back({y, d});
}

void spfa(int level) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        int len = (int)v[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now][i].to;
            if (peo[to].level <= level && peo[to].level >= level - m) {
                if (dis[to] < dis[now] + v[now][i].d) {
                    dis[to] = dis[now] + v[now][i].d;
                    if (vis[to] == 0) {
                        vis[to] = 1;
                        q.push(to);
                    }
                }
            }
        }
    }
}

int main() {
    int n, k, t, value;
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &peo[i].value, &peo[i].level, &k);
        for (int j = 0; j < k; ++j) {
            scanf("%d%d", &t, &value);
            peo[i].k.push_back({t, value});
        }
    }
    for (int i = 1; i <= n; ++i) {
        int len = (int)peo[i].k.size();
        for (int j = 0; j < len; ++j) {
            int num = peo[i].k[j].num;
            if (peo[num].level <= peo[1].level + m && peo[num].level >= peo[1].level - m) {
                insert(i, num, peo[i].value - peo[i].k[j].w - peo[num].value);
            }
        }
    }
    int Max = 0;
    for (int i = peo[1].level; i <= peo[1].level + m; ++i) {
        spfa(i);
        for (int j = 1; j <= n; ++j) {
            Max = max(dis[j], Max);
        }
    }
    printf("%d\n", peo[1].value - Max);
    return 0;
}


// poj 2502
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int maxn = 5e4 + 10, inf = 0x3fffffff;
int p, cnt, head[maxn], vis[maxn];
double dis[maxn];

struct Edge {
    int to, next;
    double d;
} edge[maxn], pp;

struct point {
    int x, y;
} s, e, tmp, stop[maxn];

double com_d(int x1, int y1, int x2, int y2) {
    return sqrt((double)(x1 - x2) * (x1 - x2) + (double)(y1 - y2) * (y1 - y2));
}

void insert(int a, int b, int r) {
    double d = com_d(stop[a].x, stop[a].y, stop[b].x, stop[b].y);
    d = d / (r / 3.6);
    pp.to = b, pp.next = head[a], pp.d = d;
    edge[++cnt] = pp;
    head[a] = cnt;
    pp.to = a, pp.next = head[b], pp.d = d;
    edge[++cnt] = pp;
    head[b] = cnt;
}

void spfa() {
    fill(dis, dis + maxn, inf);
    dis[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i; i = edge[i].next) {
            int to = edge[i].to;
            double d = edge[i].d;
            if (dis[to] > dis[now] + d) {
                dis[to] = dis[now] + d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

void ins(int num, int r) {
    for (int i = 0; i < num; ++i) {
        insert(i, num, r);
    }
}

int main() {
    int num = 2;
    scanf("%d%d%d%d", &s.x, &s.y, &e.x, &e.y);
    stop[0] = s, stop[1] = e;
    insert(0, 1, 10);
    while (~scanf("%d%d", &tmp.x, &tmp.y)) {
        stop[num] = tmp;
        ins(num++, 10);
        while (scanf("%d%d", &tmp.x, &tmp.y)) {
            if (tmp.x == -1 && tmp.y == -1) {
                break;
            }
            stop[num] = tmp;
            ins(num, 10);
            insert(num - 1, num, 40);
            ++num;
        }
    }
    spfa();
    printf("%.0lf\n", dis[1] / 60);
    return 0;
}


#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int maxn = 5e4 + 10, inf = 0x3fffffff;
int p, cnt, head[maxn], vis[maxn];
double dis[maxn];

struct Edge {
    int to, next;
    double d;
} edge[maxn], pp;

struct point {
    int x, y, id;
} s, e, tmp;

vector<point> stop[210];

double com_d(int x1, int y1, int x2, int y2) {
    return sqrt((double)(x1 - x2) * (x1 - x2) + (double)(y1 - y2) * (y1 - y2));
}

void insert(point a, point b, int r) {
    double d = com_d(a.x, a.y, b.x, b.y);
    d *= r;
    pp.to = b.id, pp.next = head[a.id], pp.d = d;
    edge[++cnt] = pp;
    head[a.id] = cnt;
    pp.to = a.id, pp.next = head[b.id], pp.d = d;
    edge[++cnt] = pp;
    head[b.id] = cnt;
}

void spfa() {
    fill(dis, dis + maxn, inf);
    dis[s.id] = 0;
    queue<int> q;
    q.push(s.id);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i; i = edge[i].next) {
            int to = edge[i].to;
            double d = edge[i].d;
            if (dis[to] > dis[now] + d) {
                dis[to] = dis[now] + d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

int main() {
    int sum = 0, num = 2;
    scanf("%d%d%d%d", &s.x, &s.y, &e.x, &e.y);
    s.id = 0, e.id = 1;
    insert(s, e, 4);
    while (~scanf("%d%d", &tmp.x, &tmp.y)) {
        if (tmp.x == -1 && tmp.y == -1) {
            ++sum;
            continue;
        }
        tmp.id = num++;
        stop[sum].push_back(tmp);
        insert(s, tmp, 4);
        insert(e, tmp, 4);
    }
    for (int i = 0; i < sum; ++i) {
        int len1 = (int)stop[i].size();
        for (int j = 0; j < len1; ++j) {
            for (int k = j + 2; k < len1; ++k) {
                insert(stop[i][j], stop[i][k], 4);
            }
            if (j < len1 - 1) {
                insert(stop[i][j], stop[i][j + 1], 1);
            }
            for (int k = i + 1; k < sum; ++k) {
                int len2 = (int)stop[k].size();
                for (int q = 0; q < len2; ++q) {
                    insert(stop[i][j], stop[k][q], 4);
                }
            }
        }
    }
    spfa();
    printf("%.0lf\n", dis[e.id] * 3 / 2000);
    return 0;
}

// hdu 4725
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
const int maxn = 4e5 + 10, inf = 0x3fffffff;
int dis[maxn], vis[maxn], head[maxn], cnt, n;

struct Edge {
    int to, d, next;
} edge[maxn << 2];

void init() {
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(head, -1, sizeof(head));
    fill(dis, dis + maxn, inf);
}

void insert(int x, int y, int d) {
    edge[cnt] = {y, d, head[x]};
    head[x] = cnt++;
}

void spfa() {
    // 卡 spfa
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next) {
            int to = edge[i].to;
            if (dis[to] > dis[now] + edge[i].d) {
                dis[to] = dis[now] + edge[i].d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

struct node {
    int id, d;
    friend bool operator < (const node& a, const node& b) {
        return a.d > b.d;
    }
} tmp;

void dij() {
    dis[1] = 0;
    priority_queue<struct node> q;
    q.push({1, 0});
    while (!q.empty()) {
        tmp = q.top();
        q.pop();
        if (vis[tmp.id]) {
            continue;
        }
        vis[tmp.id] = 1;
        for (int i = head[tmp.id]; i != -1; i = edge[i].next) {
            int to = edge[i].to, d = edge[i].d;
            if (dis[to] > dis[tmp.id] + d) {
                dis[to] = dis[tmp.id] + d;
                q.push({to, dis[to]});
            }
        }
    }
}

int main() {
    int t, m, c, x, y, d, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &c);
        init();
        int k = n + 3;
        for (int i = 2; i <= n; ++i) {
            insert(k, k - 1, c);
            insert(k - 2, k + 1, c);
            k += 2;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            insert(i, x * 2 + n - 1, 0);
            insert(x * 2 + n, i, 0);
        }
        
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, d);
            insert(y, x, d);
        }
        //spfa();
        dij();
        printf("Case #%d: ", ca++);
        if (dis[n] == inf) {
            printf("-1\n");
        } else {
            printf("%d\n", dis[n]);
        }
    }
    return 0;
}


// LightOj 1074
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 210, inf = 0x3fffffff;
int head[maxn], cnt, n, arr[maxn], num[maxn];
LL dis[maxn];
bool vis[maxn], f[maxn];

struct Edge {
    int to, next;
    LL d;
} edge[maxn * maxn];

void init() {
    memset(head, -1, sizeof(head));
    memset(num, 0, sizeof(num));
    memset(vis, 0, sizeof(vis));
    memset(f, 0, sizeof(f));
    fill(dis, dis + n + 10, inf);
    cnt = 0;
}

void insert(int x, int y, LL d) {
    edge[cnt] = {y, head[x], d};
    head[x] = cnt++;
}

void dfs(int now) {
    if (f[now]) {
        return;
    }
    f[now] = 1;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        dfs(edge[i].to);
    }
}

void spfa() {
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next) {
            int to = edge[i].to;
            LL k = pow(arr[to] - arr[now], 3);
            if (dis[to] > dis[now] + k) {
                dis[to] = dis[now] + k;
                if (vis[to] == 0 && f[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
                if (num[to] >= n) {
                    if (f[to] == 0) {
                        dfs(to);
                    }
                } else {
                    ++num[to];
                }
            }
        }
    }
}

int main() {
    int t, m, x, y, q, ca = 1;
    scanf("%d", &t);
    while (t--) {
        printf("Case %d:\n", ca++);
        scanf("%d", &n);
        init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            insert(x, y, pow(arr[y] - arr[x], 3));
        }
        spfa();
        scanf("%d", &q);
        for (int i = 0; i < q; ++i) {
            scanf("%d", &x);
            if (dis[x] < 3 || dis[x] == inf || f[x]) {
                printf("?\n");
            } else {
                printf("%lld\n", dis[x]);
            }
        }
    }
    return 0;
}


// poj 1847
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 110, inf = 0x3fffffff;
int dis[maxn], vis[maxn];
struct edge {
    int to, d;
};
vector<edge> v[maxn];

void insert(int x, int y, int d) {
    v[x].push_back({y, d});
}

void spfa(int s, int e) {
    memset(vis, 0, sizeof(vis));
    fill(dis, dis + maxn, inf);
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        int len = (int)v[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now][i].to;
            if (dis[to] > dis[now] + v[now][i].d) {
                dis[to] = dis[now] + v[now][i].d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

int main() {
    int n, s, e, k, to;
    scanf("%d%d%d", &n, &s, &e);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &k);
        if (k > 0) {
            scanf("%d", &to);
            insert(i, to, 0);
        }
        for (int j = 1; j < k; ++j) {
            scanf("%d", &to);
            insert(i, to, 1);
        }
    }
    spfa(s, e);
    if (dis[e] == inf) {
        printf("-1\n");
    } else {
        printf("%d\n", dis[e]);
    }
    return 0;
}


// poj 1511
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 1e6 + 10, inf = 0x3fffffff;
int head1[maxn], head2[maxn], dis[maxn], vis[maxn], n, cnt1, cnt2;
struct Edge {
    int to, d, next;
} edge1[maxn], edge2[maxn];

void insert(int x, int y, int d) {
    edge1[cnt1] = {y, d, head1[x]};
    head1[x] = cnt1++;
    edge2[cnt2] = {x, d, head2[y]};
    head2[y] = cnt2++;
}

void spfa1() {
    memset(vis, 0, sizeof(vis));
    fill(dis, dis + n + 10, inf);
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head1[now]; i != -1; i = edge1[i].next) {
            int to = edge1[i].to;
            if (dis[to] > dis[now] + edge1[i].d) {
                dis[to] = dis[now] + edge1[i].d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

void spfa2() {
    memset(vis, 0, sizeof(vis));
    fill(dis, dis + n + 10, inf);
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head2[now]; i != -1; i = edge2[i].next) {
            int to = edge2[i].to;
            if (dis[to] > dis[now] + edge2[i].d) {
                dis[to] = dis[now] + edge2[i].d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

int main() {
    int t, m, x, y, d;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        memset(head1, -1, sizeof(head1));
        memset(head2, -1, sizeof(head2));
        cnt1 = cnt2 = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, d);
        }
        spfa1();
        long long int ans = 0;
        for (int i = 2; i <= n; ++i) {
            ans += dis[i];
        }
        spfa2();
        for (int i = 2; i <= n; ++i) {
            ans += dis[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// poj 3660 floyd
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 110;
bool win[maxn][maxn];

int main() {
    int n, m, x, y;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        win[x][y] = 1;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && j != k && i != k
                    && win[i][k] == 1 && win[k][j] == 1) {
                    win[i][j] = 1;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int a = 0, b = 0;
        for (int j = 1; j <= n; ++j) {
            if (i != j && win[j][i] == 1) {
                ++a;
            }
        }
        for (int j = 1; j <= n; ++j) {
            if (i != j && win[i][j] == 1) {
                ++b;
            }
        }
        if (a + b == n - 1) {
            ++ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}


// poj 2240
#include <cstdio>
#include <iostream>
#include <cmath>
#include <queue>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int maxn = 50;
int vis[maxn], n;
double dis[maxn];

string name[maxn];

struct edge {
    int to;
    double r;
};

vector<edge> v[maxn];

void insert(int x, int y, double r) {
    v[x].push_back({y, r});
}

int spfa() {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    dis[0] = 100;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        int len = (int)v[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now][i].to;
            if (dis[to] < dis[now] * v[now][i].r) {
                dis[to] = dis[now] * v[now][i].r;
                if (dis[0] > 100) {
                    return 1;
                }
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
    return 0;
}

int main() {
    
    int m, x = 0, y = 0, ca = 1;
    double r;
    string s;
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; ++i) {
            cin >> name[i];
            v[i].clear();
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            cin >> s;
            for (int j = 0; j < n; ++j) {
                if (s == name[j]) x = j;
            }
            scanf("%lf", &r);
            cin >> s;
            for (int j = 0; j < n; ++j) {
                if (s == name[j]) y = j;
            }
            insert(x, y, r);
        }
        if (spfa() == 1) {
            printf("Case %d: Yes\n", ca++);
        } else {
            printf("Case %d: No\n", ca++);
        }
        
    }
    return 0;
}


// poj 1502
#include <cstdio>
#include <iostream>
#include <cmath>
#include <queue>
#include <string>
using namespace std;
const int maxn = 110, inf = 0x3fffffff;
int head[maxn], dis[maxn], vis[maxn], cnt;

struct Edge {
    int to, next, d;
} edge[maxn * maxn];

void insert(int x, int y, int d) {
    edge[cnt] = {y, head[x], d};
    head[x] = cnt++;
}

void spfa(int s) {
    fill(dis, dis + maxn, inf);
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i; i = edge[i].next) {
            int to = edge[i].to;
            if (dis[to] > dis[now] + edge[i].d) {
                dis[to] = dis[now] + edge[i].d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

int main() {
    int n, x;
    string s;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            cin >> s;
            if (s[0] != 'x') {
                x = 0;
                for (int k = 0; s[k]; ++k) {
                    x = x * 10 + s[k] - '0';
                }
                insert(i, j, x);
                insert(j, i, x);
            }
        }
    }
    spfa(1);
    int Max = 0;
    for (int j = 1; j <= n; ++j) {
        Max = max(Max, dis[j]);
    }
    printf("%d\n", Max);
    return 0;
}


// poj 1860
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
const int maxn = 110;
double dis[maxn], w;
int vis[maxn], n, s;
struct edge {
    int to;
    double k, c;
} tmp;

vector<edge> v[maxn];

void insert(int x, int y, double k1, double c1, double k2, double c2) {
    tmp.to = y, tmp.k = k1, tmp.c = c1;
    v[x].push_back(tmp);
    tmp.to = x, tmp.k = k2, tmp.c = c2;
    v[y].push_back(tmp);
}

int spfa() {
    double last = dis[s] = w;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        int len = (int)v[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now][i].to;
            double next = (dis[now] - v[now][i].c) * v[now][i].k;
            if (dis[to] < next) {
                dis[to] = next;
                if (vis[to] == 0) {
                    q.push(to);
                    vis[to] = 1;
                }
                if (dis[s] > last) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    
    int m, x, y;
    double k1, c1, k2, c2;
    scanf("%d%d%d%lf", &n, &m, &s, &w);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%lf%lf%lf%lf", &x, &y, &k1, &c1, &k2, &c2);
        insert(x, y, k1, c1, k2, c2);
    }
    if (spfa() == 1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}


// poj 3259
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 510, inf = 0x3fffffff;
int dis[maxn], vis[maxn], cnt[maxn], n;

struct edge {
    int to, d;
};
vector<edge> v[maxn];

void insert(int x, int y, int d) {
    v[x].push_back({y, d});
}

int spfa() {
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    dis[1] = 1;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        int len = (int)v[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now][i].to;
            if (dis[to] > dis[now] + v[now][i].d) {
                dis[to] = dis[now] + v[now][i].d;
                ++cnt[to];
                if (!vis[to]) {
                    q.push(to);
                }
                if (cnt[to] > n) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int t, m, w, x, y, d;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &w);
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, d);
            insert(y, x, d);
        }
        for (int i = 0; i < w; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, -d);
        }
        if (spfa() == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        
    }
    return 0;
}


// poj 3268
// 实际函数名为 spfa 写成了dij...
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 1010, inf = 0x3fffffff;
int dis1[maxn], dis2[maxn], vis[maxn], s;
struct edge {
    int to, d;
};

vector<edge> v1[maxn];
vector<edge> v2[maxn];

void insert(int x, int y, int d) {
    v1[y].push_back({x, d});
    v2[x].push_back({y, d});
}


void dij1() {
    fill(dis1, dis1 + maxn, inf);
    dis1[s] = 0;
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        vis[now] = 0;
        q.pop();
        int len = (int)v1[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v1[now][i].to;
            if (dis1[to] > dis1[now] + v1[now][i].d) {
                dis1[to] = dis1[now] + v1[now][i].d;
                if (vis[to] == 0) {
                    q.push(to);
                    vis[to] = 1;
                }
            }
        }
    }
}

void dij2() {
    fill(dis2, dis2 + maxn, inf);
    dis2[s] = 0;
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        vis[now] = 0;
        q.pop();
        int len = (int)v2[now].size();
        for (int i = 0; i < len; ++i) {
            int to = v2[now][i].to;
            if (dis2[to] > dis2[now] + v2[now][i].d) {
                dis2[to] = dis2[now] + v2[now][i].d;
                if (vis[to] == 0) {
                    q.push(to);
                    vis[to] = 1;
                }
            }
        }
    }
}

int main() {
    int n, m, x, y, d;
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &d);
        insert(x, y, d);
    }
    dij1();
    dij2();
    int Max = 0;
    for (int i = 2; i <= n; ++i) {
        Max = max(Max, dis1[i] + dis2[i]);
    }
    printf("%d\n", Max);
    return 0;
}


// poj 1797
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 1010, inf = 0x3fffffff;
LL dis[maxn], ca;
bool vis[maxn];
struct node {
    int id;
    LL d;
    friend bool operator < (const node& a, const node& b) {
        return a.d < b.d;
    }
};

vector<node> v[maxn];

void insert(int x, int y, LL d) {
    v[x].push_back({y, d});
    v[y].push_back({x, d});
}

void dij() {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    dis[1] = inf;
    priority_queue<node> q;
    q.push({1, inf});
    while (!q.empty()) {
        node now = q.top();
        q.pop();
        if (vis[now.id]) {
            continue;
        }
        vis[now.id] = 1;
        int len = (int)v[now.id].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now.id][i].id;
            if (dis[to] < min(v[now.id][i].d, now.d)) {
                dis[to] = min(v[now.id][i].d, now.d);
                q.push({to, dis[to]});
            }
        }
    }
}

int main() {
    int t, n, m, x, y, d;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, d);
        }
        dij();
        printf("Scenario #%lld:\n%lld\n\n", ++ca, dis[n]);
    }
    return 0;
}


// poj 2253
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 210, inf = 0x3fffffff;
bool vis[maxn];
double dis[maxn];

struct point {
    double x, y;
} Map[maxn];

double com_dis(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct node {
    int id;
    double d;
    friend bool operator < (const node& a, const node& b) {
        return a.d > b.d;
    }
} tmp;

vector<node> v[maxn];

void insert(int i, int j) {
    double d = com_dis(Map[i], Map[j]);
    tmp.id = j, tmp.d = d;
    v[i].push_back(tmp);
    tmp.id = i;
    v[j].push_back(tmp);
}

void dij() {
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    dis[0] = 0;
    priority_queue<node> q;
    tmp.id = tmp.d = 0;
    q.push(tmp);
    while (!q.empty()) {
        node now = q.top();
        q.pop();
        if (vis[now.id]) continue;
        vis[now.id] = 1;
        int len = (int)v[now.id].size();
        for (int i = 0; i < len; ++i) {
            int to = v[now.id][i].id;
            if (dis[to] > max(dis[now.id], v[now.id][i].d)) {
                dis[to] = max(dis[now.id], v[now.id][i].d);
                tmp.id = to, tmp.d = dis[to];
                q.push(tmp);
            }
        }
    }
}

int main() {
    int n, ca = 1;
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < maxn; ++i) {
            v[i].clear();
        }
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &Map[i].x, &Map[i].y);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                insert(i, j);
            }
        }
        dij();
        printf("Scenario #%d\nFrog Distance = %0.3lf\n\n", ca++, dis[1]);
    }
    return 0;
}


// poj 2387
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 1010, inf = 0x3fffffff;
typedef long long LL;
LL dis[maxn];
bool vis[maxn];
struct edge {
    int y;
    LL dis;
};

struct node {
    int id;
    LL dis;
};

bool operator < (const node& a, const node& b) {
    return a.dis > b.dis;
}

vector<edge> v[maxn];
void insert(int x, int y, LL d) {
    v[x].push_back({y, d});
    v[y].push_back({x, d});
}

LL dij(int e) {
    memset(vis, 0, sizeof(vis));
    int s = 1;
    fill(dis, dis + e + 10, inf);
    dis[s] = 0;
    priority_queue<node> q;
    q.push({s, 0});
    while (!q.empty()) {
        node now = q.top();
        q.pop();
        int from = now.id;
        if (vis[from] == 1) {
            continue;
        } else {
            vis[from] = 1;
        }
        // printf("from %d dis %lld\n", from, now.dis);
        int len = (int)v[from].size();
        for (int i = 0; i < len; ++i) {
            int to = v[from][i].y;
            if (dis[to] > now.dis + v[from][i].dis) {
                dis[to] = now.dis + v[from][i].dis;
                q.push({to, dis[to]});
            }
        }
    }
    return dis[e];
}

int main(int argc, const char * argv[]) {
    int t, n, x, y;
    LL d;
    scanf("%d%d", &t, &n);
    for (int i = 1; i <= n; ++i) v[i].clear();
    
    for (int i = 0; i < t; ++i) {
        scanf("%d%d%lld", &x, &y, &d);
        insert(x, y, d);
    }
    printf("%lld\n", dij(n));
    return 0;
}
*/
