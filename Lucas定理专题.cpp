//
//  main.cpp
//  Lucas专题
//
//  Created by admin on 18/9/13.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 10;
bool judge[maxn];
vector<int> prime;
vector<int> yinzi;
vector<LL> ans;

void init(LL p) {
    for (int i = 2; i <= p; ++i) {
        if (judge[i] == 0) {
            prime.push_back(i);
            for (int j = 2; i * j <= p; ++j) {
                judge[i * j] = 1;
            }
        }
    }
    LL pp = p;
    for (int i = 0; i < prime.size() && pp > 1; ++i) {
        if (pp % prime[i] == 0) {
            yinzi.push_back(prime[i]);
        }
    }
}

LL _pow(LL a, LL b, LL p) {
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

LL inv(LL a, LL p) {
    return _pow(a, p - 2, p);
}

LL C(LL n, LL m, int p) {
    if (n < m) {
        return 0;
    }
    LL up = 1, down = 1;
    for (int i = 1; i <= m; ++i) {
        up = up * (n - i + 1) % p;
        down = down * i % p;
    }
    return up * inv(down, p) % p;
}

LL lucas(LL n, LL m, int p) {
    if (m <= 0) {
        return 1;
    }
    return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

int main() {
    LL n, m, p;
    scanf("%lld%lld%lld", &n, &m, &p);
    init(p);
    if (judge[p] == 0) {
        printf("%lld\n", lucas(n, m, (int)p));
    } else {
        for (int i = 0; i < yinzi.size(); ++i) {
            ans.push_back(lucas(n, m, yinzi[i]));
        }
        LL ret = 0;
        for (int i = 0; i < yinzi.size(); ++i) {
            ret += p / yinzi[i] * inv(p / yinzi[i], yinzi[i]) % p * ans[i] % p;
        }
        printf("%lld\n", ret);
    }
    return 0;
}
/*
// hdu 4349
#include <cstdio>
using namespace std;
typedef long long LL;

int main() {
    LL n;
    while (~scanf("%lld", &n)) {
        ++n;
        LL a = 1 << 26;
        int k = 26;
        LL ans = n;
        int t = 1;
        while (n > 0) {
            while (n < a) {
                a /= 2;
                --k;
                if (k <= 0) {
                    break;
                }
            }
            if (a == n) {
                break;
            }
            ans -= (2 * a - n) * t;
            t *= 2;
            n = n - a;
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// zoj 3557
#include <cstdio>
using namespace std;
typedef long long LL;
LL p;

LL _pow(LL a, LL b) {
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

LL inv(LL a) {
    return _pow(a, p - 2);
}

LL C(LL n, LL m) {
    if (n < m) {
        return 0;
    }
    LL up = 1, down = 1;
    for (int i = 1; i <= m; ++i) {
        down = down * i % p;
        up = up * (n - i + 1) % p;
    }
    return up * inv(down) % p;
}

LL lucas(LL n, LL m) {
    if (m <= 0) {
        return 1;
    }
    return C(n % p, m % p) * lucas(n / p, m / p) % p;
}

int main() {
    LL n, m;
    while (~scanf("%lld%lld%lld", &n, &m, &p)) {
        printf("%lld\n", lucas(n - m + 1, m) % p);
    }
    
    return 0;
}


// fzu 2020
// n p 很大， m不大，暴力算出阶乘，因为阶乘最多到m，+lucas
#include <cstdio>
using namespace std;
typedef long long LL;
LL p;

LL _pow(LL a, LL b) {
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

LL C(LL n, LL m) {
    if (n < m) {
        return 0;
    }
    if (m > n-m) {
        m = n - m;
    }
    LL up = 1, down = 1;
    for (int i = 1; i <= m; ++i) {
        down = down * i % p;
        up = up * (n - i + 1) % p;
    }
    
    return up * _pow(down, p - 2) % p;
}

LL lucas(LL n, LL m) {
    if (m <= 0) {
        return 1;
    }
    return C(n % p, m % p) * lucas(n / p, m / p) % p;
}

int main() {
    LL n, m;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%I64d%I64d%I64d", &n, &m, &p);
        printf("%I64d\n", lucas(n, m));
    }
    return 0;
}

n m 很大， p不大，lucas定理 + 阶乘打表，打到p
// hdu 3944
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1e4 + 10;
LL t, k, p, fact[maxn][maxn];
bool judge[maxn] = {1, 1, 0}; // 素数-0
vector<int> prime;

void init() {
    for (int i = 2; i < maxn; ++i) {
        if (judge[i] == 0) {
            prime.push_back(i);
            for (int j = 2; i * j < maxn; ++j) {
                judge[i * j] = 1;
            }
        }
    }
    for (int i = 0; i < (int)prime.size(); ++i) {
        
        int x = prime[i];
        fact[x][0] = 1;
        for (int j = 1; j <= x; ++j) {
            fact[x][j] = fact[x][j-1] * j % x;
        }
    }
}

LL _pow(LL a, LL b) {
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

LL inv(LL a) {
    return _pow(a, p - 2);
}

LL c(LL n, LL m) {
    if (n < m) {
        return 0;
    }
    return fact[p][n] * inv(fact[p][m]) % p * inv(fact[p][n - m]) % p;
}

LL lucas(LL n, LL m) {
    if (m < p && n < p) {
        return c(n, m);
    }
    return c(n % p, m % p) * lucas(n / p, m / p) % p;
}

int main(int argc, const char * argv[]) {
    init();
    int ca = 0;
    while (~scanf("%lld%lld%lld", &t, &k, &p)) {
        printf("Case #%d: ", ++ca);
        ++t, ++k;
        if (k > (t + 1) / 2) {
            k = t + 1 - k;
        }
        LL ans = lucas(t, k - 1) + t % p - k % p;
        if (ans < 0) {
            ans += p;
        }
        printf("%lld\n", ans % p);
    }
    return 0;
}

*/
