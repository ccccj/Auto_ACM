//
//  main.cpp
//  线段树
//
//  Created by admin on 18/8/20.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long int LL;
const int maxn = 1e5 + 10, inf = 0x3fffffff;
LL arr[maxn];
LL tree[maxn << 2];
int ans[maxn], q[maxn];

LL min(LL a, LL b) {
    return a > b ? b : a;
}

void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    tree[now] = min(tree[now << 1], tree[(now << 1)|1]);
}

int query(int l, int r, LL& tmp, int now) {
    if (l == r) {
        tmp -= tree[now];
        tree[now] = inf;
        return 1;
    }
    int m = (l + r) / 2, ans = 0;
    if (tmp >= tree[now << 1]) {
        ans += query(l, m, tmp, now << 1);
    }
    
    if (tmp >= tree[(now << 1)|1]) {
        ans += query(m + 1, r, tmp, (now << 1)|1);
    }
    tree[now] = min(tree[now << 1], tree[(now << 1)|1]);
    return ans;
}

int main() {
    //freopen("/Users/admin/Desktop/test.in", "r", stdin);
    //freopen("/Users/admin/Desktop/test2.txt", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        LL c, tmp;
        scanf("%d%d%lld", &n, &m, &c);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &arr[n - i + 1]);
        }
        build(1, n, 1);
        int Max = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d", &q[i]);
            Max = max(Max, q[i]);
        }
        tmp = c;
        memset(ans, 0, sizeof(ans));
        ans[1] = query(1, n, tmp, 1);
        for (int i = 2; i <= Max; ++i) {
            if (tree[1] == inf) {
                break;
            }
            tmp += c;
            ans[i] = query(1, n, tmp, 1);
        }
        for (int i = 0; i < m; ++i) {
            printf("%d\n", ans[q[i]]);
        }
    }
    return 0;
}

/*
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
typedef long long int LL;

const int maxn = 110, MOD = 998244353, mod = 100001;

LL x0, arr[maxn], lazy[maxn << 2];
LL a, b, c;

struct node {
    LL maxx, maxy;
} tree[maxn << 2];

LL RNG61() {
    return (x0 = (100000005 * x0 + 20180821) % MOD) / 100;
}

LL com(struct node t) {
    return a * t.maxx + b * t.maxy + c * t.maxx * t.maxy;
}

void PushUp(int now) {
    tree[now].maxx = max(tree[now << 1].maxx, tree[(now << 1)|1].maxx);
    tree[now].maxy = max(tree[now << 1].maxy, tree[(now << 1)|1].maxy);
}

void build(int l, int r, int now) {
    if (l == r) {
        tree[now].maxx = l;
        tree[now].maxy = arr[l];
        return;
    }
    int m = l + (r - l) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    PushUp(now);
}

void UpdateOne(int l, int r, int L, int C, int now) {
    if (l == r) {
        tree[now].maxy = C;
        return;
    }
    int m = l + (r - l) / 2;
    if (L <= m) UpdateOne(l, m, L, C, now << 1);
    else UpdateOne(m + 1, r, L, C, (now << 1)|1);
    PushUp(now);
}

//void PushDown(int l, int m, int r, int now) {
//    if (lazy[now]) {
//        if (tree[now].x <= m) {
//            tree[now << 1].y = 100000 - tree[now << 1].y;
//            lazy[now << 1] = (lazy[now << 1] + 1) % 2;
//        } else {
//            tree[(now << 1)|1].y = 100000 - tree[(now << 1)|1].y;
//            lazy[(now << 1)|1] = (lazy[(now << 1)|1] + 1) % 2;
//        }
//        lazy[now] = 0;
//    }
//}

void update(int l, int r, int L, int R, int now) {
    if (l == r) {
        tree[now].maxy = 100000 - tree[now].maxy;
        return;
    }
    if (l >= L && r <= R) {
        LL x = tree[now].maxx;
        if (tree[x].maxy == tree[now].maxy
            && tree[x].maxy <= 100000 - tree[x].maxy) {
            tree[now].maxy = 100000 - tree[x].maxy;
            lazy[now] = (lazy[now] + 1) % 2;
            return;
        }
    }
    int m = l + (r - l) / 2;
    
    //PushDown(l, m, r, now);
    if (L <= m) update(l, m, L, R, now << 1);
    if (m + 1 <= R) update(m + 1, r, L, R, (now << 1)|1);
    
    PushUp(now);
}

LL query(int l, int r, int L, int R, int now) {
    LL x = tree[now].maxx;
    if (l >= L && r <= R
        && tree[x].maxy == tree[now].maxy) {
        return com(tree[now]);
    }
    int m = l + (r - l) / 2;
    LL ans = 0;
    if (m >= L) {
        ans = query(l, m, L, R, now << 1);
    }
    if (m + 1 <= R) {
        ans = max(ans, query(m + 1, r, L, R, (now << 1)|1));
    }
    return ans;
}

int main() {
    
    int n, m;
    while (~scanf("%d%d%lld", &n, &m, &x0)) {
        memset(lazy, 0, sizeof lazy);
        for (int i = 1; i <= n; ++i) {
            arr[i] = RNG61() % mod;
            // cout << arr[i] << endl;
        }
        build(1, n, 1);
        string s;
        for (int i = 0; i < m; ++i) {
            cin >> s;
            switch (s[0]) {
                case 'C': {
                    int p = RNG61() % n + 1, y = RNG61() % mod;
                    // cout << p << " " << y << endl;
                    UpdateOne(1, n, p, y, 1);
                    break;
                }
                case 'R': {
                    LL p1 = RNG61(), q1 = RNG61();
                    LL p = min(p1 % n + 1, q1 % n + 1), q = max(p1 % n + 1, q1 % n + 1);
                    update(1, n, (int)p, (int)q, 1);
                    break;
                }
                case 'Q': {
                    scanf("%lld%lld%lld", &a, &b, &c);
                    LL p1 = RNG61(), q1 = RNG61();
                    LL p = min(p1 % n + 1, q1 % n + 1), q = max(p1 % n + 1, q1 % n + 1);
                    printf("%lld\n", query(1, n, (int)p, (int)q, 1));
                    break;
                }
                default:
                    cout << "=========" << endl;
                    break;
            }
        }
    }
    return 0;
}


// Problem D: 奇异人生：暴风雨前夕
// 可持久化线段树
Description
如果不喜欢编程，学习算法 和 学习高数有什么不同？  —— 渣渣辉

《奇异人生：暴风雨前夕》是一款游戏。

小静非常喜欢这个游戏，于是开发了《奇怪人生：WA 的前兆》。

游戏开始时会给玩家分配一个含有 N 个正整数的序列 A1，A2，...，AN，游戏只有 4 种操作：

1. C l r d : 给区间 [ l，r ] 的每一个元素都加上 d，并创建新的存档，这是唯一一个能增加存档数目的行为。

2. Q l r : 查询当前存档的区间 [ l，r ] 的元素总和。

3. H l r t : 查询第 t 个存档中区间 [ l，r ] 的元素总和。

4. B t : 回到第 t 个存档，一旦回到第 t 个存档，在第 t 个存档以后所存的存档无效。

游戏开始时存档编号为 0，第一次执行 C 操作后，存档数 + 1。

Input
输入包含多组测试样例。

对于每组测试样例：

第一行输入 N，M，表示 A 序列的大小和操作总次数。

第二行输入 N 个整数，为 A 的序列元素。

接下来 M 行输入为操作。

( 1 <= N，M <= 105， - 109 <= Ai <= 109，1 <= l <= r <= N，- 104 <= d <= 104)

Output
对于每个 Q 和 H 操作，输出一个结果，占一行。

两组样例间空一行。

Sample Input
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4

2 4
0 0
C 1 1 1
C 2 2 -1
Q 1 2
H 1 2 1
Sample Output
4
55
9
15

0
1

// 不能过杭电~因为空间超限了~但是可以过学校oj
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

LL arr[100010];
int cnt;

struct node {
    int lc, rc;
    LL sum, lazy;
} tree[10000100];

int bulid(int l, int r) {
    int now = ++cnt;
    if (l == r) {
        tree[now].sum = arr[l];
        return now;
    }
    int m = l + (r - l) / 2;
    tree[now].lc = bulid(l, m);
    tree[now].rc = bulid(m + 1, r);
    tree[now].sum = tree[tree[now].lc].sum + tree[tree[now].rc].sum;
    return now;
}

void PushDown(int ln, int rn, int now) {
    if (tree[now].lazy) {
        // 原来的左孩子和右孩子
        int lc = tree[now].lc, rc = tree[now].rc;
        ++cnt;
        tree[cnt] = tree[lc];
        tree[now].lc = cnt;
        
        ++cnt;
        tree[cnt] = tree[rc];
        tree[now].rc = cnt;
        // 新的左孩子和右孩子
        lc = tree[now].lc, rc = tree[now].rc;
        
        tree[lc].lazy += tree[now].lazy;
        tree[rc].lazy += tree[now].lazy;
        tree[lc].sum += tree[now].lazy * ln;
        tree[rc].sum += tree[now].lazy * rn;
        tree[now].lazy = 0;
    }
}

int update(int l, int r, int L, int R, LL c, int old) {
    int now = ++cnt;
    tree[now] = tree[old];

    if (l >= L && r <= R) {
        tree[now].sum += c * (r - l + 1);
        tree[now].lazy += c;
        return now;
    }
    int m = l + (r - l) / 2;
    PushDown(m - l + 1, r - m, now);
    if (m >= L) {
        tree[now].lc = update(l, m, L, R, c, tree[now].lc);
    }
    if (m + 1 <= R) {
        tree[now].rc = update(m + 1, r, L, R, c, tree[now].rc);
    }
    tree[now].sum = tree[tree[now].lc].sum + tree[tree[now].rc].sum;
    return now;
}

LL query(int l, int r, int L, int R, int now) {
    if (l >= L && r <= R) {
        return tree[now].sum;
    }
    int m = l + (r - l) / 2;
    PushDown(m - l + 1, r - m, now);
    LL ans = 0;
    if (m >= L) {
        ans += query(l, m, L, R, tree[now].lc);
    }
    if (m + 1 <= R) {
        ans += query(m + 1, r, L, R, tree[now].rc);
    }
    return ans;
}

void print(int l, int r, int now) {
    printf("%lld  ", tree[now].sum);
    if (l == r) {
        return;
    }
    int m = l + (r-l)/2;
    print(l, m, tree[now].lc);
    print(m+1, r, tree[now].rc);
}

int main() {
    freopen("/Users/admin/Desktop/test-8.in", "r", stdin);
    freopen("/Users/admin/Desktop/aaa.out", "w", stdout);
    int n, m, ca = 1;
    while (cin >> n >> m) {
        if (ca++ > 1) {
            printf("\n");
        }
        memset(tree, 0, sizeof(tree));
        cnt = 0;
        
        vector<int> v;
        v.push_back(1);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &arr[i]);
        }
        bulid(1, n);
        int a, b, k = 1;
        LL c;
        char s[3];
        //print(1, n, k);
        //cout << endl << endl;
        for (int i = 0; i < m; ++i) {
            scanf("%s", s);
            if (s[0] == 'C') {
                // 区间修改
                scanf("%d%d%lld", &a, &b, &c);
                k = update(1, n, a, b, c, k);
                v.push_back(k);
            } else if (s[0] == 'Q') {
                // 当前区间求和
                scanf("%d%d", &a, &b);
                printf("%lld\n", query(1, n, a, b, k));
            } else if (s[0] == 'H') {
                // 某个版本区间求和
                scanf("%d%d%lld", &a, &b, &c);
                printf("%lld\n", query(1, n, a, b, v[c]));
            } else {
                // 消除存档
                scanf("%d", &a);
                if (a + 1 == v.size()) {
                    continue;
                }
                //cnt = v[a+1] - 1; 加这句就不会超空间，但是需要用别的lazy标记
                //cout << cnt << endl;
                k = v[a];
                while (v.size() > a + 1) {
                    v.pop_back();
                }
                
            }
        }
        
    }
    return 0;
}


Problem L: 区间第 K 小
Time Limit: 1 Sec  Memory Limit: 256 MB
Submit: 24  Solved: 4
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
如果不喜欢编程，学习算法 和 学习高数有什么不同？  —— 渣渣辉

给定 N 个正整数构成的序列，将对于指定的闭区间查询其区间内的第 K 小值。

Input
第一行包含两个正整数 N、M，分别表示序列的长度和查询的个数。

第二行包含 N 个正整数，表示这个序列各项的数字。

接下来 M 行每行包含三个整数 l，r，k， 表示查询区间 [ l，r ]内的第 k 小值。

( 1 <= N，M <= 2*105，- 109 <= ai <= 109)

Output
输出包含 M 行，每行 1 个正整数，依次表示每一次查询的结果。
Sample Input
5 5
25957 6405 15770 26287 26465
2 2 1
3 4 1
4 5 1
1 2 2
4 4 1
Sample Output
6405
15770
26287
25957
26287
HINT

N=5，数列长度为5，数列从第一项开始依次为 [25957 6405 15770 26287 26465 ]
第一次查询为 [2 2] 区间内的第一小值，即为6405
第二次查询为 [3 4] 区间内的第一小值，即为15770
第三次查询为 [4 5] 区间内的第一小值，即为26287
第四次查询为 [1 2] 区间内的第二小值，即为25957
第五次查询为 [4 4] 区间内的第一小值，即为26287


思路：对于每个区间[1, i]建树（i <= res，res为数组内不重复的数个数）
建树记录每个结点的个数，输入 [l, r] 后只需计算出两个版本的差，若k小于其差，则往左边走，否则往右边走（哎呀...我也说不清）
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
LL arr[200010], q[200010];
int cnt;

struct node {
    int lc, rc, cnt;
} tree[8000010];

int bulid(int l, int r) {
    int now = ++cnt;
    tree[now].cnt = 0;
    if (l == r) {
        return now;
    }
    int m = l + (r - l) / 2;
    tree[now].lc = bulid(l, m);
    tree[now].rc = bulid(m + 1, r);
    return now;
}

// 单点修改
int update(int l, int r, LL tar, int old) {
    int now = ++cnt;
    tree[now].lc = tree[old].lc;
    tree[now].rc = tree[old].rc;
    tree[now].cnt = tree[old].cnt;
    if (l == r) {
        ++tree[now].cnt;
        return now;
    }
    int m = l + (r - l) / 2;
    if (tar <= m) {
        tree[now].lc = update(l, m, tar, tree[old].lc);
    } else {
        tree[now].rc = update(m + 1, r, tar, tree[old].rc);
    }
    tree[now].cnt = tree[tree[now].lc].cnt + tree[tree[now].rc].cnt;
    return now;
}

LL query(int l, int r, int v1, int v2, int k) {
    if (l == r) {
        return q[l];
    }
    int m = l + (r - l) / 2;
    if (k <= tree[tree[v2].lc].cnt - tree[tree[v1].lc].cnt) {
        // 往左边走
        return query(l, m, tree[v1].lc, tree[v2].lc, k);
    } else {
        // 往右边走
        return query(m + 1, r, tree[v1].rc, tree[v2].rc, k - tree[tree[v2].lc].cnt + tree[tree[v1].lc].cnt);
    }
}

void print(int l, int r, int now) {
    printf("%d  ", tree[now].cnt);
    if (l == r) {
        return;
    }
    int m = l + (r-l)/2;
    print(l, m, tree[now].lc);
    print(m+1, r, tree[now].rc);
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<int> v;
        v.push_back(1);
        cnt = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &arr[i]);
            q[i] = arr[i];
        }
        // 离散化
        sort(q + 1, q + n + 1);
        // q数组长度
        LL res = unique(q + 1, q + n + 1) - q - 1;
        
        // 建立一棵空树，代表每个叶子节点的值出现了0次
        bulid(1, (int)res);
        // 对每个 [1, i] 建树
        
        for (int i = 1; i <= n; ++i) {
            LL tar = lower_bound(q + 1, q + res + 1, arr[i]) - q - 1;
            int ans = update(1, (int)res, tar + 1, v[i-1]);
            v.push_back(ans);
            //print(1, (int)res, ans);
            //printf("\n\n");
        }
        
        int v1, v2, k;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &v1, &v2, &k);
            printf("%lld\n", query(1, (int)res, v[v1 - 1], v[v2], k));
        }
    }
    return 0;
}


Problem J: 可持久化线段树
Time Limit: 1 Sec  Memory Limit: 512 MB
Submit: 4  Solved: 2
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
如果不喜欢编程，学习算法 和 学习高数有什么不同？  —— 渣渣辉

如题，你需要维护这样的一个长度为 N 的数组，支持如下几种操作

在某个历史版本上修改某一个位置上的值

访问某个历史版本上的某一位置的值

此外，每进行一次操作（对于操作2，即为生成一个完全一样的版本，不作任何改动），就会生成一个新的版本。版本编号即为当前操作的编号（从1开始编号，版本0表示初始状态数组）。

Input
输入的第一行包含两个正整数 N M， 分别表示数组的长度和操作的个数。

第二行包含 N 个整数，依次为初始状态下数组各位的值（依次为 ai ，1 ≤ i ≤ N）。

接下来 M行每行包含 3 或 4 个整数，代表两种操作之一（ i 为基于的历史版本号）：

1.对于操作1，格式为 vi 1 loci valuei，即为在版本 vi 的基础上，将 aloci 修改为 valuei。

2.对于操作2，格式为 vi 2 loci，即访问版本 vi 中的 aloci 的值。

(1 <= N，M <= 105，1 <= loci <= N，1 <= vi <= i，- 109 <= ai，valuei <= 109)

Output
输出包含若干行，依次为每个操作2的结果。
Sample Input
5 10
59 46 14 87 41
0 2 1
0 1 1 14
0 1 1 57
0 1 1 88
4 2 4
0 2 5
0 2 4
4 2 1
2 2 2
1 1 5 91
Sample Output
59
87
41
87
88
46
HINT
询问生成的版本是指你访问的那个版本的复制
样例说明：
一共11个版本，编号从0-10，依次为：
* 0 : 59 46 14 87 41
* 1 : 59 46 14 87 41
* 2 : 14 46 14 87 41
* 3 : 57 46 14 87 41
* 4 : 88 46 14 87 41
* 5 : 88 46 14 87 41
* 6 : 59 46 14 87 41
* 7 : 59 46 14 87 41
* 8 : 88 46 14 87 41
* 9 : 14 46 14 87 41
* 10 : 59 46 14 87 91
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

LL arr[100010];
int cnt;

struct node {
    LL sum; // 区间和
    int lc, rc; // 左孩子和右孩子
} tree[8000010];

int bulid(int l, int r) {
    int now = ++cnt;
    if (l == r) {
        tree[now].sum = arr[l];
        return now;
    }
    int m = l + (r - l) / 2;
    tree[now].lc = bulid(l, m);
    tree[now].rc = bulid(m + 1, r);
    tree[now].sum = tree[tree[now].lc].sum + tree[tree[now].rc].sum;
    return now;
}

// [l, r] : 当前区间
// tar : 目标下标
// c : 希望修改成什么值
// old : 原本版本的编号
int update(int l, int r, int tar, int c, int old) {
    int now = ++cnt;
    tree[now].lc = tree[old].lc;
    tree[now].rc = tree[old].rc;
    
    if (l == r) {
        tree[now].sum = c;
        return now;
    }
    int m = l + (r - l) / 2;
    if (tar <= m) tree[now].lc = update(l, m, tar, c, tree[old].lc);
    else tree[now].rc = update(m + 1, r, tar, c, tree[old].rc);
    
    tree[now].sum = tree[tree[now].lc].sum + tree[tree[now].rc].sum;
    return now;
}

LL query(int l, int r, int tar, int old) {
    if (l == r) {
        return tree[old].sum;
    }
    int m = l + (r - l) / 2;
    if (tar <= m) return query(l, m, tar, tree[old].lc);
    else return query(m + 1, r, tar, tree[old].rc);
}

void print(int now, int l, int r) {
    printf("[%d,%d] %lld ", l, r, tree[now].sum);
    if (l == r) {
        //printf("%lld ", tree[now].sum);
        return;
    }
    int mid = l + (r - l)/2;
    print(tree[now].lc, l, mid);
    print(tree[now].rc, mid + 1, r);
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        cnt = 0;
        vector<int> v;
        v.push_back(1);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &arr[i]);
        }
        bulid(1, n);
        int version, com, a, b;
        for (int i = 0; i < m; ++i) {
            
            scanf("%d%d%d", &version, &com, &a);
            
            if (com == 1) {
                // a 修改为 b
                scanf("%d", &b);
                int p = update(1, n, a, b, v[version]);
                //printf("p:%d\n", p);
                v.push_back(p);
                //print(v[version - 1], 1, n);
                //printf("\n");
            } else {
                // 访问 a 的值
                printf("%lld\n", query(1, n, a, v[version]));
                v.push_back(v[version]);
            }
            
        }
    }
    return 0;
}


Description
如果不喜欢编程，学习算法 和 学习高数有什么不同？  —— 渣渣辉

小静有一串开始时全为 0 的序列。

然后她会进行 M 次操作去更新她的序列。在 M 次操作后，你需要帮她计算的值，⨁表示异或操作。

同时，为了避免数据过大，小静同学给数据做了加密，你需要解开它。

解密函数如下，样例输入时给定 32 位整型 X，Y，Z。( ^ 为异或操作，<< 为左移，>> 为右移)




利用上述函数求出的第 i 个值设为 fi (i = 1，2，3， ...， 3m)。

小静想在每次操作后，如果 aj < vi (j = li，li + 1，... ，ri)，就把 aj 更新为 vi。

li，ri 以及 vi 的算法如下：



Input
输入的第一行为 T，表示测试样例组数。

接下来 T 行为 5 个整数，为 N，M，X，Y，Z。

(1 <= T <= 100，1 <= N <= 105，1 <= M <= 5*106，0 <= X，Y，Z <= 230)

保证所有测试样例的 N 的总和不超过 106，M 的总和不超过 5*107。

Output
对于每一组测试样例，输出一个正整数。
Sample Input
4
1 10 100 1000 10000
10 100 1000 10000 100000
100 1000 10000 100000 1000000
1000 10000 100000 1000000 10000000
Sample Output
1031463378
1446334207
351511856
47320301347
HINT

在第一组样例中 a = [1031463378]。


在第二组样例中 a = [1036205629， 1064909195， 1044643689， 1062944339， 1062944339， 1062944339， 1062944339， 1057472915， 1057472915， 1030626924]。

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef unsigned long long uL;
typedef long long LL;
int T;
unsigned n, m, x, y, z, w;
uL tree[400010];
unsigned f[50000010];

unsigned RNG61() {
    x ^= (x << 11);
    // 感觉题目讲的不是很清楚，这里题目的意思是说，就算会超范围，就让它超去吧~总之x是unsigned的，下面也一样
    x ^= (x >> 4);
    x ^= (x << 5);
    x ^= (x >> 14);
    w = (x ^ (y ^ z));
    x = y;
    y = z;
    z = w;
    return w;
}

void PushDown(int now) {
    // 如果当前结点的标记比子结点大，就向下推标记
    if (tree[now] > tree[now << 1]) {
        tree[now << 1] = tree[now];
    }
    if (tree[now] > tree[(now << 1)|1]) {
        tree[(now << 1)|1] = tree[now];
    }
}

void update(uL l, uL r, uL L, uL R, uL c, int now) {
    // 剪枝，没有这个判断会超时的
    // 例如，tree[root] = 100,这时候要更新标记，让[2,3]区间改为3
    // 由于下面的都比上面的大，所以下面的标记只会比100大，不用判断是否比3大了（肯定大）
    if (tree[now] >= c) {
        return;
    }
    // 完全包含这个区间
    if (l >= L && r <= R) {
        if (tree[now] < c) {
            tree[now] = c;
        }
        return;
    }
    // 只要比当前标记大，就更新
    uL m = (l + r) >> 1;
    if (m >= L) {
        update(l, m, L, R, c, now << 1);
    }
    if (m + 1 <= R) {
        update(m + 1, r, L, R, c, (now << 1)|1);
    }
}

uL q(uL l, uL r, int now) {
    if (l == r) {
        return l * tree[now];
    }
    PushDown(now);
    uL m = (l + r) >> 1;
    return q(l, m, now << 1) ^ q(m + 1, r, (now << 1)|1);
}

int main() {
    LL MOD = 1073741824;
    scanf("%d", &T);
    while (T--) {
        memset(tree, 0, sizeof(tree));
        scanf("%u%u%u%u%u", &n, &m, &x, &y, &z);
        for (int i = 1; i <= 3 * m; ++i) {
            f[i] = RNG61();
        }
        uL l, r, v;
        for (int i = 1; i <= m; ++i) {
            l = min(f[3*i - 2] % n + 1, f[3*i - 1] % n + 1) ;
            r = max(f[3*i - 2] % n + 1, f[3*i - 1] % n + 1) ;
            v = f[3*i] % MOD;
            update(1, n, l, r, v, 1);
        }
        printf("%llu\n", q(1, n, 1));
    }
    
    return 0;
}


Problem M: 区间求和
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 47  Solved: 13
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
如果不喜欢编程，学习算法 和 学习高数有什么不同？  —— 渣渣辉

小静有一系列长为 N 的整数序列，她想对序列的某些区间做加上某个整数的操作。

有时候她又觉得很无聊，想知道某些区间的总和。

请你帮帮笨笨的她吧。

操作为两种格式：

1. C x y z        表示在区间 [x，y] 的每个数字都加上 z。

2. Q x y          表示询问区间 [x， y] 的总和。

Input
输入有多组测试数据。(保证不超过十组)

对于每组样例：

第一行输入为 N， M，表示序列长度和操作次数。(1 <= N，Q <= 100000)

第二行输入为 N 个整数。(-1000000000 <= Ai <= 1000000000)

接下来 M 行输入为操作类型，输入格式为：

1. C x y z        表示在区间 [x，y] 的每个数字都加上 z。

2. Q x y          表示询问区间 [x， y] 的总和。

(1 <= x，y <= N，-1000000000 <= z <= 1000000000)


Output
对于每个询问操作，输出一个整数，为询问区间的数字总和。
Sample Input
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
Sample Output
4
55
9
15

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100010;
typedef long long LL;
LL arr[maxn], tree[maxn << 2], lazy[maxn << 2];

// root 标号为1
void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l+r) >> 1;
    build(l, m, now << 1);
    build(m + 1, r, now << 1 | 1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

// ln 左子树个数
// rn 右子树个数
void PushDown(int ln, int rn, int now) {
    if (lazy[now] != 0) {

        lazy[now << 1] += lazy[now];
        lazy[(now << 1)|1] += lazy[now];

        tree[now << 1] += lazy[now] * ln;
        tree[(now << 1)|1] += lazy[now] * rn;
        
        lazy[now] = 0;
    }
}

// 区间修改
// [l, r] : 当前区间
// [L, R] 要修改的点在数组中的下标
// c : 想要改成什么值或加上什么值
// now : 当前标号
// 懒惰标记，当前结点已更新，儿子未更新
void update(int l, int r, int L, int R, int c, int now) {
    if (l >= L && r <= R) {
        tree[now] += c * (r - l + 1);
        lazy[now] += c;
        return;
    }
    int m = (l+r) >> 1;
    if (L <= m) {
        // 左边需要更新
        update(l, m, L, R, c, now << 1);
    }
    if (R >= m + 1) {
        // 右边需要更新
        update(m+1, r, L, R, c, (now << 1)|1);
    }
    PushDown(m - l + 1, r - m, now);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

// 查询区间[L, R]的和
LL query(int l, int r, int L, int R, int now) {
    if (L <= l && R >= r) {
        return tree[now];
    }
    int m = (l+r) >> 1;
    // 当前区间在要求的区间里面
    LL ans = 0;
    PushDown(m - l + 1, r - m, now);
    if (L <= m) {
        // 左边需要查询
        ans += query(l, m, L, R, now << 1);
    }
    if (R >= m + 1) {
        // 右边需要查询
        ans += query(m+1, r, L, R, (now << 1)|1);
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    int n, m, a, b, c;
    while (~scanf("%d%d", &n, &m)) {
        memset(lazy, 0, sizeof(lazy));
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &arr[i]);
        }
        // now 为 1
        build(1, n, 1);
        
        char s[10];
        for (int i = 0; i < m; ++i) {
            scanf("%s", s);
            if (s[0] == 'C') {
                scanf("%d%d%d", &a, &b, &c);
                update(1, n, a, b, c, 1);
            } else {
                scanf("%d%d", &a, &b);
                printf("%lld\n", query(1, n, a, b, 1));
            }
        }
    }
    return 0;
}


// 线段树 单点修改
Problem Q: 敌兵布阵
Time Limit: 2 Sec  Memory Limit: 10000 MB
Submit: 75  Solved: 22
[Submit][Status][Web Board][Creator:201506020829]
Description
C国的死对头A国这段时间正在进行军事演习，所以C国间谍头子Derek和他手下Tidy又开始忙乎了。A国在海岸线沿直线布置了N个工兵营地Derek和Tidy的任务就是要监视这些工兵营地的活动情况。由于采取了某种先进的监测手段，所以每个工兵营地的人数C国都掌握的一清二楚每个工兵营地的人数都有可能发生变动，可能增加或减少若干人手但这些都逃不过C国的监视。
中央情报局要研究敌人究竟演习什么战术所以Tidy要随时向Derek汇报某一段连续的工兵营地一共有多少人例如Derek问:“Tidy马上汇报第3个营地到第10个营地共有多少人!”Tidy就要马上开始计算这一段的总人数并汇报。但敌兵营地的人数经常变动，而Derek每次询问的段都不一样，所以Tidy不得不每次都一个一个营地的去数，很快就精疲力尽了，Derek对Tidy的计算速度越来越不满:"你个死肥仔，算得这么慢，我炒你鱿鱼!”Tidy想：“你自己来算算看，这可真是一项累人的工作!我恨不得你炒我鱿鱼呢!”无奈之下，Tidy只好打电话向计算机专家Windbreaker求救Windbreaker说：“死肥仔，叫你平时做多点acm题和看多点算法书，现在尝到苦果了吧!”Tidy说："我知错了。。。"但Windbreaker已经挂掉电话了。Tidy很苦恼，这么算他真的会崩溃的，聪明的读者，你能写个程序帮他完成这项工作吗？不过如果你的程序效率不够高的话，Tidy还是会受到Derek的责骂的.
Input
第一行一个整数T，表示有T组数据。
每组数据第一行一个正整数N（N<=50000）表示敌人有N个工兵营地，接下来有N个正整数第i个正整数ai代表第i个工兵营地里开始时有ai个人（1<=ai<=50）。
接下来每行有一条命令，命令有4种形式：
(1) Add i ji和j为正整数表示第i个营地增加j个人（j不超过30）
(2)Sub i j i和j为正整数表示第i个营地减少j个人（j不超过30）;
(3)Query i j i和j为正整数i<=j，表示询问第i到第j个营地的总人数;
(4)End 表示结束，这条命令在每组数据最后出现;
每组数据最多有40000条命令
Output
对第i组数据首先输出“Case i:”和回车
对于每个Query询问，输出一个整数并回车表示询问的段中的总人数这个数保持在int以内。
Sample Input
1
10
1 2 3 4 5 6 7 8 9 10
Query 1 3
Add 3 6
Query 2 7
Sub 10 2
Add 6 3
Query 3 10
End
Sample Output
Case 1:
6
33
59

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 50010;
int arr[maxn], tree[maxn * 4], n;

// root 标号为1
void build(int l, int r, int now) {
    if (l == r) {
        tree[now] = arr[l];
        return;
    }
    int m = (l+r) >> 1;
    build(l, m, now << 1);
    build(m + 1, r, now << 1 | 1);
    tree[now] = tree[now << 1] + tree[(now << 1)|1];
}

// 单点修改
// [l, r] : 当前区间
// L 要修改的点在数组中的下标
// c : 想要改成什么值或加上什么值
// now : 当前标号
void UpdateOne(int l, int r, int L, int c, int now) {
    if (l == r) {
        tree[now] += c; // 加上
        return;
    }
    int m = (l+r) >> 1;
    if (L <= m) {
        UpdateOne(l, m, L, c, now << 1);
    } else {
        UpdateOne(m+1, r, L, c, (now << 1)|1);
    }
    tree[now] += c;
}

// 查询区间[L, R]的和
int query(int l, int r, int L, int R, int now) {
    if (L <= l && R >= r) {
        return tree[now];
    }
    int m = (l+r) >> 1;
    // 当前区间在要求的区间里面
    if (L >= l && R <= m) {
        // 全在左边
        return query(l, m, L, R, now << 1);
    } else if (L >= m + 1 && R <= r) {
        return query(m+1, r, L, R, (now << 1)|1);
    } else {
        return query(l, m, L, m, now << 1) + query(m+1, r, m+1, R, (now << 1)|1);
    }
    
}

int main(int argc, const char * argv[]) {
    
    int T, a, b, CA = 1;
    scanf("%d", &T);
    while (T--) {
        printf("Case %d:\n", CA++);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        // now 为 1
        build(1, n, 1);
        
        char s[10];
        while (scanf("%s", s) && s[0] != 'E') {
            scanf("%d%d", &a, &b);
            if (s[0] == 'A') {
                UpdateOne(1, n, a, b, 1);
            } else if (s[0] == 'S') {
                UpdateOne(1, n, a, -b, 1);
            } else {
                cout << query(1, n, a, b, 1) << endl;
            }
        }
    }
    return 0;
}
*/
