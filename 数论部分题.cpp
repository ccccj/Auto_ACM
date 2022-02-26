//
//  main.cpp
//  数论
//
//  Created by admin on 18/8/15.
//  Copyright © 2018年 Amon. All rights reserved.
//
/*
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

typedef long long int LL;
const int MOD = 1000003;

LL Pow(LL di, LL a) {
    
    a %= (MOD - 1); // 费马小定理
    
    LL ret = 1;
    LL now = di;
    
    while (a) { // 快速幂
        if (a & 1) {
            ret = ret * now % MOD;
            if (ret == 0) {
                return 0;
            }
        }
        now = now * now % MOD;
        a >>= 1;
    }
    return ret;
}

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

LL p(LL n) { // 专门算不取模时，k 是否大于 2 ^ n
    LL ret = 1;
    
    for (int i = 1; i <= n; ++i) {
        ret *= 2;
    }
    return ret;
}

int main() {
    
    LL n, k;
    while (~scanf("%lld%lld", &n, &k)) {
        // k > 2^n 的情况
        
        if (n < 64) {
            if (p(n) < k) {
                cout << "1 1" << endl;
                continue;
            }
        }
        // m 为 天数
        LL m = Pow(2, n), x = 1;
        
        // 计算 x = A(m, k)
        
        for (LL i = 1; i <= k; ++i) {
            x = x * (m - i + 1) % MOD;
            if (m-i+1 == 0) {
                x = 0;
                break;
            }
        }
        
        LL fenmu = Pow(m, k); // 分母
        LL fenzi = (fenmu - x + MOD) % MOD; // 分母-x
        
        LL g = gcd(fenmu, fenzi); // 化简
        
        printf("%lld %lld\n", fenzi / g, fenmu / g);
    }
    return 0;
}


// B 扩展欧几里得
Description
终于活成了自己最讨厌的模样。


小希失败了，败得一塌糊涂。他甚至从未想到自己的生命中会承受这样一次失败。Gakki给了小希一个不定方程Ax+By+C=0. Gakki问小希这个方程是否存在整数解？


如果存在，就输出x和y，否则输出-1

Input
有多组样例，每行三个数字ABC


-2×109 < A，B，C < 2×109

Output
若有解，输出一行x和y，以空格隔开。否则输出-1
Sample Input
2 5 3
Sample Output
6 -3

#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

typedef long long int LL;

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a; // gcd(a, b) = a
    }
    LL g = exgcd(b, a%b, x, y);
    LL x2 = x, y2 = y;
    x = y2;
    y = x2 - (a/b)*y2;
    return g;
}

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    LL a, b, c;
    while (cin >> a >> b >> c) {
        LL g = gcd(a, b);
        
        c *= -1;
        
        if (c % g != 0) {
            cout << -1 << endl;
            continue;
        } else {
            LL x, y;
            c /= exgcd(a, b, x, y);
            cout << c*x << ' ' << c*y << endl;
        }
    }
    return 0;
}



// A Description
终于活成了自己最讨厌的模样。


生命中有许多美好的事物，或许是落日化繁星，或许是斜阳入深林。小希在追寻自己的真理的途中迷惘不已，他沉下心来思索了一番。他发现自己必须在素数的道路上有所建树。


小希探寻了m个数，想知道他们是不是素数。

Input
一行数m，代表查询数的个数。


下面m行，每行一个数n，代表要查询的数。


1< m n<232 -1，保证大于105 的样例不会超过5%

Output
每个数输出一行，如果是素数，就输出Yes，不然就输出No
Sample Input
3
2
3
4
Sample Output
Yes
Yes
No

#include <iostream>
#include <cmath>
using namespace std;

//freopen("/Users/admin/Desktop/test-8.in", "r", stdin);
int prime[20010];
bool isp[1000010] = {1, 1, 0, 0};

void init() {
    for (int i = 2; i <= 1000000; ++i) {
        if (isp[i] == 0) {
            for (int j = 2; i * j <= 1000000; ++j) {
                isp[i * j] = 1;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    //freopen("/Users/admin/Desktop/test-8.in", "r", stdin);
    //freopen("/Users/admin/Desktop/test-8.out", "w", stdout);
    init();
    int n, m;
    while (cin >> m) {
        for (int i = 0; i < m; ++i) {
            scanf("%d", &n);
            if (n <= 1000000) {
                if (isp[n] == 1) {
                    printf("No\n");
                } else {
                    printf("Yes\n");
                }
            } else {
                int f = 1;
                for (int i = 2; i <= sqrt(n); ++i) {
                    if (n % i == 0) {
                        printf("No\n");
                        f = 0;
                        break;
                    }
                }
                if (f) {
                    printf("Yes\n");
                }
            }
        }
    }
    return 0;
}
*/
