//
//  main.cpp
//  Shenyang网络赛
//
//  Created by admin on 18/9/6.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 1e4 + 10, inf = 0x3fffffff;

LL n, m, s, e, k, t, x, y, l;

struct edge {
    LL to, l;
};

LL H[maxn];
bool vis[maxn];

vector<edge> s_edge[maxn];
vector<edge> e_edge[maxn];

void insert(LL x, LL y, LL l) {
    s_edge[x].push_back({y, l});
    e_edge[y].push_back({x, l});
}

struct node {
    LL id, sum;
    friend bool operator < (const node& a, const node& b) {
        return a.sum > b.sum;
    }
};

struct node_star {
    LL id, F, G, sum;
    friend bool operator < (const node_star& a, const node_star& b) {
        return a.F > b.F;
    }
};

void dij() {
    fill(H, H + maxn, inf);
    memset(vis, 0, sizeof(vis));
    
    H[e] = 0;
    priority_queue<node> q;
    q.push({e, 0});
    
    while (!q.empty()) {
        node now = q.top();
        q.pop();
        if (vis[now.id] == 1) {
            continue;
        }
        vis[now.id] = 1;
        int len = (int)e_edge[now.id].size();
        for (int i = 0; i < len; ++i) {
            edge x = e_edge[now.id][i];
            if (H[x.to] > H[now.id] + x.l) {
                H[x.to] = H[now.id] + x.l;
                q.push({x.to, H[x.to]});
            }
        }
    }
//    for (int i = 0; i < maxn; ++i) {
//        if (H[i] != inf) {
//            printf("i %d   H[i] %lld\n", i, H[i]);
//        }
//    }
}

bool A_star() {
    if (H[s] == inf) {
        return 0;
    }
    priority_queue<node_star> q;
    q.push({s, H[s], 0, 0});
    int kk = 0;
    while (!q.empty()) {
        node_star now = q.top();
        if (now.id == e) {
            ++kk;
            if (kk == k) {
                if (now.sum > t) {
                    return 0;
                } else {
                    return 1;
                }
            }
        }
        if (now.sum > t) {
            return 0;
        }
        q.pop();
        int len = (int)s_edge[now.id].size();
        for (int i = 0; i < len; ++i) {
            edge x = s_edge[now.id][i];
            q.push({x.to, now.G + x.l + H[x.to], now.G + x.l, now.sum + x.l});
        }
    }
    return 0;
}

int main() {
    while (~scanf("%lld%lld", &n, &m)) {
        scanf("%lld%lld%lld%lld", &s, &e, &k, &t);
        for (int i = 0; i < maxn; ++i) {
            s_edge[i].clear();
            e_edge[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            scanf("%lld%lld%lld", &x, &y, &l);
            insert(x, y, l);
        }
        dij();
        if (A_star()) {
            printf("yareyaredawa\n");
        } else {
            printf("Whitesnake!\n");
        }
    }
    return 0;
}

/*
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e5 + 10;

struct Edge {
    int next, to;
} edge[maxn];
vector<int> mp[maxn];
int head[maxn], dep[maxn],  size[maxn], tid[maxn], lazy[maxn],
n, q, cnt = 0, u, v, res = 0;
long long int segtree[maxn << 2];

void add_edge(int from, int to) {
    edge[++cnt].next = head[from];
    edge[cnt].to = to;
    head[from] = cnt;
}

void dfs(int x,int deep) {
    dep[x] = deep;
    mp[deep].push_back(x);
    size[x] = 1;
    tid[x] = ++res;
    for (int i = head[x]; i; i = edge[i].next) {
        int son = edge[i].to;
        dfs(son, deep + 1);
        size[x] += size[son];
    }
}

void update(int l, int r, long long int c, int tar, int now) {
    if (l == r) {
        segtree[now] += c;
        return;
    }
    int mid = l + (r - l)/2;
    if (tar <= mid) update(l, mid, c, tar, now << 1);
    else update(mid + 1, r, c, tar, (now << 1)|1);
    segtree[now] = segtree[now << 1] + segtree[(now << 1)|1];
}

long long int query(int L, int R, int l, int r, int now) {
    if (L <= l && R >= r) {
        return segtree[now];
    }
    //pushdown(now, l, r);
    int mid = l + (r - l)/2;
    long long int ans = 0;
    if (L <= mid) ans += query(L, R, l, mid, now << 1);
    if (R > mid) ans += query(L, R, mid + 1, r, (now << 1)|1);
    return ans;
}

struct node {
    int l;
    long long int x;
};

int main() {
    
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    
    dfs(1, 0);
    
    int op, l;
    long long int x;
    vector<node> p;
    
    for (int i = 0; i < q; i++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %lld", &l, &x);
            //int len = (int)mp[l].size();
            int len = (int)p.size(), f = 0;
            for (int i = 0; i < len; ++i) {
                if (p[i].l == l) {
                    p[i].x += x;
                    f = 1;
                    break;
                }
            }
            if (f == 0) {
                p.push_back({l, x});
            }
        } else {
            scanf("%lld", &x);
            int len = (int)p.size(), d = dep[x];
            
            for (int i = len - 1; i >= 0; --i) {
                if (p[i].l >= d) {
                    int _l = (int)mp[p[i].l].size();
                    for (int j = 0; j < _l; j++) {
                        int tar = tid[mp[p[i].l][j]];
                        if (p[i].l == dep[tar]) {
                            update(1, n, x, tar, 1);
                        }
                    }
                    p.erase(p.begin() + i);
                }
            }
            printf("%lld\n", query(tid[x], tid[x] + size[x] - 1, 1, n, 1));
            
        }
    }
    
    return 0;
}


9 100
1 2
1 6
2 3
2 5
6 7
7 8
7 9
3 4
1 2 2
1 3 1
2 2


#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxm = 1e9 + 10;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

vector<int> v[2];

int main() {
    int T, n, m, ca = 1, x;
    scanf("%d", &T);
    while (T--) {
        v[0].clear();
        v[1].clear();
        printf("Case #%d: ", ca++);
        scanf("%d%d", &n, &m);
        LL sum = (m - 1) * m / 2;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            int g = gcd(x, m);
            v[0].push_back(g);
            sum += g;
        }
        int now = 0;
        while (v[now].size()) {
            int next = now ^ 1;
            v[next].clear();
            for (int i = 0; i > v[now].size(); ++i) {
                
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}



// M
// 新增结点
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 1e6 + 1e5 + 10, inf = 0x3f3f3f3f;
typedef long long LL;

int n, m, t, si, all;

LL road[2][maxn];
bool vis[maxn];

struct edge {
    int to, ti;
};

struct node {
    int id;
    LL sum;
    friend bool operator < (node a, node b) {
        return a.sum > b.sum;
    }
};

vector<edge> arr[maxn];

void insert(int x, int y, int ti) {
    edge now = {y, ti};
    arr[x].push_back(now);
}

void dij(int p) {
    int s = 1, e = n;
    if (p == 1) {
        swap(s, e);
    }
    
    fill(road[p], road[p] + all + 10, inf);
    memset(vis, 0, sizeof(vis));
    vis[s] = 1;
    road[p][s] = 0;
    priority_queue<node> q;
    for (int i = 0; i < arr[s].size(); ++i) {
        edge now = arr[s][i];
        road[p][now.to] = road[p][s] + now.ti;
        node tmp = {now.to, road[p][now.to]};
        q.push(tmp);
    }
    while (!q.empty()) {
        node now = q.top();
        q.pop();
        if (vis[now.id] == 1) continue;
        vis[now.id] = 1;
        for (int i = 0; i < arr[now.id].size(); ++i) {
            edge e = arr[now.id][i];
            if (road[p][e.to] > road[p][now.id] + e.ti) {
                road[p][e.to] = road[p][now.id] + e.ti;
                q.push({e.to, road[p][e.to]});
            }
        }
    }
}

int main() {
    int T, ca = 1;
    scanf("%d", &T);
    while (T--) {
        printf("Case #%d: ", ca++);
        scanf("%d%d", &n, &m);
        all = n + 1;
        for (int i = 1; i < maxn; ++i) {
            arr[i].clear();
        }
        int x;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &t, &si);
            for (int j = 0; j < si; ++j) {
                scanf("%d", &x);
                insert(x, all, t);
                insert(all, x, t);
            }
            ++all;
        }
        dij(0);
        dij(1);
        int sum = inf;
        for (int i = 1; i <= n; ++i) {
            sum = min(sum, max((int)road[0][i], (int)road[1][i]));
        }
        if (sum == inf) {
            printf("Evil John\n");
            continue;
        }
        printf("%d\n", sum / 2);
        int c = 1;
        for (int i = 1; i <= n; ++i) {
            if (sum == max((int)road[0][i], (int)road[1][i])) {
                if (c++ != 1) {
                    printf(" ");
                }
                printf("%d", i);
            }
        }
        printf("\n");
    }
    return 0;
}

// H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
const int maxn = 510;

bool Map[maxn][maxn];

int main() {
    
    int T, n, m, o, com, x, y, ca = 1;
    scanf("%d", &T);
    while (T--) {
        printf("Case #%d: ", ca++);
        memset(Map, 0, sizeof(Map));
        scanf("%d%d%d%d", &n, &m, &o, &com);
        for (int i = 0; i < o; ++i) {
            scanf("%d%d", &x, &y);
            Map[x][y] = 1;
        }
        string s;
        cin >> s;
        long long int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (Map[i][j]) continue;
                int x = i, y = j;
                
                for (int k = 0; k < com; ++k) {
                    switch (s[k]) {
                        case 'U':
                            if (x > 1 && !Map[x-1][y]) {
                                x--;
                            }
                            break;
                        case 'D':
                            if (x < n && !Map[x+1][y]) {
                                x++;
                            }
                            break;
                        case 'L':
                            if (y > 1 && !Map[x][y-1]) {
                                y--;
                            }
                            break;
                        case 'R':
                            if (y < m && !Map[x][y+1]) {
                                y++;
                            }
                            break;
                        default:
                            break;
                    }
                }
                ans += (x - i) * (x - i) + (y - j) * (y - j);

            }
        }
        cout << ans << endl;
    }
    return 0;
}


// D
#include <iostream>
#include <cstdio>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main(int argc, const char * argv[]) {
    int T, n, a, b;
    scanf("%d", &T);
    int ca = 1;
    while (T--) {
        printf("Case #%d: ", ca++);
        scanf("%d%d%d", &n, &a, &b);
        if (a > b) swap(a, b);
        int sum = 0;
        int g = gcd(a, b);
        
        if ((b - a) % g == 0) {
            sum = n / g;
            if (sum % 2 == 0) {
                printf("Iaka\n");
            } else {
                printf("Yuwgna\n");
            }
            continue;
        }
        if (a % 2 == 0 && b % 2 == 0) {
            sum = n / 2;
        } else {
            sum = n;
        }
        if (sum % 2 == 0) {
            printf("Iaka\n");
        } else {
            printf("Yuwgna\n");
        }
    }
    return 0;
}

*/
