//
//  main.cpp
//  博弈论1<kuangbin>
//
//  Created by admin on 18/11/2.
//  Copyright © 2018年 Amon. All rights reserved.
//

/*
// hdu 2486 k倍动态减法
#include <cstdio>
using namespace std;
const int maxn = 1e6;
long long a[maxn] = {0, 1}, b[maxn] = {0, 1};

int main() {
    int t, n, k;
    scanf("%d", &t);
    for (int ca = 1; ca <= t; ++ca) {
        scanf("%d%d", &n, &k);
        if (k == 1) {
            if ((n & (-n)) == n) printf("Case %d: lose\n", ca);
            else printf("Case %d: %d\n", ca, n & (-n));
            continue;
        }
        int last = 0;
        for (int i = 1; ; ++i) {
            a[i] = b[i - 1] + 1;
            for (int j = 0; j <= i - 1; ++j) {
                if (a[j] * k < a[i] && a[j + 1] * k >= a[i]) {
                    b[i] = b[j] + a[i];
                    last = j;
                    break;
                }
            }
            if (n >= a[i - 1] && n < a[i]) {
                if (n == a[i - 1]) printf("Case %d: lose\n", ca);
                else {
                    for (int now = i - 1; now >= 0; --now) {
                        if (n > a[now]) n -= a[now];
                        else if (n == a[now]) {
                            printf("Case %d: %d\n", ca, n);
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    return 0;
}


// hdu 3544
#include <cstdio>
using namespace std;
typedef long long LL;
int arr[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824};

int main() {

    int t, n, ca = 1;
    scanf("%d", &t);
    while (t--) {
        LL x, y, hp = 0;
        scanf("%d", &n);
        while (n--) {
            scanf("%lld%lld", &x, &y);
            if (x > y) {
                for (int i = 0; i < 31; ++i) {
                    if (y >= arr[i] && y < arr[i + 1]) {
                        hp += x / arr[i] - 1;
                        break;
                    }
                }
            } else if (x < y) {
                for (int i = 0; i < 31; ++i) {
                    if (x >= arr[i] && x < arr[i + 1]) {
                        hp -= y / arr[i] - 1;
                        break;
                    }
                }
            }
        }
        if (hp <= 0) printf("Case %d: Bob\n", ca++);
        else printf("Case %d: Alice\n", ca++);
    }
    return 0;
}


// hdu 3537 sg 找规律
#include<cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e8 + 10;
int arr[maxn];

bool judge(int a) {
    int ans = 0;
    while (a) {
        a = a & (a - 1);
        ++ans;
    }
    return ans % 2 == 0 ? 1 : 0;
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        sort(arr, arr + n);
        int len = (int)(unique(arr, arr + n) - arr);
        
        for (int i = 0; i < len; ++i) {
            ans ^= 2 * arr[i] + judge(arr[i]);
        }
        
        if (ans == 0) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

// hdu 3537
// sg打表找规律
#include<cstdio>
#include <cstring>
using namespace std;
int sg[100], vis[100];

int main() {
    printf("0 1\n1 2\n");
    sg[0] = 1, sg[1] = 2;
    
    for (int now = 2; now < 100; ++now) {
        memset(vis, 0, sizeof(vis));
        // 改动一个
        vis[0] = 1;
        
        // 改动两个
        for (int i = 0; i < now; ++i) {
            vis[sg[i]] = 1;
        }
        // 改动三个
        for (int i = 0; i < now; ++i) {
            for (int j = 0; j < i; ++j) {
                vis[sg[i] ^ sg[j]] = 1;
            }
        }
        for (int i = 0; i < 100; ++i) {
            if (vis[i] == 0) {
                sg[now] = i;
                printf("%d %d\n", now, i);
                break;
            }
        }
    }
    return 0;
}


// hdu 3389
#include <cstdio>
using namespace std;
int main() {
    int t, n, x, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            if (i % 6 == 0 || i % 6 == 5 || i % 6 == 2) {
                ans ^= x;
            }
        }
        if (ans == 0) {
            printf("Case %d: Bob\n", ca++);
        } else {
            printf("Case %d: Alice\n", ca++);
        }
    }
    return 0;
}


// hdu 1538
#include <cstdio>
using namespace std;
int arr[14] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        if (n <= 2 * m) {
            if (n == k) {
                printf("%d\n", m - (n - 1) / 2);
            } else {
                if ((n - k) % 2) printf("0\n");
                else printf("1\n");
            }
        } else if (n == 2 * m + 1) {
            if (k < 2 * m && k & 1) printf("1\n");
            else printf("0\n");
        } else {
            for (int i = 0; i < 14; ++i) {
                if (n >= arr[i] + 2 * m && n < arr[i + 1] + 2 * m) {
                    if (k <= arr[i] + 2 * m) printf("0\n");
                    else printf("Thrown\n");
                    break;
                }
            }
        }
    }
    return 0;
}


// hdu 1850
#include <cstdio>
using namespace std;
const int maxn = 200010;
int arr[maxn];

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            ans ^= arr[i];
        }
        if (ans == 0) {
            printf("0\n");
            continue;
        }
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            int tmp = ans ^ arr[i];
            if (tmp < arr[i]) {
                ++ret;
                
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}


// hdu 2176
#include <cstdio>
using namespace std;
const int maxn = 200010;
int arr[maxn];

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            ans ^= arr[i];
        }
        if (ans == 0) {
            printf("No\n");
            continue;
        } else {
            printf("Yes\n");
        }
        for (int i = 0; i < n; ++i) {
            int tmp = ans ^ arr[i];
            if (tmp < arr[i]) {
                printf("%d %d\n", arr[i], tmp);
            }
        }
    }
    return 0;
}


// hdu 4315
#include <cstdio>
using namespace std;
const int maxn = 1010;
int arr[maxn];

int main() {
    
    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        if (n % 2 && k == 2) arr[0] = 0;
        else arr[0] = -1;
        
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        if (k == 1) {
            printf("Alice\n");
            continue;
        }
        int ans = 0;
        for (int i = n; i >= 1; i -= 2) {
            ans ^= arr[i] - arr[i-1] - 1;
        }
        if (ans == 0) printf("Bob\n");
        else printf("Alice\n");
    }
    return 0;
}


// hdu 1517 找规律
#include <cstdio>
using namespace std;
const long long int maxn = 4294967295;
int cnt = 1;
struct node {
    bool iswin;
    long long int num;
} arr[100];

int main() {
    long long int tmp = 1;
 
    for (int i = 1; ; ++i) {
        tmp *= 9;
        if (tmp > maxn) break;
        arr[cnt++] = {1, tmp};
        //printf("%lld\n", tmp);
        tmp *= 2;
        if (tmp > maxn) break;
        arr[cnt++] = {0, tmp};
        //printf("%lld\n", tmp);
    }
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 1; i < cnt; ++i) {
            if (n > arr[i-1].num && n <= arr[i].num) {
                if (arr[i].iswin == 1) {
                    printf("Stan wins.\n");
                } else {
                    printf("Ollie wins.\n");
                }
                break;
            }
        }
    }
    return 0;
}


// hdu 2177
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double k = (sqrt(5.0) + 1) / 2;

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        if (n > m) swap(n, m);
        int tmp = m - n;
        if ((int)(tmp * k) == n) {
            printf("0\n");
        } else {
            printf("1\n");
            printf("%d %d\n", (int)(tmp * k), (int)(tmp * k) + tmp);
            int t = tmp;
            
            for (int i = 1; i <= n; ++i) {
                int x = n - i;
                tmp = x / k;
                if ((int)(tmp * k) < x) ++tmp;
                else if ((int)(tmp * k) > x) --tmp;
                if (tmp == t) continue;
                
                int y = x + tmp;
                if (y == m) {
                    printf("%d %d\n", x, y);
                }
            }
            if (n == m) continue;
            
            tmp = n / k;
            if ((int)(tmp * k) < n) ++tmp;
            else if ((int)(tmp * k) > n) --tmp;
            if (n + tmp < m) {
                printf("%d %d\n", n, n + tmp);
            } else {
                tmp = n / (k + 1);
                if ((int)(tmp * (k + 1)) < n) ++tmp;
                else if ((int)(tmp * (k + 1)) > n) --tmp;
                printf("%d %d\n", (int)(tmp * k), n);
                
            }
        }
        
    }
    return 0;
}


// hdu 1527
// 威佐夫博弈 找奇异点 为
// tmp = k * (sqrt(5.0) + 1) / 2
// 第 k 个奇异点为 (tmp, tmp + k)
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double k = (sqrt(5.0) + 1) / 2;

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        if (n > m) swap(n, m);
        int tmp = m - n;
        
        if ((int)(tmp * k) == n) printf("0\n");
        else printf("1\n");
    }
    return 0;
}


// hdu 3032 sg 打表找规律
#include <cstdio>
using namespace std;

int main() {
    int t, n, x;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            if (x % 4 == 3) {
                ans ^= x + 1;
            } else if (x % 4 == 0) {
                ans ^= x - 1;
            } else {
                ans ^= x;
            }
        }
        if (ans == 0) {
            printf("Bob\n");
        } else {
            printf("Alice\n");
        }
    }
    return 0;
}

// sg 打表找规律
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100;
int sg[maxn], tmp[maxn];

int main() {
    sg[0] = 0, sg[1] = 1;
    printf("0 0\n1 1\n");
    for (int i = 2; i < maxn; ++i) {
        memset(tmp, 0, sizeof(tmp));
        for (int j = 0; j <= i - 1; ++j) tmp[sg[j]] = 1;
        for (int j = 1; j <= i / 2; ++j) {
            int t = 0;
            t ^= sg[j];
            t ^= sg[i - j];
            tmp[t] = 1;
        }
        for (int j = 0; j < maxn; ++j) {
            if (tmp[j] == 0) {
                sg[i] = j;
                break;
            }
        }
        printf("%d %d\n", i, sg[i]);
    }
    return 0;
}


// hdu 3863
#include <cstdio>
using namespace std;

int main() {
    int n;
    while (~scanf("%d", &n) && n != -1) {
        printf("I bet on Oregon Maple~\n");
    }
    return 0;
}


// hdu 3951
#include <cstdio>
using namespace std;

int main() {
    int t, ca = 1, n, k;
    scanf("%d", &t);
    while (t--) {
        printf("Case %d: ", ca++);
        scanf("%d%d", &n, &k);
        if (k >= n || (k == 1 && n % 2)) {
            printf("first\n");
        } else {
            printf("second\n");
        }
    }
    return 0;
}


// hdu 2149
#include <cstdio>
using namespace std;

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        if (n <= m) {
            for (int i = n; i < m; ++i) {
                printf("%d ", i);
            }
            printf("%d\n", m);
        } else {
            if (n % (m + 1) == 0) {
                printf("none\n");
            } else {
                printf("%d\n", n % (m + 1));
            }
        }
    }
}


// hdu 1564
#include <cstdio>
using namespace std;

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        if (n % 2 == 0) {
            printf("8600\n");
        } else {
            printf("ailyanlu\n");
        }
    }
    return 0;
}


// hdu 2188
#include <cstdio>
using namespace std;

int main() {
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        if (n % (m + 1) == 0) {
            printf("Rabbit\n");
        } else {
            printf("Grass\n");
        }
    }
    return 0;
}


// hdu 2516
// 当n为Fibonacci数的时候，先手必败。
// 第二数学归纳法证明：
// 为了方便，我们将n记为f[i]。
// 1、当i=2时，先手只能取1颗，显然必败，结论成立。
// 2、假设当i<=k时，结论成立。
//  则当i=k+1时，f[i] = f[k]+f[k-1]。
//  则我们可以把这一堆石子看成两堆，简称k堆和k-1堆。
// （一定可以看成两堆，因为假如先手第一次取的石子数大于或等于f[k-1]，则后手可以直接取完f[k]，因为f[k] < 2*f[k-1]）
//  对于k-1堆，由假设可知，不论先手怎样取，后手总能取到最后一颗。下面我们分析一下后手最后取的石子数x的情况。
//  如果先手第一次取的石子数y>=f[k-1]/3，则这小堆所剩的石子数小于2y，即后手可以直接取完，此时x=f[k-1]-y，则x<=2/3*f[k-1]。
//  我们来比较一下2/3*f[k-1]与1/2*f[k]的大小。即4*f[k-1]与3*f[k]的大小，对两值作差后不难得出，后者大。
//  所以我们得到，x<1/2*f[k]。
//  即后手取完k-1堆后，先手不能一下取完k堆，所以游戏规则没有改变，则由假设可知，对于k堆，后手仍能取到最后一颗，所以后手必胜。
//  即i=k+1时，结论依然成立。

// 那么，当n不是Fibonacci数的时候，情况又是怎样的呢？
// 这里需要借助“Zeckendorf定理”（齐肯多夫定理）：任何正整数可以表示为若干个不连续的Fibonacci数之和。
// 分解的时候，要取尽量大的Fibonacci数。
// 比如分解85：85在55和89之间，于是可以写成85=55+30，然后继续分解30,30在21和34之间，所以可以写成30=21+9，
// 依此类推，最后分解成85=55+21+8+1。
// 则我们可以把n写成  n = f[a1]+f[a2]+……+f[ap]。（a1>a2>……>ap）
// 我们令先手先取完f[ap]，即最小的这一堆。由于各个f之间不连续，则a(p-1) > ap  + 1，则有f[a(p-1)] > 2*f[ap]。即后手只能取f[a(p-1)]这一堆，且不能一次取完。
// 此时后手相当于面临这个子游戏（只有f[a(p-1)]这一堆石子，且后手先取）的必败态，即先手一定可以取到这一堆的最后一颗石子。
// 同理可知，对于以后的每一堆，先手都可以取到这一堆的最后一颗石子，从而获得游戏的胜利。

#include <cstdio>
using namespace std;
const long long int maxn = 1LL << 31;
long long int arr[100], cnt;

void init() {
    //printf("%lld\n", maxn);
    arr[0] = 2, arr[1] = 3;
    for (int i = 2; ; ++i) {
        long long int tmp = arr[i - 1] + arr[i - 2];
        if (tmp > maxn) {
            break;
        } else {
            arr[cnt = i] = tmp;
        }
        //printf("%lld\n", arr[i]);
    }
}

int main() {
    init();
    int n;
    while (~scanf("%d", &n) && n) {
        int t = 0;
        while (arr[t] < n && t <= cnt) {
            ++t;
        }
        if (arr[t] == n) {
            printf("Second win\n");
        } else {
            printf("First win\n");
        }
    }
    return 0;
}


// hdu 1525
// 记a > b,
// 如果a/b>=2,则此时正在玩游戏的人可以通过自己的操作决定必胜和必败。
// 这个人肯定知道a%b , b是必胜态还是必败态。如果是必败态，先手将a,b变成a%b , b , 那么先手肯定赢。如果是必胜态，先手将a,b变成a%b+b,b.那么对手只有将这两个数变成a%b,b,先手获胜。
// 如果b < a < 2*b , 则只能一步一步向下进行操作，直到出现上面的两种情况终止游戏。

#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int a, b, t;
    while (~scanf("%d%d", &a, &b) && (a + b)) {
        if (a == b) {
            printf("Stan wins\n");
            continue;
        }
        if (a < b) swap(a, b);
        t = 0;
        while (a > b && a < 2 * b) {
            a -= b;
            if (a < b) swap(a, b);
            ++t;
        }
        if (t % 2) {
            printf("Ollie wins\n");
        } else {
            printf("Stan wins\n");
        }
    }
    return 0;
}


// hdu 1079
#include <cstdio>
using namespace std;
const int maxn = 2010;
int arr[maxn][13][40];
int d[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int a, b, c;

bool islegal(int year, int month, int day) {
    if (year > 2001 || year < 1900) return 0;
    if (year == 2001 && month > 11) return 0;
    if (year == 2001 && month == 11 && day > 4) return 0;
    
    int tmp = d[month];
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
        ++tmp;
    }
    if (day > tmp) return 0;
    return 1;
}

void next_month(int year, int month, int day) {
    if (month == 12) a = year + 1, b = 1;
    else a = year, b = month + 1;
    c = day;
}

void next_day(int year, int month, int day) {
    if (month == 12) {
        if (day == 31) a = year + 1, b = 1, c = 1;
        return;
    }
    
    a = year;
    int tmp = d[month];
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
        ++tmp;
    }
    
    if (day == tmp) b = month + 1, c = 1;
    else b = month, c = day + 1;
}

void slove() {
    arr[2001][11][4] = 0;
    for (int year = 2001; year >= 1900; --year) {
        for (int month = 12; month >= 1; --month) {
            for (int day = 31; day >= 1; --day) {
                if (!islegal(year, month, day)) continue;
                if (year == 2001 && month == 11 && day == 4) {
                    continue;
                }
                next_month(year, month, day);
                if (islegal(a, b, c) && arr[a][b][c] == 0) {
                    arr[year][month][day] = 1;
                    continue;
                }
                next_day(year, month, day);
                if (islegal(a, b, c) && arr[a][b][c] == 0) {
                    arr[year][month][day] = 1;
                }
            }
        }
    }
}

int main() {
    int t;
    slove();
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &a, &b, &c);
        if (arr[a][b][c]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}


// hdu 1847 sg函数法
#include <cstdio>
using namespace std;
const int maxn = 1010;
int arr[maxn];
int s[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

void slove() {
    int j;
    for (int i = 1; i < maxn; ++i) {
        for (j = 0; j < 11; ++j) {
            if (i == s[j]) {
                arr[i] = 1;
                break;
            } else if (i < s[j]) {
                break;
            }
        }
        if (arr[i] == 0) {
            --j;
            for (; j >= 0; --j) {
                if (arr[i - s[j]] == 0) {
                    arr[i] = 1;
                    break;
                }
            }
        }
    }
}

int main() {
    int n;
    slove();
    while (~scanf("%d", &n)) {
        if (arr[n] == 1) printf("Kiki\n");
        else printf("Cici\n");
    }
    return 0;
}


// hdu 1847 打表找规律法
#include <cstdio>
using namespace std;

int main() {
    int n;
    while (~scanf("%d", &n)) {
        if (n % 3 == 0) {
            printf("Cici\n");
        } else {
            printf("Kiki\n");
        }
    }
    return 0;
}


// hdu 2897 巴什博奕变形
#include <cstdio>
#include <cstring>
using namespace std;

int main(int argc, const char * argv[]) {
    int n, p, q;
    while (~scanf("%d%d%d", &n, &p, &q)) {
        n %= p + q;
        if (n == 0) {
            printf("WIN\n");
        } else if (n <= p) {
            printf("LOST\n");
        } else {
            printf("WIN\n");
        }
    }
    return 0;
}


// hdu 1846 巴什博奕
#include <cstdio>
#include <cstring>
using namespace std;

int main(int argc, const char * argv[]) {
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        if (n % (m + 1) == 0) {
            printf("second\n");
        } else {
            printf("first\n");
        }
    }
    return 0;
}
*/
