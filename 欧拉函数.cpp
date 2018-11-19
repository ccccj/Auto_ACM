//
//  main.cpp
//  欧拉函数
//
//  Created by admin on 18/9/17.
//  Copyright © 2018年 Amon. All rights reserved.
//

/*
// sustoj 1908
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


// 计蒜客 分数化小数
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

LL Euler(LL x) {
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

LL fastpow(LL a, LL b, LL p) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main() {
    
    LL p, q;
    while (~scanf("%lld%lld", &p, &q)) {
        if (p % q == 0) {
            printf("%lld.0\n", p / q);
            continue;
        }
        LL z = p / q, g = gcd(p, q);
        p /= g, q /= g;
        p %= q;
        LL tmpq = q, tmpp = p * 10;
        int i1 = 0, i2 = 0;
        while (q % 2 == 0) {
            ++i1;
            q /= 2;
        }
        while (q % 5 == 0) {
            q /= 5;
            ++i2;
        }
        int i = max(i1, i2);
        LL phi = Euler(q), Min = 0x3fffffff;
        vector<int> factor;
        for (int j = 1; j * j <= phi; ++j) {
            if (phi % j == 0) {
                if (fastpow(10, j, q) == 1) {
                    Min = j;
                    break;
                }
                if (fastpow(10, phi/j, q) == 1) {
                    Min = min(phi / j, Min);
                }
            }
        }
        if (Min == 0x3fffffff) {
            printf("%lld.", z);
            for (int k = 0; ; ++k) {
                LL t = tmpp / tmpq;
                printf("%lld", t);
                tmpp = (tmpp - t * tmpq) * 10;
                if (tmpp == 0) {
                    break;
                }
            }
            printf("\n");
            continue;
        }
        //printf("%d %lld\n", i + 1, Min);
        printf("%lld.", z);
        for (int k = 0; k < i; ++k) {
            LL t = tmpp / tmpq;
            printf("%lld", t);
            tmpp = (tmpp - t * tmpq) * 10;
        }
        printf("(");
        for (int k = 0; k < Min; ++k) {
            LL t = tmpp / tmpq;
            printf("%lld", t);
            tmpp = (tmpp - t * tmpq) * 10;
        }
        printf(")\n");
    }
    return 0;
}


// hdu 3221
#include <cstdio>
using namespace std;
typedef long long LL;
LL p, phi;
int f1, f2;

void mul(LL a[2][2], LL b[2][2], int f) {
    LL ret[2][2] = {0, 0, 0, 0};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                ret[i][k] = ret[i][k] + a[i][j] * b[j][k];
                if (ret[i][k] >= phi) {
                    ret[i][k] = ret[i][k] %phi+ phi;
                }
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            a[i][j] = ret[i][j];
        }
    }
}

void pow(LL di[2][2], LL ret[2][2], LL n) {
    while (n) {
        if (n & 1) {
            mul(ret, di, 1);
        }
        mul(di, di, 2);
        n >>= 1;
    }
}

LL Euler(LL x) {
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

LL fastpow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

int main() {
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        f1 = 0, f2 = 0;
        LL a, b, n;
        scanf("%lld%lld%lld%lld", &a, &b, &p, &n);
        phi = Euler(p);
        
        LL di[2][2] = {1, 1, 1, 0};
        LL ret[2][2] = {1, 0, 0, 1};
        pow(di, ret, n - 1);
        LL x = ret[1][1], y = ret[1][0];
        printf("Case #%d: %lld\n", ca++, fastpow(a, x) * fastpow(b, y) % p);
    }
    return 0;
}


// poj 3358
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

LL Euler(LL x) {
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

LL fastpow(LL a, LL b, LL p) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

int main() {
    LL p, q, ca = 1;
    while (~scanf("%lld/%lld", &p, &q)) {
        if (p == q || p == 0) {
            printf("Case #%lld: 1,1\n", ca++);
            continue;
        }
        LL g = gcd(p, q);
        p /= g, q /= g; // p q 互质了
        // p * 2^i = p * 2^j mod q
        // p * 2^i * (2^(j-i) - 1) = 0 mod q
        // p,q 互质 所以
        LL i = 1;
        while (q % 2 == 0) {
            ++i;
            q /= 2;
        }
        // q | 2^(j-i) - 1
        // 2^(j-i) = 1 mol q
        LL phi = Euler(q);
        // j - i 是 phi的约数
        LL Min = phi;
        for (LL x = 1; x * x <= phi; ++x) {
            if (phi % x == 0) {
                if (fastpow(2, x, q) % q == 1) {
                    printf("Case #%lld: %lld,%lld\n", ca++, i, x);
                    break;
                }
                if (fastpow(2, phi/x, q) % q == 1) {
                    Min = min(Min, phi/x);
                }
            }
        }
        printf("Case #%lld: %lld,%lld\n", ca++, i, Min);
    }
    return 0;
}


#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
vector<int> p;
LL phi[maxn], s[maxn];
bool judge[maxn];

void Euler() {
    phi[1] = 1;
    s[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            p.push_back(i);
            judge[i] = 1;
        }
        int len = (int)p.size();
        for (int j = 0; j < len && i * p[j] < maxn; ++j) {
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            } else {
                phi[i * p[j]] = phi[i] * (p[j] - 1);
            }
        }
        s[i] = s[i-1] + phi[i];
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    Euler();
    int t, a, b, c, d, k, Min, Max;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        Min = min(b, d);
        Max = max(b, d);
        LL sum = s[Min/k];
        
        printf("%lld\n", sum);
    }
    return 0;
}



// hdu 2837
// [欧拉定理]
// A^x % m = A^(x%phi(m)+phi(m)) % m (x >= phi(m)才成立，所以需要在快速幂中判断)
#include <cstdio>
using namespace std;
typedef long long int LL;

LL Euler(LL x) {
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

LL fastpow(LL a, LL b, LL mod) {
    LL ret = 1;
    LL add = 0;
    int f = 0;
    for (int i = 1; i <= b; ++i) {
        ret = ret * a;
        if (ret > mod) {
            add = mod;
            f = 1;
            break;
        }
    }
    if (f) {
        ret = 1;
        while(b) {
            if(b & 1) {
                ret = ret * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
    }
    return ret + add;
}

LL solve(LL n, LL m) {
    if (n == 0) return 1;
    LL phi = Euler(m);
    return fastpow(n % 10, solve(n / 10, phi), m);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        LL n, m;
        scanf("%lld%lld", &n, &m); // f(n) % m
        printf("%lld\n", solve(n, m) % m);
    }
    return 0;
}


// hdu 4335
#include <cstdio>
using namespace std;
typedef unsigned long long LL;

LL phi(LL x) {
    LL ans = x;
    for (int i = 2; i * i <= x; ++i) {
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

LL fastpow(LL a, LL b, LL p) {
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

int main() {
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        LL b, p, m;
        scanf("%llu%llu%llu", &b, &p, &m);
        if (b == 0 && p == 1) {
            printf("Case #%d: ", ca++);
            if (m == 18446744073709551615ULL) {
                printf("18446744073709551616\n");
            } else {
                printf("%llu\n", m + 1);
            }
            continue;
        }
        LL ph = phi(p), ans = 0, i;
        LL sum = 1;
        
        for (i = 0; i <= p; ++i) {
            if (sum % ph == 0) break;
            if (fastpow(i, sum + ph, p) == b) ++ans;
            sum = sum * (i+1) % ph + ph;
        }
        for (LL now = i; now < i + p && now <= m; ++now) {
            if (fastpow(now, ph, p) == b) {
                ans += (m - now) / p + 1;
            }
            //if (sum % ph == 0) break;
        }
        
        printf("Case #%d: %llu\n", ca++, ans);
    }
    return 0;
}


// poj 3696
// 若正整数 a , n 互质，则满足 a ^ x ≡ 1 (mod n) 的最小正整数 x0 是 φ(n) 的约数。
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;

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

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    LL p;
    int ca = 1;
    while (~scanf("%lld", &p) && p) {
        printf("Case %d: ", ca++);
        p /= gcd(p, 8);
        p *= 9;
        if (gcd(p, 10) == 1) {
            LL ans = phi(p);
            LL i = 0;
            int f = 0;
            LL tmp = sqrt(ans);
            
            for (i = 1; i * i <= ans; ++i) {
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
            printf("0\n");
        }
        
    }
    return 0;
}


// hdu 1787
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;

LL phi(LL x) {
    LL ans = x;
    for (int i = 2; i * i <= x; ++i) {
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

int main() {
    
    int n;
    while (~scanf("%d", &n) && n) {
        printf("%lld\n", n - phi(n) - 1);
    }
    return 0;
}


// hdu 2855
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;

LL phi(int x) {
    LL ans = x;
    for (int i = 2; i * i <= x; ++i) {
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

int main() {
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        LL sum = 0;
        int g;
        for (g = 1; g * g < n; ++g) {
            if (n % g == 0) {
                if (g >= m) {
                    sum += phi(n / g);
                }
                if (n / g >= m) {
                    sum += phi(g);
                }
            }
        }
        
        if (g * g == n && g >= m) {
            sum += phi(g);
        }
        printf("%lld\n", sum);
    }
    return 0;
}



// HYSBZ 2818
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1e7 + 10;
vector<int> p;
LL phi[maxn], s[maxn];

void Euler() {
    phi[1] = 1;
    s[1] = 2;
    for (int i = 2; i < maxn; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            p.push_back(i);
        }
        int len = (int)p.size();
        for (int j = 0; j < len && i * p[j] < maxn; ++j) {
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            } else {
                phi[i * p[j]] = phi[i] * (p[j] - 1);
            }
        }
        s[i] = s[i-1] + 2 *phi[i];
    }
}

int main() {
    Euler();
    int n;
    while (~scanf("%d", &n)) {
        int len = (int)p.size();
        LL sum = 0;
        for (int i = 0; i < len && p[i] <= n; ++i) {
            sum += s[n/p[i]] - 1;
        }
        printf("%lld\n", sum);
    }
    return 0;
}

// hdu 5780
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int MOD = 1000000007, maxn = 1000010;
LL phi[maxn], s[maxn];
vector<int> p;

void Euler() {
    phi[1] = 1;
    s[1] = 2;
    for (int i = 2; i < maxn; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            p.push_back(i);
        }
        int len = (int)p.size();
        for (int j = 0; j < len && i * p[j] < maxn; ++j) {
            if (i % p[j] != 0) {
                phi[i * p[j]] = phi[i] * (p[j] - 1);
            } else {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
        }
        s[i] = (s[i-1] + 2 * phi[i] % MOD) % MOD;
    }
}

LL pow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

LL x1, y1;
void extgcd(LL a, LL b) {
    if (b == 0) {
        x1 = 1;
        y1 = 0;
        return;
    }
    extgcd(b, a % b);
    LL tmp = x1;
    x1 = y1;
    y1 = tmp - a/b*y1;
    return;
}

int main() {
    Euler();
    int t;
    scanf("%d", &t);
    while (t--) {
        long long int x, n, ans = 0;
        scanf("%lld%lld", &x, &n);
        if (x == 1) {
            printf("0\n");
            continue;
        }
        LL i, r;
        extgcd(x-1, MOD);
        for (i = 1; i <= n; i = r + 1) {
            r = n / (n / i);
            ans = (ans + (s[n/i] - 1) * (pow(x, i)*(pow(x, r-i+1)-1) %MOD * x1 % MOD - (r + 1 - i) % MOD)) %MOD;
        }
        printf("%lld\n", (ans+MOD)% MOD);
    }
    return 0;
}


// hdu 3501
#include <cstdio>
using namespace std;
const int MOD = 1000000007;

long long phi(int x) {
    long long ans = x;
    for (int i = 2; i * i <= x; ++i) {
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

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        printf("%lld\n", (n - 1 - phi(n)) * n / 2 % MOD);
    }
    
    return 0;
}


// hdu 2824
#include <cstdio>
#include <vector>
using namespace std;
vector<int> prime;
const int maxn = 3000000 + 10;
int phi[maxn];

void Euler() {
    phi[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            prime.push_back(i);
        }
        int len = (int)prime.size();
        for (int j = 0; j < len && i * prime[j] < maxn; ++j) {
            if (i % prime[j]) {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            } else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
}

int main() {
    Euler();
    int a, b;
    while (~scanf("%d%d", &a, &b)) {
        long long int ans = 0;
        for (int i = a; i <= b; ++i) {
            ans += phi[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// poj 3090
#include <cstdio>
#include <vector>
using namespace std;
vector<int> prime;
const int maxn = 1010;
int phi[maxn];

void Euler() {
    phi[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            prime.push_back(i);
        }
        int len = (int)prime.size();
        for (int j = 0; j < len && i * prime[j] < maxn; ++j) {
            if (i % prime[j]) {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            } else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
}

int main() {
    Euler();
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        long long int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += phi[i];
        }
        printf("%d %d %lld\n", ca++, n, 1 + ans * 2);
    }
}


// poj 2478 欧拉求和
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1e6 + 10;
int phi[maxn];
vector<int> prime;

void Euler() {
    phi[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            prime.push_back(i);
        }
        int len = (int)prime.size();
        for (int j = 0; i * prime[j] < maxn && j < len; ++j) {
            if (i % prime[j]) {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            } else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
}

int main() {
    Euler();
    int n;
    while (~scanf("%d", &n) && n) {
        long long int ans = 0;
        for (int i = 2; i <= n; ++i) {
            ans += phi[i];
        }
        printf("%lld\n", ans);
    }
    
    return 0;
}


// hdu 4992
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
typedef long long LL;
using namespace std;
const int maxn = 1000010;
int phi[maxn];
vector<int> prime, factor;

void Euler() {
    phi[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            prime.push_back(i);
        }
        int len = (int)prime.size();
        for (int j = 0; j < len && 1ll * i * prime[j] < maxn; ++j) {
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

bool hasroot(int n) {
    // 2 / 4 / p^k / 2 * p^k p是奇质数，有原根
    // if (n == 2 || n == 4) return 1; 这里不需要，因为程序前面判断过了
    int len = (int)prime.size();
    for (int i = 1; i < len; ++i) {
        if (n % prime[i] == 0) {
            while (n % prime[i] == 0) {
                n /= prime[i];
            }
            if (n == 1 || n == 2) {
                return 1;
            }
            break;
        }
    }
    return 0;
}

void divide(int n) {
    factor.clear();
    int len = (int)prime.size();
    for (int i = 0; i < len && prime[i] <= n; ++i) {
        if (n % prime[i] == 0) {
            factor.push_back(prime[i]);
            while (n % prime[i] == 0) {
                n /= prime[i];
            }
        }
    }
}

LL fastpow(LL a, LL b, LL p) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

int get_Minroot(int n) {
    int len = (int)factor.size();
    for (int i = 2; i < n; ++i) {
        
        // 必须要加这一句
        if (fastpow(i, phi[n], n) != 1) continue;
 
        int flag = 1;
        for (int j = 0; j < len; ++j) {
            if (fastpow(i, phi[n] / factor[j], n) == 1) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            return i;
        }
    }
    return -1;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    Euler();
    int n;
    while (~scanf("%d", &n)) {
        if (n == 2) {printf("1\n"); continue;}
        if (n == 4) {printf("3\n"); continue;}
        
        if (hasroot(n) == 0) {printf("-1\n"); continue;}
        divide(phi[n]);
        
        int Min = get_Minroot(n);
        if (Min == -1) {printf("-1\n"); continue;}
        int g = Min;
        vector<int> ans;
        for (int i = 1; i <= phi[n]; ++i) {
            if (gcd(i, phi[n]) == 1) {
                ans.push_back(g);
            }
            g = Min * g % n;
        }
        sort(ans.begin(), ans.end());
        int len = (int)ans.size();
        for (int i = 0; i < len - 1; ++i) {
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans[len-1]);
    }
    return 0;
}


// poj 1284
// x的原根 = phi(phi(x))
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;

int phi(int x) {
    int ans = x;
    for (int i = 2; i * i <= x; ++i) {
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

int main() {
    int n;
    while (~scanf("%d", &n)) {
        printf("%d\n", phi(phi(n)));
    }
    return 0;
}


// fzu 1759
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 1000000 + 10;

int phi(int x) {
    int ans = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            ans = ans / i * (i - 1);
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) ans = ans / x * (x - 1);
    
    return ans;
}

LL pow(LL a, int b, int MOD) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

//LL gcd(LL a, LL b) {
//    return b == 0 ? a : gcd(b, a % b);
//}

int main() {
    LL a;
    int c;
    char s[maxn];
    while (~scanf("%lld%s%d", &a, s, &c)) {
        LL f = phi(c), b = 0;
        for(int i = 0; s[i]; ++i){
            b = b * 10 + (s[i]-'0');
            b %= f;
        }
        printf("%lld\n", pow(a, b + f, c));
    }
    return 0;
}


// poj 2407 欧拉函数
#include <cstdio>
using namespace std;
int n;
int phi(int x) {
    double ans = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            ans = ans * (i - 1)/ i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        ans = ans * (x - 1)/ x;
    }
    return (int)ans;
}

int main(int argc, const char * argv[]) {
    
    while (~scanf("%d", &n) && n) {
        printf("%d\n", phi(n));
    }
    return 0;
}


// hdu 1286 欧拉函数
#include <cstdio>
using namespace std;
int n;
int phi(int x) {
    double ans = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            ans = ans * (i - 1)/ i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        ans = ans * (x - 1)/ x;
    }
    return (int)ans;
}

int main(int argc, const char * argv[]) {

    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", phi(n));
    }
    return 0;
}
*/
