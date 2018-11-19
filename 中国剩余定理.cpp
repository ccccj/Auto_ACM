//
//  main.cpp
//  中国剩余定理
//
//  Created by admin on 18/9/14.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
LL a, b, MOD;

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

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%lld%lld%lld", &a, &b, &MOD);
        printf("%lld\n", pow(a, b));
    }
    return 0;
}
/*
// MOD = i，x = j 时，经过一系列操作得到的值
// tree[i][j][rt] = tree[i][ tree[i][j][rt<<1] ] [rt<<1|1]
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 5e4 + 10;
char op[maxn];
int num[maxn], cifang[4][20][maxn], p[4] = {7, 13, 17, 19};

int tree[4][21][maxn << 4];

void init() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < p[i]; ++j) {
            cifang[i][j][0] = 1;
            for (int k = 1; k < maxn; ++k) {
                cifang[i][j][k] = cifang[i][j][k-1] * k % p[i];
            }
        }
    }
}

void pushup(int l, int r, int now) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < p[i]; ++j) {
            int x = tree[i][j][now << 1];
            tree[i][j][now] = tree[i][x][(now << 1)|1];
        }
    }
}

void build(int l, int r, int now) {
    if (l == r) {
        for (int i = 0; i < 4; ++i) { // 第几位模数
            for (int j = 0; j < p[i]; ++j) { // MOD
                if (op[l] == '*') {
                    tree[i][j][now] = (j * num[l]) % p[i];
                } else if (op[l] == '+') {
                    tree[i][j][now] = (j + num[l]) % p[i];
                } else {
                    tree[i][j][now] = cifang[i][j][num[l]];
                }
            }
        }
        return;
    }
    int m = (l + r) / 2;
    build(l, m, now << 1);
    build(m + 1, r, (now << 1)|1);
    pushup(l, r, now);
}

void update(int l, int r, int c, int now) {
    if (l == r) {
        for (int i = 0; i < 4; ++i) {
            tree[i][][now] =
        }
    }
}

int main() {
    init();
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        getchar();
        for (int i = 1; i <= n; ++i) {
            scanf("%c%d", &op[i], &num[i]);
        }
        build(1, n, 1);
        int cmd, x, pow;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &cmd, &x);
            if (cmd == 1) {
                update(1, n, x, 1);
            }
        }
        
        
        
        
    }
    return 0;
}


// poj 2891
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1e5;
LL p[maxn], ans[maxn], x, y, oldp, oldans;
int n;

LL extgcd(LL a, LL b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL g = extgcd(b, a % b);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

LL CRT() {
    oldp = p[0], oldans = ans[0];
    for (int i = 1; i < n; ++i) {
        LL g = extgcd(oldp, p[i]);
        if ((oldans - ans[i]) % g != 0) {
            return -1;
        }
        x *= (ans[i] - oldans) / g;
        LL t = p[i] / g;
        x = (x % t + t) % t;
        
        oldans += oldp * x;
        LL lcm = oldp * p[i] / g;
        oldp = lcm;
        oldans = (oldans % oldp + oldp) % oldp;
    }
    return oldans;
}

int main() {
    
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; ++i) scanf("%lld%lld", &p[i], &ans[i]);
        printf("%lld\n", CRT());
    }
    return 0;
}


#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 13;
LL p[maxn];
vector<int> ans[maxn];

int main() {
    
    int n, s, k, a;
    while (~scanf("%d%d", &n, &s) && (n + s)) {
        for (int i = 0; i < n; ++i) {
            scanf("%lld%d", &p[i], &k);
            for (int i = 0; i < k; ++i) {
                scanf("%d", &a);
                ans[i].push_back(a);
            }
        }
        LL oldp, olpans;
        
        
        
    }
    return 0;
}

// hdu 1573
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 12;
int n, m;
LL p[maxn], ans[maxn], x, y;

LL extgcd(LL a, LL b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL g = extgcd(b, a % b);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

LL oldp, oldans;

bool CRT() {
    oldp = p[0], oldans = ans[0];
    for (int i = 1; i < m; ++i) {
        LL g = extgcd(oldp, p[i]);
        if ((ans[i] - oldans) % g != 0) {
            return 0;
        }
        x *= (ans[i] - oldans) / g;
        LL tmp = p[i] / g;
        x = (x % tmp + tmp ) % tmp;
        
        oldans += oldp * x;
        
        LL lcm = oldp * p[i] / g;
        oldp = lcm;
        oldans = (oldans % lcm + lcm) % lcm;
    }
    return 1;
}

LL lcm() {
    LL g = p[0], lcm = p[0];
    for (int i = 1; i < m; ++i) {
        LL tmp = extgcd(p[i], g);
        lcm = p[i] * lcm / tmp;
        g = tmp;
    }
    return lcm;
}

int main() {
    
    int t; // x <= n
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        int f = 1;
        for (int i = 0; i < m; ++i) scanf("%lld", &p[i]);
        
        for (int i = 0; i < m; ++i) {
            scanf("%lld", &ans[i]);
            if (ans[i] != 0) {
                f = 0;
            }
        }
        if (f) {
            LL l = lcm();
            printf("%lld\n", n / l);
            continue;
        }
        
        if (CRT() == 0 || oldans > n) {
            printf("0\n");
        } else {
            printf("%lld\n", (n - oldans) / oldp + 1);
        }
    }
    return 0;
}


// hdu 3579
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 12;
int n, m;
LL p[maxn], ans[maxn], x, y;

LL extgcd(LL a, LL b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL g = extgcd(b, a % b);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

LL CRT() {
    LL oldp = p[0], oldans = ans[0];
    for (int i = 1; i < m; ++i) {
        LL g = extgcd(oldp, p[i]);
        if ((ans[i] - oldans) % g != 0) {
            return -1;
        }
        x *= (ans[i] - oldans) / g;
        LL tmp = p[i] / g;
        x = (x % tmp + tmp ) % tmp;
        
        oldans += oldp * x;
        
        LL lcm = oldp * p[i] / g;
        oldp = lcm;
        oldans = (oldans % lcm + lcm) % lcm;
    }
    return oldans;
}

LL lcm() {
    LL g = p[0], lcm = p[0];
    for (int i = 1; i < m; ++i) {
        LL tmp = extgcd(p[i], g);
        lcm = p[i] * lcm / tmp;
        g = tmp;
    }
    return lcm;
}

int main() {
    
    int t, ca = 1; // x <= n
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        int f = 1;
        for (int i = 0; i < m; ++i) scanf("%lld", &p[i]);
        for (int i = 0; i < m; ++i) {
            scanf("%lld", &ans[i]);
            if (ans[i] != 0) {
                f = 0;
            }
        }
        if (f) {
            printf("Case %d: %lld\n", ca++, lcm());
        } else {
            printf("Case %d: %lld\n", ca++, CRT());
        }
    }
    return 0;
}

// hdu 1370
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;

LL extgcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL g = extgcd(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

int main() {
    int p[] = {23, 28, 33};
    LL P = 21252;
    int ans[5];
    int n;
    scanf("%d", &n);
    while (n--) {
        int t, ca = 1;
        while (~scanf("%d%d%d%d", &ans[0], &ans[1], &ans[2], &t)) {
            if (ans[0] == -1 && ans[1] == -1 && ans[2] == -1 && t == -1) {
                break;
            }
            LL x, y, ret = 0;
            for (int i = 0; i < 3; ++i) {
                LL mi = P / p[i];
                extgcd(mi, p[i], x, y);
                ret = (ret + ans[i] * mi % P * x % P) % P;
            }
            ret = (ret - t + P) % P;
            if (ret == 0) {
                ret = P;
            }
            printf("Case %d: the next triple peak occurs in %lld days.\n", ca++, ret);
        }
    }
    return 0;
}

// poj 1006
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;

LL extgcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL g = extgcd(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

int main() {
    int p[] = {23, 28, 33};
    LL P = 21252;
    int ans[5];
    int t, ca = 1;
    while (~scanf("%d%d%d%d", &ans[0], &ans[1], &ans[2], &t)) {
        if (ans[0] == -1 && ans[1] == -1 && ans[2] == -1 && t == -1) {
            break;
        }
        LL x, y, ret = 0;
        for (int i = 0; i < 3; ++i) {
            LL mi = P / p[i];
            extgcd(mi, p[i], x, y);
            ret = (ret + ans[i] * mi % P * x % P) % P;
        }
        ret = (ret - t + P) % P;
        if (ret == 0) {
            ret = P;
        }
        printf("Case %d: the next triple peak occurs in %lld days.\n", ca++, ret);
    }
    return 0;
}


// hdu 1788
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
//const int maxn = 15;
vector<LL> m, ans, x, invx;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

LL lcm(LL a, LL b) {
    return a * b / gcd(a, b);
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

int main() {
    int n, a;
    LL k;
    while (~scanf("%d%d", &n, &a) && (n + a)) {
        m.clear(), ans.clear(), x.clear(), invx.clear();
        
        scanf("%lld", &k);
        m.push_back(k);
        ans.push_back(k - a);
        LL l = m[0];
        
        for (int i = 1; i < n; ++i) {
            scanf("%lld", &k);
            int flag = 1;
            for (int i = 0; i < m.size(); ++i) {
                if (m[i] == k) {
                    flag = 0;
                    break;
                }
            };
            if (flag) {
                m.push_back(k);
                ans.push_back(k - a);
                l = lcm(l, m[m.size() - 1]);
            }
        }
        LL ret = 0;
        for (int i = 0; i < m.size(); ++i) {
            x.push_back(l / m[i]);
            invx.push_back(inv(x[i], m[i]));
            ret = (ret + x[i] * invx[i] % l * ans[i] % l) % l;
        }
        printf("%lld\n", (ret + l) % l);
    }
    return 0;
}



// 这题不能费马小定理(log2 n)求中国剩余定理，会超时
// 扩展欧几里得(ln n)不会超时
// 福州大学 I64d 辣鸡
#include <cstdio>
using namespace std;
typedef long long LL;

const int maxn = 15;
LL m[maxn], ans[maxn], x[maxn];
LL invx[maxn];

LL x1, y1;
LL inv(LL a, LL b, LL &x1, LL &y1) {
    if (b == 0){
        x1 = 1;
        y1 = 0;
        return a;
    }
    LL gcd = inv(b, a % b, x1, y1);
    LL tmp = x1;
    x1 = y1;
    y1 = tmp - (a/b) * y1;
    return gcd;
}

int main(int argc, const char * argv[]) {
    int n;
    while (scanf("%d", &n) == 1) {
        LL l = 1; // 最小公倍数
        for (int i = 0; i < n; ++i) {
            scanf("%I64d%I64d", &m[i], &ans[i]);
            l *= m[i];
        }
        for (int i = 0; i < n; ++i) {
            x[i] = l / m[i];
            inv(x[i], m[i], x1, y1);
            invx[i] = x1;
        }
        // x * inv[x] * ans
        LL ret = 0;
        for (int i = 0; i < n; ++i) {
            ans[i] *= invx[i] * x[i];
            ret = (ret + ans[i]) % l;
        }
        printf("%I64d\n", (ret + l) % l);
    }
    return 0;
}
// java

import java.util.*;

public class Main {
    static final int maxn = 15;
    
    static long[] extgcd(long a, long p) {
        if (p == 0) {
            long[] ret = {1, 0};
            return ret;
        }
        long[] ret = extgcd(p, a % p);
        long tmp = ret[0];
        ret[0] = ret[1];
        ret[1] = tmp - (a / p) * ret[1];
        return ret;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            int n = sc.nextInt();
            long[] m = new long[maxn];
            long[] ans = new long[maxn];
            
            long l = 1;
            
            for (int i = 0; i < n; ++i) {
                m[i] = sc.nextLong();
                ans[i] = sc.nextLong();
                l *= m[i];
            }
            long ret = 0;
            for (int i = 0; i < n; ++i) {
                long p = l / m[i];
                long[] arr = extgcd(p, m[i]);
                long invp = arr[0];
                ret = (ret + p * invp % l * ans[i] % l) % l;
            }
            System.out.println((ret + l) % l);
        }
        sc.close();
    }
}


// 51Nod 1079
// 中国剩余定理模板题
#include <cstdio>
using namespace std;
typedef long long LL;

const int maxn = 15;
LL m[maxn], ans[maxn], x[maxn];
LL invx[maxn];

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

LL lcm(LL a, LL b) {
    return a * b / gcd(a, b);
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

int main(int argc, const char * argv[]) {
    int n;
    while (~scanf("%d", &n)) {
        scanf("%lld%lld", &m[0], &ans[0]);
        LL l = m[0]; // 最小公倍数
        for (int i = 1; i < n; ++i) {
            scanf("%lld%lld", &m[i], &ans[i]);
            l = lcm(l, m[i]);
        }
        for (int i = 0; i < n; ++i) {
            x[i] = l / m[i];
            invx[i] = inv(x[i], m[i]);
        }
        // x * inv[x] * ans
        LL ret = 0;
        for (int i = 0; i < n; ++i) {
            ans[i] *= invx[i] * x[i];
            ret = (ret + ans[i]) % l;
        }
        printf("%lld\n", ret);
    }
    return 0;
}
*/
