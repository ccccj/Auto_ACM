//
//  main.cpp
//  多校8
//
//  Created by admin on 18/8/15.
//  Copyright © 2018年 Amon. All rights reserved.
//
/*
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100010;

int arr[maxn], l[maxn], r[maxn], now[maxn];
bool ret[maxn];

int main() {
    int T;
    cin >> T;
    while (T--) {
        memset(ret, 0, sizeof(ret));
        memset(r, 0, sizeof(r));
        memset(l, 0, sizeof(l));
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        int tmp = arr[1], sum = 1;
        ret[1] = 1, now[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (arr[i] > tmp) {
                ret[i] = 1;
                ++sum;
                now[i] = sum;
            }
        }
        
        l[1] = 0;
        for (int i = 2; i <= n; ++i) {
             for (int j = i - 1; j >= 1; --j) {
                if (arr[j] < arr[i]) {
                    l[i] = j;
                    break;
                }
            }
        }
        r[n] = 0;
        for (int i = n - 1; i >= 1; --i) {
            for (int j = i + 1; j <= n; ++j) {
                if (arr[j] > arr[i]) {
                    r[i] = j;
                    break;
                }
            }
        }
        int a, b;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &a, &b);
            if (ret[a] == 0 || arr[a] == b) {
                cout << sum << endl;
            } else {
                if (arr[a] < b) {
                    // 改大
                    int i = a, s = sum;
                    while (i != 0) {
                        if (arr[i] <= b) {
                            i = r[i];
                            --s;
                        } else {
                            printf("%d\n", s);
                            break;
                        }
                    }
                    if (i == 0) {
                        cout << now[a] << endl;
                    }
                } else if (arr[a] > b) {
                    // 改小
                }
            }
        }
    }
    return 0;
}
*/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
// 130 * 10^6
const int mod = 998244353;

#define LL long long

LL fac[200001] = {1,1}, inv[200001], ifact[200001];


inline LL ksc(LL x,LL y) {
    return (x*y-(LL)((long double)x/mod*y)*mod+mod)%mod;
}

void init() {
    // 求阶乘
    fac[0] = 1;
    for (int i = 1; i <= 200000; ++i) {
        fac[i] = fac[i-1] * i % mod;
    }
    // 求逆元
    inv[1] = 1;
    for (int i = 2; i <= 200000; ++i) {
        inv[i] = (mod - mod/i) * inv[mod%i] % mod;
    }
    // 求阶乘的逆元
    ifact[0] = 1;
    for (int i = 1 ; i <= 200000; ++i) {
        ifact[i] = ifact[i-1] * inv[i] % mod;
    }
}

LL C(LL m, LL n) {
    if (n < 0) return 0;
    return ksc(ksc(fac[m], ifact[n]), ifact[m-n]);
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    
    while (T--) {
        
        LL n, m, k;
        scanf("%lld%lld%lld", &n, &m, &k);
        
        long long int sum = 0;
        
        for (int i = 0; i <= m; ++i) {
            if (k + m - 1 - i * n < m - 1 || k + m - 1 - i * n < 0) {
                break;
            } else {
                long long int tmp = pow(-1, i % 2) *
                ksc(C(m, i), C(k + m - 1 - i*n, m-1));
                
                tmp %= mod;
                sum = (sum + tmp + mod) % mod;
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}

/*
// 1007
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char arr[4][4];

void C1() {
    char a = arr[0][0];
    arr[0][0] = arr[1][0];
    arr[1][0] = arr[1][1];
    arr[1][1] = arr[0][1];
    arr[0][1] = a;
}

void C2() {
    char a = arr[0][1];
    arr[0][1] = arr[1][1];
    arr[1][1] = arr[1][2];
    arr[1][2] = arr[0][2];
    arr[0][2] = a;
}

void C3() {
    char a = arr[1][0];
    arr[1][0] = arr[2][0];
    arr[2][0] = arr[2][1];
    arr[2][1] = arr[1][1];
    arr[1][1] = a;
}

void C4() {
    char a = arr[1][1];
    arr[1][1] = arr[2][1];
    arr[2][1] = arr[2][2];
    arr[2][2] = arr[1][2];
    arr[1][2] = a;
}

void R1() {
    char a = arr[0][0];
    arr[0][0] = arr[0][1];
    arr[0][1] = arr[1][1];
    arr[1][1] = arr[1][0];
    arr[1][0] = a;
}

void R2() {
    char a = arr[0][1];
    arr[0][1] = arr[0][2];
    arr[0][2] = arr[1][2];
    arr[1][2] = arr[1][1];
    arr[1][1] = a;
}

void R3() {
    char a = arr[1][0];
    arr[1][0] = arr[1][1];
    arr[1][1] = arr[2][1];
    arr[2][1] = arr[2][0];
    arr[2][0] = a;
}

void R4() {
    char a = arr[1][1];
    arr[1][1] = arr[1][2];
    arr[1][2] = arr[2][2];
    arr[2][2] = arr[2][1];
    arr[2][1] = a;
}

int main(int argc, const char * argv[]) {
    int T;
    cin >> T;
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < 3; ++i) {
            scanf("%s", arr[i]);
        }
        char s[10];
        for (int i = 0; i < n; ++i) {
            scanf("%s", s);
            if (s[1] == 'C') {
                switch (s[0]) {
                    case '1':
                        C1();
                        break;
                    case '2':
                        C2();
                        break;
                    case '3':
                        C3();
                        break;
                    case '4':
                        C4();
                        break;
                    default:
                        break;
                }
            } else if (s[1] == 'R') {
                switch (s[0]) {
                    case '1':
                        R1();
                        break;
                    case '2':
                        R2();
                        break;
                    case '3':
                        R3();
                        break;
                    case '4':
                        R4();
                        break;
                    default:
                        break;
                }
            } else {
                cout << "======" << endl;
            }
        }
        for (int i = 0; i < 3; ++i) {
            printf("%s\n", arr[i]);
        }
        
    }
    
    return 0;
}
*/
