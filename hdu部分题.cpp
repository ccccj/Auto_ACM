//
//  main.cpp
//  hdu
//
//  Created by admin on 18/6/14.
//  Copyright © 2018年 Amon. All rights reserved.
//
// hdu 3037
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 100010;
LL n, m, p; // 树 豆子 MOD
LL fact[maxn];

LL _pow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = a * ans % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

LL inv(LL a) {
    return _pow(a, p - 2);
}

LL c(LL n, LL m) {
    if (n < m) {
        return 0;
    }
    return fact[n] * inv(fact[m]) % p * inv(fact[n-m]) % p;
}

LL lucas(LL n, LL m) {
    if (m <= 0) {
        return 1;
    }
    return c(n % p, m % p) * lucas(n / p, m / p) % p;
}

void init() {
    fact[0] = 1;
    for (int i = 1; i <= p; ++i) {
        fact[i] = i * fact[i-1] % p;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld%lld", &n, &m, &p);
        init();
        LL ans = lucas(n + m, n);
        printf("%lld\n", ans % p);
    }
    return 0;
}

/*
// hdu 1018
// 斯特林公式 O(1)时间算阶乘
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
double E = exp(1), pi = acos(-1);
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        LL n;
        scanf("%lld", &n);
        if (n <= 15) {
            LL ans = 1;
            for (int i = 2; i <= n; ++i) {
                ans *= i;
            }
            int k = 0;
            while (ans) {
                ++k;
                ans /= 10;
            }
            printf("%d\n", k);
        } else {
            double ans = log10(2*n*pi) / 2 + n * log10(n/E) + 1;
            printf("%d\n", (int)ans);
        }
    }
    return 0;
}


// poj 3088
// 第二类斯特林数
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 20;
typedef long long LL;

LL dp[maxn][maxn], fact[maxn], c[maxn][maxn];

void init() {
    for (int i = 1; i < maxn; ++i) {
        dp[i][1] = 1;
        for (int j = 2; j < maxn; ++j) {
            dp[i][j] = dp[i-1][j-1] + j * dp[i-1][j];
        }
    }
    fact[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fact[i] = i * fact[i-1];
    }
    c[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
}

int main() {
    init();
    int t, n, ca = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d %d ", ++ca, n);
        LL ans = 0;
        //printf("ans : %lld\n", ans);
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= n-i; ++k) {
                ans += fact[k] * c[n][i] * dp[n-i][k];
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}


#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e7 + 10;

typedef long long LL;
LL dp[maxn][3];
double k[maxn];

void init() {
    dp[1][1] = 1;
    for (int i = 2; i < maxn; ++i) {
        dp[i][2] = dp[i-1][1] + (i-1) * dp[i-1][2];
    }
    for (int i = 1; i < maxn; ++i) {
        k[i] = k[i-1] * 1 / (double)i;
    }
}
// dp(n+1, 2) = n! * sum(i=1...n)1/i
int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        
        printf(<#const char *, ...#>)
    }
    return 0;
}


// 2512
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 2010, MOD = 1000;

int dp[maxn][maxn]; // longlong 超内存

void init() {
    dp[1][1] = 1;
    for (int i = 2; i < maxn; ++i) {
        for (int j = 1; j < maxn; ++j) {
            dp[i][j] = (dp[i-1][j-1] + j*dp[i-1][j] % MOD) % MOD;
        }
    }
}

int main() {
    init();
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = (ans + dp[n][i]) % 1000;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

// fzu 1570
// 第二类斯特林数
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1000;
typedef long long LL;

LL dp[maxn][maxn];

void init() {
    dp[1][1] = 1;
    for (int i = 2; i < maxn; ++i) {
        for (int j = 1; j < maxn; ++j) {
            dp[i][j] = dp[i-1][j-1] + j*dp[i-1][j];
        }
    }
}

int main() {
    init();
    int n;
    while (~scanf("%d", &n)) {
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += dp[n][i];
        }
        printf("%I64d\n", ans); // lld算运行错误
    }
    return 0;
}

// 2643 第二类斯特林数
// 排名相同的人分到同一个集合里，可分1、2、3...n个集合，乘上阶乘即可
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long LL;
const int maxn = 110, MOD = 20090126;
LL dp[maxn][maxn], fact[maxn];

void init() {
    dp[1][1] = 1;
    for (int i = 2; i < maxn; ++i) {
        for (int j = 1; j < maxn; ++j) {
            dp[i][j] = (dp[i-1][j-1] + j * dp[i-1][j] % MOD) % MOD;
        }
    }
    fact[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fact[i] = fact[i-1] * i % MOD;
    }
}

int main() {
    init();
    int t;
    scanf("%d", &t);
    while (t--) {
        LL n, ans = 0;
        scanf("%lld", &n);
        for (int i = 1; i <= n; ++i) {
            ans = (ans + dp[n][i] * fact[i] % MOD) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

// 4372
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int maxn = 2010, MOD = 1e9 + 7;

// 打表：第一类斯特林数，阶乘，逆元，阶乘的逆元
LL dp[maxn][maxn], fact[maxn], inv[maxn], ifact[maxn];
LL c[maxn][maxn];

void init() {
    dp[1][1] = 1;
    for (int i = 2; i < maxn; ++i) {
        for (int j = 1; j < maxn; ++j) {
            dp[i][j] = (dp[i-1][j-1] + (i-1) * dp[i-1][j] % MOD) % MOD;
        }
    }
    // 阶乘
    fact[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fact[i] = fact[i-1] * i % MOD;
    }
    // 逆元
    inv[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        inv[i] = (MOD - MOD/i) *inv[MOD%i] % MOD;
    }
    // 阶乘的逆元
    ifact[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        ifact[i] = ifact[i-1] * inv[i] % MOD;
    }
    // 或直接求出阶乘
    c[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
        }
    }
}

// 求组合数
LL C(LL m, LL n) {
    if (n < 0) {
        return 0;
    }
    return fact[m] * ifact[n] % MOD * ifact[m-n] % MOD;
}

int main() {
    init();
    int t;
    scanf("%d", &t);
    while (t--) {
        LL n, f, b;
        scanf("%lld%lld%lld", &n, &f, &b);

        //printf("%lld\n", dp[n-1][f+b-2] * C(f+b-2, f-1) % MOD);
        if (f + b - 1 > n) {
            printf("0\n");
        } else {
            printf("%lld\n", dp[n-1][f+b-2] * c[f+b-2][f-1] % MOD);
        }
    }
    return 0;
}


#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

bool vis[1000010];
int num[1000010];

struct node {
    int k;
    int road;
};

void bfs() {
    vis[1] = 1;
    num[1] = 1;
    queue<node> q;
    q.push({1, 1});
    
    while (!q.empty()) {
        node now = q.front();
        int k = now.k * 3 + 1, road = now.road + 1;
        if (now.k % 2 == 0) {
            // 偶数
            k = now.k / 2;
        }
        if (k > 1 && k < 1000000 && vis[k] == 0) {
            vis[k] = 1;
            node next = {k, road};
            q.push(next);
            num[k] = road;
        }
        
        if ((now.k - 1) % 3 == 0 && vis[(now.k - 1) / 3] == 0) {
            k = (now.k - 1) * 3;
            if (k > 1 && k < 1000000) {
                vis[k] = 1;
                node next = {k, road};
                q.push(next);
                num[k] = road;
            }
        }
        
        if (now.k% 2 == 0 && vis[now.k % 2] == 0) {
            k = now.k / 2;
            if (k > 1 && k < 1000000) {
                vis[k] = 1;
                node next = {k, road};
                q.push(next);
                num[k] = road;
            }
        }
        
        q.pop();
    }
}


// 1,000,000
int main() {
    
    bfs();
    for (int i = 1; i <= 30; ++i) {
        cout << i<< ' ' << num[i] << endl;
    }
    int a, b;
    while (~scanf("%d%d", &a, &b)) {
        int tmp = num[a];
        for (int i = a + 1; i <= b; ++i) {
            if (tmp < num[b]) {
                tmp = num[b];
            }
        }
        cout << tmp << endl;
        
        
    }
    return 0;
}


// 1031
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

struct node {
    int j;
    double sta;
} arr[10010];

int v[10010];

bool cmp1(struct node a, struct node b) {
    if (abs(a.sta - b.sta) < 0.000001) {
        return a.j < b.j;
    }
    return a.sta > b.sta;
}

bool cmp2(int a, int b) {
    return a > b;
}

int main() {
    
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k)) {
        memset(arr, 0, sizeof(arr));
        double a;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%lf", &a);
                arr[j].j = j + 1;
                arr[j].sta += a;
            }
        }
        sort(arr, arr + m, cmp1);
        for (int i = 0; i < k; ++i) {
            v[i] = arr[i].j;
        }
        sort(v, v + k, cmp2);
        for (int i = 0; i < k - 1; ++i) {
            printf("%d ", v[i]);
        }
        printf("%d\n", v[k - 1]);
    }
    return 0;
}


// 1022
// 栈 第一次做可能有点不会，但以前做过类似的，就相当于水题了
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

char in[1000010], out[1000010]; // 存储出入情况
bool result[2000010]; // 用于存储过程

int main() {
    
    int n;
    while (cin >> n) {
        stack<char> s; // 用栈比较方便
        scanf("%s", in);
        scanf("%s", out);
        
        int i = 0, j = 0, r = 0;
        while (i <= n) {
            if (s.size() > 0 && s.top() == out[j]) {
                s.pop();
                ++j;
                result[r++] = 0;
            } else {
                if (i < n) {
                    s.push(in[i]);
                    result[r++] = 1;
                }
                ++i;
            }
        }
        if (j != n) {
            cout << "No." << endl;
        } else {
            cout << "Yes." << endl;
            for (int k = 0; k < r; ++k) {
                if (result[k] == 0) {
                    cout << "out" << endl;
                } else {
                    cout << "in" << endl;
                }
            }
        }
        cout << "FINISH" << endl;
        
    }
    return 0;
}


// 1021 斐波那契数列
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int arr[1000010] = {1, 2};

int main() {
    for (int i = 2; i < 1000000; ++i) {
        arr[i] = (arr[i - 1] + arr[i - 2]) % 3;
    }
    int n;
    while (~scanf("%d", &n)) {
        
        if (arr[n] % 3 == 0) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    return 0;
}


// 1020
// 水题
#include <iostream>
#include <cstdio>
using namespace std;

char str[10010];

int main() {
    
    int N;
    cin >> N;
    while (N--) {
        cin >> str;
        int i = 0, j = 0, num = 1;
        while (str[i] != '\0') {
            if (str[i + 1] != str[i]) {
                if (num > 1) {
                    char n[10];
                    sprintf(n, "%d", num);
                    for (int k = 0; n[k]; ++k) {
                        str[j++] = n[k];
                    }
                }
                str[j++] = str[i++];
                num = 1;
            } else {
                num++;
                i++;
            }
        }
        str[j] = '\0';
        cout << str << endl;
    }
    
    return 0;
}


// 1019
// 求多个数的 lcm，水题（虽然本来以为暴力会超时..结果过了..）
// 注意 gcd 和 lcm 的求法即可
#include <iostream>
#include <cstdio>

using namespace std;

long long int gcd(long long int a, long long int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

long long int lcm(long long int a, long long int b) {
    return a * b / gcd(a, b);
}

int main() {
    int T, n, a;
    cin >> T;
    while (T--) {
        long long int l = 1;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a);
            l = lcm(a, l);
        }
        printf("%lld\n", l);
    }
    return 0;
}


// 1017
// 水题，暴力
// 注意判断能否整除：取模
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    
    int T, n, m;
    cin >> T;
    while (T--) {
        int ca = 1;
        // 这里wa了几次...因为存在一个数为0，一个数不为0的情况
        // 所以不能 (n && m)，只能 (n || m) 或者 (n + m)
        while (cin >> n >> m && (n || m)) {
            int count = 0;
            for (int a = 1; a < n; ++a) {
                for (int b = a + 1; b < n; ++b) {
                    if ((a * a + b * b + m) % (a * b) == 0) {
                        ++count;
                    }
                }
            }
            printf("Case %d: %d\n", ca++, count);
        }
        // 注意格式，两段之间有个空行
        if (T > 0) {
            cout << endl;
        }
    }
    return 0;
}


// 1016
// 深搜 + 素数打表
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int n;
bool prime[41] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0};
int vis[21];
vector<int> v;

void dfs(int now, int road) {
    v.push_back(now);
    if (road == n) {
        if (prime[now + 1] == 0) {
            v.pop_back();
            return;
        }
        for (int i = 0; i < v.size() - 1; ++i) {
            cout << v[i] << ' ';
        }
        cout << v[v.size() - 1] << endl;
        v.pop_back();
        return;
    }
    for (int i = 2; i <= n; ++i) {
        if (vis[i] == 0 && prime[i + now] == 1) {
            vis[i] = 1;
            dfs(i, road + 1);
            vis[i] = 0;
        }
    }
    v.pop_back();
}

int main() {
    
    int ca = 1;
    while (cin >> n) {
        v.clear();
        memset(vis, 0, sizeof(vis));
        printf("Case %d:\n", ca++);
        dfs(1, 1);
        cout << endl;
    }
    return 0;
}


// 1015
// 深搜，做完看网上题解也有用暴力的，应该也可以
// wa了一次，后来发现需要先排序，这样可以保证最后的顺序是最大的
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int target, flag, len;
vector<int> v;
char letter[20];

// v - w^2 + x^3 - y^4 + z^5 = target
void dfs(int now, int road) {
    if (road < 1) return;
    v.push_back(now);
    
    if (road == 1) {
        //cout << v.size() << endl;
        int sum = letter[v[0]] - 'A' + 1 - pow(letter[v[1]] - 'A' + 1, 2) + pow(letter[v[2]] - 'A' + 1, 3) - pow(letter[v[3]] - 'A' + 1, 4) + pow(letter[v[4]] - 'A' + 1, 5);
        
        if (sum == target) {
            flag = 1;
        } else {
            v.pop_back();
        }
        return;
    }
    
    for (int i = len - 1; i >= 0; --i) {
        int k = 0;
        for (int j = 0; j < v.size(); ++j) {
            if (i == v[j]) {
                k = 1;
                break;
            }
        }
        if (k == 1 || i == now) continue;
        
        dfs(i, road - 1);
        if (flag) return;
        
    }
    v.pop_back();
}

int main() {
    
    while (~scanf("%d%s", &target, letter) && target) {
        len = (int)strlen(letter);
        sort(letter, letter + len);
        v.clear();
        flag = 0;
        for (int i = len - 1; i >= 0; --i) {
            dfs(i, 5);
            if (flag == 1) {
                for (int j = 0; j < 5; ++j) {
                    cout << letter[v[j]];
                }
                cout << endl;
                break;
            }
        }
        if (flag == 0) {
            cout << "no solution" << endl;
        }
    }
    return 0;
}


// 1014
// (x0 + n * step) % mod, 且不用考虑 x0 为多少
// 所以只需考虑 n * step % mod
// 因为 n 每次 + 1，下一个答案比上一个 大 (n + 1 - n) * step % mod
// 所以下一个答案为 上一个答案 +step 后 % mod
// 因此必须让其最大公约数为 1，否则会跳过一些数

#include <iostream>
#include <cstdio>
#include <cstring>

int gcd(int a, int b) {
    return (a % b == 0) ? b : gcd(b, a % b);
}

using namespace std;

int main() {
    
    int a, b;
    while (cin >> a >> b) {
        printf("%10d%10d    ", a, b);
        if(gcd(a, b) == 1) {
            cout << "Good Choice" << endl << endl;
        } else {
            cout << "Bad Choice" << endl << endl;
        }
    }
    return 0;
}


// 1013 最优方法，数论

// 九余定理：对于一个数 x ，只要 x 能除尽 9， 则 x 的各位数之和也能除尽 9
// (对于 3 也成立，因为能除尽 9 了，肯定也能除尽 3 )

// 证明：
// x = a * 1000 + b * 100 + c * 10 + d
//   = a * 999 + b * 99 + c * 9 + (a + b + c + d)
//   = 9 * (a * 99 + b * 9 + c) + (a + b + c + d)

// 前半部分可整除 9 ，因此 若 a + b + c + d 也能除尽 9，即 x 可除尽 9

// 现在我们不要求整除，而是求其余数：
 
// 因为 x = 9 * (a * 99 + b * 9 + c) + (a + b + c + d)
// 所以 x % 9 = (a + b + c + d) % 9
// 但是不能直接用 x % 9 代替各位数字之和，因为若 x 能整除 9
// 例 18，18 % 9 = 0，但各位数字之和为 9
// 所以用 （x - 1） % 9 + 1 表示其各位数字之和

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    char str[1010];
    while (~scanf("%s", str) && strcmp(str, "0") != 0) {
        int sum = 0;
        for (int i = 0; str[i]; ++i) {
            sum += str[i] - '0';
        }
        cout << (sum - 1) % 9 + 1<< endl;
        
    }
    
    return 0;
}


// 1013 中等方法
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    char str[1010];
    while (~scanf("%s", str) && strcmp(str, "0") != 0) {
        int sum = 0;
        for (int i = 0; str[i]; ++i) {
            sum += str[i] - '0';
            if (sum >= 10) {
                // 每次相加都检验，所以只可能是两位数
                sum = sum % 10 + sum / 10;
            }
        }
        cout << sum << endl;
    }
    return 0;
}


// 1013 比较挫的方法....
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main() {
    char str[1010];
    int n;
    while (~scanf("%s", str) && strcmp(str, "0") != 0) {
    flag:
        n = 0;
        for (int i = 0; str[i]; ++i) {
            n += str[i] - '0';
        }
        if (n >= 10) {
            memset(str, '0', sizeof(str));
            sprintf(str, "%d", n);
            goto flag;
        }
        cout << n << endl;
    }
    
    return 0;
}


// 水题
// 1012
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int n = 9;
    double e = 2.5, sum = 2;
    printf("n e\n- -----------\n0 1\n1 2\n2 2.5\n");
    for (int i = 3; i <= n; ++i) {
        sum *= i;
        e += 1 / sum;
        printf("%d %0.9lf\n", i, e);
    }
    return 0;
}


// 贪心水题 排序
// 1009
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Food {
    int j, f;
    double k;
} food[1010];

bool cmp(Food a, Food b) {
    return a.k > b.k;
}

int main() {
    int m, n;
    while (~scanf("%d%d", &m, &n) && (m != -1 && n != -1)) {
        for (int i = 0; i < n; ++i) {
            cin >> food[i].j >> food[i].f;
            food[i].k = (double)food[i].j / food[i].f;
        }
        sort(food, food + n, cmp);
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            if (m > food[i].f) {
                sum += food[i].j;
                m -= food[i].f;
            } else if (m > 0) {
                sum += (double)m / food[i].f * food[i].j;
                break;
            } else {
                break;
            }
        }
        printf("%0.3lf\n", sum);
    }
    
    return 0;
}


// 水题
// 1008
#include <iostream>
#include <cstdio>
using namespace std;

int arr[1010];

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        long long int sum = 0;
        cin >> arr[0];
        sum += arr[0] * 6;
        for (int i = 1; i < n; ++i) {
            cin >> arr[i];
            if (arr[i] > arr[i - 1]) {
                sum += 6 * (arr[i] - arr[i - 1]);
            } else if (arr[i] < arr[i - 1]) {
                sum += 4 * (arr[i - 1] - arr[i]);
            }
        }
        cout << n * 5 + sum << endl;
    }
    
    return 0;
}


// 1002 大数相加
#include <iostream>
#include <cstdio>
using namespace std;

// 大数相加

void sum_a_b(char a[], char b[], int len1, int len2) {
    int q = 0;
    len1--, len2—; // len1 和 len2 为长度，减 1 后为下标
    int sum[1010], i = 0; // sum 数组存储结果，i 存储 sum 的下标
    while (len1 >= 0 && len2 >= 0) { // 从两数组最后一位开始计算
        sum[i++] = (q + a[len1] + b[len2] - 2 * '0') % 10;
        q = (q + a[len1--] + b[len2--] - 2 * '0') / 10;
    }
    // 若某一个数较长，继续加
    while (len1 >= 0) {
        sum[i++] = (q + a[len1] - '0') % 10;
        q = (q + a[len1--] - '0') / 10;
    }
    while (len2 >= 0) {
        sum[i++] = (q + b[len2] - '0') % 10;
        q = (q + b[len2--] - '0') / 10;
    }
    // 加上进位的 q，若 q 为0 也没关系，下一步会去除 0
    sum[i] = q;
    
    // 若得出的 sum 中开头有过多的0
    while (sum[i] == 0) {
        --i;
    }
    
    // 这里为输出，需要将 sum 从后往前输出
    for (int j = i; j >= 0; --j) {
        cout << sum[j];
    }
    cout << endl;
}

int main() {
    int n, len1, len2;
    char a[1010], b[1010];
    char ch;
    cin >> n;
    scanf("%c", &ch);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << endl;
        len1 = len2 = 0;
        printf("Case %d:\n", i);
        int flag1 = 0, flag2 = 0;
        while (scanf("%c", &a[len1]) && a[len1] != ' ') {
            if (flag1 == 0) {
                if (a[len1] != '0') {
                    flag1 = 1;
                }
            }
            if (flag1) {
                cout << a[len1++];
            } else {
                ++len1;
            }
        }
        cout << " + ";
        while (scanf("%c", &b[len2]) && b[len2] != '\n') {
            if (flag2 == 0) {
                if (b[len2] != '0') {
                    flag2 = 1;
                }
            }
            if (flag2) {
                cout << b[len2++];
            } else {
                ++len2;
            }
        }
        cout << " = ";
        sum_a_b(a, b, len1, len2);
        
    }
    return 0;
}

// 水题
// 1001
#include <iostream>
using namespace std;

int main() {
    long long int n;
    while (cin >> n) {
        cout << (1 + n) * n / 2 << endl;
        cout << endl;
    }
    
    return 0;
}

// 水题
// 1000
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int a, b;
    while (cin >> a >> b) {
        cout << a + b << endl;
    }
    return 0;
}
*/
