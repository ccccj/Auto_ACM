//
//  main.cpp
//  网络流<kuangbin>
//
//  Created by admin on 18/10/3.
//  Copyright © 2018年 Amon. All rights reserved.
//
/*
// hdu 3376
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 610, maxm = 9e5 + 10;
int Map[maxn][maxn];
int head[maxm], cnt, p[maxm], pre[maxm], vis[maxm], dis[maxm];

struct Edge {
    int to, lastf, cost, next;
} edge[maxm * 5];

void insert(int x, int y, int f, int cost) {
    edge[cnt].to = y, edge[cnt].lastf = f, edge[cnt].cost = cost, edge[cnt].next = head[x];
    head[x] = cnt++;
    edge[cnt].to = x, edge[cnt].lastf = 0, edge[cnt].cost = -cost, edge[cnt].next = head[y];
    head[y] = cnt++;
}

int spfa(int s, int e) {
    memset(dis, -1, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; ~i; i = edge[i].next) {
            Edge c = edge[i];
            if (c.lastf && dis[c.to] < dis[now] + c.cost) {
                dis[c.to] = dis[now] + c.cost;
                p[c.to] = now;
                pre[c.to] = i;
                if (vis[c.to] == 0) {
                    vis[c.to] = 1;
                    q.push(c.to);
                }
            }
        }
    }
    return dis[e] != -1;
}

int min_cost_flow(int s, int e) {
    int ans = 0;
    while (spfa(s, e)) {
        ans += dis[e];
        for (int i = e; i != s; i = p[i]) {
            edge[pre[i]].lastf -= 1;
            edge[pre[i]^1].lastf += 1;
        }
    }
    return ans;
}

int main() {
    
    int n;
    while (~scanf("%d", &n)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &Map[i][j]);
            }
        }
        int t = n * n;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if ((i == 1 && j == 1) || (i == n && j == n)) {
                    insert((i-1)*n+j-1, (i-1)*n+j-1 + t, 2, Map[i][j]);
                } else {
                    insert((i-1)*n+j-1, (i-1)*n+j-1 + t, 1, Map[i][j]);
                }
                if (i != n) {
                    insert((i-1)*n+j-1 + t, i*n+j-1, 1, 0);
                }
                if (j != n) {
                    insert((i-1)*n+j-1 + t, (i-1)*n+j, 1, 0);
                }
            }
        }
        printf("%d\n", min_cost_flow(0, 2 * t - 1) - Map[1][1] - Map[n][n]);
    }
    return 0;
}


// 4067
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const long long int maxn = 10010, inf = 0x3f3f3f3f3f3f3f3f;
typedef long long LL;
LL n, m, cnt, head[maxn], p[maxn], pre[maxn], vis[maxn], dis[maxn], sum, flow;
LL in[maxn], out[maxn];

struct Edge {
    LL to, lastf, cost, next;
} edge[1000000];

void insert(LL x, LL y, LL f, LL cost) {
    edge[cnt] = {y, f, cost, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, 0, -cost, head[y]};
    head[y] = cnt++;
}

int spfa(LL s, LL e) {
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    queue<LL> q;
    q.push(s);
    while (!q.empty()) {
        LL now = q.front();
        q.pop();
        vis[now] = 0;
        for (LL i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (dis[c.to] > dis[now] + c.cost && c.lastf) {
                dis[c.to] = dis[now] + c.cost;
                p[c.to] = now;
                pre[c.to] = i;
                if (vis[c.to] == 0) {
                    vis[c.to] = 1;
                    q.push(c.to);
                }
            }
        }
    }
    return dis[e] != inf;
}

LL min(LL a, LL b) {
    return a < b ? a : b;
}

LL min_cost_flow(LL s, LL e) {
    LL ans = 0;
    flow = 0;
    while (spfa(s, e)) {
        LL f = inf;
        for (LL i = e; i != s; i = p[i]) {
            f = min(f, edge[pre[i]].lastf);
        }
        for (LL i = e; i != s; i = p[i]) {
            edge[pre[i]].lastf -= f;
            edge[pre[i]^1].lastf += f;
        }
        ans += f * dis[e];
        flow += f;
    }
    return ans;
}


int main() {
    LL t, x, y, a, b, s, e, S, E, ca = 1;
    scanf("%lld", &t);
    while (t--) {
        sum = cnt = 0;
        scanf("%lld%lld%lld%lld", &n, &m, &s, &e);
        memset(head, -1, sizeof(head));
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        for (int i = 0; i < m; ++i) {
            scanf("%lld%lld%lld%lld", &x, &y, &a, &b);
            if (a < b) {
                // 留
                sum += a;
                ++in[y], ++out[x];
                //printf("%d %d 1 %d\n", y, x, b-a);
                insert(y, x, 1, b - a);
            } else {
                sum += b;
                //printf("%d %d 1 %d\n", x, y, a-b);
                insert(x, y, 1, a - b);
            }
        }
        //printf("%d %d 1 0\n", e, s);
        ++out[e], ++in[s];
        S = 0, E = n + 1;
        int tmp = 0;
        for (int i = 1; i <= n; ++i) {
            if (in[i] > out[i]) {
                //printf("%d %d %d 0\n", S, i, in[i] - out[i]);
                insert(S, i, in[i] - out[i], 0);
                tmp += in[i] - out[i];
            } else if (in[i] < out[i]) {
                //printf("%d %d %d 0\n", i, E, out[i] - in[i]);
                insert(i, E, out[i] - in[i], 0);
            }
        }
        LL ans = min_cost_flow(S, E);
        if (flow < tmp) {
            printf("Case %lld: impossible\n", ca++);
        } else {
            printf("Case %lld: %lld\n", ca++, ans + sum);
        }
    }
    return 0;
}


// hdu 3667
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 110, inf = 0x3fffffff;
int head[maxn], cnt, p[maxn], pre[maxn], vis[maxn], dis[maxn], t;

struct Edge {
    int to, lastf, cost, next;
} edge[10000000];

void insert(int x, int y, int f, int cost) {
    edge[cnt].to = y, edge[cnt].lastf = f, edge[cnt].cost = cost, edge[cnt].next = head[x];
    head[x] = cnt++;
    edge[cnt].to = x, edge[cnt].lastf = 0, edge[cnt].cost = -cost, edge[cnt].next = head[y];
    head[y] = cnt++;
}

int spfa(int s, int e) {
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; ~i; i = edge[i].next) {
            Edge c = edge[i];
            if (c.lastf && dis[c.to] > dis[now] + c.cost) {
                dis[c.to] = dis[now] + c.cost;
                p[c.to] = now;
                pre[c.to] = i;
                if (vis[c.to] == 0) {
                    vis[c.to] = 1;
                    q.push(c.to);
                }
            }
        }
    }
    return dis[e] != inf;
}

int min_cost_flow(int s, int e) {
    int ans = 0;
    while (spfa(s, e)) {
        int f = inf;
        for (int i = e; i != s; i = p[i]) {
            f = min(f, edge[pre[i]].lastf);
        }
        ans += dis[e] * f;
        for (int i = e; i != s; i = p[i]) {
            edge[pre[i]].lastf -= f;
            edge[pre[i]^1].lastf += f;
        }
    }
    if (edge[t].lastf) {
        return -1;
    }
    return ans;
}

int main() {
    
    int n, m, k, x, y, a, b;
    while (~scanf("%d%d%d", &n, &m, &k)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        int s = 0, e = n + 1;
        insert(s, 1, k, 0);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d%d", &x, &y, &a, &b);
            for (int i = 1; i <= b; ++i) {
                int tmp = (i-1) * (i-1);
                insert(x, y, 1, a * (i * i - tmp));
            }
        }
        t = cnt;
        insert(n, e, k, 0);
        printf("%d\n", min_cost_flow(s, e));
    }
    return 0;
}


// hdu 2686
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 50, maxm = 2010, inf = 0x3fffffff;
int arr[maxn][maxn], Map[maxn][maxn];
int head[maxm], cnt, p[maxm], pre[maxm], vis[maxm], dis[maxm];

struct Edge {
    int to, lastf, cost, next;
} edge[400000];

void insert(int x, int y, int f, int cost) {
    edge[cnt].to = y, edge[cnt].lastf = f, edge[cnt].cost = cost, edge[cnt].next = head[x];
    head[x] = cnt++;
    edge[cnt].to = x, edge[cnt].lastf = 0, edge[cnt].cost = -cost, edge[cnt].next = head[y];
    head[y] = cnt++;
}

int spfa(int s, int e) {
    memset(dis, -1, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; ~i; i = edge[i].next) {
            Edge c = edge[i];
            if (c.lastf && dis[c.to] < dis[now] + c.cost) {
                dis[c.to] = dis[now] + c.cost;
                p[c.to] = now;
                pre[c.to] = i;
                if (vis[c.to] == 0) {
                    vis[c.to] = 1;
                    q.push(c.to);
                }
            }
        }
    }
    return dis[e] != -1;
}

int min_cost_flow(int s, int e) {
    int ans = 0;
    while (spfa(s, e)) {
        int f = inf;
        //printf("===");
        for (int i = e; i != s; i = p[i]) {
            f = min(f, edge[pre[i]].lastf);
        }
        ans += f * dis[e];
        for (int i = e; i != s; i = p[i]) {
            edge[pre[i]].lastf -= f;
            edge[pre[i]^1].lastf += f;
        }
    }
    return ans;
}

int main() {
    
    int n;
    while (~scanf("%d", &n)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &Map[i][j]);
            }
        }
        int num = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if ((i == 1 && j == 1) || (i == n && j == n)) {
                    //printf("%d %d 2 %d\n", num, num + n * n, Map[i][j]);
                    insert(num, num + n * n, 2, Map[i][j]);
                } else {
                    //printf("%d %d 1 %d\n", num, num + n * n, Map[i][j]);
                    insert(num, num + n * n, 1, Map[i][j]);
                }
                arr[i][j] = num++;
            }
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= n; ++j) {
                //printf("%d %d 1 0\n", arr[i][j] + n * n, arr[i+1][j]);
                insert(arr[i][j] + n * n, arr[i+1][j], 1, 0);
            }
        }
        for (int j = 1; j < n; ++j) {
            for (int i = 1; i <= n; ++i) {
                //printf("%d %d 1 0\n", arr[i][j] + n * n, arr[i][j+1]);
                insert(arr[i][j] + n * n, arr[i][j+1], 1, 0);
            }
        }
        printf("%d\n", min_cost_flow(0, 2 * n * n - 1) - Map[1][1] - Map[n][n]);
    }
    
    return 0;
}


// hdu 3338
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 110, maxm = 4e5, inf = 0x3fffffff;
char str[maxn][maxn][10];
int arr1[maxn][maxn], arr2[maxn][maxn], tmp[maxn][maxn];
int num1[maxn][maxn], num2[maxn][maxn], number1[maxn][maxn], number2[maxn][maxn], n, m, cnt;
int head[maxm], depth[maxm];

struct Edge {
    int to, lastf, next;
} edge[maxm * maxn];

void insert(int x, int y, int f) {
    edge[cnt].to = y, edge[cnt].lastf = f, edge[cnt].next = head[x];
    head[x] = cnt++;
    edge[cnt].to = x, edge[cnt].lastf = 0, edge[cnt].next = head[y];
    head[y] = cnt++;
}

int read() {
    int ans, sum = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%s", str[i][j]);
            if (str[i][j][0] == '.') {
                arr1[i][j] = arr2[i][j] = -2;
            } else {
                if (str[i][j][0] == 'X') {
                    arr1[i][j] = -1;
                } else {
                    ans = 0;
                    for (int k = 0; k < 3; ++k) {
                        ans = ans * 10 + str[i][j][k] - '0';
                    }
                    arr1[i][j] = ans;
                    sum += ans;
                }
                if (str[i][j][4] == 'X') {
                    arr2[i][j] = -1;
                } else {
                    ans = 0;
                    for (int k = 4; k < 7; ++k) {
                        ans = ans * 10 + str[i][j][k] - '0';
                    }
                    arr2[i][j] = ans;
                    sum += ans;
                }
            }
        }
    }
    return sum;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        int sum = read();
        insert(0, 1, sum / 2);
        int num = 2;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (arr1[i][j] == -2) {
                    number1[i][j] = num++;
                    number2[i][j] = num++;
                    continue;
                }
                if (arr1[i][j] != -1) {
                    num1[i][j] = num++;
                }
                if (arr2[i][j] != -1) {
                    num2[i][j] = num++;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (str[i][j][0] == '.') {
                    tmp[i][j] = cnt;
                    insert(number1[i][j], number2[i][j], 8);
                }
                if (arr1[i][j] != -1 && arr1[i][j] != -2) {
                    //int x = 1, y = num1[i][j], f = arr1[i][j];
                    //printf("%d %d %d\n", x, y, f);
                    int k = i + 1, all = 0;
                    while (k <= n && arr1[k][j] == -2) {
                        //int x = num1[i][j], y = number[k][j];
                        //printf("%d %d inf\n", x, y);
                        insert(num1[i][j], number1[k][j], inf);
                        ++k, ++all;
                    }
                    insert(1, num1[i][j], arr1[i][j] - all);
                }
                if (arr2[i][j] != -1 && arr2[i][j] != -2) {
                    //int x = num2[i][j], y = num, f = arr2[i][j];
                    //printf("%d %d %d\n", x, y, f);
                    int k = j + 1, all = 0;
                    while (k <= m && arr2[i][k] == -2) {
                        //int x = number2[i][k], y = num2[i][j];
                        //printf("%d %d inf\n", x, y);
                        insert(number2[i][k], num2[i][j], inf);
                        ++k, ++all;
                    }
                    insert(num2[i][j], num, arr2[i][j] - all);
                }
            }
        }
        dinic(0, num);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < m; ++j) {
                if (str[i][j][0] == '.') {
                    printf("%d ", 9 - edge[tmp[i][j]].lastf);
                } else {
                    printf("_ ");
                }
            }
            if (str[i][m][0] == '.') {
                printf("%d\n", 9 - edge[tmp[i][m]].lastf);
            } else {
                printf("_\n");
            }
            
        }
    }
    return 0;
}


// hdu 3395
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 210, inf = 0x3fffffff;
int arr[maxn], G[maxn][maxn], n;
int visl[maxn], visr[maxn], exl[maxn], exr[maxn], match[maxn], slack[maxn];

int dfs(int x) {
    visl[x] = 1;
    for (int i = 0; i < n; ++i) {
        if (visr[i] == 1) continue;
        int delta = exl[x] + exr[i] - G[x][i];
        if (delta == 0) {
            visr[i] = 1;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = x;
                return 1;
            }
        } else {
            slack[i] = min(slack[i], delta);
        }
    }
    return 0;
}

int KM() {
    memset(match, -1, sizeof(match));
    memset(exr, 0, sizeof(exr));
    for (int i = 0; i < n; ++i) {
        exl[i] = G[i][0];
        for (int j = 0; j < n; ++j) {
            exl[i] = max(exl[i], G[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        fill(slack, slack + n, inf);
        while (1) {
            memset(visl, 0, sizeof(visl));
            memset(visr, 0, sizeof(visr));
            if (dfs(i)) break;
            int d = inf;
            for (int i = 0; i < n; ++i) {
                if (!visr[i]) d = min(d, slack[i]);
            }
            for (int i = 0; i < n; ++i) {
                if (visl[i]) {
                    exl[i] -= d;
                }
                if (visr[i]) {
                    exr[i] += d;
                } else {
                    slack[i] -= d;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += G[match[i]][i];
    }
    return ans;
}

int main() {
    char str[maxn];
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            for (int j = 0; j < n; ++j) {
                if (str[j] == '1') {
                    G[i][j] = arr[i] ^ arr[j];
                } else {
                    G[i][j] = 0;
                }
            }
        }
        printf("%d\n", KM());
    }
    return 0;
}


// hdu 3315
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 310, inf = 0x3fffffff;
int G[maxn][maxn], arr[maxn], n, cnt;
int hp1[maxn], hp2[maxn], stack1[maxn], stack2[maxn];
int ex_girl[maxn], ex_boy[maxn], match[maxn], slack[maxn];
bool vis_girl[maxn], vis_boy[maxn];

bool canwin(int i, int j) {
    int t1 = hp2[j]/stack1[i], t2 = hp1[i]/stack2[j];
    if (hp1[i] - t2 * stack2[j] > 0) ++t2;
    if (hp2[j] - t1 * stack1[i] > 0) ++t1;
    
    if (t1 <= t2) {
        return 1;
    }
    return 0;
}

int dfs(int x) {
    vis_girl[x] = 1;
    for (int i = 1; i <= n; ++i) {
 
        if (vis_boy[i] == 1) continue;
        int delta = ex_girl[x] + ex_boy[i] - G[x][i];
        if (delta == 0) {
            vis_boy[i] = 1;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = x;
                return 1;
            }
        } else {
            slack[i] = min(delta, slack[i]);
        }
    }
    return 0;
}

int KM() {
    memset(ex_boy, 0, sizeof(ex_boy));
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= n; ++i) {
        ex_girl[i] = G[i][1];
        for (int j = 2; j <= n; ++j) {
            ex_girl[i] = max(ex_girl[i], G[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        fill(slack + 1, slack + n + 1, inf);
        while (1) {
            memset(vis_boy, 0, sizeof(vis_boy));
            memset(vis_girl, 0, sizeof(vis_girl));
            if (dfs(i)) break;
            int d = inf;
            for (int i = 1; i <= n; ++i) {
                if (!vis_boy[i]) d = min(d, slack[i]);
            }
            for (int i = 1; i <= n; ++i) {
                if (vis_girl[i]) {
                    ex_girl[i] -= d;
                }
                if (vis_boy[i]) {
                    ex_boy[i] += d;
                } else {
                    slack[i] -= d;
                }
            }
            
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += G[match[i]][i];
        //printf("i %d %d\n", i, match[i]);
    }
    return ans;
}

int main() {
    while (~scanf("%d", &n) && n) {
        for (int i = 1; i <= n; ++i) {
            fill(G[i] + 1, G[i] + 1 + n, -inf);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        for (int i = 1; i <= n; ++i) scanf("%d", &hp1[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &hp2[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &stack1[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &stack2[i]);
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (canwin(i, j)) {
                    G[i][j] = arr[i] * 1000;
                    //printf("%d %d\n", i, j);
                } else {
                    G[i][j] = -arr[i] * 1000;
                }
                if (i == j) {
                    ++G[i][j];
                }
            }
        }
        int ans = KM();
        if (ans < 0) {
            printf("Oh, I lose my dear seaco!\n");
        } else {
            printf("%d ", ans / 1000);
            int all = 0;
            for (int i = 1; i <= n; ++i) {
                if (match[i] == i) {
                    ++all;
                }
            }
            printf("%.3lf%%\n", (double)all / n * 100);
        }
    }
    return 0;
}


// hdu 3315
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010, inf = 0x3fffffff;
int n, m, G[maxn][maxn];
int ex_girl[maxn], ex_boy[maxn];
int match[maxn], slack[maxn];
bool vis_girl[maxn], vis_boy[maxn];

int dfs(int x) {
    vis_girl[x] = 1;
    for (int i = 1; i <= n; ++i) {
        if (vis_boy[i] == 1) continue;
        int delta = ex_girl[x] + ex_boy[i] - G[x][i];
        if (delta == 0) {
            vis_boy[i] = 1;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = x;
                return 1;
            }
        } else {
            slack[i] = min(slack[i], delta);
        }
    }
    return 0;
}

int KM() {
    memset(ex_boy, 0, sizeof(ex_boy));
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= n; ++i) {
        ex_girl[i] = G[i][1];
        for (int j = 2; j <= n; ++j) {
            ex_girl[i] = max(ex_girl[i], G[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        fill(slack + 1, slack + 1 + n, inf);
        while (1) {
            memset(vis_girl, 0, sizeof(vis_girl));
            memset(vis_boy, 0, sizeof(vis_boy));
            if (dfs(i)) break;
            int d = inf;
            for (int j = 1; j <= n; ++j) {
                if (!vis_boy[j]) {
                    d = min(d, slack[j]);
                }
            }
            for (int j = 1; j <= n; ++j) {
                if (vis_girl[j]) {
                    ex_girl[j] -= d;
                }
                if (vis_boy[j]) {
                    ex_boy[j] += d;
                } else {
                    slack[j] -= d;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (G[match[i]][i] == -inf) {
            return 1;
        }
        ans += G[match[i]][i];
    }
    return ans;
}

int main() {
    int t, x, y, d, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            fill(G[i] + 1, G[i] + 1 + n, -inf);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            G[y][x] = G[x][y] = max(G[x][y], -d);
        }
        int ans = KM();
        if (ans == 1) {
            printf("Case %d: NO\n", ca++);
        } else {
            printf("Case %d: %d\n", ca++, -ans);
        }
    }
    return 0;
}


// hdu 3488
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 305;
const int INF = 0x3f3f3f3f;
int love[MAXN][MAXN];   // 记录每个妹子和每个男生的好感度
int ex_girl[MAXN];      // 每个妹子的期望值
int ex_boy[MAXN];       // 每个男生的期望值
bool vis_girl[MAXN];    // 记录每一轮匹配匹配过的女生
bool vis_boy[MAXN];     // 记录每一轮匹配匹配过的男生
int match[MAXN];        // 记录每个男生匹配到的妹子 如果没有则为-1
int slack[MAXN];        // 记录每个汉子如果能被妹子倾心最少还需要多少期望值
int N;

bool dfs(int girl) {
    vis_girl[girl] = true;
    for (int boy = 0; boy < N; ++boy) {
        if (vis_boy[boy]) continue; // 每一轮匹配 每个男生只尝试一次
        int gap = ex_girl[girl] + ex_boy[boy] - love[girl][boy];
        if (gap == 0) {  // 如果符合要求
            vis_boy[boy] = true;
            if (match[boy] == -1 || dfs( match[boy] )) {    // 找到一个没有匹配的男生 或者该男生的妹子可以找到其他人
                match[boy] = girl;
                return true;
            }
        } else {
            slack[boy] = min(slack[boy], gap);  // slack 可以理解为该男生要得到女生的倾心 还需多少期望值 取最小值 备胎的样子【捂脸
        }
    }
    return false;
}

int KM() {
    memset(match, -1, sizeof match);    // 初始每个男生都没有匹配的女生
    memset(ex_boy, 0, sizeof ex_boy);   // 初始每个男生的期望值为0
    // 每个女生的初始期望值是与她相连的男生最大的好感度
    for (int i = 0; i < N; ++i) {
        ex_girl[i] = love[i][0];
        for (int j = 1; j < N; ++j) {
            ex_girl[i] = max(ex_girl[i], love[i][j]);
        }
    }
    // 尝试为每一个女生解决归宿问题
    for (int i = 0; i < N; ++i) {
        fill(slack, slack + N, INF);    // 因为要取最小值 初始化为无穷大
        while (1) {
            // 为每个女生解决归宿问题的方法是 ：如果找不到就降低期望值，直到找到为止
            // 记录每轮匹配中男生女生是否被尝试匹配过
            memset(vis_girl, false, sizeof vis_girl);
            memset(vis_boy, false, sizeof vis_boy);
            
            if (dfs(i)) break;  // 找到归宿 退出
            
            // 如果不能找到 就降低期望值
            // 最小可降低的期望值
            int d = INF;
            for (int j = 0; j < N; ++j)
                if (!vis_boy[j]) d = min(d, slack[j]);
            
            for (int j = 0; j < N; ++j) {
                // 所有访问过的女生降低期望值
                if (vis_girl[j]) ex_girl[j] -= d;
                
                // 所有访问过的男生增加期望值
                if (vis_boy[j]) ex_boy[j] += d;
                // 没有访问过的boy 因为girl们的期望值降低，距离得到女生倾心又进了一步！
                else slack[j] -= d;
            }
        }
    }
    
    // 匹配完成 求出所有配对的好感度的和
    int res = 0;
    for (int i = 0; i < N; ++i) {
        if (love[match[i]][i] == -INF) {
            return 1;
        } else {
            res += love[ match[i] ][i];
        }
    }
    return res;
}

int main() {
    int t, m, x, y, d;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &N, &m);
        for (int i = 0; i < N; ++i) {
            fill(love[i], love[i] + N, -INF);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            love[x-1][y-1] = max(-d, love[x-1][y-1]);
        }
        printf("%d\n", -KM());
    }
    return 0;
}


// hdu 1853
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 1010, inf = 0x3fffffff;
int n, m, used[maxn<<1], cnt, head[maxn], p[maxn], pre[maxn], vis[maxn], dis[maxn];

struct Edge {
    int to, lastf, cost, next;
} edge[maxn * maxn];

void insert(int x, int y, int f, int cost) {
    edge[cnt] = {y, f, cost, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, 0, -cost, head[y]};
    head[y] = cnt++;
}

int spfa(int s, int e) {
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; ~i; i = edge[i].next) {
            Edge c = edge[i];
            if (dis[c.to] > dis[now] + c.cost && c.lastf) {
                dis[c.to] = dis[now] + c.cost;
                p[c.to] = now;
                pre[c.to] = i;
                if (vis[c.to] == 0) {
                    vis[c.to] = 1;
                    q.push(c.to);
                }
            }
        }
    }
    return dis[e] != inf;
}

int min_cost_flow(int s, int e) {
    int ans = 0;
    while (spfa(s, e)) {
        for (int i = e; i != s; i = p[i]) {
            used[i] = 1;
            edge[pre[i]].lastf -= 1;
            edge[pre[i]^1].lastf += 1;
        }
        ans += dis[e];
    }
    for (int i = 1 + n; i <= 2 * n; ++i) {
        if (used[i] == 0) {
            ans = -1;
            break;
        }
    }
    return ans;
}

int main() {
    int x, y, d, s = 0, e;
    while (~scanf("%d%d", &n, &m)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        memset(used, 0, sizeof(used));
        e = 2 * n + 1;
        for (int i = 1; i <= n; ++i) {
            insert(s, i, 1, 0);
            insert(i + n, e, 1, 0);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y + n, 1, d);
        }
        printf("%d\n", min_cost_flow(s, e));
    }
    return 0;
}


// // hdu 3081
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 110;
int arr[maxn], fri[maxn][maxn], used[maxn], girl[maxn];

int find(int x, int n) {
    for (int i = 1; i <= n; ++i) {
        if (fri[x][i] == 1 && used[i] == 0) {
            used[i] = 1;
            if (girl[i] == -1 || find(girl[i], n)) {
                girl[i] = x;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int t, n, m, f, x, y;
    scanf("%d", &t);
    while (t--) {
        memset(fri, 0, sizeof(fri));
        memset(girl, -1, sizeof(girl));
        scanf("%d%d%d", &n, &m, &f);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            fri[x][y] = 1;
        }
        for (int i = 0; i < f; ++i) {
            scanf("%d%d", &x, &y);
            for (int i = 1; i <= n; ++i) {
                if (fri[x][i] == 1) {
                    fri[y][i] = 1;
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (fri[y][i] == 1) {
                    fri[x][i] = 1;
                }
            }
        }
        int ans = 0, tmp = 0;
        while (1) {
            tmp = 0;
            for (int i = 1; i <= n; ++i) {
                memset(used, 0, sizeof(used));
                if (find(i, n)) {
                    ++tmp;
                } else {
                    break;
                }
            }
            if (tmp == n) {
                ++ans;
                for (int i = 1; i <= n; ++i) {
                    fri[girl[i]][i] = 0;
                }
                memset(girl, -1, sizeof(girl));
            } else {
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}


// hdu 2732
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
const int maxn = 200010, inf = 0x3fffffff;
int head[maxn], depth[maxn], cnt, arr[100][100];
char Map1[100][100], Map2[100][100];
struct Edge {
    int to, lastf, next;
} tmp, edge[maxn << 3];

void insert(int x, int y, int f) {
    tmp.to = y, tmp.lastf = f, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int d, n, m, t, s = 0, e, sum, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &d);
        cnt = 0;
        memset(head, -1, sizeof(head));
        memset(arr, 0, sizeof(arr));
        for (int i = 0; i < n; ++i) scanf("%s", Map1[i]);
        for (int i = 0; i < n; ++i) scanf("%s", Map2[i]);
        m = (int)strlen(Map1[0]);
        int num = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                //if (Map1[i][j] > '0') {
                arr[i][j] = ++num;
                //}
            }
        }
        e = 2 * num + 1, sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (Map1[i][j] > '0') {
                    //int x = arr[i][j], y = arr[i][j] + num, f = Map1[i][j] - '0';
                    //printf("%d %d %d\n", x, y, f);
                    insert(arr[i][j], arr[i][j] + num, Map1[i][j] - '0');
                    if (i <= d-1 || j <= d-1 || j >= m-d || i >= n-d) {
                        //x = arr[i][j] + num, y = e;
                        //printf("%d %d inf\n", x, y);
                        insert(arr[i][j] + num, e, inf);
                    } else {
                        for (int a = 0; a < n; ++a) {
                            for (int b = 0; b < m; ++b) {
                                if (sqrt((a - i) * (a - i) * 1.0 + (b - j) * (b - j) * 1.0) > d) {
                                    continue;
                                }
                                //                                if (a < 0 || a >= n || b < 0 || b >= m) continue;
                                //                                if (Map1[a][b] > '0') {
                                //x = arr[i][j] + num, y = arr[a][b];
                                //printf("%d %d inf\n", x, y);
                                insert(arr[i][j] + num, arr[a][b], inf);
                                //                                }
                            }
                        }
                    }
                }
                if (Map2[i][j] == 'L') {
                    ++sum;
                    //int x = s, y = arr[i][j], f = 1;
                    //printf("%d %d %d\n", x, y, f);
                    insert(s, arr[i][j], 1);
                }
            }
        }
        int ans = sum - dinic(s, e);
        printf("Case #%d:", ca++);
        if (ans == 0) {
            printf(" no lizard was left behind.\n");
        } else if (ans == 1) {
            printf(" 1 lizard was left behind.\n");
        } else {
            printf(" %d lizards were left behind.\n", ans);
        }
        
    }
    return 0;
}


// hdu 4289
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 200010, inf = 0x3fffffff;
int arr[maxn], head[maxn], depth[maxn], cnt;
struct Edge {
    int to, lastf, next;
} tmp, edge[maxn << 1];

inline void insert1(int x, int y, int f) {
    tmp.to = y, tmp.lastf = f, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = f, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}


inline void insert(int x, int y, int f) {
    tmp.to = y, tmp.lastf = f, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}

inline int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

inline int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

inline int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, m, s, e, x, y;
    while (~scanf("%d%d%d%d", &n, &m, &s, &e)) {
        e += n;
        cnt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
            insert1(i, i + n, arr[i]);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            insert(x + n, y, inf);
            insert(y + n, x, inf);
        }
        printf("%d\n", dinic(s, e));
    }
    return 0;
}


// poj 1459
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 20010, inf = 0x3fffffff;
int head[maxn], depth[maxn], cnt;
struct Edge {
    int to, lastf, next;
} tmp, edge[maxn << 1];

inline void insert(int x, int y, int f) {
    tmp.to = y, tmp.lastf = f, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}

inline int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

inline int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

inline int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int read() {
    int ans = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        ans = ans * 10 + ch - '0';
        ch = getchar();
    }
    return ans;
    
}

int main() {
    int n, a, b, m, s, e, x, y, d;
    while (~scanf("%d%d%d%d", &n, &a, &b, &m)) {
        cnt = 0, s = n, e = s + 1;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < m; ++i) {
            x = read(); y = read(); d = read();
            insert(x, y, d);
            //printf("%d %d %d\n", x + n, y, d);
        }
        for (int i = 0; i < a; ++i) {
            x = read(); d = read();
            //printf("%d %d %d\n", x, x + n, d);
            insert(s, x, d);
            //printf("%d %d %d\n", s, x, inf);
        }
        for (int i = 0; i < b; ++i) {
            x = read(); d = read();
            insert(x, e, d);
            //printf("%d %d %d\n", n + x, e, inf);
            //printf("%d %d %d\n", x, x + n, d);
        }
        printf("%d\n", dinic(s, e));
    }
    return 0;
}


// hdu 3416
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;
const int maxn = 1e5 + 10, inf = 0x3fffffff;
int head1[maxn], head2[maxn], dis1[maxn], dis2[maxn], cnt1, cnt2;
int u[maxn], v[maxn], d[maxn], vis[maxn], depth[maxn];

struct Edge {
    int to, lastf, cost, next;
} tmp, edge1[maxn << 2], edge2[maxn << 2];

void insert(Edge edge[], int head[], int x, int y, int f, int cost, int& cnt) {
    tmp.to = y, tmp.lastf = f, tmp.cost = cost, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.cost = -cost, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}

int spfa(int s, int e, int dis[], Edge edge[], int head[]) {
    memset(vis, 0, sizeof(vis));
    fill(dis, dis + maxn, inf);
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (dis[c.to] > dis[now] + c.cost && c.lastf > 0) {
                dis[c.to] = dis[now] + c.cost;
                if (vis[c.to] == 0) {
                    vis[c.to] = 1;
                    q.push(c.to);
                }
            }
        }
    }
    return dis[e] != inf;
}

inline int bfs(int s, int e, int head[], Edge edge[]) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

inline int dfs(int now, int e, int f, int head[], Edge edge[]) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf), head, edge);
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

inline int dinic(int s, int e, int head[], Edge edge[]) {
    int ans = 0, d;
    while (bfs(s, e, head, edge)) {
        while ((d = dfs(s, e, inf, head, edge)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        cnt1 = 0;
        cnt2 = 0;
        memset(head1, -1, sizeof(head1));
        memset(head2, -1, sizeof(head2));
        
        int n, m, s, e;
        scanf("%d%d", &n, &m);
        
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &u[i], &v[i], &d[i]);
            insert(edge1, head1, u[i], v[i], 1, d[i], cnt1);
            insert(edge2, head2, v[i], u[i], 1, d[i], cnt2);
        }
        scanf("%d%d", &s, &e);
        int mind;
        if (spfa(s, e, dis1, edge1, head1) && spfa(e, s, dis2, edge2, head2)) {
            cnt1 = 0;
            memset(head1, -1, sizeof(head1));
            mind = dis1[e];
            for (int i = 1; i <= m; ++i) {
                if (dis1[u[i]] + dis2[v[i]] == mind - d[i]) {
                    insert(edge1, head1, u[i], v[i], 1, d[i], cnt1);
                }
            }
            printf("%d\n", dinic(s, e, head1, edge1));
        } else {
            printf("0\n");
        }
    }
    return 0;
}


// hdu 4292
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 2e6, inf = 0x3fffffff;
int head[maxn], depth[maxn], cnt;
struct Edge {
    int to, lastf, next;
} tmp, edge[maxn << 1];

inline void insert(int x, int y, int f) {
    tmp.to = y, tmp.lastf = f, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}

inline int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

inline int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

inline int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, f, d, x;
    char str[1000];
    while (~scanf("%d%d%d", &n, &f, &d)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        int s = 0, e = f + 2 * n + d + 1;
        for (int i = 1; i <= f; ++i) {
            scanf("%d", &x);
            insert(s, i, x);
        }
        for (int i = 1; i <= d; ++i) {
            scanf("%d", &x);
            insert(f + 2 * n + i, e, x);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%s", str+1);
            for (int j = 1; j <= f; ++j) {
                if (str[j] == 'Y') {
                    insert(j, f + i, 1);
                }
            }
            insert(f + i, f + i + n, 1);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%s", str+1);
            for (int j = 1; j <= d; ++j) {
                if (str[j] == 'Y') {
                    insert(f + n + i, f + 2 * n + j, 1);
                }
            }
        }
        printf("%d\n", dinic(s, e));
    }
    return 0;
}


// poj 3436
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1e6, inf = 0x3fffffff;
int head[maxn], depth[maxn], cnt;
int in[55][15], out[55][15], m[55];

struct Edge {
    int to, lastf, next;
} edge[maxn], tmp;

struct node {
    int x, y, k;
    friend bool operator < (const node& a, const node& b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }
    friend bool operator == (const node& a, const node& b) {
        return (a.x == b.x && a.y == b.y)
        || (a.y == b.x && a.x == b.y);
    }
};

void insert(int x, int y, int f) {
    tmp.to = y, tmp.lastf = f, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}


int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int k, n, s = 0, e;
    while (~scanf("%d%d", &k, &n)) {
        memset(head, -1, sizeof(head));
        cnt = 0, e = 2 * n + 1;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &m[i]);
            for (int j = 1; j <= k; ++j) scanf("%d", &in[i][j]);
            for (int j = 1; j <= k; ++j) scanf("%d", &out[i][j]);
        }
        for (int i = 1; i <= n; ++i) {
            int t1 = 0, t2 = 0;
            for (int j = 1; j <= k; ++j) {
                if (in[i][j] == 0 || in[i][j] == 2) ++t1;
            }
            if (t1 == k) {
                //int x = s, y = i, f = m[i];
                insert(s, i, inf);
            }
            for (int j = 1; j <= n; ++j) {
                int flag = 1;
                for (int z = 1; z <= k; ++z) {
                    if (in[j][z] == 0 && out[i][z] == 1) {
                        flag = 0;
                        break;
                    }
                    if (in[j][z] == 1 && out[i][z] == 0) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    //int x = n + i, y = j, f = m[i];
                    insert(n + i, j, inf);
                }
            }
            for (int j = 1; j <= k; ++j) {
                if (out[i][j] == 1) ++t2;
            }
            if (t2 == k) {
                //int x = i + n, y = e, f = m[i];
                insert(i + n, e, inf);
            }
        }
        for (int i = 1; i <= n; ++i) {
            insert(i, i + n, m[i]);
        }
        printf("%d ", dinic(s, e));
        
        node v[255];
        int cnt = 0;
        for (int now = 1 + n; now <= 2 * n; ++now) {
            for (int i = head[now]; i != -1; i = edge[i].next) {
                Edge c = edge[i];
                if (i % 2 == 0 && c.lastf < inf && c.to != e) {
                    v[cnt++] = {now - n, c.to, inf - c.lastf};
                }
            }
        }
        int len = cnt;
        //int len = (int)(unique(v, v + cnt) - v);
        printf("%d\n", len);
        for (int i = 0; i < len; ++i) {
            printf("%d %d %d\n", v[i].x, v[i].y, v[i].k);
        }
    }
    return 0;
}


// hdu 3605
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 2e6, inf = 0x3fffffff;
int head[maxn], depth[maxn], dp[2000], cnt;

struct Edge {
    int to, lastf, next;
} tmp, edge[maxn << 1];

void insert(int x, int y, int f) {
    tmp.to = y, tmp.lastf = f, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) {
                    break;
                }
            }
        }
    }
    if (delta == 0) {
        depth[now] = -1;
    }
    return delta;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        memset(dp, 0, sizeof(dp));
        int x;
        for (int i = 1; i <= n; ++i) {
            int t = 0;
            for (int j = 0; j < m; ++j) {
                scanf("%d", &x);
                if (x == 1) {
                    t += 1 << j;
                }
            }
            ++dp[t];
        }
        int s = 0, num = 1, sum = 1;
        for (int i = 1; i < 1025; ++i) {
            if (dp[i]) {
                ++sum;
            }
        }
        for (int i = 1; i < 1025; ++i) {
            if (dp[i]) {
                insert(s, num, dp[i]);
                for (int j = 0; j < m; ++j) {
                    if ((i >> j) & 1) {
                        insert(num, sum + j, dp[i]);
                    }
                }
                ++num;
            }
        }
        int e = sum + m + 1;
        for (int i = 0; i < m; ++i) {
            scanf("%d", &x);
            insert(sum + i, e, x);
        }
        if (dinic(s, e) < n) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}


// hdu 4280
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 100010, inf = 0x3fffffff;
int head[maxn], depth[maxn], cnt;
struct Edge {
    int to, lastf, next;
} edge[maxn << 1];

int Scan() {
    int res = 0, ch, flag = 0;
    if ((ch = getchar()) == '-')
        flag = 1;
    else if (ch >= '0' && ch <= '9')
        res = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9')
        res = res * 10 + ch - '0';
    return flag ? -res : res;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == e) {
            return 1;
        }
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf > 0) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    int delta = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf > 0) {
            int d = dfs(c.to, e, min(f - delta, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                delta += d;
                if (f - delta == 0) break;
            }
        }
    }
    if (delta == 0) depth[now] = -1;
    return delta;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    int t, n, m, x, y, d, Max, Min, maxi, mini;
    t = Scan();
    while (t--) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        n = Scan();
        m = Scan();
        Max = Min = Scan();
        y = Scan();
        maxi = 1, mini = 1;
        for (int i = 2; i <= n; ++i) {
            x = Scan();
            y = Scan();
            if (x > Max) Max = x, maxi = i;
            if (x < Min) Min = x, mini = i;
        }
        int s = mini, e = maxi;
        for (int i = 0; i < m; ++i) {
            x = Scan();
            y = Scan();
            d = Scan();
            edge[cnt] = {y, d, head[x]};
            head[x] = cnt++;
            edge[cnt] = {x, d, head[y]};
            head[y] = cnt++;
        }
        printf("%d\n", dinic(s, e));
    }
    return 0;
}


// poj 2516
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
using namespace std;
const int maxn = 1e3 + 10, inf = 0x3fffffff;
int head[maxn], dis[maxn], vis[maxn], p[maxn], pre[maxn], n, m, k, cnt;
struct Edge {
    int to, lastf, cost, next;
} tmp, edge[maxn * maxn];

int arr1[60][60], arr2[60][60], arr3[60][60][60];

void insert(int x, int y, int f, int cost) {
    tmp.to = y, tmp.lastf = f, tmp.cost = cost, tmp.next = head[x];
    edge[cnt] = tmp;
    head[x] = cnt++;
    tmp.to = x, tmp.lastf = 0, tmp.cost = -cost, tmp.next = head[y];
    edge[cnt] = tmp;
    head[y] = cnt++;
}

int spfa(int s, int e) {
    memset(vis, 0, sizeof(vis));
    fill(dis, dis + maxn, inf);
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (dis[c.to] > dis[now] + c.cost && c.lastf > 0) {
                dis[c.to] = dis[now] + c.cost;
                p[c.to] = now;
                pre[c.to] = i;
                if (vis[c.to] == 0) {
                    vis[c.to] = 1;
                    q.push(c.to);
                }
            }
        }
    }
    return dis[e] != inf;
}

int cost;
int min_cost_flow(int s, int e) {
    int flow = 0;
    cost = 0;
    while (spfa(s, e)) {
        int f = inf;
        for (int now = e; now != s; now = p[now]) {
            f = min(f, edge[pre[now]].lastf);
        }
        flow += f;
        cost += f * dis[e];
        for (int now = e; now != s; now = p[now]) {
            edge[pre[now]].lastf -= f;
            edge[pre[now] ^ 1].lastf += f;
        }
    }
    return flow;
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &k) && n + m + k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                scanf("%d", &arr1[i][j]);
                //arr1[i][j] = Scan();
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= k; ++j) {
                scanf("%d", &arr2[i][j]);
                //arr2[i][j] = Scan();
            }
        }
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int z = 1; z <= m; ++z) {
                    scanf("%d", &arr3[i][j][z]);
                    //arr3[i][j][z] = Scan();
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= k; ++i) {
            cnt = 0;
            memset(head, -1, sizeof(head));
            int s = 0, e = n + m + 1, sum = 0;
            for (int j = 1; j <= m; ++j) {
                //int x = s, y = n + j, f = arr2[j][i];
                insert(s, n + j, arr2[j][i], 0);
            }
            for (int j = 1; j <= n; ++j) {
                sum += arr1[j][i];
                //int f = arr1[j][i];
                insert(j, e, arr1[j][i], 0);
                for (int z = 1; z <= m; ++z) {
                    //int x = z + n, y = j, c = arr3[i][j][z];
                    insert(z + n, j, inf, arr3[i][j][z]);
                }
            }
            if (min_cost_flow(s, e) != sum) {
                ans = -1;
                break;
            } else {
                ans += cost;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}


// UVA 10480
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
using namespace std;
const int maxn = 510, inf = 0x3fffffff;
int head[maxn], depth[maxn], n, m, cnt;

struct Edge {
    int to, lastf, next;
} edge[maxn * maxn];

struct node {
    int x, y;
    friend bool operator < (const node& a, const node& b) {
        if (a.x == b.x) return a.y > b.y;
        return a.x > b.x;
    }
    friend bool operator == (const node& a, const node& b) {
        return a.x == b.x && a.y == b.y;
    }
};

void insert(int x, int y, int f) {
    edge[cnt] = {y, f, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, 0, head[y]};
    head[y] = cnt++;
    edge[cnt] = {x, f, head[y]};
    head[y] = cnt++;
    edge[cnt] = {y, 0, head[x]};
    head[x] = cnt++;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    depth[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf > 0) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf > 0) {
            int d = dfs(c.to, e, min(f, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                return d;
            }
        }
    }
    return 0;
}

void dinic(int s, int e) {
    while (bfs(s, e)) {
        while (dfs(s, e, inf)) {
            ;
        }
    }
    set<node> ss;
    for (int now = 1; now <= n; ++now) {
        for (int i = head[now]; i != -1; i = edge[i].next) {
            if ((depth[now] == 0 && depth[edge[i].to] > 0)
                || (depth[now] > 0 && depth[edge[i].to] == 0)) {
                int x = now, y = edge[i].to;
                if (x > y) {
                    swap(x, y);
                }
                ss.insert({x, y});
            }
        }
    }
    for (set<node>::iterator it = ss.begin(); it != ss.end(); ++it) {
        printf("%d %d\n", it->x, it->y);
    }
}

int main() {
    int x, y, f;
    while (~scanf("%d%d", &n, &m) && n + m) {
        memset(head, -1, sizeof(head));
        cnt = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &f);
            insert(x, y, f);
        }
        dinic(1, 2);
        printf("\n");
    }
    return 0;
}


// poj 2195
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1010, inf = 0x3fffffff;
char str[maxn][maxn];
int arr[maxn][maxn], head[maxn], cnt, n, m;
int p[maxn], pre[maxn], dis[maxn], vis[maxn];

struct Edge {
    int to, lastf, cost, next;
} edge[maxn * maxn];

void insert(int x, int y, int f, int cost) {
    edge[cnt] = {y, f, cost, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, 0, -cost, head[y]};
    head[y] = cnt++;
}

int abs(int a) {
    return a > 0 ? a : -a;
}

void connect(int s, int e) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (str[i][j] == 'H') {
                // 洞
                insert(arr[i][j], e, 1, 0);
            } else if (str[i][j] == 'm') {
                // 人
                insert(s, arr[i][j], 1, 0);
                for (int x = 0; x < n; ++x) {
                    for (int y = 0; y < m; ++y) {
                        if (str[x][y] == 'H') {
                            insert(arr[i][j], arr[x][y], inf, abs(x-i) + abs(y-j));
                        }
                    }
                }
            }
        }
    }
}

int spfa(int s, int e) {
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next) {
            int to = edge[i].to, d = edge[i].cost;
            if (edge[i].lastf > 0 && dis[to] > dis[now] + d) {
                dis[to] = dis[now] + d;
                p[to] = now;
                pre[to] = i;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
    return dis[e] != inf;
}

int min_cost(int s, int e) {
    int ans = 0;
    while (spfa(s, e)) {
        int f = inf;
        for (int i = e; i != s; i = p[i]) {
            f = min(f, edge[pre[i]].lastf);
            ans += edge[pre[i]].cost;
        }
        for (int i = e; i != s; i = p[i]) {
            edge[pre[i]].lastf -= f;
            edge[pre[i]^1].lastf += f;
        }
    }
    return ans;
}

int main() {
    while (~scanf("%d%d", &n, &m) && n + m) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        int s = 0, e = 1, num = 2;
        for (int i = 0; i < n; ++i) {
            scanf("%s", str[i]);
            for (int j = 0; j < m; ++j) {
                if (str[i][j] == 'H' || str[i][j] == 'm')
                    arr[i][j] = num++;
            }
        }
        connect(s, e);
        printf("%d\n", min_cost(s, e));
    }
    return 0;
}


// poj 1087
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
using namespace std;
const int maxn = 1100, inf = 0x3fffffff;
int head[maxn], cnt, depth[maxn];
string k1[maxn], k2[maxn], k3[maxn], k4[maxn];
struct Edge {
    int to, lastf, next;
} edge[maxn * maxn];

void insert(int x, int y, int f) {
    edge[cnt] = {y, f, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, 0, head[y]};
    head[y] = cnt++;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    depth[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf > 0) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf > 0) {
            int d = dfs(c.to, e, min(f, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    memset(head, -1, sizeof(head));
    int n, m, s = 0, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        cin >> k1[i];
        insert(s, i, 1);
    }
    scanf("%d", &m);
    int e = n + m + 1;
    string tmp;
    for (int i = n + 1; i < e; ++i) {
        cin >> tmp >> k2[i - n];
        insert(i, e, 1);
    }
    scanf("%d", &k);
    for (int i = e + 1; i <= e + k; ++i) {
        cin >> k4[i - e] >> k3[i - e];
        for (int j = 1; j <= n; ++j) {
            if (k3[i-e] == k1[j]) {
                insert(j, i, 1);
            }
        }
        for (int j = 1; j <= m; ++j) {
            if (k4[i-e] == k2[j]) {
                insert(i + k, j + n, 1);
            }
        }
        insert(i, i + k, inf);
    }
    for (int i = e + 1; i <= e + k; ++i) {
        for (int j = e + k + 1; j <= e + 2 * k; ++j) {
            if (i != j - k && k4[j - k - e] == k3[i - e]) {
                insert(j, i, inf);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (k1[i] == k2[j]) {
                insert(i, j + n, 1);
            }
        }
    }
    printf("%d\n", m - dinic(s, e));
    return 0;
}


// poj 3281
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1e4 + 10, inf = 0x3fffffff;
int head[maxn], depth[maxn], cnt;

struct Edge {
    int to, lastf, next;
} edge[maxn];

void insert(int x, int y, int f) {
    edge[cnt] = {y, f, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, 0, head[y]};
    head[y] = cnt++;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf > 0) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf > 0) {
            int d = dfs(c.to, e, min(f, c.lastf));
            if (d > 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main() {
    memset(head, -1, sizeof(head));
    int n, f, d, k1, k2, x;
    scanf("%d%d%d", &n, &f, &d);
    int s = 0, e = f + d + 1;
    for (int i = 1; i <= f; ++i) insert(s, i, 1);
    for (int i = f + 1; i <= f + d; ++i) insert(i, e, 1);
    int now = e + 1;
    
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &k1, &k2);
        for (int j = 0; j < k1; ++j) {
            scanf("%d", &x);
            insert(x, now, 1);
        }
        insert(now, now + 1, 1);
        ++now;
        for (int j = 0; j < k2; ++j) {
            scanf("%d", &x);
            insert(now, x + f, 1);
        }
        ++now;
    }
    printf("%d\n", dinic(s, e));
    return 0;
}


// hdu 1532
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 210, inf = 0x3fffffff;
int head[maxn], depth[maxn], cnt;

struct Edge {
    int to, lastf, next;
} edge[maxn << 1];

void insert(int x, int y, int f) {
    edge[cnt] = {y, f, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, 0, head[y]};
    head[y] = cnt++;
}

int bfs(int s, int e) {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i != -1; i = edge[i].next) {
            Edge c = edge[i];
            if (depth[c.to] == 0 && c.lastf > 0) {
                depth[c.to] = depth[now] + 1;
                q.push(c.to);
            }
        }
    }
    return depth[e] != 0;
}

int dfs(int now, int e, int f) {
    if (now == e) {
        return f;
    }
    for (int i = head[now]; i != -1; i = edge[i].next) {
        Edge c = edge[i];
        if (depth[c.to] == depth[now] + 1 && c.lastf > 0) {
            int d = dfs(c.to, e, min(f, c.lastf));
            if (d != 0) {
                edge[i].lastf -= d;
                edge[i^1].lastf += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int e) {
    int ans = 0, d;
    while (bfs(s, e)) {
        while ((d = dfs(s, e, inf)) != 0) {
            ans += d;
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    int m, n, x, y, f;
    while (~scanf("%d%d", &m, &n)) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &f);
            insert(x, y, f);
        }
        printf("%d\n", dinic(1, n));
    }
    return 0;
}

*/
