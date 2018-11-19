//
//  main.cpp
//  sustoj校内选拔赛
//
//  Created by admin on 18/9/29.
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
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
const int maxn = 15;

int x, _y1, _y2, _y3, _y4, cnt, num;

struct edge {
    int x1, y1, x2, y2;
} wall[maxn];

struct point {
    int x, y;
} P[maxn];

struct G {
    int to;
    double cost;
};

vector<G> v[maxn];

double cross(edge a, edge b) {
    return a.x1 * b.y2 - a.x2 * b.y1;
}

bool judge(edge a, edge b) { // 判断两条线段是否相交
    edge x = {a.x1, a.y1, b.x1, b.y1}, y = {a.x1, a.y1, b.x2, b.y2};
    if (cross(x, y) < 0) {
        return 1;
    }
    return 0;
}

void _insert(int from, int to, double cost) {
    v[from].push_back({to, cost});
    v[to].push_back({from, cost});
}

double com_dis(int a, int b) {
    return sqrt((P[a].x - P[b].x) * (P[a].x - P[b].x) + (P[a].y - P[b].y) * (P[a].y - P[b].y));
}

void insert(int n) {
    int now = n - 1;
    for (int i = 0; i < now; ++i) {
        edge t = {P[i].x, P[i].y, P[now].x, P[now].y};
        int flag = 0;
        int j;
        if (i % 2) {
            j = i + 2;
        } else {
            j = i + 1;
        }
        for (; j < now; j += 2) {
            if (judge(t, {P[j].x, P[j].y, P[j+1].x, P[j+1].y}) == 1) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            _insert(i, now, com_dis(i, now));
        }
    }
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        cnt = 0, num = 0;
        P[cnt++] = {0, 5};
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d%d%d", &x, &_y1, &_y2, &_y3, &_y4);
            if (_y1 != 0) {
                wall[num++] = {x, 0, x, _y1};
                P[cnt++] = {x, 0};
                insert(cnt);
                P[cnt++] = {x, _y1};
                insert(cnt);
            }
            if (_y2 != _y3) {
                wall[num++] = {x, _y2, x, _y3};
                P[cnt++] = {x, _y2};
                P[cnt++] = {x, _y3};
            }
            if (_y4 != 10) {
                wall[num++] = {x, _y4, x, 10};
                P[cnt++] = {x, _y4};
                P[cnt++] = {x, 10};
            }
        }
        P[cnt++] = {10, 5};
        
    }
    return 0;
}


Problem J: 共产主义接班人
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 18  Solved: 8
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
教练是一位令人敬佩的共青团员。因为他乐于助人的品行，使得他在整个社区的团支部人人皆知。

在社区里，从左到右排列着 N + 1 户家庭，其中教练住在左边第 1 户。

社区里每一户家庭都让教练操心，因此教练总是去帮助他们。

教练认为每一户家庭都有一个操心指数 A，而教练有一个爱心指数 B。

当 B ≥ A 时，教练的热情之心促使自己必须帮助这户家庭，事件完成后，爱心指数就会变为 B - A。

教练每天下班后都非常开心，使得他的爱心指数增加 C。并且教练每次下班后，都会从右侧的社区大门进入小区，然后依次经过其他家庭，回到自己家中。

教练想知道，他在第 K 天下班时，可以帮助多少户家庭。

PS：教练第 1 天早上的爱心指数为 0。

Input
输入的第一行为 T，(0 < T ≤ 10)，表示测试样例组数。

对于每组测试样例：

第一行输入三个正整数 N， M，C，表示社区中有 N + 1 户人家，M 个询问和教练每天增加的爱心指数 C。

第二行输入 N 个正整数，表示第 i 户人家的操心指数 Ai。

接下来 M 行为一个整数 K，表示询问第 K 天教练帮助的家庭数。

(0 < N，M，C ≤ 105  0 < Ai，K < 109)

Output
对于每组询问，输出一个数字，表示第 K 天教练帮助的家庭数。

Sample Input
1
5 6 5
3 2 4 8 5
3
4
5
6
1
2
Sample Output
2
0
1
0
1
1

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


Problem K: 66666666666666666666666666666666666666666666666666666666666666666666666
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 49  Solved: 3
[Submit][Status][Web Board][Creator:201606060501][Edit] [TestData]
Description
众所周知，教练是一个喜欢喊 666 的大佬。

有一天教练在喊 666 的时候，突然想到，是否任意一个数的倍数都可以用 666...666 来表示呢？他随机测试了几个数字，发现 666666 是 13 的倍数，6666666666666666 是 17 的倍数。

他觉得自己发现了一个伟大的定理 —— 666...666(n 个 6) 可以是任意一个数的倍数。啊哈，可惜这是错误的。然而教练坚持认为自己是对的，他向你问了几个数，聪明的你能告诉他，多少个 6 可以是这个数的倍数，或者任意多个 6 都不可能是这个数的倍数吗？

Input
本题有多个测试用例。

每组测试用例由一个单独的 x 构成（1 ≤ x ≤ 5000000000）。

Output
请输出 多少个 6 组成的数，可以为 x 的倍数（若有多个答案，请输出最小答案）。注意要加 Case 哦~    具体格式请看样例。

若无解，则输出 -1 。

Sample Input
13
17
10
Sample Output
Case 1: 6
Case 2: 16
Case 3: -1

#include <cstdio>
#include <cmath>
#include <time.h>
#include <cstdlib>
using namespace std;
typedef long long LL;

// 求解欧拉函数
LL phi(LL x) {
    LL ans = x;
    for (LL i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            ans = ans / i * (i - 1);
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        ans = ans / x * (x - 1);
    }
    return ans;
}

// 快速乘
LL multi(LL a, LL b, LL mod) {
    LL ret = 0;
    while (b) {
        if (b & 1) {
            ret = (ret + a) % mod;
        }
        a = (a << 1) % mod;
        b >>= 1;
    }
    return ret;
}

// 快速幂
LL fastpow(LL a, LL b, LL p) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = multi(ans, a, p);
        }
        a = multi(a, a, p);
        b >>= 1;
    }
    return ans;
}

// 求解最大公约数
LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    LL p;
    int ca = 1;
    while (~scanf("%lld", &p) && p) {
        printf("Case %d: ", ca++);
        p /= gcd(p, 6);
        // p 和 6 有最大公约数，先约去这个数，此时原题变为了 111...111 可以被 p 整除
        p *= 9;
        // 此时原题变为了 999...999 可以被 p 整除，即 100...000 - 1 可以被 p 整除
        // 也就是说，100...000 % p 余 1，求最少有多少个 0
        // 已知以下定理：
        // 若正整数 a, p 互质，则满足 a ^ x ≡ 1 (mod p) 的最小的正整数 x0， 是 φ(p) 的约数（因子）。
        // φ(p) 为 欧拉函数，即 10^x ≡ 1 (mod p) 的最小的正整数解是 φ(p) 的因子
        
        if (gcd(p, 10) == 1) {
            // 互质
            LL ans = phi(p); // 欧拉函数
            LL i = 0;
            int f = 0;
            LL tmp = sqrt(ans);
            
            // 下面这样求主要是将 O(n) 变为 O(根号n)
            // ans = φ(p)，求 ans 的因子
            for (i = 1; i * i <= ans; ++i) {
                // 解在 1 - sqrt(ans) 内
                if (ans % i == 0) {
                    if (fastpow(10, i, p) == 1) {
                        f = 1;
                        break;
                    }
                }
            }
            if (f) {
                printf("%lld\n", i);
            } else {
                // 解在 sqrt(ans) - ans 内
                for (i = tmp; i >= 1; --i) {
                    if (ans % (ans / i) == 0) {
                        if (fastpow(10, ans / i, p) == 1) {
                            break;
                        }
                    }
                }
                printf("%lld\n", ans / i);
            }
            
        } else {
            // 不互质，则无解
            printf("-1\n");
        }
    }
    return 0;
}


Problem D: 秋雨绵绵
Time Limit: 3 Sec  Memory Limit: 128 MB
Submit: 16  Solved: 8
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
某年月日，林虎牛无意间坠落山崖，发现一处洞天福地。他惊奇万分，向内探索着，希望可以找到一本绝世神功的秘籍，从而称霸武林。功夫不负有心人，林虎牛在犄角旮旯里发现一本残破的书，定睛一看，竟然是天下武学出龙泉的龙泉寺不传之宝——《近世代数》！他翻开第一页，只见书上写着“欲练神功，必先自宫”。林虎牛不以为然，继续向后翻，发现了一句话“不欲自宫，须破迷踪”。然后一幅巨大的公式展现在他的面前。望着巨大的公式，林虎牛不禁感叹道：

我喜欢下雨天，喜欢听雨滴轻敲窗户的声音。我还喜欢数学，数学是世界上最优美的语言，现在定义一个数列，f(n) = b0*f(n-1) + b1*f(n-2) + c  (n ≥ 2)。
http://101.200.61.174/JudgeOnline/upload/image/20180928/20180928141354_17996.png
求f(n)和S，是不是超级简单啊？

你能帮助林虎牛，摆脱《近世代数》第一页命运的桎梏吗？

Input
第一行一个整数 T (1 ≤ T ≤ 10000)，表示数据组数。

每组数据一行 7 个整数 f(0)，f(1)， b0，b1， c， n， M，

(0 ≤ f(0)， f(1)， b0， b1，c，n ≤ 109，0 ≤ M ≤ 1018)

Output
对于每组数据，输出3行表示答案。

第1行，Case #n:

第2行，f(n)

第3行，S

Sample Input
4
1 1 1 1 3 3 1000007
7306 706 3212 7370 272 5530 5463632982528872
8301 6758 4216 6812 5221 1263 3364759590556141
5361 6799 8850 8489 3314 4023 92841679252408
Sample Output
case #1:
9
45
case #2:
209299065202560
1063977121315696
case #3:
38201780978456
512816412033891
case #4:
66715290041187
70899807864777

#include <cstdio>
using namespace std;
typedef long long LL;
LL f0, f1, b0, b1, c, n, mod, f = 1, sum;

LL ksc(LL x,LL y) {
    return (x*y-(LL)((long double)x/mod*y)*mod+mod)%mod;
}

int main() {
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld%lld%lld%lld%lld%lld", &f0, &f1, &b0, &b1, &c, &n, &mod);
        sum = ksc(f0, f1);
        if (n == 0) {
            printf("case #%d:\n%lld\n%lld\n", ca++, f0, f0);
            continue;
        } else if (n == 1) {
            printf("case #%d:\n%lld\n%lld\n", ca++, f1, sum);
            continue;
        }
        for (int i = 2; i <= n; ++i) {
            f = ((ksc(f0, b1) + ksc(f1, b0)) % mod + c) % mod;
            sum = ksc(sum, f);
            f0 = f1;
            f1 = f;
        }
        printf("case #%d:\n%lld\n%lld\n", ca++, f, sum);
        
    }
    return 0;
}


Problem E: RMB 游戏
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 38  Solved: 14
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
我承认玩过 CF， 但只玩了 5 分钟，CF里充满了喧嚣和暴力。 没有书，并不适合我。 我喜欢学习，学习使我快乐，优秀是一种习惯。

Q 老师手上有一堆卡牌，卡牌上写了一个数字 Ai (正整数)，当前他有 n 张牌，然后他总是随机取出两张来，然后他一眼就能看出这两牌中哪一张小（相同就取相同的），作为这两张牌的有效分值，然后呢他陷入了沉思，对于 n 张牌取两张牌，显然有确定的组合可能性，即 n*(n-1)/2 对组合，然后他想知道所有这些组合中第 k 大的分值是多少？

Input
输入一个 t 表示数据组数；(0 < t ≤ 5000)

接下来一行是 n ， k，表示 n 张牌和最后第 k 大的分值；（1 < n < 25000，保证0 < k ≤ n*(n-1)/2）

接下来一行是 n 个值 Ai，表示第 i 张牌上的数字(0 < Ai ≤ 10000000)。

Output
每组数据输出一行，即第k大的分值为多少。

Sample Input
2
3 2
1 2 3
3 1
4 2 1
Sample Output
1
2

#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2500010;
int arr[maxn];

int main() {
    int t, n;
    long long k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%lld", &n, &k);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        sort(arr, arr + n);
        long long int sum = 0, S = 0;
        for (int i = n - 2; i >= 0; --i) {
            ++sum;
            S += sum;
            if (S >= k) {
                printf("%d\n", arr[i]);
                break;
                
            }
        }
        
    }
    return 0;
}


Problem H: 有种放学别走
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 36  Solved: 12
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
科大广场是这个城市最大最热(门)的广场，所以我们总是可以看到很多人在放风筝。

某天，教练说要请我们去科大广场做游戏！游戏是酱紫的：

1. 2N 个人围成一个正 2N 边形。

2. 用 N 条彩带将两个人连接起来。

3. 两条彩带之间不能相交。

教练想知道一共有多少种连法呢？

Input
输入包含多组测试数据。

对于每组测试样例，输入一个正整数  N (0 < N ≤ 1000)。
Output
输出一个方案数，由于数字可能很大，教练希望你可以给方案数膜一下19260817。
Sample Input
2
3
Sample Output
2
5

#include <cstdio>
using namespace std;
const int maxn = 1010, mod = 19260817;
long long int arr[maxn<<1];

void init() {
    arr[0] = 1;
    arr[2] = 1;
    for (int i = 4; i < maxn * 2; i += 2) {
        for (int j = 0; j <= i - 2; j += 2) {
            arr[i] = (arr[i] + arr[j] * arr[i-j-2] % mod) % mod;
        }
    }
}

int main() {
    init();
    int n;
    while (~scanf("%d", &n)) {
        printf("%lld\n", arr[n << 1]);
    }
    return 0;
}


Problem I: 单身狗的寻觅
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 54  Solved: 6
[Submit][Status][Web Board][Creator:winsoul][Edit] [TestData]
Description
你是个单身狗吗？那就来相亲吧！

西安有一个神奇的地方，叫做“SUST_ACM 婚姻介绍所”。

里面有很多需要相亲的程序猿和程序媛。

每个人等待相亲的人都有一个编号(有可能重复)，其中程序猿为奇数，程序媛为偶数。

现在他们正排成一排等待相亲。

每个人都只能和相邻的两个人配对，当然绝不允许同性配对。

老大想让介绍所的撮合对数最大化，你告诉老大最多可以匹配多少对吗?

Input
输入包含多组测试数据。

对于每组测试样例：

第一行输入为一个整数 N (1 ≤ N ≤ 108)。

第二行输入 N 个正整数(0 < ID ≤ 10000)。

Output
输出可以匹配的最大对数。
Sample Input
6
1 2 3 4 5 5
Sample Output
2

#include <cstdio>
using namespace std;

int main() {
    
    int n, x;
    while (~scanf("%d", &n)) {
        int sum = 0, last = -1;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            if (last == -1) {
                last = x;
            } else {
                if ((last + x) % 2) {
                    // 一奇一偶
                    ++sum;
                    last = -1;
                } else {
                    last = x;
                }
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}


Problem G: 营救教练计划
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 3  Solved: 3
[Submit][Status][Web Board][Creator:201606060501][Edit] [TestData]
Description
第三次宇宙 ACM 大赛开战了。

创客由于 Winsoul 的泄密，导致教练被外星人 Hulin 绑架了。他被绑去了一个遥远的星球—— Yoyo星球。

从创客到 Yoyo星球只有一条路可以走。这条路长度总共为 n 。现在我们假设创客在 0 号位置，Yoyo星球在 n 号位置，你可以开着飞船从 0 飞到 1 ，再飞到 2 ，再飞到 3... 直到到 n 。

Amon 现在要去解救教练。可是飞船这么飞太慢了，等到了 Yoyo星球，教练等的黄花菜都凉了。所以 Amon 去找了邪恶又伟大的巫师帮助他。

巫师给了 Amon 两瓶药，一瓶随机药，一瓶传送药。他们分别有以下作用：

随机药：用完后的每次飞行，可以花和原本相同的时间，但是飞过 1、2、3、4、5、6  或 7 个地区。

也就是说，原本飞船在 第 i 号位置，可能会随机飞到 i+1，i+2，i+3，i+4，i+5，i+6 或 i+7 号位置，且只耗费 1 的时间。我们假设飞到每个位置的概率都相等。

传送药：在某些特定的位置，飞船可以直接从 x 号位置飞到 y 号位置，且不耗费任何时间。

Amon 一拿到药就把要用掉啦，并且立马前往 Yoyo星球。

注意，若 Amon 最后一次飞行，飞到了 n+1 或 n+2 或 ... n+6，我们也算他已经到达了终点哦~

我们假设每次的飞行时间为 1，请问 Amon飞到 Yoyo星球需要耗费的时间的数学期望是多少呢？

Input
本题有多组测试用例。

每组测试用例第一行有一个 n，代表 Yoyo星球的位置，和一个 m，代表跳跃点的个数。(1 ≤ n ≤ 100000，1 ≤ m ≤ 5000)。

接下来 m 行，每行一个 x 和一个 y (1 ≤ x，y ≤ n)（没有任意两个x相同）。

Output
输出 Amon 从创客到 Yoyo星球（大于等于n的位置）所需时间的数学期望（保留四位小数）。创客的位置始终为 0。

Sample Input
3 0
6 2
2 4
5 6
Sample Output
1.3061
1.6560

// 一道简单的期望dp~希望大家喜欢~
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
const int maxn = 1e5 + 10;
double dp[maxn];

int main(int argc, const char * argv[]) {
    int n, m, x, y;
    while (~scanf("%d%d", &n, &m)) {
        // 初始化 dp 数组为0
        memset(dp, 0, sizeof(dp));
        // 用 map 存储所有的跳跃点
        map<int, int> mp;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            mp[x] = y;
        }
        // dp[i] 存储从第i个位置到 n 需要飞多长时间的数学期望
        // n 位置当然是 0 啦
        // 注意，n 后面的几个位置也是0
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (mp.find(i) != mp.end()) {
                // 如果 i 位置可以直接飞到后面某个位置，那么他们的期望是相同的
                dp[i] = dp[mp[i]];
            } else {
                // 枚举后面七个位置，注意，n 后面的都是0
                // dp[i] = dp[i+1]/7 + dp[i+2]/7 + dp[i+3]/7 + dp[i+4]/7 + dp[i+5]/7 + dp[i+6]/7 + dp[i+7]/7 + 1
                double sum = 0;
                int num = 0;
                for (int j = i + 1; num < 7; ++j, ++num) {
                    sum += dp[j] + 1;
                }
                dp[i] = sum / num;
            }
        }
        printf("%.4lf\n", dp[0]);
    }
    return 0;
}
*/
