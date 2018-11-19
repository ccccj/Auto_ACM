//
//  main.cpp
//  二分 尺取 单调栈队列
//
//  Created by admin on 18/11/5.
//  Copyright © 2018年 Amon. All rights reserved.
//


/*
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
LL arr[maxn], sum[maxn], pow[40], t, n;

void init() {
    pow[0] = 1;
    for (int i = 1; i < 40; ++i) {
        pow[i] = pow[i - 1] * 2;
    }
}

LL find(LL L, LL R) { // 范围在 [L, R)
    LL ans = 0, l = 1, r = 0;
    for (LL i = 1; i <= n; ++i) {
        if (l < i) l = i;
        if (r < i - 1) r = i - 1;
        
        while (sum[l] - sum[i - 1] < L && l <= n) ++l;
        if (l > n) continue;
        while (sum[r + 1] - sum[i - 1] < R && r < n) ++r;
        
        if (l > r) continue;
        
        if (sum[l] - sum[i - 1] >= L && sum[l] - sum[i - 1] < R && sum[r] - sum[i - 1] >= L && sum[r] - sum[i - 1] < R) {
            ans += (r - l + 1) * i + ((r - l + 1) * (l + r)) / 2;
        }
    }
    return ans;
}

int main() {
    init();
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &arr[i]);
            sum[i] = sum[i - 1] + arr[i];
        }
        LL ans = 0;
        for (LL k = 1; k < 35; ++k) {
            ans += find(pow[k - 1], pow[k]) * k;
        }
        ans += find(0, 1);
        printf("%lld\n", ans);
    }
    return 0;
}


#include <cstdio>
#include <cstdlib>
using namespace std;
const int maxn = 1e6 + 10;
int arr[maxn], sum, ansl, ansr, l, r;

int main() {
    int n, q, k;
    while (~scanf("%d%d", &n, &q) && (n + q)) {
        for (int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
        while (q--) {
            scanf("%d", &k);
            sum = 0;
            ansl = ansr = l = r = 1;
            int Min = 0;
            while (1) {
                while (r <= n && abs(sum) < k) {
                    sum += arr[r++];
                    if (abs(Min - k) > abs(abs(sum) - k)) {
                        Min = abs(sum), ansl = l, ansr = r - 1;
                    }
                }
                if (r == n + 1) break;
                while (abs(sum) >= k && l <= r) {
                    sum -= arr[l++];
                    if (abs(Min - k) > abs(abs(sum) - k)) {
                        Min = abs(sum), ansl = l, ansr = r;
                    }
                }
            }
            printf("%d %d %d\n", Min, ansl, ansr);
        }
    }
    return 0;
}


// hdu 5646
#include <cstdio>
using namespace std;
typedef long long LL;
const int mod = 1e9 + 7;

int main() {
    int t;
    LL n, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &k);
        if ((1 + k) * k / 2 > n) {
            printf("-1\n");
            continue;
        }
        // 求最大的开始值
        LL a = (2 * n / k + 1 - k) / 2, ans = 1;
        LL tmp = n - (2 * a + k - 1) * k / 2; // 多余的值
        //printf("%lld\n", a);
        for (int i = 1; i <= k; ++i) {
            LL aa = a;
            if (i >= k - tmp + 1) ++aa; // 将 tmp 分到后面的数上面
            ans = ans * aa % mod;
            a += 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// hdu 3415
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 10;
int arr[maxn], sum[maxn], q[maxn], ans[maxn];

int main() {
    int t, n, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
            arr[i + n] = arr[i];
        }
        for (int i = 1; i <= 2 * n; ++i) {
            sum[i] = sum[i - 1] + arr[i];
        }
        int l = 0, r = 0, Max = arr[1];
        q[0] = 0;
        int ansl = 1, ansr = 1;
        for (int i = 1; i <= 2 * n; ++i) {
            if (i - q[l] > k) ++l;
            ans[i] = sum[i] - sum[q[l]];
            while (sum[i] < sum[q[r]] && l <= r) {
                --r;
            }
            q[++r] = i;
            if (Max < ans[i]) {
                Max = ans[i];
                ansl = q[l] + 1, ansr = i;
                if (ansl > n) ansl -= n;
                if (ansr > n) ansr -= n;
            }
            //printf("Max %d\n", Max);
        }
        printf("%d %d %d\n", Max, ansl, ansr);
        
    }
    return 0;
}


// hdu 3410
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e5;
int arr[maxn], q[maxn], left[maxn], right[maxn], cnt, ca;

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
        
        cnt = 0;
        q[cnt++] = 0;
        for (int i = 1; i < n; ++i) {
            while (arr[i] > arr[q[cnt - 1]] && cnt > 0) {
                --cnt;
            }
            if (cnt > 0) right[q[cnt - 1]] = i + 1;
            q[cnt++] = i;
        }
        //        for (int i = 0; i < n; ++i) {
        //            printf("%d ", right[i]);
        //        }
        //        printf("\n");
        
        cnt = 0;
        q[cnt++] = n - 1;
        for (int i = n - 2; i >= 0; --i) {
            while (arr[i] > arr[q[cnt - 1]] && cnt > 0) {
                --cnt;
            }
            if (cnt > 0) left[q[cnt - 1]] = i + 1;
            q[cnt++] = i;
        }
        //        for (int i = 0; i < n; ++i) {
        //            printf("%d ", left[i]);
        //        }
        //        printf("\n");
        printf("Case %d:\n", ++ca);
        for (int i = 0; i < n; ++i) {
            printf("%d %d\n", left[i], right[i]);
        }
    }
    return 0;
}


// hdu 4122
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 3e3, maxm = 1e5 + 10;
LL arr[maxm], Min[maxm], q[maxm], l, r, num[maxn], time[maxn];
LL monthday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char str[][10] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

struct date {
    LL month, day, year, hour;
};

bool isleep(LL year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

LL gettime(date da) {
    LL y = 2000, m = 1, d = 1, ans = (da.year - y) * 365 * 24;
    while (y < da.year) {
        if (isleep(y)) ans += 24;
        ++y;
    }
    if (isleep(da.year) && da.month >= 3) ans += 24;
    
    while (m < da.month) {
        ans += monthday[m++] * 24;
    }
    ans += 24 * (da.day - d) + da.hour;
    return ans;
}

int main() {
    int n, m, t, s;
    date d;
    char tmp[10];
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        for (int i = 0; i < n; ++i) {
            scanf("%s%lld%lld%lld%lld", tmp, &d.day, &d.year, &d.hour, &num[i]);
            for (int j = 1; j <= 12; ++j) {
                if (strcmp(tmp, str[j]) == 0) {
                    d.month = j; break;
                }
            }
            time[i] = gettime(d);
            //printf("%d %d\n", i, time[i]);
        }
        scanf("%d%d", &t, &s);
        for (int i = 0; i < m; ++i) scanf("%lld", &arr[i]);
        q[l = r = 0] = 0, Min[0] = arr[0];
        
        for (int i = 1; i < m; ++i) {
            if (i - q[l] > t) ++l;
            while (arr[i] <= arr[q[r]] + s * (i - q[r]) && r >= l) {
                --r;
            }
            q[++r] = i;
            Min[i] = arr[q[l]] + s * (i - q[l]);
        }
        //        for (int i = 0; i < m; ++i) {
        //            printf("%d ", Min[i]);
        //        }
        //        printf("\n");
        LL ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += num[i] * Min[time[i]];
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// hdu 1506
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long LL;
LL arr[maxn], q[maxn], cnt, left[maxn], right[maxn];

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; ++i) scanf("%lld", &arr[i]);
        memset(left, -1, sizeof(left));
        memset(right, 0, sizeof(right));
        
        cnt = 0;
        q[cnt++] = 0;
        for (int i = 1; i < n; ++i) {
            while (arr[i] < arr[q[cnt - 1]] && cnt > 0) {
                right[q[cnt - 1]] = i;
                --cnt;
            }
            q[cnt++] = i;
        }
        for (int i = 0; i < n; ++i) {
            if (right[i] == 0) right[i] = n;
            //printf("%d ", right[i]);
        }
        //printf("\n");
        cnt = 0;
        q[cnt++] = n - 1;
        for (int i = n - 2; i >= 0; --i) {
            while (arr[i] < arr[q[cnt - 1]] && cnt > 0) {
                left[q[cnt - 1]] = i;
                --cnt;
            }
            q[cnt++] = i;
        }
        //for (int i = 0; i < n; ++i) {
        //printf("%d ", left[i]);
        //}
        LL Max = 0;
        for (int i = 0; i < n; ++i) {
            Max = max(Max, (right[i] - left[i] - 1) * arr[i]);
        }
        printf("%lld\n", Max);
    }
    return 0;
}


// hdu 1937
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 310;
char s[maxn][maxn];
int arr[maxn][maxn];

int main() {
    
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k) && (n + m + k)) {
        for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                arr[i][j] = arr[i][j - 1] + (s[i][j] == '.');
                //printf("%d ", arr[i][j]);
            }
            //printf("\n");
        }
        int Min = 0x3fffffff;
        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; ++j) {
                int l = 1, r = 1, sum = arr[1][j] - arr[1][i - 1];
                while (1) {
                    while (sum < k && r < n) {
                        ++r;
                        sum += arr[r][j] - arr[r][i - 1];
                    }
                    if (sum < k) break;
                    
                    while (sum >= k) {
                        Min = min(Min, (r - l + 1) * (j - i + 1));
                        sum -= arr[l][j] - arr[l][i - 1];
                        ++l;
                    }
                    
                }
            }
        }
        printf("%d\n", Min);
    }
    return 0;
}


// hdu 5178
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
LL arr[maxn], t, n, k;

int main() {
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &k);
        for (int i = 0; i < n; ++i) scanf("%lld", &arr[i]);
        sort(arr, arr + n);
        LL ans = 0;
        for (int l = 0; l < n; ++l) {
            int pos = (int)(upper_bound(arr, arr + n, arr[l] + k) - arr);
            ans += pos - l - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// hdu 5672
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e6 + 10;
int vis[30];

int main() {
    int t, k;
    char s[maxn];
    scanf("%d", &t);
    while (t--) {
        scanf("%s%d", s, &k);
        memset(vis, 0, sizeof(vis));
        int len = (int)strlen(s);
        int r = 0, num = 0;
        long long ans = 0;
        for (int l = 0; l < len; ++l) {
            while (num < k && r < len) {
                if (vis[s[r] - 'a'] == 0) {
                    ++num;
                }
                ++vis[s[r++] - 'a'];
            }
            if (num >= k) ans += len - r + 1;
            else break;
            
            --vis[s[l] - 'a'];
            if (vis[s[l] - 'a'] == 0) --num;
        }
        printf("%lld\n", ans);
    }
    return 0;
}


// poj 2739 尺取法
#include <cstdio>
using namespace std;
const int maxn = 1e4 + 10;
int prime[maxn], cnt;
bool is[maxn];

void init() {
    for (int i = 2; i < maxn; ++i) {
        if (is[i] == 0) {
            prime[cnt++] = i;
            for (int j = 2; i * j < maxn; ++j) {
                is[i * j] = 1;
            }
        }
    }
}

int main() {
    init();
    int n;
    while (~scanf("%d", &n) && n) {
        int l = 0, r = 0, sum = 0, ans = 0;
        while (1) {
            if (prime[r] > n) break;
            while (sum < n) {
                sum += prime[r++];
                if (sum == n) ++ans;
            }
            while (sum >= n) {
                sum -= prime[l++];
                if (sum == n) ++ans;
            }
            if (sum == n) ++ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}


// poj 3061 尺取法1
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int arr[maxn];

int main() {
    int t, n, s;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &s);
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            sum += arr[i];
        }
        if (sum < s) {printf("0\n"); continue;}
        if (arr[0] >= s) {printf("1\n"); continue;}
        
        int Min = n + 1, nowsum = arr[0], left = 0;
        for (int i = 1; i < n; ++i) {
            nowsum += arr[i];
            if (nowsum >= s) {
                while (nowsum >= s) {
                    nowsum -= arr[left++];
                }
                Min = min(Min, i - left + 2);
            }
        }
        printf("%d\n", Min);
    }
    return 0;
}


// poj 3061 尺取法2
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int arr[maxn];

int main() {
    int t, n, s;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &s);
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            sum += arr[i];
        }
        if (sum < s) {printf("0\n"); continue;}
        if (arr[0] >= s) {printf("1\n"); continue;}
        
        int Min = n, nowsum = arr[0], l = 0, r = 1;
        while (1) {
            while (nowsum < s && r < n) {
                nowsum += arr[r++];
            }
            if (nowsum < s) break;
            Min = min(Min, r - l);
            while (nowsum >= s) {
                nowsum -= arr[l++];
            }
            Min = min(Min, r - l + 1);
        }
        printf("%d\n", Min);
    }
    return 0;
}


// hdu 5256
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int arr[maxn], b[maxn], ca;

int main() {
    
    int t, n, cnt;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            arr[i] -= i;
        }
        b[0] = arr[0];
        cnt = 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] >= b[cnt - 1]) b[cnt++] = arr[i];
            else {
                int now = (int)(upper_bound(b, b + cnt, arr[i]) - b);
                b[now] = arr[i];
            }
        }
        printf("Case #%d:\n%d\n", ++ca, n - cnt);
    }
    return 0;
}


// hdu 3244 二分+完全背包。。然而我暴力。。
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 110, inf = 0x3fffffff;

int n, k;
struct node {
    int x, y, s1, s2, p1, p2;
} arr[maxn];

bool judge(int m) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int d = m * arr[i].x - arr[i].y; // 还需买多少
        if (d <= 0) continue;
        int Min = inf;
        // 遍历大包，买j个大包
        for (int j = 0; ; ++j) {
            int res = d - j * arr[i].s2;
            int tmp = j * arr[i].p2;
            
            if (res > 0) tmp += ((res - 1) / arr[i].s1 + 1) * arr[i].p1;
            Min = min(Min, tmp);
            if (res <= 0) break;
        }
        sum += Min;
        if (sum > k) return 0;
    }
    return 1;
}

int main() {
    while (~scanf("%d%d", &n, &k) && (n + k)) {
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d%d%d%d", &arr[i].x, &arr[i].y, &arr[i].s1, &arr[i].p1, &arr[i].s2, &arr[i].p2);
        }
        int l = 0, r = 1e6;
        while (l < r) {
            int m = (l + r) / 2;
            if (m == 5) {
                ;
            }
            if (judge(m)) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        printf("%d\n", l - 1);
    }
    return 0;
}


// hdu 4190 二分
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 5e5 + 10;
int arr[maxn], n, k;

bool judge(LL m) {
    if (m == 0) return 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cnt += (arr[i] - 1) / m + 1;
        if (cnt > k) return 0;
    }
    return 1;
}

int main() {
    while (~scanf("%d%d", &n, &k) && !(n == -1 && k == -1)) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        LL l = 0, r = 3000000000000;
        while (l < r) {
            LL m = (l + r) / 2;
            if (judge(m)) r = m;
            else l = m + 1;
        }
        printf("%lld\n", r);
    }
    return 0;
}


// hdu 2289
#include <cstdio>
#include <cmath>
using namespace std;
const double eps = 1e-7, pi = acos(-1);
double r1, r2, h, v;

double findv(double m) {
    return pi * (m*m*m*(r2-r1)*(r2-r1)/(3*h*h) + m*r1*r1 + r1*m*m*(r2-r1)/h);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lf%lf%lf%lf", &r1, &r2, &h, &v);
        double l = 0, r = h;
        while (fabs(r - l) > eps) {
            double m = (l + r) / 2;
            if (findv(m) - v < 0) l = m;
            else r = m;
        }
        printf("%.6f\n", l);
    }
    return 0;
}


// hdu 4768
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 5e4 + 10;
LL A[maxn], B[maxn], C[maxn];
int n;
LL max(LL a, LL b) {return a > b ? a : b;}
LL min(LL a, LL b) {return a < b ? a : b;}

bool judge(LL m) {
    LL cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (m < A[i]) continue;
        LL Min = min(m, B[i]);
        LL tmp = (Min - A[i]) / C[i] + 1;
        if (tmp > 0) cnt += tmp;
    }
    return cnt % 2 == 1;
}

int main() {
    while (~scanf("%d", &n)) {
        LL Max = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld%lld%lld", &A[i], &B[i], &C[i]);
            Max = max(Max, B[i]);
        }
        LL l = 0, r = Max + 1;
        while (l < r) {
            LL m = (l + r) / 2;
            if (judge(m)) r = m;
            else l = m + 1;
        }
        if (r == Max + 1) printf("DC Qiang is unhappy.\n");
        else {
            LL cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (r > B[i] || r < A[i]) continue;
                if ((r - A[i]) % C[i] == 0) ++cnt;
            }
            printf("%lld %lld\n", r, cnt);
        }
    }
    return 0;
}


// poj 3122
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 1e4 + 10;
const double pi = acos(-1.0), eps = 1e-8;
int arr[maxn], t, n, f;

bool judge(double now) {
    if (fabs(now) < eps) return 1;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cnt += (int)(arr[i] / now);
    }
    return cnt >= f;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &f);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            arr[i] *= arr[i];
        }
        ++f;
        double l = 0, r = 1e8;
        while (fabs(r - l) > eps) {
            double m = (l + r) / 2;
            if (judge(m)) {
                l = m;
            } else {
                r = m;
            }
        }
        printf("%.4f\n", l * pi);
    }
    return 0;
}


// poj 3258
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int L, n, m, arr[maxn];

bool judge(int len) {
    int last = 0, tmp = m;
    for (int i = 0; i < n; ++i) {
        if (arr[i] - last >= len) {
            last = arr[i];
        } else {
            --tmp;
        }
        if (tmp < 0) return 0;
    }
    if (L - last < len) --tmp;
    return tmp >= 0;
}

int main() {
    scanf("%d%d%d", &L, &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    sort(arr, arr + n);
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) / 2;
        if (mid < 5) {
            ;
        }
        if (judge(mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    printf("%d\n", l - 1);
    return 0;
}


// poj 3579
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int arr[maxn], n;

bool judge(int m) {
    int cnt = 0;
    long long sum = n * (n - 1) / 2;
    for (int i = 0; i < n; ++i) {
        int pos = (int)(lower_bound(arr, arr + n, arr[i] + m) - arr);
        cnt += n - pos;
        if (cnt >= sum / 2 + 1) return 1;
    }
    if (cnt >= sum / 2 + 1) return 1;
    return 0;
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        sort(arr, arr + n);
        int l = 0, r = 2e9;
        while (l < r) {
            int m = (l + r) / 2;
            if (judge(m)) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        printf("%d\n", l - 1);
    }
    return 0;
}


// CodeForces - 343C
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int n1, n2;
struct node {
    LL now, left;
} tmp[maxn];
LL arr1[maxn], arr2[maxn];

LL abs(LL a) {return a > 0 ? a : -a;}
int max(int a, int b) {return a > b ? a : b;}

bool judge(LL m) {
    for (int i = 0; i < n1; ++i) {
        tmp[i].now = arr1[i], tmp[i].left = m;
    }
    int Min = 0;
    for (int i = 0; i < n2; ++i) {
        while (tmp[Min].left < abs(tmp[Min].now - arr2[i])) {
            ++Min;
            if (Min >= n1) return 0;
        }
        LL a = tmp[Min].left - abs(tmp[Min].now-arr2[i]);
        int j, k;
        for (j = i; j < n2; ++j) {
            if (a <arr2[j] - arr2[i]) break;
        }
        LL b = tmp[Min].left;
        for (k = j; k < n2; ++k) {
            if (b - (arr2[k]-arr2[i]) - abs(arr2[k] - tmp[Min].now) < 0) {
                break;
            }
        }
        --j, --k;
        i = max(j, k);
        tmp[Min].left = 0;
    }
    return 1;
}

int main() {
    scanf("%d%d", &n1, &n2);
    for (int i = 0; i < n1; ++i) scanf("%lld", &arr1[i]);
    for (int i = 0; i < n2; ++i) scanf("%lld", &arr2[i]);
    LL l = 0, r = 1e12;
    while (l < r) {
        LL m = (l + r) / 2;
        if (judge(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    printf("%lld\n", r);
    return 0;
}


// poj 3104
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
LL arr[maxn], k, Max = -1;

LL max(LL a, LL b) {
    return a < b ? b : a;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
        Max = max(Max, arr[i]);
    }
    scanf("%lld", &k);
    if (k == 1) {printf("%lld\n", Max); return 0;}
    
    LL l = 1, r = Max, sum, m = 0;
    while (l < r) {
        m = (l + r) / 2, sum = 0;
        int flag = 0;
        for (int i = 0; i < n && !flag; ++i) {
            if (arr[i] > m) {
                sum += (LL)(ceil((double)(arr[i] - m) / (k - 1)));
                if (sum > m) flag = 1;
            }
        }
        if (flag) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    printf("%lld\n", r);
    return 0;
}


// CodeForces - 371C
#include <cstdio>
using namespace std;
typedef long long LL;
char s[110]; // 配方
int B, S, C, nb, ns, nc, pb, ps, pc;
LL sum;

int main(int argc, const char * argv[]) {
    scanf("%s", s);
    
    for (int i = 0; s[i]; ++i) {
        if (s[i] == 'B') ++B;
        else if (s[i] == 'S') ++S;
        else ++C;
    }
    scanf("%d%d%d", &nb, &ns, &nc);
    scanf("%d%d%d", &pb, &ps, &pc); // 单价
    scanf("%lld", &sum);
    LL l = 0, r = 1e13, m = 0, res = 0;
    while (l < r) {
        m = (l + r) / 2;
        LL all = 0;
        if (nb < m * B) all += (m * B - nb) * pb;
        if (ns < m * S) all += (m * S - ns) * ps;
        if (nc < m * C) all += (m * C - nc) * pc;
        if (all > sum) {
            r = m;
        } else {
            l = m + 1;
            res = m;
        }
    }
    printf("%lld\n", res);
    return 0;
}
*/
