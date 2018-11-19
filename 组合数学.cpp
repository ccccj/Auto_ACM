//
//  main.cpp
//  组合数学专题
//
//  Created by admin on 18/9/22.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}


LL lcm(LL a, LL b) {
    return a * b / gcd(a, b);
}

int main() {
    
    int t, n;
    LL x;
    scanf("%d", &t);
    while (t--) {
        LL l;
        scanf("%d%lld", &n, &l);
        
        for (int i = 1; i < n; ++i) {
            scanf("%lld", &x);
            l = lcm(l, x);
        }
        printf("%lld\n", l);
    }
    return 0;
}

/*
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 510;
LL q[maxn * maxn / 2];
bool vis[maxn][maxn];

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        memset(vis, 0, sizeof(vis));
        scanf("%d", &n);
        LL sum = n * (n - 1) / 2;
        for (LL i = 0; i < sum; ++i) {
            scanf("%lld", &q[i]);
        }
        if (n == 1) {
            printf("0\n");
            continue;
        } else if (n == 1) {
            printf("1\n");
            continue;
        }
        LL cnta = 3, cntq = 2;
        LL arr[maxn];
        arr[0] = 0, arr[1] = q[0], arr[2] = q[1];
        vis[0][1] = 1, vis[0][2] = 1;
        while (cnta < n) {
            for (LL i = 0; i < cnta; ++i) {
                int f = 0;
                for (LL j = i + 1; j < cnta; ++j) {
                    if (vis[i][j] == 0) {
                        if (arr[i] + arr[j] == q[cntq]) {
                            ++cntq;
                            vis[i][j] = 1;
                        } else {
                            f = 1;
                            break;
                        }
                    }
                }
                if (f == 1) {
                    break;
                }
            }
            vis[0][cnta] = 1;
            arr[cnta++] = q[cntq++];
        }
        printf("%lld\n", cntq);
    }
    return 0;
}


#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 110;
LL C(int n, int m) {
    LL ans = 1;
    for (int i = 1; i <= m; ++i) {
        ans = ans * (n - i + 1) / i;
    }
    return ans;
}

int main() {
    
    int n, m;
    while (~scanf("%d%d", &n, &m) && n + m) {
        if (m > n) {
            printf("0\n");
            continue;
        }
        printf("%lld\n", C(n+m, m) - C(n+m, n-1));
        
        
    }
    return 0;
}


#include <cstdio>
using namespace std;
typedef long long LL;

const int maxn = 1010, p = 1e9 + 7;

int main() {
    
    int n, r, k, m;
    while (~scanf("%d%d%d%d", &n, &r, &k, &m)) {
        
        
        
    }
    return 0;
}


// hdu 1171
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 250005;
LL value[maxn], num[maxn], c[maxn], tmp[maxn], n, sum;

void slove() {
    memset(c, 0, sizeof(c));
    for (int i = 0, t = 0; t <= num[0]; i += value[0], ++t) {
        c[i] = 1;
    }
    for (int i = 1; i < n; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0, t = 0; t <= num[i]; k += value[i], ++t) {
            for (int j = 0; j + k <= sum; ++j) {
                if (c[j]) {
                    tmp[j+k] += c[j];
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
    }
}

int main() {
    
    while (~scanf("%lld", &n) && n > 0) {
        sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld%lld", &value[i], &num[i]);
            sum += value[i] * num[i];
        }
        slove();
        for (LL i = sum / 2; i >= 0; --i) {
            if (c[i]) {
                printf("%lld %lld\n", sum - i, i);
                break;
            }
        }
    }
    return 0;
}


// hdu 1124
#include <cstdio>
using namespace std;
typedef long long LL;

int main() {
    int t;
    LL n;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        LL ans = 0;
        while (n) {
            ans += n / 5;
            n /= 5;
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// hdu 4248
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 10010, p = 1e9 + 7;
int num[maxn], n;
LL c[maxn], tmp[maxn];
LL fact[maxn] = {1}, inv[maxn], sum;

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

void init() {
    for (int i = 1; i < maxn; ++i) {
        fact[i] = fact[i-1] * i % p;
    }
    inv[maxn-1] = fastpow(fact[maxn-1], p-2);
    for (int i = maxn - 2; i >= 0; --i) {
        inv[i] = inv[i+1] * (i+1) % p;
    }
}

void slove() {
    memset(c, 0, sizeof(c));
    c[0] = 1;
    for (int i = 0; i < n; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0; k <= num[i]; ++k) {
            for (int j = 0; j + k <= sum; ++j) {
                if (c[j]) {
                    tmp[j+k] = (tmp[j+k] + c[j]*inv[k] % p) % p;
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
//        for (int i = 0; i <= sum; ++i) {
//            if (c[i]) printf("%d %lld\n", i, c[i]);
//        }
//        printf("\n");
    }
}

int main() {
    init();
    int ca = 1;
    while (~scanf("%d", &n)) {
        printf("Case %d: ", ca++);
        sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &num[i]);
            sum += num[i];
        }
        slove();
        LL ans = 0;
        for (int i = 1; i <= sum; ++i) {
            ans = (ans + c[i] * fact[i] % p) % p;
        }
        printf("%lld\n", (ans + p) % p);
    }
    return 0;
}


// hdu 1521
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn = 15;
double c[maxn<<1], tmp[maxn<<1];
long long int fact[maxn];
int n, m, num[maxn];

void init() {
    fact[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fact[i] = fact[i-1] * i;
    }
}

void slove() {
    memset(c, 0, sizeof(c));
    for (int i = 0; i <= num[1]; ++i) {
        c[i] += (double)1 / fact[i];
    }
    for (int i = 2; i <= n; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0; k <= num[i]; ++k) {
            for (int j = 0; j <= m; ++j) {
                if (fabs(c[j]) > 0) {
                    tmp[j+k] += c[j] / fact[k];
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
    }
}

int main() {
    init();
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; ++i) {
           scanf("%d", &num[i]);
        }
        slove();
        printf("%.0f\n", c[m] * fact[m]);
        
    }
    return 0;
}


#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn = 2010, mod = 1e9 + 7;
LL S1[maxn][maxn], fact[maxn] = {1};

inline LL ksc(LL x,LL y) {
    return (x*y-(LL)((long double)x/mod*y)*mod+mod)%mod;
}

void init() {
    for (int i = 1; i < maxn; ++i) {
        fact[i] = fact[i-1] * i % mod;
    }
    S1[1][1] = 1;
    for (int i = 2; i < maxn; ++i) {
        for (int j = 1; j <= i; ++j) {
            S1[i][j] = (S1[i-1][j-1] + ksc((i-1),S1[i-1][j])) % mod;
        }
    }
}

LL fastpow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans = ksc(ans, a);
        }
        a = ksc(a, a);
        b >>= 1;
    }
    return ans;
}

LL inv(LL a) {
    return fastpow(a, mod - 2);
}

LL C(int n, int m) {
    return fact[n] * inv(fact[m]) % mod * inv(fact[n - m]) % mod;
}

int main() {
    init();
    int t, n, f, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &f, &b);
        if (f + b - 1 > n) {
            printf("0\n");
            continue;
        }
        printf("%lld\n", (S1[n - 1][f+b-2]*C(f+b-2, f-1)%mod+mod) % mod);
    }
    return 0;
}


// hdu 1398
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 350;
int c[maxn<<1], tmp[maxn<<1];
int m[20];

void init() {
    fill(c, c + maxn, 1);
    for (int i = 2; i <= 17; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0; k < maxn; k += m[i]) {
            for (int j = 0; j < maxn; ++j) {
                if (c[j]) {
                    tmp[j + k] += c[j];
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
    }
}

int main() {
    for (int i = 1; i <= 17; ++i) {
        m[i] = i * i;
    }
    init();
    int n;
    while (~scanf("%d", &n) && n) {
        printf("%d\n", c[n]);
    }
    return 0;
}


// hdu 1028
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 200;
LL c[maxn<<1], tmp[maxn<<1];

void init() {
    fill(c, c + (maxn<<1), 1);
    for (int i = 2; i < maxn; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0; k < maxn; k += i) {
            for (int j = 0; j < maxn; ++j) {
                if (c[j]) {
                    tmp[j+k] += c[j];
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
    }
}

int main() {
    init();
    int n;
    while (~scanf("%d", &n)) {
        printf("%lld\n", c[n]);
    }
    return 0;
}

// hdu 1085
// 生成函数
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 16010;
int m[] = {1, 2, 5}, num[3];
LL c[maxn], tmp[maxn];

void slove() {
    for (int i = 0; i <= num[0]; ++i) {
        ++c[i];
    }
    for (int i = 1; i <= 2; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0, n = 0; k <= maxn / 2 && n <= num[i]; k += m[i], ++n) {
            for (int j = 0; j <= maxn / 2; ++j) {
                if (c[j]) {
                    tmp[k+j] += c[j];
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
//        for (int j = 0; j <= maxn; ++j) {
//            if (c[j]) {
//               printf("%d %lld\n", j, c[j]);
//            }
//        }
    }
}

int main() {
    while (~scanf("%d%d%d", &num[0], &num[1], &num[2])) {
        memset(c, 0, sizeof(c));
        if (num[0] + num[1] + num[2] == 0) {
            break;
        }
        slove();
        int Max = num[0] + num[1] * 2 + num[2] * 5 + 1;
        for (int i = 0; i <= Max; ++i) {
            if (c[i] == 0) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}


// hdu 2028 生成函数
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 110;
LL c[maxn], tmp[maxn], num[26];

void slove() {
    for (int i = 0; i <= num[1]; ++i) {
        c[i] = 1;
    }
    for (int i = 2; i <= 26; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0, n = 0; k <= maxn/2 && n <= num[i]; k += i, ++n) {
            for (int j = 0; j <= maxn / 2; ++j) {
                if (c[j]) {
                    tmp[j + k] += c[j];
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= 26; ++i) {
            scanf("%lld", &num[i]);
        }
        slove();
        LL ans = 0;
        for (int i = 0; i <= 50; ++i) {
            ans += c[i];
        }
        printf("%lld\n", ans - 1);
    }
    return 0;
}


// hdu 2069
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 510;
LL c[maxn][maxn], tmp[maxn][maxn];
LL m[] = {5, 10, 25, 50};

void init() {
    for (int i = 0; i < maxn; ++i) {
        c[i][i] = 1;
    }
    for (int i = 0; i < 4; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int k = 0, num = 0; k <= maxn / 2; k += m[i], ++num) {
            for (int j = 0; j <= maxn / 2; ++j) {
                for (int z = 0; z < maxn; ++z) {
                    if (c[j][z]) {
                        tmp[j + k][z + num] += c[j][z];
                    }
                }
            }
        }
        memcpy(c, tmp, sizeof(c));
//        for (int j = 0; j <= 250; ++j) {
//            if (c[j]) {
//                printf("%d %lld\n", j, c[j]);
//            }
//        }
    }
}

int main() {
    init();
    int n;
    while (~scanf("%d", &n)) {
        LL ans = 0;
        for (int i = 0; i <= 100; ++i) {
            ans += c[n][i];
        }
        printf("%lld\n", ans);
    }
    
    return 0;
}


// hdu 2152 生成函数
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 100010;

LL a[maxn], b[maxn];
LL c[maxn], tmp[maxn];

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(c, 0, sizeof(c));
        for (int i = 0; i < n; ++i) {
            scanf("%lld%lld", &a[i], &b[i]);
        }
        for (LL i = a[0]; i <= b[0]; ++i) {
            ++c[i];
        }
//        for (int z = 0; z <= m; ++z) {
//            if (c[z]) {
//                printf("z:%d %lld\n", z, c[z]);
//            }
//        }
        for (int i = 1; i < n; ++i) {
            memset(tmp, 0, sizeof(tmp));
            for (LL k = a[i]; k <= b[i]; ++k) {
                for (int j = 0; j <= m; ++j) {
                    if (c[j]) {
                        tmp[k+j] += c[j];
                    }
                }
            }
            memcpy(c, tmp, sizeof(c));
//            for (int z = 0; z <= m; ++z) {
//                if (c[z]) {
//                    printf("z:%d %lld\n", z, c[z]);
//                }
//            }
        }
        printf("%lld\n", c[m]);
    }
    return 0;
}


// hdu 2512 斯特林数
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 2010, mod = 1000;

int S2[maxn][maxn];

void init() {
    S2[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        for (int j = 1; j <= i; ++j) {
            S2[i][j] = (S2[i-1][j-1] + j * S2[i-1][j] % mod) % mod;
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
            ans = (ans + S2[n][i]) % mod;
        }
        printf("%lld\n", (ans + mod) % mod);
    }
    
    return 0;
}


// hdu 2067
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 40;

LL arr[maxn][maxn];

void init() {
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) {
            if (i == 0 || j == 0) {
                arr[i][j] = 1;
            } else {
                arr[i][j] = arr[i-1][j] + arr[i][j-1];
                if (i == j - 1) {
                    arr[i][j] -= arr[i][j-2];
                } else if (i == j + 1) {
                    arr[i][j] -= arr[i-2][j];
                }
            }
        }
    }
}

int main() {
    init();
    
    int n, ca = 1;
    while (~scanf("%d", &n) && n != -1) {
        printf("%d %d %lld\n", ca++, n, arr[n][n]);
    }
    return 0;
}


// hdu 2068
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 30;
LL arr[maxn];

void init() {
    arr[0] = 1;
    arr[2] = 1;
    for (int i = 3; i < maxn; ++i) {
        arr[i] = (i-1) * (arr[i-1] + arr[i-2]);
    }
}

LL C(int n, int m) {
    LL ans = 1;
    for (int i = 1; i <= m; ++i) {
        ans = ans * (n - i + 1) / i;
    }
    return ans;
}

int main() {
    init();
    int n;
    while (~scanf("%d", &n) && n) {
        int m = (n + 1) / 2;
        LL ans = 0;
        for (int i = m; i <= n; ++i) {
            ans += C(n, i) * arr[n-i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// hdu 2049
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 25;
LL arr[maxn];

void init() {
    arr[2] = 1;
    for (int i = 3; i < maxn; ++i) {
        arr[i] = (i - 1) * (arr[i-1] + arr[i-2]);
    }
}

LL C(int n, int m) {
    LL ans = 1;
    for (int i = 1; i <= m; ++i) {
        ans = ans * (n - i + 1) / i;
    }
    return ans;
}

int main() {
    init();
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        printf("%lld\n", C(n, m) * arr[m]);
        
    }
    return 0;
}


#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 26;
int arr[maxn];

int read() {
    int ans = 0;
    int ch;
    while ((ch = getchar()) >= '0' && ch <= '9') {
        ans = ans * 10 + ch - '0';
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        for (int i = 1; i <= maxn; ++i) {
            arr[i] = read();
        }
        
        
        
    }
    return 0;
}

// 错排
// hdu 1465
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 25;
LL arr[maxn];

void init() {
    arr[2] = 1;
    for (int i = 3; i < maxn; ++i) {
        arr[i] = (i - 1) * (arr[i-1] + arr[i-2]);
    }
}
int main() {
    init();
    int n;
    while (~scanf("%d", &n)) {
        printf("%lld\n", arr[n]);
    }
    return 0;
}


// 5651
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1010, p = 1000000007;
typedef long long LL;
char str[maxn];
int vis[26];
LL fact[maxn] = {1}, inv[maxn], ifact[maxn];

void init() {
    for (int i = 1; i < maxn; ++i) {
        fact[i] = fact[i-1] * i % p;
    }
    inv[1] = 1;
    for (int i = 2; i <= maxn; ++i) {
        inv[i] = (p - p/i) * inv[p%i] % p;
    }
    ifact[0] = 1;
    for (int i = 1 ; i <= maxn; ++i) {
        ifact[i] = ifact[i-1] * inv[i] % p;
    }
}

inline LL ksc(LL x,LL y) {
    return (x*y-(LL)((long double)x/p*y)*p+p)%p;
}

LL C(LL m, LL n) {
    if (n < 0) return 0;
    return ksc(ksc(fact[m], ifact[n]), ifact[m-n]);
}

int main(int argc, const char * argv[]) {
    init();
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(vis, 0, sizeof(vis));
        scanf("%s", str);
        int flag = 0;
        LL num = 0;
        for (int i = 0; str[i]; ++i) {
            ++vis[str[i] - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            if (vis[i] > 0) {
                if (vis[i] % 2) {
                    --vis[i];
                    ++flag;
                }
                vis[i] /= 2;
                num += vis[i];
            }
        }
        if (flag > 1) {
            printf("0\n");
            continue;
        }
        LL ans = 1;
        for (int i = 0; i < 26; ++i) {
            if (vis[i] >= 1) {
                ans = ans * C(num, vis[i]) % p;
                num -= vis[i];
            }
        }
        printf("%lld\n", (ans + p) % p);
    }
    return 0;
}
*/

