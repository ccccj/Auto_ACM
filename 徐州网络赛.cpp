//
//  main.cpp
//  xuzhou网络赛
//
//  Created by admin on 18/9/9.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    
    
    return 0;
}
/*
// G
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 5e4 + 10;

struct node {
    LL x, y;
} arr[maxn];

LL x[maxn], y[maxn], tree_x[maxn << 2], tree_y[maxn << 2];

LL max(LL a, LL b) {
    return a > b ? a : b;
}

void update_y(int l, int r, int tar, LL y, int now) {
    if (l == r) {
        if (tree_y[now] < y) {
            tree_y[now] = y;
        }
        return;
    }
    int m = (r + l) / 2;
    if (tar <= m) update_y(l, m, tar, y, now << 1);
    else update_y(m + 1, r, tar, y, (now << 1)|1);
    tree_y[now] = max(tree_y[now << 1], tree_y[(now << 1)|1]);
}

void update_x(int l, int r, int tar, LL x, int now) {
    if (l == r) {
        if (tree_x[now] < x) {
            tree_x[now] = x;
        }
        return;
    }
    int m = (r + l) / 2;
    if (tar <= m) update_x(l, m, tar, x, now << 1);
    else update_x(m + 1, r, tar, x, (now << 1)|1);
    tree_x[now] = max(tree_x[now << 1], tree_x[(now << 1)|1]);
}

LL query_y(int l, int r, int L, int R, int now) {
    LL ans = 0;
    if (l >= L && r <= R) {
        return tree_y[now];
    }
    int m = (r + l) / 2;
    if (m >= L) {
        ans = query_y(l, m, L, R, now << 1);
    }
    if (m < R) {
        ans = max(ans, query_y(m + 1, r, L, R, (now << 1)|1));
    }
    return ans;
}

LL query_x(int l, int r, int L, int R, int now) {
    LL ans = 0;
    if (l >= L && r <= R) {
        return tree_x[now];
    }
    int m = (r + l) / 2;
    if (m >= L) {
        ans = query_x(l, m, L, R, now << 1);
    }
    if (m < R) {
        ans = max(ans, query_x(m + 1, r, L, R, (now << 1)|1));
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld", &x[i], &y[i]);
        arr[i].x = x[i], arr[i].y = y[i];
    }
    sort(x, x + n);
    sort(y, y + n);
    LL resx = unique(x, x + n) - x, resy = unique(y, y + n) - y;
    LL ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        int pos = (int)(lower_bound(x, x + resx, arr[i].x) - x);
        LL k = query_y(0, n - 1, pos, n - 1, 1);
        //cout << "k  " << k << endl;
        if (k < arr[i].y) {
            ans += arr[i].y - k;
          //  cout << "x   " << arr[i].y - k << endl;
        }
        update_y(0, n - 1, pos, arr[i].y, 1);
    }
    
    for (int i = n - 1; i >= 0; --i) {
        int pos = (int)(lower_bound(y, y + resy, arr[i].y) - y);
        LL k = query_x(0, n - 1, pos, n - 1, 1);
        //cout << "k  " << k << endl;
        if (k < arr[i].x) {
            ans += arr[i].x - k;
            //cout << "y  " << arr[i].y - k << endl;
        }
        update_x(0, n - 1, pos, arr[i].x, 1);
    }
    
    printf("%lld\n", ans);
    return 0;
}


// A
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int MOD = 1e9 + 7;

LL _pow(LL a, LL b) {
    LL ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

LL fact(LL a) {
    LL ans = 1;
    for (int i = 3; i <= a; ++i) {
        ans = (ans * i) % MOD;
    }
    return ans;
}

int main() {
    int t;
    LL m, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &m, &k);
        if (m == 1) {
            LL ans = _pow(2, k);
            printf("%lld\n", ans);
        } else if (k == 1) {
            cout << 2 << endl;
        } else {
            LL tmp = _pow(2, k) - 1;
            LL ans = _pow(tmp, m);
            m %= 2;
            ans += pow(-1, m) * tmp;
            
            if (m == 1) {
                ans += (tmp + 1) * _pow(tmp, m - 3);
            }
            printf("%lld\n", ans % MOD);
        }
    }
    return 0;
}


#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int sum = 0;
    for (unsigned i = 0; i < 8; ++i) {
        for (unsigned j = 0; j < 8; ++j) {
            if (((i ^ j) & 1) == 1 && (((i ^ j) >> 1) & 1) == 1
                && (((i ^ j) >> 2) & 1) == 1) {
                continue;
            }
            for (unsigned k = 0; k < 8; ++k) {
                if (((k ^ j) & 1) == 1 && (((k ^ j) >> 1) & 1) == 1
                    && (((k ^ j) >> 2) & 1) == 1) {
                    continue;
                }
                for (unsigned z = 0; z < 8; ++z) {
                    if (((k ^ z) & 1) == 1 && (((k ^ z) >> 1) & 1) == 1&& (((k ^ z) >> 2) & 1) == 1) {
                        continue;
                    }
                    for (int y = 0; y < 8; ++y) {
                        if (((i ^ y) & 1) == 1 && (((i ^ y) >> 1) & 1) == 1 && (((i ^ y) >> 2) & 1) == 1) {
                            continue;
                        }
                        if (((y ^ z) & 1) == 1 && (((y ^ z) >> 1) & 1) == 1 && (((y ^ z) >> 2) & 1) == 1) {
                            continue;
                        }
                        printf("%d %d %d %d %d\n", i, j, k, z, y);
                        ++sum;

                    }
                    
                }
            }
        }
    }
    cout << sum << endl;
    return 0;
}


#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long LL;
LL segtree[maxn << 2], a[maxn << 2], sum[maxn << 2];
int n, q;

void build_sum(int l, int r, int now) {
    if (l == r) {
        sum[now] = a[l];
        return;
    }
    int mid = (l + r)/2;
    build_sum(l, mid, now << 1);
    build_sum(mid + 1, r, (now << 1)|1);
    sum[now] = sum[now << 1] + sum[(now << 1)|1];
}

void build_tree(int l, int r, int now) {
    if (l == r) {
        segtree[now] = a[l]*(n - l + 1);
        return;
    }
    int mid = l + (r - l)/2;
    build_tree(l, mid, now << 1);
    build_tree(mid + 1, r, (now << 1)|1);
    segtree[now] = segtree[now << 1] + segtree[(now << 1)|1];
}

void update_sum(int l, int r, long long int tar, long long int c, int now) {
    if (l == r) {
        sum[now] = c;
        return;
    }
    int mid = l + (r - l)/2;
    if (tar <= mid) update_sum(l, mid, tar, c, now << 1);
    else update_sum(mid + 1, r, tar, c, (now << 1)|1);
    sum[now] = sum[now << 1] + sum[(now << 1)|1];
}

void update_tree(int l, int r, long long int tar, long long int c, int now) {
    if (l == r) {
        segtree[now] = c*(n - l + 1);
        return;
    }
    int mid = l + (r - l)/2;
    if (tar <= mid) update_tree(l, mid, tar, c, now << 1);
    else update_tree(mid + 1, r, tar, c, (now << 1)|1);
    segtree[now] = segtree[now << 1] + segtree[(now << 1)|1];
}

LL query_sum(int L, int R, long long int l, long long int r, int now) {
    if (L <= l && R >= r) {
        return sum[now];
    }
    LL ans = 0;
    int mid = l + (r - l)/2;
    if (L <= mid) ans += query_sum(L, R, l, mid, now << 1);
    if (R > mid) ans += query_sum(L, R, mid + 1, r, (now << 1)|1);
    return ans;
}

LL query_tree(int L, int R, long long int l, long long int r, int now) {
    if (L <= l && R >= r) {
        return segtree[now];
    }
    LL ans = 0;
    int mid = l + (r - l)/2;
    if (L <= mid) ans += query_tree(L, R, l, mid, now << 1);
    if (R > mid) ans += query_tree(L, R, mid + 1, r, (now << 1)|1);
    return ans;
}


int main()
{
    while (scanf("%d %d", &n, &q) != EOF) {
        memset(segtree, 0, sizeof segtree);
        memset(sum, 0, sizeof sum);
        
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        
        build_sum(1, n, 1);
        build_tree(1, n, 1);
        
        LL c, b, op;
        for (int i = 0; i < q; i++) {
            scanf("%lld %lld %lld", &op, &b, &c);
            if (op == 1) {
                //printf("** %lld %lld\n",query_tree(b, c, 1, n, 1), query_sum(b, c, 1, n, 1));
                printf("%lld\n", query_tree(b, c, 1, n, 1) - query_sum(b, c, 1, n, 1)*(n - c));
            } else {
                update_sum(1, n, b, c, 1);
                update_tree(1, n, b, c, 1);
            }
            
        }
    }
    
    return 0;
}


#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;
char str[2000000];

int main()
{
    int T, n;
    char s[10];
    scanf("%d", &T);
    while (T--) {
        scanf("%d %s", &n, s);
        scanf("%s", str);
        
        int f = -1;
        for (int i = 0; i < n; ++i) {
            if (s[0] != str[i]) {
                f = i;
                break;
            }
        }
        if (f == -1) {
            printf("1\n");
            continue;
        }
        long long int ans = 0;
        int m = abs(s[0] - str[f]);
        while (m) {
            m /= 10;
            ans++;
        }
        ans += 2 * (n - f - 1);
        printf("%lld\n", ans);
    }
    
    return 0;
}
*/
