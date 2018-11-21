//
//  main.cpp
//  <kuangbin>dp1
//
//  Created by Amon on 2018/11/16.
//  Copyright © 2018 Amon. All rights reserved.
//
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010, inf = 0x3fffffff;
int x[maxn], y[maxn], dp[maxn][maxn], sub[maxn], sum[maxn], path[maxn][maxn];
vector<int> v;
bool is(int i, int j, int k) {
  while (path[i][j] != k) {
    if (path[i][j] == 0) {
      return 1;
    }
    --i, j -= sub[i];
  }
  return path[i][j] != k;
}

int main() {
  int n, m, ca = 1;
  while (~scanf("%d%d", &n, &m) && (n + m)) {
    printf("Jury #%d\n", ca++);
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d", &x[i], &y[i]);
      sub[i] = x[i] - y[i] + 400, sum[i] = x[i] + y[i];
    }
    memset(dp, -1, sizeof dp);
    memset(path, 0, sizeof path);

    for (int i = 1; i <= n; ++i) {
      dp[1][sub[i]] = sum[i];
    }
    for (int i = 2; i <= m; ++i) {
      for (int j = 0; j < maxn; ++j) {
        for (int k = 1; k <= n; ++k) {
          if (j >= sub[k] && dp[i-1][j-sub[k] != -1] && dp[i-1][j-sub[k]] + sum[k] > dp[i][j]
              && is(i-1, j-sub[k], k)) {
            dp[i][j] = dp[i-1][j-sub[k]] + sum[k];
            path[k][j] = i;
          }
        }
      }
    }
    int i, j, tmp = 0;
    for (i = 400, j = 400; ; ++i, --j) {
      if (dp[m][i] != -1) break;
      if (dp[m][j] != -1) break;
    }

    if (dp[m][i] != -1) tmp = i;
    else tmp = j;
    int s = dp[m][tmp];
    tmp -= 400;
    printf("tmp %d   s %d\n", tmp, s);
    printf("Best jury has value %d for prosecution and value %d for defence:\n", (s + tmp) / 2, (s - tmp) / 2);

    while (path[m][tmp] != 0) {
      int k = path[m][tmp];
      v.push_back(k);
      --m, tmp -= sub[k];
    }

    for (int i = (int)v.size() - 1; i >= 0; --i) {
      printf(" %d", v[i]);
    }
    cout << endl;
  }
  return 0;
}

/*
// p3666
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 2e3 + 10, inf = 0x3fffffff;
int arr[maxn], dp[maxn][maxn], tmp[maxn], lastMin[maxn];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
    tmp[i] = arr[i];
  }
  sort(tmp + 1, tmp + 1 + n);
  for (int i = 1; i <= n; ++i) {
    int Min = inf;
    for (int j = 1; j <= n; ++j) {
      Min = min(Min, dp[i - 1][j]);
      dp[i][j] = Min + abs(arr[i] - tmp[j]);
      //printf("%d %d %d\n", i, j, dp[i][j]);
    }
  }
  int ans = inf;
  for (int i = 1; i <= n; ++i) {
    ans = min(ans, dp[n][i]);
  }
  for (int i = 1; i <= n; ++i) {
    int Min = inf;
    for (int j = n; j >= 1; --j) {
      Min = min(Min, dp[i - 1][j]);
      dp[i][j] = Min + abs(arr[i] - tmp[j]);
      //printf("%d %d %d\n", i, j, dp[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    ans = min(ans, dp[n][i]);
  }
  printf("%d\n", ans);
  return 0;
}


// hdu 2859
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e3 + 10;
char Map[maxn][maxn];
int dp[maxn][maxn], n;

bool judge(int i, int j) {
  return i >= 0 && i < n && j >= 0 && j < n;
}

int main() {
  while (~scanf("%d", &n) && n) {
    for (int i = 0; i < n; ++i) scanf("%s", Map[i]);
    int Max = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = n - 1; j >= 0; --j) {
        dp[i][j] = 1;
        if (judge(i - 1, j + 1)) {
          for (int k = 1; k <= dp[i-1][j+1]; ++k) {
            if (Map[i-k][j] == Map[i][j+k]) {
              dp[i][j] = k + 1;
            } else {
              break;
            }
          }
        }
        Max = max(Max, dp[i][j]);
      }
    }
    printf("%d\n", Max);
  }
  return 0;
}


// hdu 1789
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e5, inf = 0x3fffffff;
int n, dp[maxn], Time[maxn], Last[maxn];
struct node {
  char s[110];
  int d, c;
} arr[maxn];

void init() {
  memset(Time, 0, sizeof(Time));
  memset(Last, 0, sizeof(Last));
  fill(dp, dp + maxn, inf);
  dp[0] = 0;
}

void dfs(int now) {
  if (Last[now]) dfs(Last[now]);
  int tmp = now ^ Last[now];
  for (int i = 0; i < 20; ++i) {
    if ((tmp >> i) & 1) {
      printf("%s\n", arr[i + 1].s);
      return;
    }
  }
}

bool cmp(node a, node b) {
  return strcmp(a.s, b.s) > 0;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%s%d%d", arr[i].s, &arr[i].d, &arr[i].c);
    }
    sort(arr + 1, arr + n + 1, cmp);
    for (int i = 1; i < 1 << n; ++i) {
      for (int j = 0; j < 16; ++j) {
        if ((i >> j) & 1) {
          int last = i - (1 << j);
          Time[i] = Time[last] + arr[j + 1].c;
          if (Time[i] <= arr[j + 1].d) {
            if (dp[i] > dp[last]) {
              dp[i] = dp[last];
              Last[i] = last;
            }
          } else {
            if (dp[i] > dp[last] + Time[i] - arr[j + 1].d) {
              dp[i] = dp[last] + Time[i] - arr[j + 1].d; Last[i] = last;
            }
          }
        }
      }
    }
    printf("%d\n", dp[(1 << n) - 1]);
    dfs((1 << n) - 1);
  }
  return 0;
}


// hdu 1024
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 10, inf = 0x3fffffff;
int arr[maxn], dp[2][maxn], Maxi[2][maxn];

int main() {
  int k, n;
  while (~scanf("%d%d", &k, &n)) {
    for (int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
    memset(Maxi, 0, sizeof(Maxi));
    fill(Maxi[1], Maxi[1] + n + 1, -inf);
    memset(dp, 0, sizeof(dp));

    int last = 0, now = 1;
    for (int i = 1; i <= k; ++i) {
      int Max = -inf;
      for (int j = 1; j <= n; ++j) {
        if (i > j) {
          dp[now][j] = -inf;
          continue;
        }
        // 单独一组 / 和前面归为一组
        dp[now][j] = max(Maxi[last][j - 1], dp[now][j - 1]) + arr[j];
        //printf("%d %d\n", Maxi[last][j - 1], dp[now][j - 1]);
        Max = Maxi[now][j] = max(Max, dp[now][j]);
        //printf("dp[now][j] %d %d %d\n", i, j, dp[now][j]);
        //printf("Maxi[now][j] now:%d j:%d %d\n", now, j, Maxi[now][j]);
      }
      swap(now, last);
    }
    int Max = -inf;
    // i 从 k 开始，否则错误
    for (int i = k; i <= n; ++i) {
      Max = max(Maxi[k % 2][i], Max);
    }
    printf("%d\n", Max);
  }
  return 0;
}


// poj 3616 0ms
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
struct node {
  int s, e, get;
} arr[maxn];

int dp[maxn];

bool cmp(node a, node b) {
  if (a.s == b.s && a.e == b.e) return a.get < b.get;
  if (a.s == b.s) return a.e < b.e;
  return a.s < b.s;
}

int main() {
  int t, n, r;
  scanf("%d%d%d", &t, &n, &r);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &arr[i].s, &arr[i].e, &arr[i].get);
  }
  int Max = 0;
  sort(arr + 1, arr + n + 1, cmp);
  for (int i = 1; i <= n; ++i) {
    dp[i] = arr[i].get;
    for (int j = 1; j < i; ++j) {
      if (arr[i].s >= arr[j].e + r) {
        dp[i] = max(dp[i], dp[j] + arr[i].get);
      }
    }
    Max = max(Max, dp[i]);
  }
  printf("%d\n", Max);
  return 0;
}


// poj 3616 860ms
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
struct node {
  int s, e, get;
} arr[maxn];

int dp[1000010];

bool cmp(node a, node b) {
  if (a.s == b.s && a.e == b.e) return a.get < b.get;
  if (a.s == b.s) return a.e < b.e;
  return a.s < b.s;
}

int main() {
  int t, n, r;
  scanf("%d%d%d", &t, &n, &r);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &arr[i].s, &arr[i].e, &arr[i].get);
  }
  memset(dp, 0, sizeof(dp));
  sort(arr + 1, arr + n + 1, cmp);
  for (int i = 1; i <= n; ++i) {
    for (int j = t; j >= arr[i].e; --j) {
      dp[j] = max(dp[j], dp[arr[i].s - r] + arr[i].get);
    }
  }
  printf("%d\n", dp[t]);
  return 0;
}


// hdu 1078
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int n, k, arr[maxn][maxn], dp[maxn][maxn], Max;
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

bool canstay(int x, int y, int to_x, int to_y) {
  if (to_x >= 1 && to_x <= n && to_y >= 1 && to_y <= n
      && arr[x][y] < arr[to_x][to_y]) return 1;
  return 0;
}

void dfs(int x, int y) {
  if (dp[x][y] == -1) {
    dp[x][y] = arr[x][y];
    for (int i = 1; i <= k; ++i) {
      for (int j = 0; j < 4; ++j) {
        int to_x = x + dir[j][0] * i, to_y = y + dir[j][1] * i;
        if (canstay(x, y, to_x, to_y)) {
          dfs(to_x, to_y);
          dp[x][y] = max(dp[x][y], dp[to_x][to_y]+arr[x][y]);
        }
      }
    }
    Max = max(Max, dp[x][y]);
  }
}

int main() {
  while (~scanf("%d%d", &n, &k) && !(n == -1 && k == -1)) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        scanf("%d", &arr[i][j]);
      }
    }
    memset(dp, -1, sizeof(dp));
    Max = 0;
    dfs(1, 1);
    printf("%d\n", Max);
  }
  return 0;
}

/////
// poj 3186
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2e3 + 10;
int arr[maxn], dp[maxn][maxn], n;

int main() {
  while (~scanf("%d", &n)) {
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &arr[i]);
    }
    memset(dp, 0, sizeof(dp));

    for (int len = n - 1; len >= 1; --len) {
      for (int l = 1; l <= n; ++l) {
        int r = l + len - 1;
        if (r > n) continue;
        if (l-1 >= 1) dp[l][r] = max(dp[l][r], dp[l-1][r] + (n-len) * arr[l-1]);
        if (r+1 <= n) dp[l][r] = max(dp[l][r], dp[l][r+1] + (n-len) * arr[r+1]);
        //printf("%d %d %d\n", l, r, dp[l][r]);
      }
    }
    int Max = 0;
    for (int i = 1; i <= n; ++i) {
      Max = max(Max, dp[i][i] + n * arr[i]);
    }
    printf("%d\n", Max);
  }
  return 0;
}


// poj 1661
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e3 + 10, inf = 0x3fffffff;
struct node {
  int x1, x2, h, lt, rt;
} arr[maxn];

bool cmp(node a, node b) {
  if (a.h == b.h && a.x1 == b.x1) return a.x2 < b.x2;
  if (a.h == b.h) return a.x1 < b.x1;
  return a.h < b.h;
}

int main() {
  int t, n, x, y, Max;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d", &n, &x, &y, &Max);
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d%d", &arr[i].x1, &arr[i].x2, &arr[i].h);
      if (arr[i].x1 > arr[i].x2) swap(arr[i].x1, arr[i].x2);
      arr[i].lt = arr[i].rt = inf;
    }
    sort(arr + 1, arr + n + 1, cmp);
    arr[n + 1].x1 = arr[n + 1].x2 = x;
    arr[n + 1].h = y;
    for (int i = 1; i <= n + 1; ++i) {
      bool f1 = 1, f2 = 1;
      for (int j = i - 1; j > 0; --j) {
        if (arr[i].h - arr[j].h > Max || (!f1 && !f2)) break;

        if (arr[i].x1 >= arr[j].x1 && arr[i].x1 <= arr[j].x2 && f1) {
          arr[i].lt = arr[i].h - arr[j].h + min(arr[j].lt + arr[i].x1 - arr[j].x1, arr[j].rt + arr[j].x2 - arr[i].x1);
          f1 = 0;
        }
        if (arr[i].x2 >= arr[j].x1 && arr[i].x2 <= arr[j].x2 && f2) {
          arr[i].rt = arr[i].h - arr[j].h + min(arr[j].lt + arr[i].x2 - arr[j].x1, arr[j].rt + arr[j].x2 - arr[i].x2);
          f2 = 0;
        }
      }
      if (f1 && arr[i].h < Max) arr[i].lt = arr[i].h;
      if (f2 && arr[i].h < Max) arr[i].rt = arr[i].h;
      if (arr[i].lt > arr[i].rt) {
        arr[i].lt = min(arr[i].rt + arr[i].x2 - arr[i].x1, arr[i].lt);
      } else {
        arr[i].rt = min(arr[i].lt + arr[i].x2 - arr[i].x1, arr[i].rt);

      }
    }
    printf("%d\n", arr[n + 1].lt);
  }
  return 0;
}


// hdu 1160
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
struct node {
  int w, s, id;
} arr[maxn];
int last[maxn], b[maxn];

bool cmp(node a, node b) {
  if (a.w == b.w) return a.s < b.s;
  return a.w > b.w;
}

int main() {
  int cnt = 1;
  while (~scanf("%d%d", &arr[cnt].w, &arr[cnt].s)) {
    arr[cnt].id = cnt;
    ++cnt;
  }
  sort(arr + 1, arr + cnt + 1, cmp);
  memset(last, -1, sizeof(last));
  b[1] = 1;
  int Max = 0;
  //    for (int i = 1; i < cnt; ++i) {
  //        printf("%d %d %d %d\n", i, arr[i].id, arr[i].w, arr[i].s);
  //    }
  for (int i = 2; i < cnt; ++i) {
    b[i] = 1;
    for (int j = 0; j < i; ++j) {
      if (arr[j].w > arr[i].w && arr[j].s < arr[i].s
          && b[i] < b[j] + 1) {
        last[i] = j;
        b[i] = b[j] + 1;
      }
    }
    if (b[Max] < b[i]) Max = i;
  }
  //    for (int i = 1; i < cnt; ++i) {
  //        printf("%d %d %d\n", i, b[i], last[i]);
  //    }
  printf("%d\n", b[Max]);
  while (last[Max] != -1) {
    printf("%d\n", arr[Max].id);
    Max = last[Max];
  }
  printf("%d\n", arr[Max].id);
  return 0;
}


// hdu 1260
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2010;
int one[maxn], two[maxn], dp[maxn];
int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &one[i]);
    for (int i = 2; i <= n; ++i) scanf("%d", &two[i]);
    dp[1] = one[1];
    for (int i = 2; i <= n; ++i) {
      dp[i] = min(dp[i-1] + one[i], dp[i-2] + two[i]);
    }
    //printf("%d\n", dp[n]);
    int h = 8, m = 0, s = dp[n];
    m = s / 60;
    s %= 60;
    h += m / 60;
    m %= 60;
    h %= 24;
    printf("%02d:%02d:%02d %s\n", h % 12, m, s, h < 12 ? "am" : "pm");
  }
  return 0;
}


// hdu 1114 多重背包
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 510, inf = 0x3fffffff;
int v[maxn], w[maxn];
int dp[10010];

int main() {
  int t, a, b, sum, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &a, &b);
    sum = b - a;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d", &v[i], &w[i]);
    }
    fill(dp, dp + sum + 1, inf);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = w[i]; j <= sum; ++j) {
        if (dp[j-w[i]] != inf) {
          dp[j] = min(dp[j], dp[j-w[i]] + v[i]);
        }
        //printf("%d\n", dp[j]);
      }
    }
    //        for (int i = 1; i <= n; ++i) {
    //            for (int j = 0; j <= sum; ++j) {
    //                printf("%d ", dp[i][j]);
    //            }
    //            printf("\n===========================\n");
    //        }
    if (dp[sum] == inf) printf("This is impossible.\n");
    else printf("The minimum amount of money in the piggy-bank is %d.\n", dp[sum]);
  }
  return 0;
}


// poj 2533
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1100;
int arr[maxn], b[maxn];

int main() {
  int n;
  while (~scanf("%d", &n)) {
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &arr[i]);
    }
    int Max = 1;
    for (int i = 1; i <= n; ++i) {
      b[i] = 1;
      for (int j = 1; j < i; ++j) {
        if (arr[i] > arr[j] && b[i] < b[j] + 1) {
          b[i] = b[j] + 1;
        }
      }
      Max = max(Max, b[i]);
    }
    printf("%d\n", Max);
  }

  return 0;
}


// hdu 1159
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e4;
char s1[maxn], s2[maxn];
int arr[maxn][maxn];

int main() {
  while (~scanf("%s%s", s1 + 1, s2 + 1)) {
    int len1 = (int)strlen(s1 + 1), len2 = (int)strlen(s2 + 1);;
    for (int i = 1; i <= len1; ++i) {
      for (int j = 1; j <= len2; ++j) {
        if (s1[i] == s2[j]) {
          arr[i][j] = arr[i - 1][j - 1] + 1;
        } else {
          arr[i][j] = max(arr[i][j - 1], arr[i - 1][j]);
        }
      }
    }
    printf("%d\n", arr[len1][len2]);
  }
  return 0;
}


// hdu 1069
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 110;
int a, b, c, height[maxn];
struct node {
  int a, b, h;
} arr[maxn];

bool cmp(node a, node b) {
  if (a.a == b.a && a.b == b.b) return a.h > b.h;
  if (a.a == b.a) return a.b > b.b;
  return a.a > b.a;
}

int main() {
  int n, ca = 1;
  while (~scanf("%d", &n) && n) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d", &a, &b, &c);
      arr[++cnt] = {max(a, b), min(a, b), c};
      arr[++cnt] = {max(a, c), min(a, c), b};
      arr[++cnt] = {max(b, c), min(b, c), a};
    }
    sort(arr + 1, arr + cnt + 1, cmp);
    int Max = 0;
    for (int i = 1; i <= cnt; ++i) {
      height[i] = arr[i].h;
      for (int j = 1; j < i; ++j) {
        if (arr[i].a < arr[j].a && arr[i].b < arr[j].b) {
          if (height[j] + arr[i].h > height[i]) {
            height[i] = height[j] + arr[i].h;
          }
        }
      }
      Max = max(Max, height[i]);
    }
    printf("Case %d: maximum height = %d\n", ca++, Max);
  }
  return 0;
}


// hdu 1087
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 10;
LL arr[maxn], b[maxn];

LL max(LL a, LL b) {return a > b ? a : b;}

int main() {
  int n;
  while (~scanf("%d", &n) && n) {
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &arr[i]);
      b[i] = arr[i];
    }
    LL Max = b[1];
    for (int i = 2; i <= n; ++i) {
      for (int j = 1; j < i; ++j) {
        if (arr[i] > arr[j] && b[i] < b[j] + arr[i]) {
          b[i] = b[j] + arr[i];
        }
      }
      Max = max(Max, b[i]);
    }
    printf("%lld\n", Max);
  }
  return 0;
}


// hdu 1176
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110000;
int arr[maxn][12];

int main() {
  int n, x, y, Max;
  while (~scanf("%d", &n) && n) {
    memset(arr, 0, sizeof(arr));
    Max = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &x, &y);
      ++arr[y][x];
      Max = max(Max, y);
    }
    for (int i = Max - 1; i >= 0; --i) {
      for (int j = 0; j <= 10; ++j) {
        if (j < 5 - i || j > 5 + i) continue;

        if (j == 0) {
          arr[i][j] += max(arr[i+1][j], arr[i+1][j+1]);
        } else if (j == 10) {
          arr[i][j] += max(arr[i+1][j], arr[i+1][j-1]);
        } else {
          arr[i][j] += max(max(arr[i+1][j], arr[i+1][j-1]), arr[i+1][j+1]);
        }
      }
    }
    //        for (int i = 0; i <= Max; ++i) {
    //            printf("%d : ", i);
    //            for (int j = 0; j <= 10; ++j) {
    //                printf("%d ", arr[i][j]);
    //            }
    //            printf("\n");
    //        }
    printf("%d\n", arr[0][5]);
  }
  return 0;
}


// hdu 1257 求最长上升子序列
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10100;
int arr[maxn], b[maxn];

int main() {
  int n, Max;
  while (~scanf("%d", &n)) {
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &arr[i]);
    }
    Max = b[1] = 1;
    for (int i = 2; i <= n; ++i) {
      b[i] = 1;
      for (int j = 1; j < i; ++j) {
        if (arr[j] <= arr[i]) {
          if (b[i] < b[j] + 1) {
            b[i] = b[j] + 1;
            Max = max(Max, b[i]);
          }
        }
      }
    }
    printf("%d\n", Max);
  }
  return 0;
}


// hdu 1029
#include <cstdio>
using namespace std;

int main(int argc, const char * argv[]) {
  int n, num, cnt, x;
  while (~scanf("%d", &n)) {
    scanf("%d", &num);
    cnt = 1;
    for (int i = 1; i < n; ++i) {
      scanf("%d", &x);
      if (x == num) ++cnt;
      else --cnt;
      if (cnt == 0) {
        cnt = 1, num = x;
      }
    }
    printf("%d\n", num);
  }
  return 0;
}
*/
