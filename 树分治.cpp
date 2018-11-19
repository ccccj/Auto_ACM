//
//  main.cpp
//  树分治
//
//  Created by admin on 18/10/8.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 4e5 + 10;
int head[maxn], cnt, n;

struct Edge {
    int to, d, next;
} edge[10 * maxn], q[10 * maxn];

void insert(int x, int y, int d) {
    ++cnt;
    edge[cnt].to = y, edge[cnt].d = d, edge[cnt].next = head[x];
    head[x] = cnt;
}

void Tarjan() {
    
}

int main() {
    int t, m, x, y, d;
    scanf("%d", &t);
    while (t--) {
        cnt = 0;
        memset(head, 0, sizeof(head));
        scanf("%d%d", &n, &m);
        for (int i = 1; i < n; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, d);
            insert(y, x, d);
        }
        
        
        
    }
    return 0;
}

/*
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 3e6 + 10;
int head[maxn], arr[maxn], cnt, num;
int qhead[maxn], qcnt;
int ans1[maxn*10], ans[maxn*10];
int father[maxn], vis[maxn];

struct Edge {
    int to, next;
} edge[10 * maxn], q[10 * maxn];

void init() {
    qcnt = cnt = 0;
    num = 1;
    memset(vis, 0, sizeof(vis));
    memset(head, 0, sizeof(head));
    memset(qhead, 0, sizeof(qhead));
    memset(ans1, 0, sizeof(ans1));
    memset(ans, 0, sizeof(ans));
}

void insert(int x, int y) {
    ++cnt;
    edge[cnt].to = y, edge[cnt].next = head[x];
    head[x] = cnt;
}

void insert1(int x, int y) {
    ++qcnt;
    q[qcnt].to = y, q[qcnt].next = qhead[x];
    qhead[x] = qcnt;
}

int find(int x) {
    return father[x] == x ? x : father[x] = find(father[x]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) father[fx] = fy;
}

void Tarjan(int now) {
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        Tarjan(to);
        merge(to, now);
    }
    vis[now] = 1;
    int k = find(now);
    for (int i = qhead[now]; i; i = q[i].next) {
        int to = q[i].to;
        if (to != now && vis[to] == 1) {
            if (find(to) == k)
                ans[ans1[i]] = 1;
        }
    }
}

int main() {
    int t, n, m, a, b, ca = 1;
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        for (int fa = 0; fa < n; ++fa) {
            for (int i = 0; i < arr[fa + 1]; ++i) {
                father[num] = num;
                insert(fa, num++);
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &a, &b); // 询问a是否为b祖先
            insert1(a, b);
            ans1[qcnt] = i;
        }
        Tarjan(0);
        printf("Case %d:\n", ca++);
        for (int i = 0; i < m; ++i) {
            if (ans[i]) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
        if (t > 0) {
            printf("\n");
        }
    }
    return 0;
}

2
6
3 2 1 1 0 2
5
0 1
2 4
3 5
1 8
6 9
5
2 0 3 0 1
4
2 6
1 6
2 3
3 5
*/
/*
// poj 1330
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 40010;
int head[maxn], cnt, n, root[maxn], x, y;
int fa[maxn], vis[maxn];

struct Edge {
    int to, next;
} edge[10 * maxn];

void init() {
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(root, 0, sizeof(root));
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
}

void insert(int x, int y) {
    ++cnt;
    edge[cnt].to = y, edge[cnt].next = head[x];
    head[x] = cnt;
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
    }
}

void Tarjan(int now) {
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        Tarjan(to);
        merge(to, now);
    }
    vis[now] = 1;
    if (x == now && vis[y] == 1) {
        printf("%d\n", find(y));
        return;
    }
    if (y == now && vis[x] == 1) {
        printf("%d\n", find(x));
        return;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        init();
        for (int i = 1; i < n; ++i) {
            scanf("%d%d", &x, &y);
            insert(x, y);
            root[y] = 1;
        }
        int rt = 1;
        for (int i = 1; i <= n; ++i) {
            if (root[i] == 0) {
                rt = i;
                break;
            }
        }
        scanf("%d%d", &x, &y);
        Tarjan(rt);
    }
    return 0;
}


// poj 1741
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10010, inf = 0x3fffffff;
int head[maxn], cnt, n, k, ret;
int size[maxn], maxv[maxn], vis[maxn], root, allnode;
vector<int> dis;

struct Edge {
    int to, d, next;
} edge[10 * maxn];

void insert(int x, int y, int d) {
    ++cnt;
    edge[cnt].to = y, edge[cnt].d = d, edge[cnt].next = head[x];
    head[x] = cnt;
    ++cnt;
    edge[cnt].to = x, edge[cnt].d = d, edge[cnt].next = head[y];
    head[y] = cnt;
}

void init() {
    allnode = n;
    ret = root = cnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(head, 0, sizeof(head));
    maxv[root] = inf;
}

void get_root(int now, int fa) { // 查找重心
    size[now] = 1;
    maxv[now] = 0;
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (to != fa && vis[to] == 0) {
            get_root(to, now);
            size[now] += size[to];
            // 选能让最大子树最小的结点作为重心
            maxv[now] = max(maxv[now], size[to]);
        }
    }
    maxv[now] = max(maxv[now], allnode - maxv[now]);
    if (maxv[root] > maxv[now]) root = now;
}

void dfs_dis(int now, int fa, int d) { // 计算到当前根的距离
    dis.push_back(d);
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (to != fa && vis[to] == 0) {
            dfs_dis(to, now, d + edge[i].d);
        }
    }
}

int cal(int rt, int d) {
    dis.clear();
    dfs_dis(rt, -1, d);
    sort(dis.begin(), dis.end());
    int ans = 0;
    int len = (int)dis.size();
    for (int l = 0, r = len - 1; l < r; ) {
        if (dis[l] + dis[r] > k) {
            --r;
        } else {
            ans += r - l;
            ++l;
        }
    }
    return ans;
}

void work(int rt) {
    vis[rt] = 1;
    ret += cal(rt, 0);
    for (int i = head[rt]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (vis[to] == 0) {
            ret -= cal(to, edge[i].d); // 减去同一子树中，前面加进去了的
            allnode = size[to];
            root = 0;
            get_root(to, rt);
            work(root);
        }
    }
}

int main() {
    int x, y, d;
    while (~scanf("%d%d", &n, &k) && n + k) {
        init();
        for (int i = 1; i < n; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            insert(x, y, d);
        }
        get_root(1, -1);
        work(root);
        printf("%d\n", ret);
    }
    return 0;
}


// poj 2186
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 100010;
int head[maxn], cnt, out[maxn];
int dfn[maxn], low[maxn], color[maxn], vis[maxn], num, colornum;
stack<int> s;

struct Edge {
    int to, next;
} edge[10 * maxn];

void insert(int x, int y) {
    ++cnt;
    edge[cnt].to = y, edge[cnt].next = head[x];
    head[x] = cnt;
}

void Tarjan(int now) {
    vis[now] = 1;
    dfn[now] = low[now] = ++num;
    s.push(now);
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (dfn[to] == 0) Tarjan(to);
        if (vis[to] == 1) low[now] = min(low[to], low[now]);
    }
    if (low[now] == dfn[now]) {
        ++colornum;
        int tmp;
        do {
            tmp = s.top();
            color[tmp] = colornum;
            vis[tmp] = 0;
            s.pop();
        } while (tmp != now);
    }
    
}

int main() {
    int n, m, x, y, flag = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        insert(x, y);
    }
    for (int i = 1; i <= n; ++i) {
        if  (color[i] == 0) Tarjan(i);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = head[i]; j; j = edge[j].next) {
            int to = edge[j].to;
            if (color[i] != color[to]) {
                ++out[color[i]];
            }
        }
    }
    int tmp = 0;
    for (int i = 1; i <= colornum; ++i) {
        if (out[i] == 0) {
            tmp = i;
            ++flag;
        }
    }
    if (flag == 0 || flag > 1) {
        printf("0\n");
    } else {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (color[i] == tmp) {
                ++ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}


// hdu 1269
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 10010;
int dfn[maxn], low[maxn], vis[maxn];
int head[maxn], cnt, dfsnum, sum;

struct Edge {
    int to, next;
} edge[maxn * 10];

void init() {
    cnt = dfsnum = sum = 0;
    memset(head, 0, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(dfn, 0, sizeof(dfn));
}

void insert(int x, int y) {
    edge[++cnt] = {y, head[x]};
    head[x] = cnt;
}

void Tarjan(int now) {
    dfn[now] = low[now] = ++dfsnum;
    vis[now] = 1;
    
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (vis[to] == 0) Tarjan(to);
        if (vis[to] == 1) low[now] = min(low[now], low[to]);
    }
    if (dfn[now] == low[now]) ++sum;
}



int main(int argc, const char * argv[]) {
    int n, m, x, y;
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        init();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            insert(x, y);
        }
        for (int i = 1; i <= n; ++i) {
            if (vis[i] == 0) {
                Tarjan(i);
            }
        }
        if (sum == 1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
*/
