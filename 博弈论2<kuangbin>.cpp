//
//  main.cpp
//  博弈论2<kuangbin>
//
//  Created by admin on 18/11/7.
//  Copyright © 2018年 Amon. All rights reserved.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int head[maxn], dep[maxn], cycle[maxn], vis[maxn], cnt, num;
struct Edge {
    int to, next;
} edge[maxn << 2];

struct node {
    int a, b;
} Map[maxn];

bool operator == (node a, node b) {
    return (a.a == b.a && a.b == b.b) || (a.a == b.b && a.b == b.a);
}

bool cmp(node a, node b) {
    if (a.a == b.a) return a.b < b.b;
    return a.a < b.a;
}

void insert(int x, int y) {
    edge[cnt].to = y, edge[cnt].next = head[x];
    head[x] = cnt++;
    edge[cnt].to = x, edge[cnt].next = head[y];
    head[y] = cnt++;
}

void find_dfs_num(int now, int fa) {
    vis[now] = 1;
    dep[now] = dep[fa] + 1;
    for (int i = head[now]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (to == fa) continue;
        if (vis[to]) {
            cycle[to] = 1;
        } else {
            find_dfs_num(to, now);
        }
    }
}

int dfs(int now, int fa) {
    vis[now] = 1;
    int ans = 0;
    for (int i = head[now]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (to == fa || vis[to]) continue;
        //printf("%d %d\n", now, to);
        if (cycle[to] == 0) ans ^= dfs(to, now) + 1;
        else {
            int kkk = 0;
            for (int j = head[to]; ~j; j = edge[j].next) {
                vis[to] = 0;
                if (vis[edge[j].to]) continue;
                vis[edge[j].to] = 1;
                //printf("%d\n", edge[j].to);
                int d = 1, tmp = j;
                while (edge[tmp].to != to) {
                    for (int k = head[edge[tmp].to]; ~k; k = edge[k].next) {
                        if (vis[edge[k].to] == 0) {
                            //vis[edge[k].to] = 1;
                            tmp = k;
                            break;
                        }
                    }
                    
                    ++d;
                    vis[edge[tmp].to] = 1;
                    //printf("%d\n", edge[tmp].to);
                }
                kkk ^= d % 2 == 0 ? 0 : 1;
            }
            ans ^= kkk + 1;
        }
    }
    return ans;
}

void init() {
    cnt = num = 0;
    memset(head, -1, sizeof(head));
    memset(cycle, 0, sizeof(cycle));
    memset(dep, 0, sizeof(dep));
    memset(vis, 0, sizeof(vis));
}

int main() {
    int k, a, b, n, m;
    while (~scanf("%d", &k)) { // k 棵树
        long long int ans = 0;
        while (k--) {
            init();
            scanf("%d%d", &n, &m);
            for (int i = 0; i < m; ++i) {
                scanf("%d%d", &a, &b);
                insert(a, b);
                //if (a > b) swap(a, b);
                //Map[i].a = a, Map[i].b = b;
            }
            //sort(Map, Map + m, cmp);
            //m = (int)(unique(Map, Map + m) - Map);
            //for (int i = 0; i < m; ++i) {
                //insert(Map[i].a, Map[i].b);
            //}
            find_dfs_num(1, 0);
//            for (int i = 1; i <= n; ++i) {
//                printf("%d %d\n", i, cycle[i]);
//            }
            memset(vis, 0, sizeof(vis));
            ans ^= dfs(1, 0);
            printf("%lld\n", ans);
        }
        if (ans) printf("Sally\n");
        else printf("Harry\n");
    }
    return 0;
}
/*
1
18 20
1 2
2 8
8 9
2 3
3 4
3 5
5 6
6 7
2 10
10 11
10 12
12 13
12 14
14 15
13 16
16 17
17 18
13 18
6 5
10 2

1
15 14
1 2
2 8
8 9
2 3
3 4
3 5
5 6
6 7
2 10
10 11
10 12
12 13
12 14
14 15

2
2 5
1 2
1 2
2 1
2 1
1 2
4 8
1 2
2 3
2 4
3 4
1 2
2 3
1 2
2 3



#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1010;
struct Edge {
    int to, next;
} edge[maxn << 2];

int head[maxn];
int cnt;

void insert(int x, int y) {
    edge[cnt] = {y, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, head[y]};
    head[y] = cnt++;
}

int dfs(int now, int fa) {
    int ans = 0;
    for (int i = head[now]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (to == fa) continue;
        //printf("%d %d\n", now, to);
        ans ^= dfs(to, now) + 1;
    }
    return ans;
}

int main() {
    int t, k, a, b, root, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &k); // k棵树
        long long int ans = 0;
        while (k--) {
            cnt = 0;
            memset(head, -1, sizeof(head));
            scanf("%d%d", &n, &root);
            --n;
            while (n--) {
                scanf("%d%d", &a, &b);
                insert(a, b);
            }
            ans ^= dfs(root, -1);
        }
        if (ans) printf("The first player wins\n");
        else printf("The second player wins\n");
    }
    return 0;
}

#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1010;
struct Edge {
    int to, w, next;
} edge[maxn << 2];

int head[maxn];
int cnt;

void insert(int x, int y, int w) {
    edge[cnt] = {y, w, head[x]};
    head[x] = cnt++;
    edge[cnt] = {x, w, head[y]};
    head[y] = cnt++;
}

int dfs(int now, int fa) {
    int ans = 0;
    for (int i = head[now]; ~i; i = edge[i].next) {
        int to = edge[i].to, w = edge[i].w;
        if (to == fa) continue;
        //printf("%d %d\n", now, to);
        ans ^= dfs(to, now) + w;
    }
    return ans;
}

int main() {
    int t, k, a, b, w, ca = 1;
    scanf("%d", &t);
    while (t--) {
        cnt = 0;
        memset(head, -1, sizeof(head));
        scanf("%d", &k);
        k--;
        while (k--) {
            scanf("%d%d%d", &a, &b, &w);
            insert(a, b, w);
        }
        int ans = dfs(0, -1);
        if (ans) printf("Case %d: Emily\n", ca++);
        else printf("Case %d: Jolly\n", ca++);
    }
    return 0;
}


#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 300;
int sg[maxn][2][2], vis[maxn], X[maxn];

void init() {
    
    for (int i = 1; i < maxn; i++) {
        for (int l = 0; l <= 1; ++l) {
            for (int r = 0; r <= 1; ++r) {
                memset(vis, 0, sizeof vis);
                for (int j = 1; j <= i; j++) {
                    int t = sg[i - j][l][1];
                    t ^= sg[j - 1][1][r];
                    vis[t] = 1;
                }
                for (int j = 0; j < maxn; j++) {
                    if (vis[j] == 0) {
                        sg[i][l][r] = j;
                        //printf("%d %d\n", i, j);
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    init();
    char s[300];
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int ans = 0, cnt = 0;
        int now;
        for (now = 0; s[now]; ++now) {
            if (s[now] == 'X') X[cnt++] = now;
        }
        if (cnt == 0) {
            ans ^= sg[now][0][0];
            if (ans == 0) printf("0\n");
            else {
                for (int i = 0; s[i]; ++i) {
                    if ((sg[i][0][1] ^ sg[now - i - 1][1][0]) == 0) {
                        printf("%d ", i + 1);
                    }
                }
                printf("\n");
            }
        } else {
            int size = (int)strlen(s);
            ans ^= sg[X[0]][0][1];
            for (int i = 1; i < cnt; ++i) {
                ans ^= sg[X[i] - X[i - 1] - 1][1][1];
            }
            ans ^= sg[size - X[cnt-1] - 1][1][0];
            
            if (ans == 0) printf("0\n");
            else {
                for (int i = 0; i < X[0]; ++i) {
                    int r = X[0] - i - 1;
                    if ((ans ^ sg[X[0]][0][1] ^ sg[i][0][1] ^ sg[r][1][1]) == 0) {
                        printf("%d ", i + 1);
                    }
                }
                for (int i = 0; i < cnt; ++i) {
                    int len = X[i] - X[i-1] - 1;
                    for (int j = X[i-1] + 1; j < X[i]; ++j) {
                        int l = j - X[i-1] - 1;
                        int r = X[i] - j - 1;
                        if ((ans ^ sg[len][1][1] ^ sg[l][1][1] ^ sg[r][1][1]) == 0) {
                            printf("%d ", j + 1);
                        }
                    }
                }
                for (int i = X[cnt-1] + 1; i < size; ++i) {
                    int l = i - X[cnt-1] - 1;
                    int r = size - 1 - i - 1;
                    if ((ans ^ sg[size - X[cnt-1]][1][0] ^ sg[l][1][1] ^ sg[r][1][0]) == 0) {
                        printf("%d ", i + 1);
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}


// LightOJ - 1393
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int t, n, m, x, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        long long int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &x);
                if ((n - i + m - j) % 2) {
                    ans ^= x;
                }
            }
        }
        if (ans) printf("Case %d: win\n", ca++);
        else printf("Case %d: lose\n", ca++);
    }
    return 0;
}


// LightOJ - 1344
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 55;
int sg[maxn][maxn]; // 当前手镯 i-j区间的 sg 值
int arr[maxn][maxn], num[maxn]; // 存储每个手镯的权值，每个手镯有多少个珠子
int sgtmp[maxn]; // 第 i 个手镯的 sg 值
int ret[maxn][maxn];  // 去掉第 i 个手镯的第 j 个珠子后，这个手镯的 sg 值

struct node {
    int x, y;
} output[maxn * maxn]; // 存储最后的输出答案

bool operator == (node a, node b) {
    return a.x == b.x && arr[a.x][a.y] == arr[b.x][b.y];
}

bool cmp(node a, node b) {
    if (a.x == b.x) {
        return arr[a.x][a.y] < arr[b.x][b.y];
    }
    return a.x < b.x;
}

int dfs(int now, int l, int r) { // 查找 sg 值
    if (l > r) return 0;
    if (l == r) return sg[l][r] = 1; // 只有一颗珠子，直接取走，必赢
    
    if (sg[l][r] != -1) return sg[l][r]; // 已找过
    
    int vis[maxn]; // 不可为全局变量
    memset(vis, 0, sizeof(vis));
    
    for (int i = l; i <= r; ++i) { // 挑选下标为i处的珠子
        int tmp = 0, last = -1;
        
        // 找到第一颗小于当前权值的珠子
        for (int j = l; j <= r; ++j) {
            if (arr[now][j] < arr[now][i]) {
                last = j; break;
            }
        }
        
        // last 为 -1时，代表已找不到
        for (int j = last + 1; j <= r && last != -1; ++j) {
            if (arr[now][j] >= arr[now][i]) {
                tmp ^= dfs(now, last, j - 1);
                last = -1;
                for (int k = j + 1; k <= r; ++k) {
                    if (arr[now][k] < arr[now][i]) {
                        last = j = k;
                        break;
                    }
                }
            }
        }
        // 这个手镯的最后一段没被搜索
        if (last != -1) {
            tmp ^= dfs(now, last, r);
        }
        vis[tmp] = 1;
        // 记录下来，方便后面输出
        if (l == 1 && r == num[now]) ret[now][i] = tmp;
        //        if (l == 1 && r == num[now]) {
        //            printf("%d %d %d\n", now, i, tmp);
        //        }
    }
    
    for (int i = 0; ; ++i) {
        if (vis[i] == 0) {
            sg[l][r] = i;
            return i;
        }
    }
    return -1;
}

int main() {
    int t, k, ca = 1;
    scanf("%d", &t);
    while (t--) {
        int ans = 0;
        scanf("%d", &k);
        for (int i = 1; i <= k; ++i) {
            memset(sg, -1, sizeof(sg));
            scanf("%d", &num[i]);
            for (int j = 1; j <= num[i]; ++j) {
                scanf("%d", &arr[i][j]);
            }
            sgtmp[i] = dfs(i, 1, num[i]);
            //printf("%d\n", sgtmp[i]);
            ans ^= sgtmp[i];
            //            for (int i = 1; i <= num[i]; ++i) {
            //                for (int j = i; j <= num[i]; ++j) {
            //                    printf("%d %d %d\n", i, j, sg[i][j]);
            //                }
            //            }
        }
        if (ans == 0) printf("Case %d: Genie\n", ca++);
        else {
            int cnt = 0;
            printf("Case %d: Aladdin\n", ca++);
            memset(output, 0, sizeof(output));
            for (int i = 1; i <= k; ++i) {
                for (int j = 1; j <= num[i]; ++j) {
                    
                    if ((ans ^ sgtmp[i] ^ ret[i][j]) == 0) {
                        //printf("(%d %d)", i, arr[i][j]);
                        output[cnt++] = {i, j};
                    }
                }
            }
            // 排序并去重，输出
            sort(output, output + cnt, cmp);
            cnt = (int)(unique(output, output + cnt) - output);
            for (int i = 0; i < cnt; ++i) {
                printf("(%d %d)", output[i].x, arr[output[i].x][output[i].y]);
            };
            printf("\n");
        }
    }
    return 0;
}


// LightOJ 1401
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 110;

int sg[maxn][3][3]; // 0->.  1->O  2->X
int vis[maxn];

void init() {
    for (int i = 1; i < maxn; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                memset(vis, 0, sizeof(vis));
                for (int pos = 1; pos <= i; ++pos) {
                    if (!((pos == 1 && j == 1)
                          || (i == pos && 1 == k))) {
                        vis[sg[pos - 1][j][1] ^ sg[i - pos][1][k]] = 1;
                        //printf("%d %d\n", sg[pos - 1][j][1], sg[i - pos][1][k]);
                    }
                    if (!((pos == 1 && j == 2)
                          || (i == pos && k == 2))) {
                        vis[sg[pos - 1][j][2] ^ sg[i - pos][2][k]] = 1;
                        //printf("%d %d\n", sg[pos - 1][j][2], sg[i - pos][2][k]);
                    }
                }
                for (int t = 0; ; ++t) {
                    if (vis[t] == 0) {
                        sg[i][j][k] = t;
                        //if (j > 0 && k > 0) printf("%d %d %d %d\n", i, j, k, t);
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    init();
    int t, ca = 1;
    char s[maxn];
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int num = 0, last = 0, lc = 0, ans = 0;
        for (int i = 0; s[i]; ++i) {
            if (s[i] != '.') {
                ++num;
                int nowc = s[i] == 'O' ? 1 : 2;
                ans ^= sg[i - last][lc][nowc];
                lc = nowc, last = i + 1;
            }
        }
        ans ^= sg[strlen(s) - last][lc][0];
        if (num % 2 == 0) {
            if (ans == 0) printf("Case %d: No\n", ca++);
            else printf("Case %d: Yes\n", ca++);
        } else {
            if (ans != 0) printf("Case %d: No\n", ca++);
            else printf("Case %d: Yes\n", ca++);
        }
    }
    return 0;
}


// LightOJ 1199
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e4 + 10;
int sg[maxn], vis[maxn];

void init() {
    for (int i = 3; i < maxn; ++i) {
        memset(vis, 0, sizeof(vis));
        for (int j = 1; j <= i / 2; ++j) {
            int x = i - j, y = i - x;
            if (x == y) continue;
            vis[sg[x] ^ sg[y]] = 1;
        }
        for (int j = 0; j < maxn; ++j) {
            if (vis[j] == 0) {
                sg[i] = j;
                break;
            }
        }
    }
}

int main() {
    init();
    int t, n, x, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            ans ^= sg[x];
        }
        if (ans) printf("Case %d: Alice\n", ca++);
        else printf("Case %d: Bob\n", ca++);
    }
    return 0;
}


// LightOJ - 1315
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1010;
int dir[6][2] = {{1, -2}, {-1, -3}, {-1, -2}, {-2, -1}, {-3, -1}, {-2, 1}};
int sg[maxn][maxn];
int vis[maxn];

bool valid(int x, int y) {
    if (x >= 0 && y >= 0) return 1;
    return 0;
}

int main() {
    
    for (int i = 1; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) {
            memset(vis, 0, sizeof(vis));
            for (int d = 0; d < 6; ++d) {
                int x = j + dir[d][0], y = i - j + dir[d][1];
                if (valid(x, y)) {
                    vis[sg[x][y]] = 1;
                }
            }
            for (int k = 0; k < maxn; ++k) {
                if (vis[k] == 0) {
                    sg[j][i - j] = k;
                    break;
                }
            }
        }
    }
    int t, n, x, y, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &x, &y);
            ans ^= sg[x][y];
        }
        if (ans) printf("Case %d: Alice\n", ca++);
        else printf("Case %d: Bob\n", ca++);
    }
    return 0;
}


// LightOJ - 1296
#include <cstdio>
using namespace std;

int main() {

    int t, ca = 1, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = 0, x;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            
            while (x % 2) {
                x /= 2;
            }
            ans ^= x / 2;
        }
        if (ans) printf("Case %d: Alice\n", ca++);
        else printf("Case %d: Bob\n", ca++);
    }
    return 0;
}


// LightOJ - 1186
#include <cstdio>
using namespace std;
const int maxn = 110;
int arr[maxn];
int main() {
    int t, ca = 1, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = 0, x;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            ans ^= (x - arr[i] - 1);
        }
        if (ans == 0) printf("Case %d: black wins\n", ca++);
        else printf("Case %d: white wins\n", ca++);
    }
    return 0;
}


// LightOJ - 1192
#include <cstdio>
using namespace std;

int main() {
    int t, ca = 1, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = 0, a, b;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &a, &b);
            ans ^= (b - a - 1);
        }
        if (ans == 0) printf("Case %d: Bob\n", ca++);
        else printf("Case %d: Alice\n", ca++);
    }
    return 0;
}


// LightOJ - 1247
#include <cstdio>
using namespace std;

int main() {
    int t, ca = 1, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int sum = 0, x;
            for (int j = 0; j < m; ++j) {
                scanf("%d", &x);
                sum += x;
            }
            ans ^= sum;
        }
        if (ans == 0) printf("Case %d: Bob\n", ca++);
        else printf("Case %d: Alice\n", ca++);
    }
    
    return 0;
}


// LightOJ - 1253
#include <cstdio>
using namespace std;
typedef long long LL;

int main(int argc, const char * argv[]) {
    
    int t, n, x, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int tmp = 0;
        LL ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            if (x == 1) ++tmp;
            ans ^= x;
        }
        if (tmp == n) {
            if (n % 2) printf("Case %d: Bob\n", ca++);
            else printf("Case %d: Alice\n", ca++);
        } else {
            if (ans == 0) printf("Case %d: Bob\n", ca++);
            else printf("Case %d: Alice\n", ca++);
        }
    }
    return 0;
}
*/
