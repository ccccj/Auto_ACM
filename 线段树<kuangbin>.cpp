//
//  main.cpp
//  kuangbin线段树
//
//  Created by admin on 18/10/30.
//  Copyright © 2018年 Amon. All rights reserved.
//
/*
// hdu 4553
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 25;
// 0 空闲 1 基友 2 女神 -1 无效
struct node {
    int lazy_d, lazy_n;
    int dl, dr, dm;
    int nl, nr, nm;
} tree[maxn << 2];

int ans;

void change_ds(int l, int r, int C, int now) {
    int a;
    if (C == 0) a = r - l + 1;
    else if (C == 1 || C == 2) a = 0;
    tree[now].dl = tree[now].dr = tree[now].dm = a;
}

void change_ns(int l, int r, int C, int now) {
    int a;
    if (C == 0) a = r - l + 1;
    else if (C == 2) a = 0;
    tree[now].nl = tree[now].nr = tree[now].nm = a;
}

void pushdown(int l, int r, int now) {
    int m = (l + r) / 2;
    if (tree[now].lazy_d != -1) {
        tree[now << 1].lazy_d = tree[(now << 1)|1].lazy_d = tree[now].lazy_d;
        change_ds(l, m, tree[now].lazy_d, now << 1);
        change_ds(m + 1, r, tree[now].lazy_d, (now << 1)|1);
        tree[now].lazy_d = -1;
    }
    if (tree[now].lazy_n != -1) {
        tree[now << 1].lazy_n = tree[(now << 1)|1].lazy_n = tree[now].lazy_n;
        change_ns(l, m, tree[now].lazy_n, now << 1);
        change_ns(m + 1, r, tree[now].lazy_n, (now << 1)|1);
        tree[now].lazy_n = -1;
    }
}

void pushup(int l, int r, int now) {
    int m = (l + r) / 2;
    if (tree[now << 1].dm + tree[(now << 1)|1].dm == r - l + 1) {
        tree[now].dm = r - l + 1;
    } else {
        int Max = max(tree[now << 1].dm, tree[(now << 1)|1].dm);
        if (tree[now << 1].dr + tree[(now << 1)|1].dl > Max) {
            Max = tree[now << 1].dr + tree[(now << 1)|1].dl;
        }
        tree[now].dm = Max;
    }
    if (tree[now << 1].dl == m - l + 1) {
        tree[now].dl = m - l + 1 + tree[(now << 1)|1].dl;
    } else {
        tree[now].dl = tree[now << 1].dl;
    }
    if (tree[(now << 1)|1].dr == r - m) {
        tree[now].dr = r - m + tree[now << 1].dr;
    } else {
        tree[now].dr = tree[(now << 1)|1].dr;
    }
    
    /////////////////////////////////////////////
    
    if (tree[now << 1].nm + tree[(now << 1)|1].nm == r - l + 1) {
        tree[now].nm = r - l + 1;
    } else {
        int Max = max(tree[now << 1].nm, tree[(now << 1)|1].nm);
        if (tree[now << 1].nr + tree[(now << 1)|1].nl > Max) {
            Max = tree[now << 1].nr + tree[(now << 1)|1].nl;
        }
        tree[now].nm = Max;
    }
    if (tree[now << 1].nl == m - l + 1) {
        tree[now].nl = m - l + 1 + tree[(now << 1)|1].nl;
    } else {
        tree[now].nl = tree[now << 1].nl;
    }
    if (tree[(now << 1)|1].nr == r - m) {
        tree[now].nr = r - m + tree[now << 1].nr;
    } else {
        tree[now].nr = tree[(now << 1)|1].nr;
    }
}

void update(int l, int r, int L, int R, int C, int now) {
    if (l >= L && r <= R) {
        if (C == 0) {
            tree[now].lazy_d = tree[now].lazy_n = C;
            change_ds(l, r, C, now), change_ns(l, r, C, now);
        } else if (C == 1) {
            tree[now].lazy_d = C;
            change_ds(l, r, C, now);
        } else if (C == 2) {
            tree[now].lazy_d = tree[now].lazy_n = C;
            change_ns(l, r, C, now);
            change_ds(l, r, C, now);
        }
        return;
    }
    int m = (l + r) / 2;
    pushdown(l, r, now);
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
    pushup(l, r, now);
}

void build(int l, int r, int now) {
    if (l == r) {
        tree[now].lazy_d = tree[now].lazy_n = -1;
        tree[now].dl = tree[now].dr = tree[now].dm = 1;
        tree[now].nl = tree[now].nr = tree[now].nm = 1;
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    pushup(l, r, now);
}

void query(int l, int r, int now, int C, int k) {
    if (l == r) {
        ans = l;
        return;
    }
    pushdown(l, r, now);
    int m = (l + r) / 2;
    if (k == 1) {
        if (tree[now << 1].dm >= C) {
            query(l, m, now << 1, C, k);
        } else if (tree[now << 1].dr + tree[(now << 1)|1].dl >= C) {
            ans = m - tree[now << 1].dr + 1;
        } else {
            query(m + 1, r, (now << 1)|1, C, k);
        }
    } else {
        if (tree[now << 1].nm >= C) {
            query(l, m, now << 1, C, k);
        } else if (tree[now << 1].nr + tree[(now << 1)|1].nl >= C) {
            ans = m - tree[now << 1].nr + 1;
        } else {
            query(m + 1, r, (now << 1)|1, C, k);
        }
    }
}

int main() {
    //freopen("/Users/admin/Desktop/in.txt", "r", stdin);
    //freopen("/Users/admin/Desktop/out2.txt", "w", stdout);
    int t, n, m, x, y, ca = 1;
    char s[10];
    scanf("%d", &t);
    while (t--) {
        printf("Case %d:\n", ca++);
        memset(tree, 0, sizeof(tree));
        scanf("%d%d", &n, &m);
        build(1, n, 1);
        while (m--) {
            //for (int i = 1; i <= 33; ++i) {
                //printf("i %d:\n%d %d %d\n%d %d %d\n%d %d\n", i, tree[i].dl, tree[i].dr, tree[i].dm, tree[i].nl, tree[i].nr, tree[i].nm, tree[i].lazy_d, tree[i].lazy_n);
            //}
            scanf("%s", s);
            if (s[0] == 'D') {
                // 基友
                scanf("%d", &x);
                if (tree[1].dm < x) {
                    printf("fly with yourself\n");
                } else {
                    query(1, n, 1, x, 1);
                    update(1, n, ans, ans + x - 1, 1, 1);
                    for (int i = 1; i <= 33; ++i) {
                        //printf("i %d:\n%d %d %d\n%d %d %d\n%d %d\n", i, tree[i].dl, tree[i].dr, tree[i].dm, tree[i].nl, tree[i].nr, tree[i].nm, tree[i].lazy_d, tree[i].lazy_n);
                    }
                    printf("%d,let's fly\n", ans);
                }
            } else if (s[0] == 'N') {
                // 女神
                scanf("%d", &x);
                if (tree[1].dm >= x) {
                    query(1, n, 1, x, 1);
                    printf("%d,don't put my gezi\n", ans);
                    update(1, n, ans, ans + x - 1, 2, 1);
                } else {
                    if (tree[1].nm < x) {
                        printf("wait for me\n");
                    } else {
                        query(1, n, 1, x, 2);
                        printf("%d,don't put my gezi\n", ans);
                        update(1, n, ans, ans + x - 1, 2, 1);
                    }
                }
                for (int i = 1; i <= 21; ++i) {
                    //printf("i %d:\n%d %d %d\n%d %d %d\n%d %d\n", i, tree[i].dl, tree[i].dr, tree[i].dm, tree[i].nl, tree[i].nr, tree[i].nm, tree[i].lazy_d, tree[i].lazy_n);
                }
            } else {
                // 学习
                scanf("%d%d", &x, &y);
                update(1, n, x, y, 0, 1);
                //for (int i = 1; i <= 33; ++i) {
                    //printf("i %d:\n%d %d %d\n%d %d %d\n%d %d\n", i, tree[i].dl, tree[i].dr, tree[i].dm, tree[i].nl, tree[i].nr, tree[i].nm, tree[i].lazy_d, tree[i].lazy_n);
                //}
                printf("I am the hope of chinese chengxuyuan!!\n");
            }
        }
    }
    return 0;
}


// poj 2991
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 1e5;
int lazy[maxn << 2], len[maxn];
double pre[maxn];

struct Point {
    double x, y;
    Point(double a = 0, double b = 0) {x = a, y = b;}
} p[maxn], tree[maxn << 2];

void change(int now, double C) {
    C = C / 180 * acos((long double)-1);
    double x = tree[now].x, y = tree[now].y;
    tree[now].x = x * cos(C) - y * sin(C);
    tree[now].y = y * cos(C) + x * sin(C);
}

void pushdown(int now) {
    if (lazy[now]) {
        int C = lazy[now];
        lazy[now << 1] += C;
        lazy[(now << 1)|1] += C;
        change(now << 1, C);
        change((now << 1)|1, C);
        lazy[now] = 0;
    }
}

void pushup(int now) {
    tree[now].x = tree[now << 1].x + tree[(now << 1)|1].x;
    tree[now].y = tree[now << 1].y + tree[(now << 1)|1].y;
}

void update(int l, int r, int L, int R, double C, int now) {
    if (l >= L && r <= R) {
        lazy[now] += C;
        change(now, C);
        return;
    }
    pushdown(now);
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
    pushup(now);
}

void build(int l, int r, int now) {
    if (l == r) {
        tree[now].x = 0, tree[now].y = len[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    pushup(now);
}

int main() {
    //freopen("/Users/admin/Desktop/in.txt", "r", stdin);
    //freopen("/Users/admin/Desktop/out1.txt", "w", stdout);
    int n, m, ca = 1;
    while (~scanf("%d%d", &n, &m)) {
        if (ca++ != 1) {
            printf("\n");
        }
        memset(lazy, 0, sizeof(lazy));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &len[i]);
            pre[i] = 180;
        }
        pre[1] = 0; // 第一根竖直
        build(1, n, 1);
        int l, r = n;
        double a;
        while (m--) {
            scanf("%d%lf", &l, &a);
            ++l;
            update(1, n, l, r, a - pre[l], 1);
            pre[l] = a;
            printf("%.2f %.2f\n", tree[1].x, tree[1].y);
        }
    }
    return 0;
}


// hdu 4614
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 1e5;
int ans, k1, k2, tree[maxn << 2];

void pushdown(int ln, int rn, int now) {
    if (tree[now] == ln + rn) {
        tree[now << 1] = ln, tree[(now << 1)|1] = rn;
    } else if (tree[now] == 0) {
        tree[now << 1] = tree[(now << 1)|1] = 0;
    }
}

void update_clear(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        int d = r - l + 1;
        ans += d - tree[now];
        tree[now] = d;
        return;
    }
    int m = (l + r) / 2;
    pushdown(m - l + 1, r - m, now);
    if (m >= L) update_clear(l, m, L, R, now << 1);
    if (m < R) update_clear(m + 1, r, L, R, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

void update_set(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        tree[now] = 0;
        return;
    }
    int m = (l + r) / 2;
    pushdown(m - l + 1, r - m, now);
    if (m >= L) update_set(l, m, L, R, now << 1);
    if (m < R) update_set(m + 1, r, L, R, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

void find_first(int l, int r, int tar, int now) {
    if (l == r) {
        if (tree[now]) k1 = l;
        return;
    }
    int m = (l + r) / 2;
    pushdown(m - l + 1, r - m, now);
    if (tree[now << 1] && tar <= m) find_first(l, m, tar, now << 1);
    if (tree[(now << 1)|1] && k1 == -1)
        find_first(m + 1, r, tar, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

int query(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        return tree[now];
    }
    int m = (l + r) / 2, ret = 0;
    pushdown(m - l + 1, r - m, now);
    if (m >= L) {
        ret += query(l, m, L, R, now << 1);
    }
    if (m < R) {
        ret += query(m + 1, r, L, R, (now << 1)|1);
    }
    return ret;
}

int main() {
    int t, n, m, k, a, f;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        tree[1] = n;
        while (m--) {
            scanf("%d%d%d", &k, &a, &f);
            if (k == 1) {
                // a 开始放 f 朵花
                k1 = -1;
                ans = 0;
                find_first(1, n, a + 1, 1);
                if (k1 == -1) printf("Can not put any one.\n");
                else {
                    int tmp = query(1, n, k1, n, 1);
                    if (tmp <= f) f = tmp;
                    
                    k2 = k1;
                    int l = k1, r = n;
                    while (r >= l) {
                        int m = (l + r) / 2;
                        int ret = query(1, n, k1, m, 1);
                        if (ret > f) {
                            r = m - 1;
                        } else if (ret < f) {
                            l = m + 1;
                        } else {
                            k2 = m;
                            r = m - 1;
                        }
                    }
                    
                    printf("%d %d\n", k1 - 1, k2 - 1);
                    update_set(1, n, k1, k2, 1);
                }
            } else {
                // 清空 a-f
                ans = 0;
                update_clear(1, n, a + 1, f + 1, 1);
                printf("%d\n", ans);
            }
        }
        printf("\n");
    }
    return 0;
}


// hdu 3974
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e5;
int head[maxn], in[maxn], cnt;
int si[maxn], son[maxn], dfs[maxn], num;
int tree[maxn << 2];

struct Edge {
    int to, next;
} edge[maxn];

void insert(int x, int y) {
    edge[++cnt] = {x, head[y]};
    head[y] = cnt;
}

void dfs_son(int now, int fa) {
    int Max = -1, s = 0;
    si[now] = 1;
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (to == fa) continue;
        dfs_son(to, now);
        si[now] += si[to];
        if (Max < si[to]) s = to, Max = si[to];
    }
    son[now] = s;
}

void dfs_dfs(int now, int fa) {
    dfs[now] = ++num;
    if (si[now] == 1) return;
    
    dfs_dfs(son[now], now);
    for (int i = head[now]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (to == fa || to == son[now]) continue;
        dfs_dfs(to, now);
    }
}

void init() {
    memset(head, 0, sizeof(head));
    memset(in, 0, sizeof(in));
    memset(si, 0, sizeof(si));
    memset(tree, -1, sizeof(tree));
    cnt = num = 0;
}

void update(int l, int r, int L, int R, int C, int now) {
    if (l >= L && r <= R) {
        tree[now] = C;
        return;
    }
    if (tree[now] != -1) {
        tree[now << 1] = tree[(now << 1)|1] = tree[now];
        tree[now] = -1;
    }
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
}

int query(int l, int r, int tar, int now) {
    if (l == r || tree[now] != -1) {
        return tree[now];
    }
    int m = (l + r) / 2;
    if (tar <= m) return query(l, m, tar, now << 1);
    else return query(m + 1, r, tar, (now << 1)|1);
}

int main() {
    int t, n, m, x, y, root = 0, ca = 1;
    scanf("%d", &t);
    char s[10];
    while (t--) {
        init();
        printf("Case #%d:\n", ca++);
        scanf("%d", &n);
        for (int i = 1; i < n; ++i) {
            scanf("%d%d", &x, &y);
            insert(x, y);
            ++in[x];
        }
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 0) {
                root = i;
                break;
            }
        }
        dfs_son(root, -1);
        dfs_dfs(root, -1);
        scanf("%d", &m);
        while (m--) {
            scanf("%s", s);
            if (s[0] == 'T') {
                // 分配任务
                scanf("%d%d", &x, &y);
                update(1, n, dfs[x], dfs[x] + si[x] - 1, y, 1);
            } else {
                // 查询
                scanf("%d", &x);
                printf("%d\n", query(1, n, dfs[x], 1));
            }
        }
    }
    return 0;
}


// hdu 1828
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 1e5;
int tree[maxn << 2], X[maxn], Y[maxn], len[maxn << 2];
struct Line1 {
    int x, y1, y2, flag;
    Line1() {}
    Line1(int a, int b, int c, int d) {x = a, y1 = b, y2 = c, flag = d;}
} line1[maxn];

struct Line2 {
    int y, x1, x2, flag;
    Line2() {}
    Line2(int a, int b, int c, int d) {y = a, x1 = b, x2 = c, flag = d;}
} line2[maxn];

void update(int l, int r, int L, int R, int C, int now, int k) {
    if (l >= L && r <= R) {
        tree[now] += C;
        if (k == 1) {
            if (tree[now]) len[now] = Y[r] - Y[l - 1];
            else len[now] = len[now << 1] + len[(now << 1)|1];
        } else {
            if (tree[now]) len[now] = X[r] - X[l - 1];
            else len[now] = len[now << 1] + len[(now << 1)|1];
        }
        return;
    }
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, C, now << 1, k);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1, k);
    if (k == 1) {
        if (tree[now]) len[now] = Y[r] - Y[l - 1];
        else len[now] = len[now << 1] + len[(now << 1)|1];
    } else {
        if (tree[now]) len[now] = X[r] - X[l - 1];
        else len[now] = len[now << 1] + len[(now << 1)|1];
    }
}

bool cmp1(Line1 a, Line1 b) {
    if (a.x == b.x) return a.y1 < b.y1;
    return a.x < b.x;
}

bool cmp2(Line2 a, Line2 b) {
    if (a.y == b.y) return a.x1 < b.x1;
    return a.y < b.y;
}

int main() {
    int n, x1, y1, x2, y2;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        line1[2 * i] = Line1(x1, y1, y2, 1);
        line1[2 * i + 1] = Line1(x2, y1, y2, -1);
        Y[2*i] = y1, Y[2*i+1] = y2;
        
        line2[2 * i] = Line2(y1, x1, x2, 1);
        line2[2 * i + 1] = Line2(y2, x1, x2, -1);
        X[2*i] = x1, X[2*i+1] = x2;
    }
    sort(X, X + 2 * n), sort(Y, Y + 2 * n);
    sort(line1, line1 + 2 * n, cmp1);
    sort(line2, line2 + 2 * n, cmp2);
    int cnt = (int)(unique(Y, Y + 2 * n) - Y), last = 0, ans = 0;
    for (int i = 0; i < 2 * n; ++i) {
        int l = (int)(lower_bound(Y, Y + cnt, line1[i].y1) - Y) + 1;
        int r = (int)(lower_bound(Y, Y + cnt, line1[i].y2) - Y);
        update(1, cnt - 1, l, r, line1[i].flag, 1, 1);
        ans += abs(len[1] - last);
        last = len[1];
        //printf("%d\n", len[1]);
    }
    memset(tree, 0, sizeof(tree));
    memset(len, 0, sizeof(len));
    //printf("%d\n", ans);
    cnt = (int)(unique(X, X + 2 * n) - X), last = 0;
    for (int i = 0; i < 2 * n; ++i) {
        int l = (int)(lower_bound(X, X + cnt, line2[i].x1) - X) + 1;
        int r = (int)(lower_bound(X, X + cnt, line2[i].x2) - X);
        update(1, cnt - 1, l, r, line2[i].flag, 1, 2);
        ans += abs(len[1] - last);
        last = len[1];
        //printf("%d\n", len[1]);
    }
    printf("%d\n", ans);
    return 0;
}


// hdu 1542 扫描线
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e3;
const double eps = 1e-8;
struct Line {
    double x, y1, y2;
    int flag; // 1 左 -1 右
} line[maxn];
double Y[maxn];
int tree[maxn << 2];
double len[maxn << 2];

bool cmp(Line a, Line b) {
    if (fabs(a.x - b.x) < eps) return a.y2 < b.y2;
    return a.x < b.x;
}

void update(int l, int r, int L, int R, int C, int now) {
    if (l >= L && r <= R) {
        tree[now] += C;
        if (tree[now]) len[now] = Y[r] - Y[l-1];
        else len[now] = len[now << 1] + len[(now << 1)|1];
        return;
    }
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
    if (tree[now]) len[now] = Y[r] - Y[l-1];
    else len[now] = len[now << 1] + len[(now << 1)|1];
}

int main() {
    int n, ca = 1;
    double x1, y1, x2, y2;
    while (~scanf("%d", &n) && n) {
        int cnt = 0;
        memset(tree, 0, sizeof(tree));
        memset(len, 0, sizeof(len));
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            line[cnt].x = x1, line[cnt].y1 = y1, line[cnt].y2 = y2;
            Y[cnt] = y1;
            line[cnt++].flag = 1;
            line[cnt].x = x2, line[cnt].y1 = y1, line[cnt].y2 = y2;
            Y[cnt] = y2;
            line[cnt++].flag = -1;
        }
        sort(line, line + cnt, cmp);
        sort(Y, Y + cnt);
        cnt = int(unique(Y, Y + cnt) - Y);
        double ans = 0;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int l = (int)(lower_bound(Y, Y + cnt, line[i].y1) - Y) + 1;
            int r = (int)(lower_bound(Y, Y + cnt, line[i].y2) - Y);
            update(1, cnt - 1, l, r, line[i].flag, 1);
            ans += len[1] * (line[i+1].x - line[i].x);
        }
        printf("Test case #%d\n", ca++);
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}


// poj 2777
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int tree[maxn << 2], lazy[maxn << 2];

void pushdown(int now) {
    if (lazy[now]) {
        tree[now << 1] = tree[(now << 1)|1] = tree[now];
        lazy[now << 1] = lazy[(now << 1)|1] = lazy[now];
        lazy[now] = 0;
    }
}

void update(int l, int r, int L, int R, int C, int now) {
    if (l >= L && r <= R) {
        tree[now] = 1 << C;
        lazy[now] = C;
        return;
    }
    pushdown(now);
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
    tree[now] = tree[now << 1] | tree[(now << 1)|1];
}

int query(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        return tree[now];
    }
    pushdown(now);
    int m = (l + r) / 2;
    int ans = 0;
    if (m >= L) ans = query(l, m, L, R, now << 1);
    if (m < R) ans |= query(m + 1, r, L, R, (now << 1)|1);
    return ans;
}

int main() {
    
    int n, m, o, l, r, c;
    char s[10];
    
    while (~scanf("%d%d%d", &n, &o, &m)) {
        fill(tree, tree + (maxn << 2), 2);
        
        while (m--) {
            scanf("%s%d%d", s, &l, &r);
            if (l > r) swap(l, r);
            
            if (s[0] == 'C') {
                // 涂色
                scanf("%d", &c);
                update(1, n, l, r, c, 1);
            } else {
                int ans = query(1, n, l, r, 1), ret = 0;
                while (ans) {
                    ans = ans & (ans - 1);
                    ++ret;
                }
                printf("%d\n", ret);
            }
        }

    }
    return 0;
}


// hdu 4578
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn = 1e5, mod = 10007;

LL tree[4][maxn << 2];
LL lazy_add[maxn << 2], lazy_mult[maxn << 2], lazy_c[maxn << 2];

void update_add(int son, LL c, int si) {
    c %= mod;
    lazy_add[son] = (lazy_add[son] + c) % mod;
    tree[3][son] += c*c%mod*c%mod*si%mod + 3*c%mod*c%mod*tree[1][son]%mod + 3*tree[2][son]%mod*c%mod;
    tree[3][son] %= mod;
    tree[2][son] += c*c%mod*si%mod + tree[1][son]*c%mod*2%mod;
    tree[2][son] %= mod;
    tree[1][son] += c*si%mod;
    tree[1][son] %= mod;
}

void update_mult(int son, LL c) {
    c %= mod;
    lazy_mult[son] = lazy_mult[son] * c % mod;
    lazy_add[son] = lazy_add[son] * c % mod;
    
    tree[1][son] = tree[1][son] * c % mod;
    tree[2][son] = tree[2][son] * c % mod * c % mod;
    tree[3][son] = tree[3][son] * c % mod * c % mod * c % mod;
}

void update_c(int son, LL c, int si) {
    c %= mod;
    lazy_c[son] = c;
    lazy_mult[son] = 1;
    lazy_add[son] = 0;
    tree[1][son] = c * si % mod;
    tree[2][son] = c * c % mod * si % mod;
    tree[3][son] = c * c % mod * c % mod * si % mod;
}

void pushdown(int ln, int rn, int now) {
    if (lazy_c[now]) {
        update_c(now << 1, lazy_c[now], ln);
        update_c((now << 1)|1, lazy_c[now], rn);
        lazy_c[now] = 0;
    }
    if (lazy_mult[now] != 1) {
        update_mult(now << 1, lazy_mult[now]);
        update_mult((now << 1)|1, lazy_mult[now]);
        lazy_mult[now] = 1;
    }
    if (lazy_add[now]) {
        update_add(now << 1, lazy_add[now], ln);
        update_add((now << 1)|1, lazy_add[now], rn);
        lazy_add[now] = 0;
    }
}

void pushup(int now) {
    for (int i = 1; i <= 3; ++i) {
        tree[i][now] = (tree[i][now << 1] + tree[i][(now << 1)|1]) % mod;
    }
}

void update(int l, int r, int L, int R, int C, int now, int type) {
    if (l >= L && r <= R) {
        if (type == 1) {
            //printf("now %d %lld\n", now, tree[3][now]);
            tree[3][now] += C * C % mod * C % mod * (r - l + 1) % mod + 3 * C % mod * C % mod * tree[1][now] % mod + 3 * tree[2][now] * C % mod;
            tree[3][now] %= mod;
            tree[2][now] += C * C % mod * (r - l + 1) % mod + 2 * tree[1][now] * C % mod;
            tree[2][now] %= mod;
            tree[1][now] += C * (r - l + 1) % mod;
            tree[1][now] %= mod;
            //printf("now %d %lld\n", now, tree[3][now]);
            lazy_add[now] = (lazy_add[now] + C) % mod;
        } else if (type == 2) {
            tree[3][now] = C * C % mod * C % mod * tree[3][now] % mod;
            tree[2][now] = C * C % mod * tree[2][now] % mod;
            tree[1][now] = tree[1][now] * C % mod;
            lazy_mult[now] = lazy_mult[now] * C % mod;
            lazy_add[now] = lazy_add[now] * C % mod;
        } else {
            tree[1][now] = C * (r - l + 1) % mod;
            tree[2][now] = C * C % mod * (r - l + 1) % mod;
            tree[3][now] = C * C % mod * C % mod * (r - l + 1) % mod;
            lazy_c[now] = C;
            lazy_mult[now] = 1;
            lazy_add[now] = 0;
        }
        return;
    }
    int m = (l + r) / 2;
    pushdown(m - l + 1, r - m, now);
    if (m >= L) update(l, m, L, R, C, now << 1, type);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1, type);
    pushup(now);
}

LL query(int l, int r, int L, int R, int p, int now) {
    if (l >= L && r <= R) {
        return tree[p][now];
    }
    int m = (l + r) / 2;
    LL ans = 0;
    pushdown(m - l + 1, r - m, now);
    if (m >= L) ans += query(l, m, L, R, p, now << 1);
    if (m < R) ans = (ans + query(m + 1, r, L, R, p, (now << 1)|1)) % mod;
    
    return ans;
}

int main() {
    int n, q, com, l, r, c;
    //freopen("/Users/admin/Desktop/in.txt", "r", stdin);
    //freopen("/Users/admin/Desktop/out.txt", "w", stdout);
    while (~scanf("%d%d", &n, &q) && (n + q)) {
        memset(tree, 0, sizeof(tree));
        memset(lazy_add, 0, sizeof(lazy_add));
        memset(lazy_c, 0, sizeof(lazy_c));
        fill(lazy_mult, lazy_mult + (maxn << 2), 1);
        for (int i = 0; i < q; ++i) {
            scanf("%d%d%d%d", &com, &l, &r, &c);
            if (com != 4) {
                //printf("1 %lld\n", tree[2][2]);
                update(1, n, l, r, c, 1, com);
            } else {
                printf("%lld\n", query(1, n, l, r, c, 1) % mod);
            }
        }
    }
    return 0;
}


// zoj 1610
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5;
int left[maxn], right[maxn], color[maxn], tree[maxn << 2];
int ans[maxn], last;

void update(int l, int r, int L, int R, int C, int now) {
    if (l >= L && r <= R) {
        tree[now] = C;
        return;
    }
    if (tree[now] != -1) {
        tree[now << 1] = tree[(now << 1)|1] = tree[now];
        tree[now] = -1;
    }
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
}

void query(int l, int r, int now) {
    if (l > r) {
        return;
    }
    if (l == r || tree[now] != -1) {
        //printf("[%d, %d]  %d\n", l, r, tree[now]);
        if (tree[now] != last) {
            ++ans[tree[now]];
            last = tree[now];
        }
        return;
    }
    int m = (l + r) / 2;
    query(l, m, now << 1);
    query(m + 1, r, (now << 1)|1);
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        if (n == 0) {
            printf("\n");
            continue;
        }
        int Min = 0x3fffffff, Max = -1;
        int min_c = 0x3fffffff, max_c = -1;
        memset(tree, -1, sizeof(tree));
        memset(ans, -1, sizeof(ans));
        
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d", &left[i], &right[i], &color[i]);
            ++left[i];
            Min = min(Min, left[i]), Max = max(Max, right[i]);
            min_c = min(min_c, color[i]), max_c = max(max_c, color[i]);
        }
        for (int i = 1; i <= n; ++i) {
            update(Min, Max, left[i], right[i], color[i], 1);
        }
        last = -1;
        query(Min, Max, 1);
        for (int i = min_c; i <= max_c; ++i) {
            if (ans[i] + 1 > 0) printf("%d %d\n", i, ans[i] + 1);
        }
        printf("\n");
    }
    return 0;
}


// hdu 1540
#include <cstdio>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 50010, inf = 0x3fffffff;
int Min[maxn << 2], Max[maxn << 2];

void update_Min(int l, int r, int tar, int C, int now) {
    if (l == r) {
        Min[now] = C;
        //printf("Min now:%d Min[now]:%d\n", now, Min[now]);
        return;
    }
    int m = (l + r) / 2;
    if (tar <= m) update_Min(l, m, tar, C, now << 1);
    else update_Min(m + 1, r, tar, C, (now << 1)|1);
    Min[now] = min(Min[now << 1], Min[(now << 1)|1]);
    //printf("Min now:%d Min[now]:%d\n", now, Min[now]);
}

void update_Max(int l, int r, int tar, int C, int now) {
    if (l == r) {
        Max[now] = C;
        //printf("Max now:%d Max[now]:%d\n", now, Max[now]);
        return;
    }
    int m = (l + r) / 2;
    if (tar <= m) update_Max(l, m, tar, C, now << 1);
    else update_Max(m + 1, r, tar, C, (now << 1)|1);
    Max[now] = max(Max[now << 1], Max[(now << 1)|1]);
    //printf("Max now:%d Max[now]:%d\n", now, Max[now]);
}

int query_Min(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        //printf("Min now:%d Min[now]:%d\n", now, Min[now]);
        return Min[now];
    }
    int m = (l + r) / 2;
    int ans = inf;
    if (m >= L) ans = query_Min(l, m, L, R, now << 1);
    if (m < R) ans = min(ans, query_Min(m + 1, r, L, R, (now << 1)|1));
    return ans;
}

int query_Max(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        //printf("Max now:%d Max[now]:%d\n", now, Max[now]);
        return Max[now];
    }
    int m = (l + r) / 2;
    int ans = -inf;
    if (m >= L) {
        ans = query_Max(l, m, L, R, now << 1);
    }
    if (m < R) {
        int tmp = query_Max(m + 1, r, L, R, (now << 1)|1);
        ans = max(ans, tmp);
    }
    return ans;
}

int main() {
    int n, q, x;
    char s[100];
    while (~scanf("%d%d", &n, &q)) {
        fill(Min, Min + (maxn << 2), n + 1);
        fill(Max, Max + (maxn << 2), 0);
        stack<int> stack;
        while (q--) {
            scanf("%s", s);
            if (s[0] == 'D') {
                // 删除
                scanf("%d", &x);
                stack.push(x);
                update_Min(1, n, x, x, 1);
                update_Max(1, n, x, x, 1);
            } else if (s[0] == 'R') {
                // 恢复
                int tmp = stack.top();
                stack.pop();
                update_Min(1, n, tmp, n + 1, 1);
                update_Max(1, n, tmp, 0, 1);
            } else {
                // 询问
                scanf("%d", &x);
                int a = query_Min(1, n, x, n, 1);
                int b = query_Max(1, n, 1, x, 1);
                if (a == b) {
                    printf("0\n");
                } else {
                    printf("%d\n", a - b - 1);
                }
            }
        }
    }
    return 0;
}


// hdu 4027
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100010;

LL arr[maxn], tree[maxn << 2];

void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

void update(int l, int r, int L, int R, int now) {
    if (l == r) {
        //tree[now] = (int)(sqrt((double)tree[now]) + 0.5);
        tree[now] = (int)(sqrt((double)tree[now]));
        //printf("i %d %lld\n", l, tree[now]);
        return;
    }
    if (r - l + 1 == tree[now]) {
        return;
    }
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, now << 1);
    if (m < R) update(m + 1, r, L, R, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

LL query(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        return tree[now];
    }
    int m = (l + r) / 2;
    LL ans = 0;
    if (m >= L) ans += query(l, m, L, R, now << 1);
    if (m < R) ans += query(m + 1, r, L, R, (now << 1)|1);
    return ans;
}

int main() {
    int n, q, com, x, y, ca = 1;
    while (~scanf("%d", &n)) {
        printf("Case #%d:\n", ca++);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &arr[i]);
        }
        build(1, n, 1);
        scanf("%d", &q);
        while (q--) {
            scanf("%d%d%d", &com, &x, &y);
            if (x > y) {
                swap(x, y);
            }
            if (com == 0) {
                update(1, n, x, y, 1);
            } else {
                printf("%lld\n", query(1, n, x, y, 1));
            }
        }
        printf("\n");
    }
    return 0;
}


// poj 3264
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 51000;
int arr[maxn];

struct node {
    int Min, Max;
} tree[maxn << 2];

void build(int l, int r, int now) {
    if (l == r) {
        tree[now].Min = tree[now].Max = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    tree[now].Min = min(tree[now << 1].Min, tree[(now << 1)|1].Min);
    tree[now].Max = max(tree[now << 1].Max, tree[(now << 1)|1].Max);
}

int query_min(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        //printf("min %d %d\n", l, tree[now].Min);
        return tree[now].Min;
    }
    int m = (l + r) / 2, ans = 0x3fffffff;
    if (m >= L) ans = query_min(l, m, L, R, now << 1);
    if (m < R) ans = min(ans, query_min(m + 1, r, L, R, (now << 1)|1));
    return ans;
}

int query_max(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        //printf("max %d %d\n", l, tree[now].Max);
        return tree[now].Max;
    }
    int m = (l + r) / 2, ans = 0;
    if (m >= L) ans = query_max(l, m, L, R, now << 1);
    if (m < R) ans = max(ans, query_max(m + 1, r, L, R, (now << 1)|1));
    return ans;
}

int main() {
    int n, q, x, y;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    build(1, n, 1);
    while (q--) {
        scanf("%d%d", &x, &y);
        //int a = query_max(1, n, x, y, 1);
        //int b = query_min(1, n, x, y, 1);
        //printf("%d - %d\n", a, b);
        printf("%d\n", query_max(1, n, x, y, 1) - query_min(1, n, x, y, 1));
    }
    return 0;
}


// hdu 1698
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 100010;
int arr[maxn], tree[maxn << 2], lazy[maxn << 2];

void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

void pushdown(int ln, int rn, int now) {
    if (lazy[now]) {
        lazy[now << 1] = lazy[(now << 1)|1] = lazy[now];
        tree[now << 1] = lazy[now] * ln;
        tree[(now << 1)|1] = lazy[now] * rn;
        lazy[now] = 0;
    }
}

void update(int l, int r, int L, int R, int C, int now) {
    if (l >= L && r <= R) {
        tree[now] = C * (r - l + 1);
        lazy[now] = C;
        return;
    }
    int m = (l + r) / 2;
    pushdown(m - l + 1, r - m, now);
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

int main() {
    int t, n, q, x, y, c, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &q);
        fill(arr, arr + n + 1, 1);
        memset(lazy, 0, sizeof(lazy));
        build(1, n, 1);
        while (q--) {
            scanf("%d%d%d", &x, &y, &c);
            update(1, n, x, y, c, 1);
        }
        printf("Case %d: The total value of the hook is %d.\n", ca++, tree[1]);
    }
    return 0;
}


// poj 2528
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010;
int left[maxn], right[maxn], tree[maxn << 2];
int arr[maxn], vis[maxn];

void update(int l, int r, int L, int R, int now, int C) {
    if (l >= L && r <= R) {
        tree[now] = C;
        return;
    }
    if (tree[now]) {
        tree[now << 1] = tree[(now << 1)|1] = tree[now];
        tree[now] = 0;
    }
    int m = (l + r) / 2;
    if (m >= L) update(l, m, L, R, now << 1, C);
    if (m < R) update(m + 1, r, L, R, (now << 1)|1, C);
}

void query(int l, int r, int now) {
    if (l > r) {
        return;
    }
    if (l == r || tree[now] != 0) {
        //printf("[%d, %d] %d\n", l, r, tree[now]);
        vis[tree[now]] = 1;
        return;
    }
    int m = (l + r) / 2;
    query(l, m, now << 1);
    query(m + 1, r, (now << 1)|1);
}

int main() {
    int t, n, cnt, ans;
    scanf("%d", &t);
    while (t--) {
        cnt = ans = 0;
        memset(tree, 0, sizeof(tree));
        memset(vis, 0, sizeof(vis));
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &left[i], &right[i]);
            arr[cnt++] = left[i], arr[cnt++] = right[i];
        }
        sort(arr, arr + cnt);
        cnt = (int)(unique(arr, arr + cnt) - arr);
        for (int i = 1; i <= n; ++i) {
            int L = (int)(lower_bound(arr, arr + cnt, left[i]) - arr) + 1;
            int R = (int)(lower_bound(arr, arr + cnt, right[i]) - arr) + 1;
            update(1, cnt, L, R, 1, i);
        }
        query(1, cnt, 1);
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) ++ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}


// poj 3468
#include <cstdio>
using namespace std;
const int maxn = 100010;
typedef long long LL;
LL arr[maxn], tree[maxn << 2], lazy[maxn << 2];

void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

void pushdown(int ln, int rn, int now) {
    if (lazy[now] != 0) {
        lazy[now << 1] += lazy[now];
        lazy[(now << 1)|1] += lazy[now];
        tree[now << 1] += ln * lazy[now];
        tree[(now << 1)|1] += rn * lazy[now];
        lazy[now] = 0;
    }
}

LL query(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        return tree[now];
    }
    int m = (l + r) / 2;
    pushdown(m - l + 1, r - m, now);
    LL ans = 0;
    if (m >= L) ans += query(l, m, L, R, now << 1);
    if (m < R) ans += query(m + 1, r, L, R, (now << 1)|1);
    return ans;
}

void update(int l, int r, int L, int R, int C, int now) {
    if (l >= L && r <= R) {
        tree[now] += C * (r - l + 1);
        lazy[now] += C;
        return;
    }
    int m = (l + r) / 2;
    pushdown(m - l + 1, r - m, now);
    if (m >= L) update(l, m, L, R, C, now << 1);
    if (m < R) update(m + 1, r, L, R, C, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

int main() {
    int n, q, x, y, a;
    char s[100];
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &arr[i]);
    }
    build(1, n, 1);
    while (q--) {
        scanf("%s%d%d", s, &x, &y);
        if (s[0] == 'Q') {
            printf("%lld\n", query(1, n, x, y, 1));
        } else {
            scanf("%d", &a);
            update(1, n, x, y, a, 1);
        }
    }
    return 0;
}


// hdu 1754
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200010;
int arr[maxn], tree[maxn << 2];

void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    tree[now] = max(tree[now << 1], tree[(now << 1)|1]);
}

int query(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        return tree[now];
    }
    int m = (l + r) / 2, ans = -1;
    if (m >= L) ans = query(l, m, L, R, now << 1);
    if (m < R) {
        ans = max(ans, query(m + 1, r, L, R, (now << 1)|1));
    }
    return ans;
}

void update(int l, int r, int tar, int C, int now) {
    if (l == r) {
        tree[now] = C;
        return;
    }
    int m = (l + r) / 2;
    if (tar <= m) {
        update(l, m, tar, C, now << 1);
    } else {
        update(m + 1, r, tar, C, (now << 1)|1);
    }
    tree[now] = max(tree[now << 1], tree[(now << 1)|1]);
}

int main() {
    int n, m, x, y;
    char s[20];
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        build(1, n, 1);
        while (m--) {
            scanf("%s%d%d", s, &x, &y);
            if (s[0] == 'Q') {
                printf("%d\n", query(1, n, x, y, 1));
            } else {
                update(1, n, x, y, 1);
            }
            
        }
    }
    return 0;
}


// hdu 1166
#include <cstdio>
using namespace std;
const int maxn = 50010;
int arr[maxn], tree[maxn << 2];

void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

void add(int l, int r, int tar, int C, int now) {
    if (l == r) {
        tree[now] += C;
        return;
    }
    int m = (l + r) / 2;
    if (tar <= m) {
        add(l, m, tar, C, now << 1);
    } else {
        add(m + 1, r, tar, C, (now << 1)|1);
    }
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

int query(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        return tree[now];
    }
    int m = (l + r) / 2, ans = 0;
    if (m >= L) ans += query(l, m, L, R, now << 1);
    if (m < R) ans += query(m + 1, r, L, R, (now << 1)|1);
    return ans;
}

int main(int argc, const char * argv[]) {
    int t, n, x, y, ca = 1;
    scanf("%d", &t);
    char com[100];
    while (t--) {
        printf("Case %d:\n", ca++);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        build(1, n, 1);
        while (scanf("%s", com) && com[0] != 'E') {
            scanf("%d%d", &x, &y);
            if (com[0] == 'Q') {
                printf("%d\n", query(1, n, x, y, 1));
            } else if (com[0] == 'A') {
                add(1, n, x, y, 1);
            } else {
                add(1, n, x, -y, 1);
            }
        }
    }
    return 0;
}
*/
