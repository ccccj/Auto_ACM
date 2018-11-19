//
//  main.cpp
//  容斥原理
//
//  Created by admin on 18/9/25.
//  Copyright © 2018年 Amon. All rights reserved.
//
// hdu 3929
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 20;
int n;
LL arr[maxn], ans;

int countbit(LL x) {
    int ret = 0;
    while (x) {
        x = x & (x - 1);
        ++ret;
    }
    return ret;
}

void dfs(int k, LL ret, int t) {
    ans += (1LL << countbit(ret)) * t;
    for (int i = k + 1; i < n; ++i) {
        dfs(i, ret & arr[i], t * -2);
    }
}

int main() {
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &arr[i]);
        }
        for (int i = 0; i < n; ++i) {
            dfs(i, arr[i], 1);
        }
        printf("Case #%d: %lld\n", ca++, ans);
    }
    return 0;
}

/*
// hdu 5212
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 1e4 + 10;
LL p[maxn], arr[maxn], p = 10007;

void divide(LL x) {
    LL i = 2;
    ++p[x];
    for ( ; i * i < x; ++i) {
        if (x % i == 0) {
            ++p[i];
            ++p[x / i];
        }
    }
    if (x == i * i) {
        ++p[i];
    }
}

int main() {
    LL n, x;
    while (~scanf("%lld", &n)) {
        memset(p, 0, sizeof(p));
        LL ans = 0;
        for (LL i = 1; i <= n; ++i) {
            scanf("%lld", &x);
            arr[i] = x;
            ans += x * (x - 1);
            divide(x);
        }
        for (LL i = maxn - 1; i > 1; --i) {
            if (p[i]) {
                p[i] = p[i] * (p[i] - 1) % p;
                int t = 0;
                for (int j = 2; i * j < maxn; ++j) {
                    if (p[i * j]) {
                        t = (t + p[i * j]) % p;
                    }
                }
                p[i] =(p[i] - t) % p;
                ans = (ans + p[i] * i % p * (i - 1) % p) % p;
            }
        }
        printf("%lld\n", (ans + p) % p);
        
    }
    return 0;
}

// hdu 6397
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 2e5 + 10;

LL fact[maxn] = {1}, inv[maxn], p = 998244353;

LL fastpow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}

void init() {
    for (int i = 1; i < maxn; ++i) {
        fact[i] = i * fact[i - 1] % p;
    }
    inv[maxn - 1] = fastpow(fact[maxn - 1], p - 2);
    for (int i = maxn - 2; i >= 0; --i) {
        inv[i] = inv[i + 1] * (i + 1) % p;
    }
}

LL C(LL n, LL m) {
    if (n < m) {
        return 0;
    }
    return fact[n] * inv[m] % p * inv[n - m] % p;
}

int main() {
    init();
    int t;
    scanf("%d", &t);
    while (t--) {
        LL n, m, k, ans = 0;
        scanf("%lld%lld%lld", &n, &m, &k);
        for (int i = 0; i <= m; ++i) {
            if (m + k - 1 - n * i < m - 1) {
                break;
            }
            ans = (ans + (LL)pow(-1, i % 2) * C(m, i) * C(m + k - 1 - n*i, m - 1) % p) % p;
        }
        printf("%lld\n", (ans + p) % p);
    }
    return 0;
}
 
// CF 547C
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 10;
LL arr[maxn], factor[maxn], p[maxn], num[maxn], cnt, now;
bool vis[maxn];

void divide(LL x) {
    cnt = 0;
    for (LL i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            factor[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        factor[cnt++] = x;
    }
}

LL slove(LL status) {
    LL ans = 0;
    for (LL i = 1; i < 1 << cnt; ++i) {
        LL sum = 1, t = 0;
        for (int j = 0; j < cnt; ++j) {
            if (i & (1 << j)) {
                ++t;
                sum *= factor[j];
            }
        }
        num[sum] = t;
        if (status == 1) {
            ans += pow(-1, (num[sum] + 1)% 2) * p[sum];
            ++p[sum];
        } else {
            --p[sum];
            ans += pow(-1, (num[sum] + 1)% 2) * p[sum];
        }
    }
    return ans;
}

int main() {
    int n, q;
    LL x, last = 0;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", & arr[i]);
    }
    for (int i = 0; i < q; ++i) {
        scanf("%lld", &x);
        vis[x] ^= 1;
        
        divide(arr[x]);
        LL k = slove(vis[x]);
        if (vis[x] == 0) {
            // -
            --now;
            printf("%lld\n", last - now + k);
            last = last - now + k;
        } else {
            // +
            printf("%lld\n", last + now - k);
            last += now - k;
            ++now;
        }
    }
    return 0;
}


// poj 3904
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 1e4 + 10;
int factor[maxn], p[maxn], num[maxn], cnt;
LL ans;

LL C(LL n) {
    return n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4;
}


void divide(LL t) {
    cnt = 0;
    for (int i = 2; i * i <= t; ++i) {
        if (t % i == 0) {
            factor[cnt++] = i;
            while (t % i == 0) {
                t /= i;
            }
        }
    }
    if (t > 1) {
        factor[cnt++] = (int)t;
    }
}

void slove() {
    for (int i = 1; i < 1 << cnt; ++i) {
        int t = 0, sum = 1;
        for (int j = 0; j < cnt; ++j) {
            if (i & (1 << j)) {
                ++t;
                sum *= factor[j];
            }
        }
        num[sum] = t;
        ++p[sum];
    }
}

int main() {
    int n, x;
    while (~scanf("%d", &n)) {
        memset(num, 0, sizeof(num));
        memset(p, 0, sizeof(p));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            divide(x);
            slove();
        }
        ans = 0;
        for (int i = 0; i <= 10000; ++i) {
            if (p[i] >= 4) {
                ans += pow(-1, num[i] % 2) * C(p[i]);
            }
        }
        printf("%lld\n", C(n) + ans);
    }
    return 0;
}

// CF 451E
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 25, p = 1e9 + 7;
LL n, s, arr[maxn], ans = 0;

LL fact(LL n, LL m) {
    LL ans = 1;
    for (LL i = n; i <= n + m - 1; ++i) {
        ans = ans *  i % p;
    }
    return ans;
}

LL fastpow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}

LL x, y;
void exgcd(LL a, LL b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
}

LL inv(LL a) {
//    exgcd(a, p);
//    return x;
    return fastpow(a, p - 2);
}

LL C(LL n, LL m) {
    if (n < m) {
        return 0;
    }
    return fact(n - m + 1, m) * inv(fact(1, m)) % p;
}

LL lucas(LL n, LL m) {
    if (m <= 0) {
        return 1;
    }
    return C(n%p, m%p) * lucas(n/p, m/p) % p;
}

void dfs(int k, int now, LL ret) {
    if (ret > s + n - 1) {
        return;
    }
    ans = (ans + (LL)pow(-1, now % 2) * lucas(s + n - 1 - ret, n - 1)) % p;
    for (int i = k + 1; i < n; ++i) {
        dfs(i, now + 1, ret + arr[i] + 1);
    }
}

int main() {
    scanf("%lld%lld", &n, &s);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }
    ans = lucas(s + n - 1, n - 1);
    for (int i = 0; i < n; ++i) {
        dfs(i, 1, arr[i] + 1);
    }
    printf("%lld\n", (ans % p + p) % p);
    return 0;
}


// hdu 4407
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
typedef long long LL;
LL x, y, len;

vector<LL> factor;
LL ans;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

void dfs(int k, int now, LL ret) {
    if (ret > 400000) {
        return;
    }
    LL a = (y / ret + 1) * (y / ret);
    LL b = ((x - 1) / ret + 1) * ((x - 1) / ret);
    ans += pow(-1, (now + 1) % 2) * (a - b) * ret / 2;
    for (int i = k + 1; i < len; ++i) {
        dfs(i, now + 1, ret * factor[i]);
    }
}

int main() {
    LL t, n, m, com, c, p;
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        map<LL, LL> mp;
        for (int i = 0; i < m; ++i) {
            scanf("%lld", &com);
            if (com == 1) {
                scanf("%lld%lld%lld", &x, &y, &p);
                factor.clear();
                LL tmp = p;
                for (int j = 2; j * j <= tmp; ++j) {
                    if (tmp % j == 0) {
                        factor.push_back(j);
                        while (tmp % j == 0) {
                            tmp /= j;
                        }
                    }
                }
                if (tmp > 1) {
                    factor.push_back(tmp);
                }
                ans = 0;
                len = (int)factor.size();
                for (int j = 0; j < len; ++j) {
                    dfs(j, 1, factor[j]);
                }
                ans = (1 + y) * y / 2 - (x - 1) * x / 2 - ans;
                map<LL, LL>::iterator it = mp.begin();
                for (; it != mp.end(); ++it) {
                    if (it->first >= x && it->first <= y) {
                        if (gcd(p, it->first) == 1) {
                            ans -= it->first;
                        }
                        if (gcd(p, it->second) == 1) {
                            ans += it->second;
                        }
                    }
                }
                printf("%lld\n", ans);
            } else {
                // 修改
                scanf("%lld%lld", &x, &c);
                mp[x] = c;
            }
        }
    }
    return 0;
}


// hdu 3208
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
LL a, b, ans, ret;

struct node {
    LL t, num;
};
vector<node> mi;

LL fastpow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            double judge = 1.0 * ((LL)(1e18) + 500) / ans;
            if (a > judge) return -1;
            ans *= a;
        }
        b >>= 1;
        if (a > ((LL)1 << 31) && b > 0)
            return -1;
        a=a*a;
    }
    return ans;
}

LL _pow(LL x, LL k) { // 求 x ^ (1/k)
    LL r = (LL)pow(x, 1.0/k);
    LL t, p;
    p = fastpow(r, k);
    if (p == x) {
        return r;
    }
    // 提高精度
    
    if (p > x || p == -1) {
        r--;
    } else {
        t = fastpow(r + 1, k);
        if (t != -1 && t <= x) r++;
    }
    return r;
}

int main() {
    while (~scanf("%lld%lld", &a, &b) && a + b) {
        ans = b - a + 1;
        
        mi.clear();
        for (int i = 63; i >= 2; --i) {
            LL t1 = (LL)(_pow(b, i));
            LL t2 = (LL)(_pow(a - 1, i));
            LL tmp = (t1 - t2) * (i - 1);
            if (tmp != 0) {
                mi.push_back({i, t1 - t2});
            }
        }
        int len = (int)mi.size();
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < i; ++j) {
                if (mi[j].t % mi[i].t == 0) {
                    mi[i].num -= mi[j].num;
                }
            }
            ans += mi[i].num * (mi[i].t - 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// URAL 1091
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

int k, s;
LL ret, ans;

LL C(int n, int m) {
    if (n < m) {
        return 0;
    }
    LL ans = 1;
    for (int i = 1; i <= m; ++i) {
        ans = ans * (n - i + 1) / i;
    }
    return ans;
    
}

void dfs(int t, int now) {
    if (ret > s) {
        return;
    }
    int num = s / ret;
    ans += pow(-1, (now+1)%2) * C(num, k);
    
    for (int i = t + 1; i < 17; ++i) {
        ret *= prime[i];
        dfs(i, now + 1);
        ret /= prime[i];
    }
}

int main() {
    
    scanf("%d%d", &k, &s);
    for (int i = 0; i < 17; ++i) {
        ret = prime[i];
        dfs(i, 1);
    }
    printf("%lld\n", ans > 10000 ? 10000 : ans);
    return 0;
}


// hdu 1695
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
LL n, m, ans, len, ret;
vector<int> p;

void dfs(int k, int now, LL range) {
    if (ret > range) {
        return;
    }
    ans += pow(-1, (now+1)%2) * (range / ret);
    for (int i = k + 1; i < len; ++i) {
        ret *= p[i];
        dfs(i, now + 1, range);
        ret /= p[i];
    }
}

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main() {
    
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        printf("Case %d: ", ca++);
        LL k, a, b;
        scanf("%lld%lld%lld%lld%lld", &a, &n, &b, &m, &k);
        if (k == 0) {
            printf("0\n");
            continue;
        }
        if (m > n) {
            swap(n, m);
        }
        m /= k, n /= k;
        ans = 0;
        for (int t = 1; t <= n; ++t) {
            int tmp = t;
            p.clear();
            for (int i = 2; i * i <= tmp; ++i) {
                if (tmp % i == 0) {
                    p.push_back(i);
                    while (tmp % i == 0) {
                        tmp /= i;
                    }
                }
            }
            if (tmp > 1) {
                p.push_back(tmp);
            }
            len = (LL)p.size();
            for (int i = 0; i < len; ++i) {
                ret = p[i];
                dfs(i, 1, min(m, t));
            }
        }
        //ans++;
        //printf("%lld\n", ans);
        printf("%lld\n", (n - m) * m + m + (m * m - m) / 2 - ans);
    }
    return 0;
}


// hdu 2841
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;
LL n, m;
LL ans, ret, len;
vector<int> v;

void dfs(int k, int now) {
    if (ret > n) {
        return;
    }
    ans += (LL)pow(-1, (now + 1) % 2) * n / ret;
    for (int i = k + 1; i < len; ++i) {
        ret *= v[i];
        dfs(i, now + 1);
        ret /= v[i];
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        ans = 0;
        for (int k = 1; k <= m; ++k) {
            v.clear();
            int tmp = k;
            for (int i = 2; i * i <= tmp; ++i) {
                if (tmp % i == 0) {
                    v.push_back(i);
                    while (tmp % i == 0) {
                        tmp /= i;
                    }
                }
            }
            if (tmp > 1) {
                v.push_back(tmp);
            }
            len = (LL)v.size();
            for (int i = 0; i < len; ++i) {
                ret = v[i];
                dfs(i, 1);
            }
        }
        printf("%lld\n", n * m - ans);
        
    }
    return 0;
}


// hdu 4135
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;
LL a, b, n, len, ans, ret;
vector<int> p;
void dfs(int k, int now) {
    ans += pow(-1, (now+1) % 2) * (b / ret - (a-1) / ret);
    for (int i = k + 1; i < len; ++i) {
        ret *= p[i];
        dfs(i, now + 1);
        ret /= p[i];
    }
}

int main() {
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        printf("Case #%d: ", ca++);
        scanf("%lld%lld%lld", &a, &b, &n);
        p.clear();
        int tmp = (int)n;
        for (int i = 2; i * i <= tmp; ++i) {
            if (tmp % i == 0) {
                p.push_back(i);
                while (tmp % i == 0) {
                    tmp /= i;
                }
            }
        }
        if (tmp > 1) {
            p.push_back(tmp);
        }
        len = (LL)p.size(), ans = 0;
        for (int i = 0; i < len; ++i) {
            ret = p[i];
            dfs(i, 1);
        }
        printf("%lld\n", b - a + 1 - ans);
    }
    return 0;
}


// hdu 1796
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 15;
LL p[maxn], n, m, ans, ret;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

void dfs(int k, int now) {
    if (ret > n) return;
    
    ans += pow(-1, (now + 1) % 2) * (n / ret);
    for (int i = k + 1; i < m; ++i) {
        LL g = gcd(ret, p[i]);
        ret = ret * p[i] / g;
        //ret *= p[i];
        dfs(i, now + 1);
        ret = ret * g / p[i];
        //ret /= p[i];
    }
}

int main() {
    while (~scanf("%lld%lld", &n, &m)) {
        --n;
        int x;
        for (int i = 0; i < m; ++i) {
            scanf("%d", &x);
            if (x != 0) {
                p[i] = x;
            } else {
                --i, --m;
            }
        }
        ans = 0;
        for (int i = 0; i < m; ++i) {
            ret = p[i];
            dfs(i, 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// hdu 2204
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
// 在 1-n 内可以使得，开k次方的，有 n^(1/k) 个数
const int maxn = 65;
const double EPS = 1e-7;
vector<int> prime;
bool judge[maxn];
LL n, ret, ans;

void init() {
    for (int i = 2; i < maxn; ++i) {
        if (judge[i] == 0) {
            prime.push_back(i);
            for (int j = 2; i * j < maxn; ++j) {
                judge[i * j] = 1;
            }
        }
    }
}

void dfs(int k, int now) {
    
    if (ret > 60) return;
    
    ans += pow(-1, (now+1) % 2) * (LL)(pow(n, (double)1/ret) + EPS - 1);
    
    for (int i = k + 1; prime[i] <= 60; ++i) {
        ret *= prime[i];
        dfs(i, now + 1);
        ret /= prime[i];
    }
}

int main(int argc, const char * argv[]) {
    init();
    while (~scanf("%lld", &n)) {
        ans = 0;
        for (int i = 0; prime[i] <= 60; ++i) {
            ret = 1;
            ret *= prime[i];
            dfs(i, 1);
        }
        printf("%lld\n", ans + 1);
    }
    return 0;
}
*/
