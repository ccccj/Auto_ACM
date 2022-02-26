
/*
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 50;
int f[maxn], d[maxn], t[maxn];

int main() {
  int n, h;
  while (~scanf("%d", &n) && n) {
    scanf("%d", &h);
    h *= 60;
    for (int i = 0; i < n; ++i) scanf("%d", &f[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &d[i]);

  }
  return 0;
}



#include <cstdio>
using namespace std;
const int maxn = 100010;
int l[maxn], r[maxn], cnt;

int main() {
  int t, m;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &m);
    cnt = 0;
    while (~scanf("%d%d", &l[cnt], &r[cnt]) && !(l[cnt] == 0 && r[cnt] == 0)) {
      if (r[cnt] <= 0) continue;
      if (l[cnt] < 0) l[cnt] = 0;
      ++cnt;
    }



  }
  return 0;
}


#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2010;
struct Edge {
  int to, next;
} edge[maxn];
int v[maxn], head[maxn], nowv[maxn], vis[maxn], cnt, Max, maxi, ans;

void insert(int x, int y) {
  edge[++cnt].to = y, edge[cnt].next = head[x];
  head[x] = cnt;
}

void dfs(int rt, int now) {
  if (vis[rt]) return;
  nowv[rt] = now * v[rt];
  for (int i = head[rt]; i; i = edge[i].next) {
    dfs(edge[i].to, now + 1);
  }
}

void addans(int rt, int now) {

}

int main() {
  int n, root, x, y;
  while (~scanf("%d%d", &n, &root) && (n + root)) {
    memset(head, 0, sizeof head);
    memset(vis, 0, sizeof vis);

    cnt = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &v[i]);
    }
    for (int i = 0; i < n - 1; ++i) {
      scanf("%d%d", &x, &y);
      insert(x, y);
    }
    Max = 0, maxi = -1;
    ans = nowv[root] = v[root];
    for (int i = head[root]; i; i = edge[i].next) {
      dfs(edge[i].to, 2);
    }
    for (int i = 1; i <= n; ++i) {
      if (vis[i] == 0 && Max < nowv[i]) Max = nowv[i], maxi = i;
    }

  }
  return 0;
}


// POJ 3363
#include <cstdio>
using namespace std;
const int maxn = 110;
char str[maxn][maxn];
int arr[maxn][maxn];

int main() {
  int n, m, r, c;
  while (~scanf("%d%d%d%d", &n, &m, &r, &c) && (n + m + r + c)) {
    for (int i = 0; i < n; ++i) {
      scanf("%s", str[i]);
      for (int j = 0; j < m; ++j) {
        arr[i][j] = str[i][j] - '0';
      }
    }
    int ans = 0;
    for (int i = 0; i <= n - r; ++i) {
      for (int j = 0; j <= m - c; ++j) {
        if (arr[i][j] == 1) {
          ++ans;
          for (int a = i; a < i + r; ++a) {
            for (int b = j; b < j + c; ++b) {
              arr[a][b] ^= 1;

            }
          }
        }
      }
    }
    bool flag = 1;
    for (int i = n - r + 1; i < n && flag; ++i) {
      for (int j = 0; j < m && flag; ++j) {
        if (arr[i][j]) flag = 0;
      }
    }
    for (int i = 0; i < n && flag; ++i) {
      for (int j = m - c + 1; j < m && flag; ++j) {
        if (arr[i][j]) flag = 0;
      }
    }
    if (!flag) printf("-1\n");
    else printf("%d\n", ans);
  }
  return 0;
}


// UVA 10821
#include <cstdio>
using namespace std;
int pow[31] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
  2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,
  2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456
, 536870912, 1073741824};

void recursive(int l, int r, int h) {
  int now = r - pow[h - 1] + 1;
  if (now < l) now = l;

  printf(" %d", now);
  if (now - 1 >= l) recursive(l, now - 1, h - 1);
  if (r >= now + 1) recursive(now + 1, r, h - 1);
}

int main() {
  int n, h, ca = 1;
  while (~scanf("%d%d", &n, &h) && (n + h)) {
    printf("Case %d:", ca++);
    if (pow[h] - 1 < n || n < h) {printf(" Impossible.\n"); continue;}
    recursive(1, n, h);
    printf("\n");
  }
  return 0;
}


// UVA 591
#include <cstdio>
using namespace std;
const int maxn = 100;
int arr[maxn];

int main() {
  int n, ca = 1;
  while (~scanf("%d", &n) && n) {
    int sum = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &arr[i]);
      sum += arr[i];
    }
    sum /= n;
    for (int i = 0; i < n; ++i) {
      if (arr[i] > sum) ans += (arr[i] - sum);
    }
    printf("Set #%d\nThe minimum number of moves is %d.\n\n", ca++, ans);

  }
  return 0;
}


// URAL 1025
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 110;
int arr[maxn];

int main() {
  int n;
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", &arr[i]);
    }
    sort(arr, arr + n);
    long long int ans = 0;
    for (int i = 0; i <= (n - 1) / 2; ++i) {
      ans += (arr[i] + 1) / 2;
    }
    printf("%lld\n", ans);

  }
  return 0;
}


// URAL 1161
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;
const int maxn = 1010;

double com(double a, double b) {
  return 2 * sqrt(a * b);
}

int main() {
  int n;
  while (~scanf("%d", &n)) {
    priority_queue<double> q;
    double x;
    for (int i = 0; i < n; ++i) {
      scanf("%lf", &x);
      q.push(x);
    }
    double ans = q.top();
    while (!q.empty()) {
      double a = q.top(), b;
      q.pop();
      if (q.empty()) {ans = a; break;}
      b = q.top();
      q.pop();
      ans = com(a, b);
      if (q.empty()) break;
      q.push(ans);
    }
    printf("%.2f\n", ans);

  }
  return 0;
}


// UVA 714
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1010;
int arr[maxn], n, k;

bool judge(LL m) {
  LL nowsum = 0;
  int t = 1;
  for (int i = 0; i < n; ++i) {
    if (arr[i] > m) return 0;

    if (nowsum + arr[i] <= m) {
      nowsum += arr[i];
    } else {
      ++t;
      nowsum = arr[i];
    }
  }
  return t <= k;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    LL sum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &arr[i]);
      sum += arr[i];
    }
    LL l = 0, r = sum, ans = sum;
    while (l < r) {
      LL m = (l + r) / 2;
      if (judge(m)) {
        ans = r;
        r = m;
      } else {
        l = m + 1;
      }
    }
    //printf("%lld\n", r);
    sum = 0;
    vector<int> v[k + 1];
    int tmp = k;
    for (int i = n - 1; i >= 0; --i) {
      if (sum + arr[i] <= r && tmp <= i + 1) {
        v[tmp].push_back(arr[i]);
        sum += arr[i];
      } else {
        --tmp;
        v[tmp].push_back(arr[i]);
        sum = arr[i];
      }
    }

    for (int i = 1; i <= k; ++i) {
      if (i > 1) printf("/ ");
      int len = v[i].size();
      for (int j = len - 1; j >= 0; --j) {
        if (i == k && j == 0) printf("%d", v[i][j]);
        else printf("%d ", v[i][j]);
      }
    }
    printf("\n");
  }
  return 0;
}

// UVA 2519
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const double eps = 1e-8;
struct Point {
  int x, y;
} arr[maxn];

int vis[maxn];

bool cmp(Point a, Point b) {
  if (a.x == b.x) return a.y > b.y;
  return a.x < b.x;
}

double dis(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  int n, d, ca = 1;
  while (~scanf("%d%d", &n, &d) && (n + d)) {
    memset(vis, 0, sizeof vis);

    bool flag = 1;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &arr[i].x, &arr[i].y);
      if (abs(arr[i].y) > d) flag = 0;
    }
    if (flag == 0) {
      printf("Case %d: -1\n", ca++);
    } else {
      sort(arr, arr + n, cmp);
      vis[0] = 1;
      double now = sqrt((double)d * d - arr[0].y * arr[0].y) + arr[0].x;
      //printf("now : %f arr[0].x : %d\n", now, arr[0].x);
      for (int i = 1; i < n; ++i) {
        //printf("dis %f\n", dis(now, 0, arr[i].x, arr[i].y));

        if (dis(now, 0, arr[i].x, arr[i].y) - d > eps) {
          vis[i] = 1;
          now = sqrt((double)d * d - arr[i].y * arr[i].y) + arr[i].x;
          for (int j = i - 1; j >= 0; --j) {
            if (vis[j] && dis(now, 0, arr[j].x, arr[j].y) < d - eps) {
              vis[j] = 0;
            }
          }
          //printf("now : %f\n", now);

        }
      }
      int ans = 0;
      for (int i = 0; i < n; ++i) {
        if (vis[i]) {
          ++ans;
          //printf("i: %d\n", i);
        }
      }
      printf("Case %d: %d\n", ca++, ans);
    }
  }
  return 0;
}


// UVA 2322
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5010, inf = 0x3fffffff;
struct node {
  int l, r;
} arr[maxn];

int b[maxn];

bool cmp(node a, node b) {
  if (a.l == b.l) return a.r < b.r;
  return a.l < b.l;
}

int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &arr[i].l, &arr[i].r);
    }
    sort(arr, arr + n, cmp);
    int last = arr[0].r, ans = 1;
    b[0] = 1;
    for (int i = 1; i < n; ++i) {
      b[i] = 1;
      for (int j = 0; j < i; ++j) {
        if (arr[i].r < arr[j].r && 1 + b[j] > b[i]) b[i] = 1 + b[j];
      }
      ans = max(ans, b[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}


// UVA 10954
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int main() {

  int n, x, y;
  while (~scanf("%d", &n) && n) {
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &x);
      q.push(x);
    }
    long long int sum = 0;
    while (!q.empty()) {
      x = q.top();
      q.pop();
      if (q.empty()) break;
      y = q.top();
      q.pop();
      sum += x + y;
      if (q.empty()) break;
      q.push(x + y);
    }
    printf("%lld\n", sum);

  }
  return 0;
}


// UVA 10026
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const double eps = 1e-8;
struct node {
  int t, s, id;
  double k;
} arr[maxn];

bool cmp(node a, node b) {
  if (fabs(a.k - b.k) < eps) return a.id < b.id;
  return a.k > b.k;
}

int main() {
  int t, n, ca = 1;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      arr[i].id = i;
      scanf("%d%d", &arr[i].t, &arr[i].s);
      arr[i].k = (double)arr[i].s / arr[i].t;
    }
    if (ca++ > 1) printf("\n");

    sort(arr + 1, arr + n + 1, cmp);
    printf("%d", arr[1].id);

    for (int i = 2; i <= n; ++i) {
      printf(" %d", arr[i].id);
    }
    printf("\n");
  }
  return 0;
}


// POJ 2287
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int tianji[maxn], qiwang[maxn];

bool cmp(int a, int b) {return a > b;}

int main() {
  int n;
  while (~scanf("%d", &n) && n) {
    for (int i = 0; i < n; ++i) scanf("%d", &tianji[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &qiwang[i]);
    sort(tianji, tianji + n, cmp);
    sort(qiwang, qiwang + n, cmp);
    int ans = 0, tl = 0, tr = n - 1;
    for (int i = 0; i < n; ++i) {
      if (tianji[tl] > qiwang[i]) {
        ++ans, ++tl;
      } else if (tianji[tl] < qiwang[i]) {
        --ans, --tr;
      } else {
        while (i < n && tl <= tr) {
          while (tianji[tr] > qiwang[n - 1] && i < n && tl <= tr) {
            --n, --tr, ++ans;
          }
          if (tianji[tr] < qiwang[n - 1]) {
            --ans, --tr;
            break;
          } else if (tianji[tr] == qiwang[n - 1]) {
            if (tianji[tr] == qiwang[i]) {
              --tr;
            } else {
              --ans, --tr;
            }

            break;
          }
        }
      }
    }
    printf("%d\n", ans * 200);

  }
  return 0;
}


// ZOJ 1375
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;
int t, n, k, sum[maxn], vis[maxn];
struct node {
  int x1, x2;
} arr[maxn];

bool cmp(node a, node b) {
  if (a.x2 == b.x2) return a.x1 < b.x1;
  return a.x2 > b.x2;
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    memset(sum, 0, sizeof sum);
    memset(vis, 0, sizeof vis);

    for (int i = 0; i < n; ++i) {
      scanf("%d%*d%d%*d", &arr[i].x1, &arr[i].x2);
      if (arr[i].x1 > arr[i].x2) swap(arr[i].x1, arr[i].x2);
      for (int j = arr[i].x1; j <= arr[i].x2; ++j) {
        ++sum[j];
      }
    }
    int ans = 0;
    sort(arr, arr + n, cmp);
    for (int i = 0; i < maxn; ++i) {
      while (sum[i] > k) {
        for (int j = 0; j < n; ++j) {
          if (vis[j]) continue;
          if (arr[j].x1 <= i && i <= arr[j].x2) {
            vis[j] = 1;
            for (int d = i; d <= arr[j].x2; ++d) {
              --sum[d];
            }
            ++ans;
            break;
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
*/
