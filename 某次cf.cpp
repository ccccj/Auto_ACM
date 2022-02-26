//
//  main.cpp
//  cf1
//
//  Created by admin on 18/9/17.
//  Copyright © 2018年 Amon. All rights reserved.
//
// C
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 2e5 + 10;
bool is[maxn];

struct node {
    int num, id;
    friend bool operator < (node a, node b) {
        return a.num < b.num;
    }
};

priority_queue<node> q, p;
vector <int> zero;

int main()
{
    int fu = 0, zheng = 0, n, x;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (x < 0) {
            q.push({x, i});
            fu++;
        } else if (x == 0) {
            zero.push_back(i);
        } else {
            p.push({x, i});
            zheng++;
        }
    }
    
    if (zheng != 0) {
        if (fu%2 && zero.size() != 0) {
            //奇数个负数，有0有正数
            printf("1 %d %d\n", q.top().id, zero[0]);
            q.pop();
        } else if (fu%2 && zero.size() == 0) {
            //奇数个负数，有正数没0
            printf("2 %d\n", q.top().id);
            q.pop();
        }
    } else if (zheng == 0) {
        if (fu %2  && zero.size() != 0) {
            //有负数 有0 没有正数 最大只能为 0
            printf("1 %d %d\n", q.top().id, zero[0]);
            q.pop();
        }else if (fu%2 && zero.size() == 0) {
            //有奇数个负数 没0 没正数 //去掉一个负数
            printf("2 %d\n", q.top().id);
            q.pop();
        }
    }
    
    vector<int> v;
    while(!q.empty()) {
        v.push_back(q.top().id);
        q.pop();
    }
    while(!p.empty()) {
        v.push_back(p.top().id);
        p.pop();
    }
    int len1 = (int)v.size();
    for (int i = 0; i < len1 - 1; i++) {
        printf("1 %d %d\n", v[i], v[i + 1]);
    }
    
    int len = (int)zero.size();
    if (len != 0) {
        for (int i = 0; i < len - 1; i++) {
            printf("1 %d %d\n", zero[i], zero[i + 1]);
        }
        if (len1 != 0) printf("2 %d\n", zero[len - 1]);
    }
    
    return 0;
}

/*
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 200010;
int n;
LL t, ans, a[maxn], sum[maxn];

struct node {
    int left, right;
};

void recursionMax (int left, int right) {
    // 只有一个数
    if (left == right) {
        if (a[left] < t) {
            ++ans;
        }
        return;
    }
    int mid = (left + right) / 2;
    
    recursionMax (left, mid); // 左
    recursionMax(mid + 1, right); // 右
    
    for (int i = left; i <= mid; ++i) {
        for (int j = mid + 1; j <= right; ++j) {
            if (i == 0) {
                if (sum[j] < t) {
                    //printf("%lld\n", sum[j]);
                    ++ans;
                }
            } else {
                if (sum[j] - sum[i - 1] < t) {
                    ++ans;
                }
            }
        }
    }
    
}

int main() {
    
    while (~scanf("%d%lld", &n, &t)) {
        ans = 0;
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            sum[i] = sum[i-1] + a[i];
            //printf("%lld\n", sum[i]);
        }
        recursionMax(0, n - 1);
        printf("%lld\n", ans);
    }
    return 0;
}


// B
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long LL;
const int inf = 0x3fffffff;
LL A, B, C, AB, AC, BC, ABC;

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main() {
    
    int n;
    while (~scanf("%d", &n)) {
        A = B = C = AB = AC = BC = ABC = inf;
        char s[10];
        int t;
        for (int i = 0; i < n; ++i) {
            scanf("%d%s", &t, s);
            if (s[1] == '\0') {
                if (s[0] == 'A') {
                    A = min(A, t);
                } else if (s[0] == 'B') {
                    B = min(B, t);
                } else {
                    C = min(C, t);
                }
            } else if (s[2] == '\0') {
                sort(s, s + 2);
                if (s[0] == 'A') {
                    if (s[1] == 'B') {
                        AB = min(AB, t);
                    } else {
                        AC = min(AC, t);
                    }
                } else {
                    BC = min(BC, t);
                }
            } else {
                ABC = min(ABC, t);
            }
        }
        LL Min = ABC;
        if (AB + C < Min) Min = AB + C;
        if (A + BC < Min) Min = A + BC;
        if (B + AC < Min) Min = B + AC;
        if (A + B + C < Min) Min = A + B + C;
        
        if (AB + BC < Min) Min = AB + BC;
        if (AB + AC < Min) Min = AB + AC;
        if (AC + BC < Min) Min = AC+ BC;
        
        if (Min == inf) {
            printf("-1\n");
            continue;
        }
        printf("%lld\n", Min);
        
    }
    return 0;
}


// A
#include <cstdio>
#include <algorithm>
using namespace std;
int arr[110];

int main(int argc, const char * argv[]) {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        int tmp = m;
        int Max = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            Max = max(arr[i], Max);
        }
        int ans = Max;
        for (int i = 0; i < n; ++i) {
            m -= Max - arr[i];
        }
        if (m > 0) {
            if (m % n == 0) {
                ans += m / n;
            } else {
                ans += m / n + 1;
            }
        }
        printf("%d %d\n", ans, tmp + Max);
    }
    return 0;
}
*/
